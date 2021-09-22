
uint32_t ltc2400_read(uint8_t ncs, uint8_t sdo, uint8_t sck) {
  uint32_t data = 0;
  digitalWrite(sck, LOW);
  digitalWrite(ncs, LOW);
  while (digitalRead(sdo)); // Wait until conversion finished

  uint8_t tmp = 0;
  tmp = shiftIn(sdo, sck, MSBFIRST);
  data |= ((uint32_t)tmp) << 24L;
  tmp = shiftIn(sdo, sck, MSBFIRST);
  data |= ((uint32_t)tmp) << 16L;
  tmp = shiftIn(sdo, sck, MSBFIRST);
  data |= ((uint32_t)tmp) << 8L;
  tmp = shiftIn(sdo, sck, MSBFIRST);
  data |= ((uint32_t)tmp) << 0L;

  digitalWrite(sck, LOW);
  digitalWrite(ncs, HIGH);
  return data;
}

int32_t ltc2400_convert_raw(uint32_t data) {
  // I could do some C casting hackery.
  // Or I could make this more understandable.

  // Extract the sign bit
  byte positive = (data & (1UL << 29)) >> 29;

  // Extract the actual data bits
  data &= 0x1FFFFFFFUL;
  // Negative numbers are 29-bit 2's complement
  if (!positive) {
    data ^= 0x1FFFFFFFUL;
    data += 1UL;
  }
  int32_t value = data;
  if (!positive) {
    value = value * -1L;
  }
  return value;
}

//Double ltc2400_convert(uint32_t data) {
//  Double value = ltc2400_convert_raw(data);
//  // Normalize (such that 1.0 is full scale)
//  value = value / Double(0x0FFFFFFFUL);
//  return value;
//}

//Double ltc2400_adjust(Double norm, enum Range mode) {
//  int scale = quick_pow10(mode - 1);
//  // TODO: make fancy and multi-scaled
////  Double offset = 2.5E-5;
//  Double offset = 0;
//  Double vref = 4.096;
//  Double val = (norm - offset) * vref * Double(scale);
//  return val;
//}

Double ltc2400_adjust(int32_t raw, enum Range mode) {
  int index = mode - 1;
  if (index < 0) index = 0;
  if (index > 3) index = 3;

  CalibrationPoint cal_point = current_calibration.x[index];
  Double val = Double(raw - cal_point.zero_offset) * Double(cal_point.reference_voltage) / Double(cal_point.scale);
  return val;
}

float ltc2400_adjust_float_norm(int32_t raw) {
  return raw / float(0x0FFFFFFFUL);
}

long quick_pow10(long n)
{
  static long pow10[10] = {
    1L, 10L, 100L, 1000L, 10000L,
    100000L, 1000000L, 10000000L, 100000000L, 1000000000L
  };

  return pow10[n];
}
