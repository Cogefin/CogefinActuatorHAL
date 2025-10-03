#include "../config.h"

#ifdef USE_NSEG_LED

#include "OSL12306_16.h"


OSL12306_16::OSL12306_16(bool pin_mode, uint8_t * char_pin_list, uint8_t pin_dp, uint8_t num, uint8_t * digit_pin_list):
  _pin_mode(pin_mode),
  _pin_list(char_pin_list),
  _dp_pin(pin_dp),
  _num_digits(num),
  _digit_pin_list(digit_pin_list)
{}

void OSL12306_16::begin(void) {
  for (int i=0; i< _OSL12306_16_CHAR_PINS; i++) {
    _char_pin[i] = _pin_list[i];
    pinMode(_char_pin[i], OUTPUT);
  }
  for (int i=0; i<_num_digits; i++ ) {
    _digit_pin[i] = _digit_pin_list[i];
    pinMode(_digit_pin[i], OUTPUT);
  }
  pinMode(_dp_pin, OUTPUT);
}

uint8_t OSL12306_16::displayOne(uint8_t n, bool dp, char dispChar) {
  if (n>_num_digits-1) return _OSL12306_16_FUNCTION_FAIL;
  uint16_t pinState = encode(dispChar);
  if (pinState == _OSL12306_16_FUNCTION_FAIL) return _OSL12306_16_FUNCTION_FAIL;
  if (pinState != 0 ) {
    for (int i= _OSL12306_16_CHAR_PINS -1; i>=0; i--) {
      if ((0b1 & pinState) > 0) {
        if (_pin_mode == OSL12306_16_TYPE_CATHODE_COMMON) {
          digitalWrite(_char_pin[i],HIGH);
        } else {
          digitalWrite(_char_pin[i],LOW);
        }
      }
      pinState = pinState >> 1;
    }
  }
  if (dp) {
    pointOn();
  } else {
    pointOff();
  }
  return digitOn(n);
}

void OSL12306_16::pointOn(void) {
  if (_pin_mode == OSL12306_16_TYPE_CATHODE_COMMON) {
    digitalWrite(_dp_pin, HIGH);
  } else {
    digitalWrite(_dp_pin, LOW);
  }
}

void OSL12306_16::pointOff(void) {
  if (_pin_mode == OSL12306_16_TYPE_CATHODE_COMMON) {
    digitalWrite(_dp_pin, LOW);
  } else {
    digitalWrite(_dp_pin, HIGH);
  }
}

uint8_t OSL12306_16::digitOn(uint8_t n) {
  if (n>_num_digits-1) return _OSL12306_16_FUNCTION_FAIL;
  if (_pin_mode == OSL12306_16_TYPE_CATHODE_COMMON) {
    digitalWrite(_digit_pin[n], LOW);
  } else {
    digitalWrite(_digit_pin[n], HIGH);
  }
  return _OSL12306_16_FUNCTION_SUCCESS;
}

uint8_t OSL12306_16::digitOff(uint8_t n) {
  if (n>_num_digits-1) return _OSL12306_16_FUNCTION_FAIL;
  if (_pin_mode == OSL12306_16_TYPE_CATHODE_COMMON) {
    digitalWrite(_digit_pin[n], HIGH);
  } else {
    digitalWrite(_digit_pin[n], LOW);
  }
  return _OSL12306_16_FUNCTION_SUCCESS;
}

//uint8_t OSL12306_16::display(uint64_t points, char dispData[]) {
//uint8_t OSL12306_16::display(uint64_t points, const char dispData[]) {
uint8_t OSL12306_16::display(uint64_t points, const char dispData[]) {
  for (int i=0; i<_num_digits; i++ ) {
    if ((0b1 & points) > 0) {
      if (_OSL12306_16_FUNCTION_FAIL == displayOne(i,true,dispData[i])) return _OSL12306_16_FUNCTION_FAIL;
    } else {
      if (_OSL12306_16_FUNCTION_FAIL == displayOne(i,false,dispData[i])) return _OSL12306_16_FUNCTION_FAIL;
    }
    if (_num_digits>1) {
      delayMicroseconds(_OSL12306_16_BIT_DELAY);
      if (_OSL12306_16_FUNCTION_FAIL == digitOff(i)) return _OSL12306_16_FUNCTION_FAIL;
    }
    points = points >> 1;
  }
  delayMicroseconds(_OSL12306_16_BIT_DELAY);
  return _OSL12306_16_FUNCTION_SUCCESS;
}

uint8_t OSL12306_16::clear(void) {
  for (int i=0; i<_num_digits; i++) {
    digitOff(i);
  }
  for (int i=0; i<_OSL12306_16_CHAR_PINS; i++) {
    if (_pin_mode == OSL12306_16_TYPE_CATHODE_COMMON) {
      digitalWrite(_char_pin[i],LOW);
    } else {
      digitalWrite(_char_pin[i],HIGH);
    }
  }
  pointOff();
  return _OSL12306_16_FUNCTION_SUCCESS;
};

/* convert charactor to led bitmap

   : A1 A2 B  C  D1 D2 E  F  G1 G2 J  K  L  M  N  P
SP : 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 : 0000000000000000 : 0x0000
 - : 0  0  0  0  0  0  0  0  1  1  0  0  0  0  0  0 : 0000000011000000 : 0x00C0
 0 : 1  1  1  1  1  1  1  1  0  0  1  0  0  1  0  0 : 1111111100100100 : 0xFF24
 1 :                                  1        1    :            10010 : 0x0012
 2 : 1  1  1     1  1  1     1  1                   : 1110111011000000 : 0xEEC0
 3 : 1  1  1  1  1  1        1  1                   : 1111110011000000 : 0xFCC0
 4 :       1  1           1  1  1                   : 0011000111000000 : 0x31C0
 5 : 1  1     1  1  1     1  1  1                   : 1101110111000000 : 0xDDC0
 6 : 1  1     1  1  1  1  1  1  1                   : 1101111111000000 : 0xDFC0
 7 : 1  1  1  1           1                         : 1111000100000000 : 0xF100
 8 : 1  1  1  1  1  1  1  1  1  1                   : 1111111111000000 : 0xFFC0
 9 : 1  1  1  1  1  1     1  1  1                   : 1111110111000000 : 0xFDC0
 A : 1  1  1  1        1  1  1  1                   : 1111001111000000 : 0xF3C0
 b :          1  1  1  1  1  1  1                   : 0001111111000000 : 0x1FC0
 C : 1  1        1  1  1  1                         : 1100111100000000 : 0xCF00
 d :       1  1  1  1  1     1  1                   : 0011111011000000 : 0x3EC0
 E : 1  1        1  1  1  1  1  1                   : 1100111111000000 : 0xCFC0
 F : 1  1              1  1  1  1                   : 1100001111000000 : 0xC3C0
 G : 1  1     1  1  1  1  1     1                   : 1101111101000000 : 0xDF40
 H :       1  1        1  1  1  1                   : 0011001111000000 : 0x33C0
 I : 1  1        1  1                 1        1    : 1100110000010010 : 0xCC12
 J : 1  1        1                    1        1    : 1100100000010010 : 0xC812
 k :                                  1  1  1  1    : 0000000000011110 : 0x001E
 L :             1  1  1  1                         : 0000111100000000 : 0x0F00
 M :       1  1        1  1        1     1          : 0011001100101000 : 0x3328
 N :       1  1        1  1        1        1       : 0011001100100100 : 0x3324
 O : 1  1  1  1  1  1  1  1  0  0  0  0  0  0  0  0 : 1111111100000000 : 0xFF00
 P : 1  1  1           1  1  1  1                   : 1110001111000000 : 0xE3C0
 Q : 1  1  1  1  1  1  1  1  0  0  0  0  0  1  0  0 : 1111111100000100 : 0xFF04
 R : 1  1  1           1  1  1  1           1       : 1110001111000100 : 0xE3C4
 S : 1  1     1  1  1     1  1  1                   : 1101110111000000 : 0xDDC0
 T : 1  1                             1        1    : 1100000000010010 : 0xC012
 U :       1  1  1  1  1  1  0  0  0  0  0  0  0  0 : 0011111100000000 : 0x3F00
 V :                   1  1              1        1 : 0000001100001001 : 0x0309
 W :       1  1  1  1  1  1  0  0  0  0  0  0  1  0 : 0011111100000010 : 0x3F02
 X :                               1     1  1     1 : 0000000000101101 : 0x002D
 Y :                               1     1     1    : 0000000000101010 : 0x002A
 Z : 1  1        1  1                    1        1 : 1100110000001001 : 0xCC09

 */





uint16_t OSL12306_16::encode(char charactor){
  uint16_t charMap[_OSL12306_16_NUM_OF_CHARS] = {
      0x00C0, 0xFF24, 0x0012, 0xEEC0, 0xFCC0, 0x31C0, 0xDDC0, 0xDFC0, 0xF100, 0xFFC0, 0xFDC0, 0xF3C0, 
      0x1FC0, 0xCF00, 0x3EC0, 0xCFC0, 0xC3C0, 0xDF40, 0x33C0, 0xCC12, 0xC812, 0x001E, 0x0F00, 0x3328, 
      0x3324, 0xFF00, 0xE3C0, 0xFF04, 0xE3C4, 0xDDC0, 0xC012, 0x3F00, 0x0309, 0x3F02, 0x002D, 0x002A, 
      0xCC09 };
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
    case 'g' : return charMap[17];
    case 'G' : return charMap[17];
    case 'h' : return charMap[18];
    case 'H' : return charMap[18];
    case 'i' : return charMap[19];
    case 'I' : return charMap[19];
    case 'j' : return charMap[20];
    case 'J' : return charMap[20];
    case 'k' : return charMap[21];
    case 'K' : return charMap[21];
    case 'l' : return charMap[22];
    case 'L' : return charMap[22];
    case 'm' : return charMap[23];
    case 'M' : return charMap[23];
    case 'n' : return charMap[24];
    case 'N' : return charMap[24];
    case 'o' : return charMap[25];
    case 'O' : return charMap[25];
    case 'p' : return charMap[26];
    case 'P' : return charMap[26];
    case 'q' : return charMap[27];
    case 'Q' : return charMap[27];
    case 'r' : return charMap[28];
    case 'R' : return charMap[28];
    case 's' : return charMap[29];
    case 'S' : return charMap[29];
    case 't' : return charMap[30];
    case 'T' : return charMap[30];
    case 'u' : return charMap[31];
    case 'U' : return charMap[31];
    case 'v' : return charMap[32];
    case 'V' : return charMap[32];
    case 'w' : return charMap[33];
    case 'W' : return charMap[33];
    case 'x' : return charMap[34];
    case 'X' : return charMap[34];
    case 'y' : return charMap[35];
    case 'Y' : return charMap[35];
    case 'z' : return charMap[36];
    case 'Z' : return charMap[36];
  }
  return 0;
}

#endif /* USE_NSEG_LED */