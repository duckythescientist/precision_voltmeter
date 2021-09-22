
//void interrupt_handler() {
//  interrupt_happened = true;
//}
//
//Double low_noise_chunk() {
//  const int readings_count = 100;
//  uint32_t readings[readings_count];
//  digitalWrite(LED4, HIGH);
//  cli();
//  set_sleep_mode(SLEEP_MODE_ADC);
//  //max7219.MAX7219_ShutdownStart();
//  attachPCINT(digitalPinToPCINT(ADC_SDO), interrupt_handler, FALLING);
//  disablePCINT(digitalPinToPCINT(ADC_SDO));
//  sei();
//  ltc2400_read();  // Throw out current reading
//  digitalWrite(ADC_nCS, LOW);
//  for (int i=0; i<readings_count; i++) {
//    enablePCINT(digitalPinToPCINT(ADC_SDO));
//    sleep_mode();
//    disablePCINT(digitalPinToPCINT(ADC_SDO));
//    uint32_t reading = ltc2400_read();
//    digitalWrite(ADC_nCS, LOW);
//    readings[i] = reading;
//  }
//  //max7219.MAX7219_ShutdownStop();
//
//  Double val = 0.0;
//  stats.clear();
//  for (int i=0; i<readings_count; i++) {
//    int32_t reading = ltc2400_convert_raw(readings[i]);
//    // val += reading;
//    stats.add((float)reading);
//  }
//  val /= Double(readings_count);
//  return val;
//}



//void loop() {
//  digitalWrite(LED1, HIGH);
//  range_mode = RANGE_x1;
//  relay_mode = RANGE_x1;
//  set_relays(relay_mode);
//  Double value = low_noise_chunk();
//  value = ltc2400_adjust(value, relay_mode);
//  float f_value = value;
//  digitalWrite(LED1, LOW);
//  // Serial.begin(115200);
//  display_value(Double(stats.average()), RANGE_AUTO);
//  delay(1000);
////  while (!Serial);
//  Serial.println("Stats:");
//  Serial.print("\tCount : ");
//  printnum(stats.count());
//  Serial.print("\tMin   : ");
//  printnum(stats.minimum());
//  Serial.print("\tMax   : ");
//  printnum(stats.maximum());
//  Serial.print("\tMean  : ");
//  printnum(stats.average());
//  Serial.print("\tStdDev: ");
//  printnum(stats.pop_stdev());
//  delay(1000);
//}

//void loop() {
//  Serial.println("Trying power things");
//  delay(1000);
//  if (digitalRead(BUTTON_PIN)) {
//    return;
//  }
//  power_all_disable();
//  digitalWrite(LED1, HIGH);
//  _delay_ms(2000);
//  Serial.println("Disabled");
//  _delay_ms(2000);
//  cli();
//  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//  attachPCINT(digitalPinToPCINT(BUTTON_PIN), interrupt_handler, FALLING);
//  disablePCINT(digitalPinToPCINT(BUTTON_PIN));
//  sei();
//  enablePCINT(digitalPinToPCINT(BUTTON_PIN));
//  sleep_mode();
//  disablePCINT(digitalPinToPCINT(BUTTON_PIN));
//  digitalWrite(LED1, LOW);
//
//  power_all_enable();
//  _delay_ms(1000);
//  Serial.println("Wew, power");
//  delay(5000);
//}
