
void save_calibration() {
  EEPROM.put(CAL_EEPROM_ADDRESS, current_calibration);  // Doesn't rewrite if the value didn't change
  Serial.println(F("Saved cal"));
}

int load_calibration() {
  Calibration saved_calibration;
  EEPROM.get(CAL_EEPROM_ADDRESS, saved_calibration);
  if (saved_calibration.version != CAL_VERSION) {
    Serial.println(F("BAD CAL DATA"));
    Calibration clean_calibration;  // Rely on default constructor, hopefully
    current_calibration = clean_calibration;
    // save_calibration();
    return -1;
  }
  else {
    Serial.print(F("Loaded cal ver: "));
    Serial.println(saved_calibration.version, HEX);
    current_calibration = saved_calibration;
    return 0;
  }
}



void print_cal() {
  if (current_calibration.calibrated) {
    Serial.print(F("Calibrated: YES: "));
  }
  else {
    Serial.print(F("Calibrated: NO: "));
  }
  Serial.println(current_calibration.calibrated, BIN);
  char buf[16];
  for (int i=0; i<4; i++) {
    CalibrationPoint cal = current_calibration.x[i];
    Serial.print(F("Cal slot"));
    Serial.print(i, DEC);
    Serial.println(":");

    Serial.print(F("\tzero : "));
    snprintf(buf, 16, "0x%08lX", cal.zero_offset);
    Serial.println(buf);
    Serial.print(F("\tscale: "));
    snprintf(buf, 16, "0x%08lX", cal.scale);
    Serial.println(buf);
    Serial.print(F("\tref  : 0x"));

    // WHAT THE FUCK IS WRONG WITH THIS SNPRINTF????
    // WHY DO I HAVE TO BREAK IT INTO TWO CALLS?????
    // THIS DOESN'T WORK:
    // snprintf(buf, 16, "%08lX%08lX", ((uint64_t)cal.reference_voltage >> 32) & 0xFFFFFFFFUL, ((uint64_t)cal.reference_voltage) & 0xFFFFFFFFUL);
    // I HAVE TO DO THIS:
    snprintf(buf, 16, "%08lX", (uint32_t)((uint64_t)cal.reference_voltage >> 32) & 0xFFFFFFFFUL);
    snprintf(&buf[8], 8, "%08lX", (uint32_t)((uint64_t)cal.reference_voltage) & 0xFFFFFFFFUL);

    Serial.println(buf);
    Serial.print(F("\t     : "));
    Serial.println(fp64_ds((float64_t)cal.reference_voltage), 8);
  }
}


void zero_cal() {
  Serial.println(F("Preparing to cal"));
  while (Serial.available() > 0) {
    Serial.read();  // Flush serial input
  }
  Serial.println(F("Short inputs and press B1 or send 'y'"));
  max7219.Clear();
  max7219.DisplayText("Short", 0);
  while (read_buttons() != 1 && !(Serial.available() > 0 && Serial.read() == 'y'));  // Wait for input
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  Serial.println(F("Calibrating..."));
  max7219.Clear();
  max7219.DisplayText("CAL . . .", 0);
  delay(5000);
  for (int i=0; i<4; i++) {
    zero_cal_single(i);
  }
  Serial.println(F("Cal finished"));
  max7219.Clear();
  max7219.DisplayText("CAL Fin", 0);
  current_calibration.calibrated |= 1<<0;
  save_calibration();
  delay(3000);
  digitalWrite(LED2, LOW);
  averaging_mode = AVERAGE_NONE;
  update_range_mode(RANGE_AUTO);
}


#define ZERO_CAL_COUNT (256)
void zero_cal_single(int ind) {
  enum Range mode = static_cast<Range>(ind + 1);
  set_relays(mode);
  Serial.print(F("Cal x"));
  Serial.println(quick_pow10(ind), DEC);
  max7219.Clear();
  max7219.DisplayText("CAL", 0);
  max7219.DisplayChar(0, '0' + ind, 0);
  int32_t val;
  int64_t acc = 0LL;
  // Discard first few
  for (int i=0; i<5; i++) {
    ltc2400_read(); 
  }
  for (int i=0; i<ZERO_CAL_COUNT; i++) {
    val = ltc2400_convert_raw(ltc2400_read());
    acc += (int64_t)val;
  }
  acc /= (int64_t)ZERO_CAL_COUNT;
  Serial.print(F("Offset: "));
  Serial.println((int32_t)acc, DEC);
  current_calibration.x[ind].zero_offset = acc;
}


#define VALUE_CAL_COUNT (256)
void cal_at_value(enum Range mode, float64_t real_value) {
  int index = (int)mode - 1;
  Serial.println(F("Preparing to cal"));
  while (Serial.available() > 0) {
    Serial.read();  // Flush serial input
  }
  Serial.print(F("Apply "));
  Serial.print(fp64_ds(real_value));
  Serial.println(F(" V and press B1 or send 'y'"));
  max7219.Clear();
  max7219.DisplayText("rEAdY", 0);
  while (read_buttons() != 1 && !(Serial.available() > 0 && Serial.read() == 'y'));  // Wait for input
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  Serial.println(F("Calibrating..."));
  max7219.Clear();
  max7219.DisplayText("CAL . . .", 0);
  set_relays(mode);
  delay(5000);
  int32_t val;
  int64_t acc = 0LL;
  // Discard first few
  for (int i=0; i<5; i++) {
    ltc2400_read();
  }
  for (int i=0; i<VALUE_CAL_COUNT; i++) {
    val = ltc2400_convert_raw(ltc2400_read());
    acc += (int64_t)val;
  }
  acc /= (int64_t)VALUE_CAL_COUNT;
  Serial.println(F("Cal finished"));
  max7219.Clear();
  max7219.DisplayText("CAL Fin", 0);

  uint32_t scale = acc - current_calibration.x[index].zero_offset;
  current_calibration.x[index].scale = scale;
  current_calibration.x[index].reference_voltage = real_value;
  current_calibration.calibrated |= 1<<(int)mode;
  save_calibration();
  delay(3000);
  digitalWrite(LED2, LOW);
  averaging_mode = AVERAGE_NONE;
  update_range_mode(RANGE_AUTO);
}
