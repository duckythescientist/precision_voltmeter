
/*
   Architecture:
   ADC 24-bit over SPI: LTC2400
   Voltage reference 4.096V: MAX6126 or ADR4540
   Divider, switched by relays: Caddock 1776-C68
       x1, x10, x100, x1000

   UI:
   Display 8-digit 7-segment: MAX7219
   Buttons:
       AUTO: fixed vs auto ranging
       AVG: change averaging settings
       HOLD: min/max hold



*/

#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <fp64lib.h>
#include <PinChangeInterrupt.h> // https://github.com/NicoHood/PinChangeInterrupt
#include <Statistic.h> // https://github.com/RobTillaart/Statistic

#include "double.h"
#include "max7219.h"
#include "freememory.h"
#include "cal.h"


#define ADC_nCS 16
#define ADC_SDO 14
#define ADC_SCK 15

// Arduino needs declarations with default arguments in the main .ino file
uint32_t ltc2400_read(uint8_t ncs = ADC_nCS, uint8_t sdo = ADC_SDO, uint8_t sck = ADC_SCK);


#define LED1 3
#define LED2 5
#define LED3 6
#define LED4 9
uint8_t led_pins[] = {LED1, LED2, LED3, LED4};

#define BUTTON_PIN A8

//#define MAX_CLK 18
//#define MAX_CS 19
//#define MAX_DIN 20
MAX7219 max7219;

enum Range : uint8_t {RANGE_AUTO = 0, RANGE_x1, RANGE_x10, RANGE_x100, RANGE_x1k, RANGE_NONE};
enum Range range_mode = RANGE_x1k;
enum Range relay_mode = RANGE_NONE;

//#define RELAY_x1   1
//#define RELAY_x10  0
//#define RELAY_x100 2
//#define RELAY_x1k  4


#define RELAY_x100 1
#define RELAY_x10  0
#define RELAY_x1   2
#define RELAY_x1k  4

#define ALPHA_2Hz (0.6262344812602125f)
#define ALPHA_0p2Hz (0.14350373836394034f)
#define ALPHA_0p05Hz (0.04020288254460277f)

enum AveragingMode : uint8_t {AVERAGE_NONE = 0, AVERAGE_FAST, AVERAGE_SLOW, AVERAGE_SUPER_SLOW, AVERAGING_MODES_COUNT} averaging_mode = AVERAGE_NONE;
Double averaged;

bool interrupt_happened = false;

Statistic stats;



void set_relays(enum Range mode) {
  digitalWrite(RELAY_x1, mode == RANGE_x1);
  digitalWrite(RELAY_x10, mode == RANGE_x10);
  digitalWrite(RELAY_x100, mode == RANGE_x100);
  digitalWrite(RELAY_x1k, mode == RANGE_x1k);
}


void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, LOW);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED3, LOW);
  pinMode(LED4, OUTPUT);
  digitalWrite(LED4, LOW);
  pinMode(BUTTON_PIN, INPUT);


  pinMode(ADC_nCS, OUTPUT);
  digitalWrite(ADC_nCS, HIGH);
  pinMode(ADC_SDO, INPUT);
  pinMode(ADC_SCK, OUTPUT);
  digitalWrite(ADC_SCK, LOW);

  pinMode(RELAY_x1, OUTPUT);
  pinMode(RELAY_x10, OUTPUT);
  pinMode(RELAY_x100, OUTPUT);
  pinMode(RELAY_x1k, OUTPUT);
  relay_mode = RANGE_x1k;
  set_relays(relay_mode);

  max7219.Begin();
  max7219.MAX7219_SetBrightness(0x5);  // 0x0 - 0xF
  max7219.Clear();
  max7219.DisplayText("hEllo", 0);
  delay(1000);
  Serial.println("hello");
  delay(1000);
  Serial.println("hello again");
  load_calibration();
  print_cal();
  if (!current_calibration.calibrated) {
    Serial.println(F("UNCALIBRATED"));
    max7219.Clear();
    max7219.DisplayText("UnCAL", 0);
    delay(3000);
  }

  //  // Putting the processor to sleep messes with updates
  //  // so wait here while button 1 is held.
  //  while (read_buttons() == 1) {
  //    delay(5000);
  //    Serial.println(F("Waiting for update"));
  //  }

}


void update_average(Double val) {
  switch (averaging_mode) {

    case AVERAGE_FAST:
      averaged += (val - averaged) * Double(ALPHA_2Hz);
      break;
    case AVERAGE_SLOW:
      averaged += (val - averaged) * Double(ALPHA_0p2Hz);
      break;
    case AVERAGE_SUPER_SLOW:
      averaged += (val - averaged) * Double(ALPHA_0p05Hz);
      break;
    case AVERAGE_NONE:
    default:
      averaged = val;
      break;
  }
}
//float get_iir_alpha(float f, float sampling_period=0.13333f) {
//  float foo = TWO_PI * sampling_period * f;
//  return foo / (1 + foo);
//}

//import math
//def get_iir_alpha(f, sampling_period=0.13333):
//    foo = 2 * math.pi * sampling_period * f
//    return foo / (1 + foo)




void update_range_mode(enum Range mode) {
  // Change hardware for new range_mode
  range_mode = mode;
  digitalWrite(LED1, LOW);
  digitalWrite(LED3, LOW);
  switch (range_mode) {
    case RANGE_x10:
      Serial.println(F("Range x10"));
      relay_mode = RANGE_x10;
      break;
    case RANGE_x100:
      Serial.println(F("Range x100"));
      relay_mode = RANGE_x100;
      break;
    case RANGE_x1k:
      Serial.println(F("Range x1k"));
      relay_mode = RANGE_x1k;
      break;
    case RANGE_x1:
    Serial.println(F("DANGER RANGE x1"));
        digitalWrite(LED3, HIGH);
        relay_mode = RANGE_x1;
        break;
    case RANGE_AUTO:  // FALLTHROUGH
    default:
      Serial.println(F("Range AUTO"));
      digitalWrite(LED1, HIGH);
      relay_mode = RANGE_x1k;
      break;
  }
  set_relays(relay_mode);
}

void handle_serial() {
  int cal_mode = 0;
  float64_t real_value = float64_ONE_POSSIBLE_NAN_REPRESENTATION;
  char buf[32];
  size_t len;
  int command = Serial.read();
  if (command >= 'A' && command <= 'Z') {
    command ^= 0x20;
  }
  switch (command) {
    case '?':
      Serial.println(F("Precision Voltmeter"));
      Serial.print(F("\tVersion: "));
      Serial.println(CAL_VERSION, HEX);
      Serial.println(F("\tDate: " __DATE__));
      break;
    case 'z':
      zero_cal();
      break;
    case 'p':
      print_cal();
      break;
    case 'c':
      cal_mode = Serial.read();
      if (cal_mode < '0' || cal_mode > '3') {
        Serial.print(F("Bad cal mode "));
        Serial.println(cal_mode);
        return;
      }
      cal_mode = cal_mode - '0';
      if (Serial.read() != ':') {
        Serial.println(F("Format error"));
        return;
      }
      len = Serial.readBytesUntil('\n', buf, sizeof(buf));
      if (!len) {
        Serial.println(F("Failed to read number"));
        return;
      }
      real_value = fp64_atof(buf);
      if (fp64_isfinite(real_value)) {
        cal_at_value(static_cast<Range>(cal_mode + 1), real_value);
      }
      else {
        Serial.println(F("Bad number"));
      }
      break;
    case ' ':
    case '\r':
    case '\n':
      break;
    default:
      Serial.print(F("Unk cmd:"));
      Serial.println(command, HEX);
      break;
  }
}

void loop() {
  static int last_button = 0;

  //  int mem = freeMemory();
  //  Serial.print("freemem:");
  //  Serial.println(mem);

  if (Serial.available() > 0) {
    handle_serial();
  }

  int button = read_buttons();
  if (button && button != last_button) {
    Serial.print("Button pressed: ");
    Serial.println(button);

    if (button == 1) {
      // Update range_mode
      switch (range_mode) {
        case RANGE_AUTO:
          range_mode = RANGE_x10;
          break;
        case RANGE_x10:
          range_mode = RANGE_x100;
          break;
        case RANGE_x100:
          range_mode = RANGE_x1k;
          break;
        case RANGE_x1k: // FALLTHROUGH
        default:
          range_mode = RANGE_AUTO;
          break;
      }
      update_range_mode(range_mode);
    }

    if (button == 2) {
      averaging_mode = static_cast<AveragingMode>((averaging_mode + 1) % AVERAGING_MODES_COUNT);
      switch (averaging_mode) {
        case AVERAGE_FAST:
          Serial.println(F("Avg fast"));
          analogWrite(LED2, 16);
          break;
        case AVERAGE_SLOW:
          Serial.println(F("Avg slow"));
           analogWrite(LED2, 64);
          break;
        case AVERAGE_SUPER_SLOW:
          Serial.println(F("Avg SUPER slow"));
          digitalWrite(LED2, HIGH);
          break;
        case AVERAGE_NONE:  // FALLTHROUGH
        default:
          Serial.println(F("Avg none"));
          digitalWrite(LED2, LOW);
          break;
      }
    }

    if (button == 3) {
      if (range_mode != RANGE_x1) {
        update_range_mode(RANGE_x1);
      }
      else {
        update_range_mode(RANGE_AUTO);
      }

    }

    if (button == 4) {
      // not currently handled
    }

    if (button == 5) {
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      delay(3000);
      button = read_buttons();
      if (button == 5) {
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        while (read_buttons());
        zero_cal();
      }
      else {
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);
      }
    }
  }
  last_button = button;

  uint32_t reading = ltc2400_read();
  int32_t raw = ltc2400_convert_raw(reading);
  float float_norm = ltc2400_adjust_float_norm(raw);
  Double voltage = ltc2400_adjust(raw, relay_mode);
  char buf[16] = {0};
  snprintf(buf, 32, "Raw: 0x%08lx ", raw);
  Serial.print(buf);
  Serial.println(float_norm, 7);
  update_average(voltage);
  display_value(averaged, range_mode);

  if (range_mode == RANGE_AUTO) {
    // Check if outside of range
    if (float_norm < -0.06 || float_norm > 1.1) {
      // Could step up by one level, but going straight to x1k works too.
      relay_mode = RANGE_x1k;
      set_relays(relay_mode);
      // Throw out the current conversion
      ltc2400_read();
    }
    // Should we increase sensitivity?
    else if (float_norm > -0.005 && float_norm < 0.09) {
      switch (relay_mode) {
        case RANGE_x1k:
          Serial.println(F("Inc x100"));
          relay_mode = RANGE_x100;
          set_relays(relay_mode);
          break;
        case RANGE_x100:
          Serial.println(F("Inc x10"));
          relay_mode = RANGE_x10;
          set_relays(relay_mode);
          break;
        case RANGE_x10:
          // Don't go to x1 sensitivity automatically
          break;
        default:
          // Only here if something went wrong in the code
          Serial.println(F("Fail. Range x1k"));
          relay_mode = RANGE_x1k;
          set_relays(relay_mode);
          break;
      }
    }
  }


  bool error = false;
  if (range_mode != RANGE_AUTO) {
    if (float_norm < -0.073) {
      max7219.DisplayText("-UndEr  ", 0);
      error = true;
    }
    if (float_norm > 1.12) {
      max7219.DisplayText("OVEr    ", 0);
      error = true;
    }
  }

  if (error) {
    set_relays(RANGE_NONE);
    while (read_buttons()) {
      ; // Wait for buttons to be idle
    }
    while (!read_buttons()) {
      ; // Wait for button press to continue after error
    }
    max7219.Clear();
    while (read_buttons()) {
      ; // Wait for buttons to be idle
    }
    set_relays(relay_mode);
  }

}
