
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
    save_calibration();
    return -1;
  }
  else {
    Serial.print(F("Loaded cal ver: "));
    Serial.println(saved_calibration.version, HEX);
    current_calibration = saved_calibration;
    return 0;
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
  save_calibration();
  delay(3000);
}


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
  for (int i=0; i<64; i++) {
    val = ltc2400_convert_raw(ltc2400_read());
    acc += (int64_t)val;
  }
  acc /= 64LL;
  Serial.print(F("Offset: "));
  Serial.println((int32_t)acc, DEC);
  current_calibration.x[ind].zero_offset = acc;
}
