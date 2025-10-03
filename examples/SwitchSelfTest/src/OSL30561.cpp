
#include "../config.h"

#ifdef USE_NSEG_LED

#include "OSL30561.h"


OSL30561::OSL30561(bool type, uint8_t pin_a, uint8_t pin_b, uint8_t pin_c, uint8_t pin_d, uint8_t pin_e, uint8_t pin_f, uint8_t pin_g, uint8_t pin_dp, uint8_t num, uint8_t * ptr):
  _pin_mode(type),
  _pin_a(pin_a),
  _pin_b(pin_b),
  _pin_c(pin_c),
  _pin_d(pin_d),
  _pin_e(pin_e),
  _pin_f(pin_f),
  _pin_g(pin_g),
  _pin_dp(pin_dp),
  _num_digits(num),
  _pin_list(ptr)
{}



void OSL30561::begin(void) {
  _char_pin[0] = _pin_a;
  _char_pin[1] = _pin_b;
  _char_pin[2] = _pin_c;
  _char_pin[3] = _pin_d;
  _char_pin[4] = _pin_e;
  _char_pin[5] = _pin_f;
  _char_pin[6] = _pin_g;
  for (int i=0; i< _OSL30561_CHAR_PINS; i++) {
    pinMode(_char_pin[i], OUTPUT);
  }
  for (int i=0; i<_num_digits; i++ ) {
    pinMode(_pin_list[i], OUTPUT);
    _digit_pin[i] = _pin_list[i];
  }
  pinMode(_pin_dp, OUTPUT);
}

uint8_t OSL30561::displayOne(uint8_t n, bool point, char dispChar) {
  if (n>_num_digits-1) return _OSL30561_FUNCTION_FAIL;
  uint8_t pinState = encode(dispChar);
  if (pinState == _OSL30561_FUNCTION_FAIL) return _OSL30561_FUNCTION_FAIL;
  if (pinState != 0 ) {
    for (int i= _OSL30561_CHAR_PINS -1; i>=0; i--) {
      if ((0b1 & pinState) > 0) {
        if (_pin_mode == OSL30561_TYPE_CATHODE_COMMON) {
          digitalWrite(_char_pin[i],HIGH);
        } else {
          digitalWrite(_char_pin[i],LOW);
        }
      } else {
        if (_pin_mode == OSL30561_TYPE_CATHODE_COMMON) {
          digitalWrite(_char_pin[i],LOW);
        } else {
          digitalWrite(_char_pin[i],HIGH);
        }
      }
      pinState = pinState >> 1;
    }
  }
  if (point) {
    pointOn();
  } else {
    pointOff();
  }
  return digitOn(n);
}

void OSL30561::pointOn(void) {
  if (_pin_mode == OSL30561_TYPE_CATHODE_COMMON) {
    digitalWrite(_pin_dp,HIGH);
  } else {
    digitalWrite(_pin_dp,LOW);
  }
}

void OSL30561::pointOff(void) {
  if (_pin_mode == OSL30561_TYPE_CATHODE_COMMON) {
    digitalWrite(_pin_dp,LOW);
  } else {
    digitalWrite(_pin_dp,HIGH);
  }
}

uint8_t OSL30561::digitOn(uint8_t n) {
  if (n>_num_digits-1) return _OSL30561_FUNCTION_FAIL;
  if (_pin_mode == OSL30561_TYPE_CATHODE_COMMON) {
    digitalWrite(_digit_pin[n],LOW);
  } else {
    digitalWrite(_digit_pin[n],HIGH);
  }
  return _OSL30561_FUNCTION_SUCCESS;
}

uint8_t OSL30561::digitOff(uint8_t n) {
  if (n>_num_digits-1) return _OSL30561_FUNCTION_FAIL;
  if (_pin_mode == OSL30561_TYPE_CATHODE_COMMON) {
    digitalWrite(_digit_pin[n],HIGH);
  } else {
    digitalWrite(_digit_pin[n],LOW);
  }
  return _OSL30561_FUNCTION_SUCCESS;
}

//uint8_t OSL30561::display(uint64_t points, char dispData[]) {
//uint8_t OSL30561::display(uint32_t points, const char dispData[]) {
uint8_t OSL30561::display(uint64_t points, const char dispData[]) {
  for (int i=0; i<_num_digits; i++ ) {
    if ((0b1 & points) > 0) {
      if (_OSL30561_FUNCTION_FAIL == displayOne(i,true,dispData[i])) return _OSL30561_FUNCTION_FAIL;
    } else {
      if (_OSL30561_FUNCTION_FAIL == displayOne(i,false,dispData[i])) return _OSL30561_FUNCTION_FAIL;
    }
    if (_num_digits>1) {
      delayMicroseconds(_OSL30561_BIT_DELAY);
      if (_OSL30561_FUNCTION_FAIL == digitOff(i)) return _OSL30561_FUNCTION_FAIL;
    }
    points = points >> 1;
  }
  delayMicroseconds(_OSL30561_BIT_DELAY);
  return _OSL30561_FUNCTION_SUCCESS;
}

uint8_t OSL30561::clear(void) {
  for (int i=0; i<_num_digits; i++) {
    digitOff(i);
  }
  for (int i=0; i<_OSL30561_CHAR_PINS; i++) {
    if (_pin_mode == OSL30561_TYPE_CATHODE_COMMON) {
      digitalWrite(_char_pin[i],LOW);
    } else {
      digitalWrite(_char_pin[i],HIGH);
    }
  }
  pointOff();
  return _OSL30561_FUNCTION_SUCCESS;
};

/* convert charactor to led bitmap
 - :             G : 0000001
 0 : A,B,C,D,E,F   : 1111110
 1 :   B,C         : 0110000
 2 : A,B,  D,E,  G : 1101101
 3 : A,B,C,D,    G : 1111001
 4 :   B,C,    F,G : 0110011
 5 : A,  C,D,  F,G : 1011011
 6 : A,  C,D,E,F,G : 1011111
 7 : A,B,C,    F   : 1110010
 8 : A,B,C,D,E,F,G : 1111111
 9 : A,B,C,D,  F,G : 1111011
 A : A,B,C,  E,F,G : 1110111
 b :     C,D,E,F,G : 0011111
 C : A,    D,E,F   : 1001110
 d :   B,C,D,E,  G : 0111101
 E : A,    D,E,F,G : 1001111
 F : A,      E,F,G : 1000111
 */



uint8_t OSL30561::encode(char charactor){
  uint8_t charMap[17] = { 0b0000001, 0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011, 0b1011011, 0b1011111, 0b1110010, 0b1111111, 0b1111011, 0b1110111, 0b0011111, 0b1001110, 0b0111101, 0b1001111, 0b1000111};
  if (charactor == 0 ) return 0;
  switch(charactor) {
    case '-' : return charMap[0];
    case '0' : return charMap[1];
    case '1' : return charMap[2];
    case '2' : return charMap[3];
    case '3' : return charMap[4];
    case '4' : return charMap[5];
    case '5' : return charMap[6];
    case '6' : return charMap[7];
    case '7' : return charMap[8];
    case '8' : return charMap[9];
    case '9' : return charMap[10];
    case 'a' : return charMap[11];
    case 'A' : return charMap[11];
    case 'b' : return charMap[12];
    case 'B' : return charMap[12];
    case 'c' : return charMap[13];
    case 'C' : return charMap[13];
    case 'd' : return charMap[14];
    case 'D' : return charMap[14];
    case 'e' : return charMap[15];
    case 'E' : return charMap[15];
    case 'f' : return charMap[16];
    case 'F' : return charMap[16];
  }
  return 0;
}

#endif /* USE_NSEG_LED */
