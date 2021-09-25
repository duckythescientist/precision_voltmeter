#ifndef cal_h
#define cal_h

#define CAL_VERSION_MAJOR 0
#define CAL_VERSION_MINOR 5

#define CAL_EEPROM_ADDRESS 0


#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <EEPROM.h>
#include <fp64lib.h>
#include <stdint.h>

#define CAL_VERSION ((0xcafeUL << 16UL) | (((uint32_t) CAL_VERSION_MAJOR) << 8UL) | ((uint32_t) CAL_VERSION_MINOR))

typedef struct {
  int32_t zero_offset;
  int32_t scale;
  float64_t reference_voltage;
} CalibrationPoint;

typedef struct {
  uint32_t version = CAL_VERSION;
  uint8_t calibrated = 0;
  CalibrationPoint x[4] = { {0L, 1L<<28, (float64_t)0x4010624DD2F1A9FCULL},
                            {0L, 1L<<28, (float64_t)0x40447AE147AE147BULL},
                            {0L, 1L<<28, (float64_t)0x407999999999999AULL},
                            {0L, 1L<<28, (float64_t)0x40B0000000000000ULL}
  };
} Calibration;

Calibration current_calibration;


#endif // cal_h
