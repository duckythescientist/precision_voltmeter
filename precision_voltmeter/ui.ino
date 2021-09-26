
//void number_fill(char * text, long value, int digits) {
//  for (int i=0; i<digits; i++) {
//    int exponent = digits - i - 1;
//    long divisor = quick_pow10(exponent);
//    long x = value / ;
//    if (x < 0 || x > 9) x = 10;
//    text[i] = "0123456789?"[x];
//    value %= divisor;
//  }
//}


void display_value(Double val, enum Range range) {
  //  Serial.print("Got val:");
  //  Serial.println(fp64_to_string(val, 17, 0));
  bool is_negative = fp64_signbit(val);
  val = fp64_abs(val);
  Double f_whole = fp64_trunc(val);
  Double f_remainder = val - f_whole;
  //  Serial.print("f_remainder:");
  //  Serial.println(fp64_to_string(f_remainder, 17, 0));
  int whole = fp64_to_int16(f_whole);

  int n_whole_digits = 1;
  if (range == RANGE_AUTO) {
    if (whole >= 1000) {
      n_whole_digits = 4;
    }
    else if (whole >= 100) {
      n_whole_digits = 3;
    }
    else if (whole >= 10) {
      n_whole_digits = 2;
    }
    else {
      n_whole_digits = 1;
    }
  }
  else {
    if (range == RANGE_x1k) {
      n_whole_digits = 4;
    }
    else if (range == RANGE_x100) {
      n_whole_digits = 3;
    }
    else if (range == RANGE_x10) {
      n_whole_digits = 2;
    }
    else {
      n_whole_digits = 1;
    }
  }
  int n_remaining_digits = 8 - 1 - n_whole_digits;
  // There has got to be a better way to do this.
  int32_t multiplier = quick_pow10(n_remaining_digits);
  Double f_rem_int = f_remainder * Double(multiplier);
  //  Serial.print("f_rem_int:");
  //  Serial.println(fp64_to_string(f_rem_int, 17, 0));
  int32_t rem_int = fp64_lrint(f_rem_int);
  // Limit rem_int at the extremes due to weird rounding
  // Otherwise something like round(4.9999, 3)
  // turns into 4 and 1000 instead of 4 and 999.
  if (rem_int < 0L) {
    rem_int = 0L;
  }
  if (rem_int >= multiplier) {
    rem_int = multiplier - 1;
  }

  //  Serial.print("whole:");
  //  Serial.println(whole);
  //  Serial.print("    rem:");
  //  Serial.println(rem_int);

  char text[12] = {0};
  text[0] = is_negative ? '-' : ' ';
  const static char * fmtstr_1 = "%1d.%06ld";
  const static char * fmtstr_2 = "%2d.%05ld";
  const static char * fmtstr_3 = "%3d.%04ld";
  const static char * fmtstr_4 = "%4d.%03ld";
  const char * const fmt_array[] = {
    fmtstr_1,
    fmtstr_2,
    fmtstr_3,
    fmtstr_4,
  };

  const char * const fmtstr = fmt_array[n_whole_digits - 1];

  snprintf(&text[1], 11, fmtstr, whole, rem_int);
  Serial.println(text);
  //  max7219.Clear();
  max7219.DisplayText(text, 0);
}


int read_buttons() {
  /* each switch connects the analog line to ground through a resistor
      10k pullup to Vcc
      Resistors: 1.8k, 4.7k, 10k, 22k
  */
  int val = analogRead(BUTTON_PIN);
  if (val < 137)
    return 5;  // Buttons 3 and 4 together
  else if (val < 242)
    return 4;
  else if (val < 420)
    return 3;
  else if (val < 608)
    return 2;
  else if (val < 864)
    return 1;
  else
    return 0;
}

void print_large_num(float val) {
  int32_t whole = (int32_t)val;
  float remainder = val - (float)whole;
  int32_t dec_remainder = remainder * 100.0;
  char buf[32];
  snprintf(buf, 32, "%8ld.%02ld\n", whole, dec_remainder);
  Serial.print(buf);
}
