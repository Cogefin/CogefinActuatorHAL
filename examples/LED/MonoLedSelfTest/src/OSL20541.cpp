#include "../config.h"
#ifdef USE_NSEG_LED

#include "OSL20541.h"


OSL20541::OSL20541(bool pin_mode, uint8_t * char_pin_list, uint8_t pin_dp, uint8_t num, uint8_t * ptr):
  _pin_mode(pin_mode),
  _char_pin_list(char_pin_list),
  _pin_dp(pin_dp),
  _num_digits(num),
  _pin_list(ptr)
{}


void OSL20541::begin(void) {
  for (int i=0; i< _OSL20541_CHAR_PINS; i++) {
    _char_pin[i] = _char_pin_list[i];
    pinMode(_char_pin[i], OUTPUT);
  }
  for (int i=0; i<_num_digits; i++ ) {
    pinMode(_pin_list[i], OUTPUT);
    _digit_pin[i] = _pin_list[i];
  }
  pinMode(_pin_dp, OUTPUT);
}

uint8_t OSL20541::displayOne(uint8_t n, bool point, char dispChar) {
  if (n>_num_digits-1) return _OSL20541_FUNCTION_FAIL;
  uint16_t pinState = encode(dispChar);
  if (pinState == _OSL20541_FUNCTION_FAIL) return _OSL20541_FUNCTION_FAIL;
  if (pinState!=0) {
    for (int i= _OSL20541_CHAR_PINS -1; i>=0; i--) {
      if ((0b1 & pinState) > 0) {
        if (_pin_mode == OSL20541_TYPE_CATHODE_COMMON) {
          digitalWrite(_char_pin[i],HIGH);
        } else {
          digitalWrite(_char_pin[i],LOW);
        }
      } else {
        if (_pin_mode == OSL20541_TYPE_CATHODE_COMMON) {
          digitalWrite(_char_pin[i],LOW);
        } else {
          digitalWrite(_char_pin[i],HIGH);
        }
      }
      pinState = pinState >> 1;
    }
  } else {
    for (int i= _OSL20541_CHAR_PINS -1; i>=0; i--) {
      if (_pin_mode == OSL20541_TYPE_CATHODE_COMMON) {
        digitalWrite(_char_pin[i],LOW);
      } else {
        digitalWrite(_char_pin[i],HIGH);
      }
    }
  }
  if (point) {
    pointOn();
  } else {
    pointOff();
  }
  return digitOn(n);
}

void OSL20541::pointOn(void) {
  if (_pin_mode == OSL20541_TYPE_CATHODE_COMMON) {
    digitalWrite(_pin_dp,HIGH);
  } else {
    digitalWrite(_pin_dp,LOW);
  }
}

void OSL20541::pointOff(void) {
  if (_pin_mode == OSL20541_TYPE_CATHODE_COMMON) {
    digitalWrite(_pin_dp,LOW);
  } else {
    digitalWrite(_pin_dp,HIGH);
  }
}

uint8_t OSL20541::digitOn(uint8_t n) {
  if (n>_num_digits-1) return _OSL20541_FUNCTION_FAIL;
  if (_pin_mode == OSL20541_TYPE_CATHODE_COMMON) {
    digitalWrite(_digit_pin[n],LOW);
  } else {
    digitalWrite(_digit_pin[n],HIGH);
  }
  return _OSL20541_FUNCTION_SUCCESS;
}

uint8_t OSL20541::digitOff(uint8_t n) {
  if (n>_num_digits-1) return _OSL20541_FUNCTION_FAIL;
  if (_pin_mode == OSL20541_TYPE_CATHODE_COMMON) {
    digitalWrite(_digit_pin[n],HIGH);
  } else {
    digitalWrite(_digit_pin[n],LOW);
  }
  return _OSL20541_FUNCTION_SUCCESS;
}

uint8_t OSL20541::display(uint64_t points, const char dispData[]) {
  for (int i=0; i<_num_digits; i++ ) {
    if ((0b1 & points) > 0) {
      if (_OSL20541_FUNCTION_FAIL == displayOne(i,true,dispData[i])) return _OSL20541_FUNCTION_FAIL;
    } else {
      if (_OSL20541_FUNCTION_FAIL == displayOne(i,false,dispData[i])) return _OSL20541_FUNCTION_FAIL;
    }
    if (_num_digits>1) {
      delayMicroseconds(_OSL20541_BIT_DELAY);
      if (_OSL20541_FUNCTION_FAIL == digitOff(i)) return _OSL20541_FUNCTION_FAIL;
    }
    points = points >> 1;
  }
  delayMicroseconds(_OSL20541_BIT_DELAY);
  return _OSL20541_FUNCTION_SUCCESS;
}

uint8_t OSL20541::clear(void) {
  for (int i=0; i<_num_digits; i++) {
    digitOff(i);
  }
  for (int i=0; i<_OSL20541_CHAR_PINS; i++) {
    if (_pin_mode == OSL20541_TYPE_CATHODE_COMMON) {
      digitalWrite(_char_pin[i],LOW);
    } else {
      digitalWrite(_char_pin[i],HIGH);
    }
  }
  pointOff();
  return _OSL20541_FUNCTION_SUCCESS;
};

/* convert charactor to led bitmap
   : A  B  C  D  E  F  G1 G2 H  J  K  L  M  N
 - :                   1  1                   : 00000011000000 : 00C0
 0 : 1  1  1  1  1  1        1        1       : 11111100100100 : 3F24
 1 :                            1        1    : 00000000010010 : 0012
 2 : 1  1     1  1     1  1                   : 11011011000000 : 36C0
 3 : 1  1  1  1        1  1                   : 11110011000000 : 3CC0
 4 :    1  1        1  1  1                   : 01100111000000 : 19C0
 5 : 1     1  1     1  1  1                   : 10110111000000 : 2DC0
 6 : 1     1  1  1  1  1  1                   : 10111111000000 : 2FC0
 7 : 1  1  1        1                         : 11100100000000 : 3900
 8 : 1  1  1  1  1  1  1  1                   : 11111111000000 : 3FC0
 9 : 1  1  1  1     1  1  1                   : 11110111000000 : 3DC0
 A : 1  1  1     1  1  1  1                   : 11101111000000 : 3BC0
 b :       1  1  1  1  1  1                   : 00111111000000 : 0FC0
 C : 1        1  1  1                         : 10011100000000 : 2700
 d :    1  1  1  1     1  1                   : 01111011000000 : 1EC0
 E : 1        1  1  1  1  1                   : 10011111000000 : 27C0
 F : 1           1  1  1  1                   : 10001111000000 : 23C0
 G : 1     1  1  1  1     1                   : 10111101000000 : 2F40
 H :    1  1     1  1  1  1                   : 01101111000000 : 1BC0
 I : 1        1                 1        1    : 10010000010010 : 2412
 J :    1  1  1  1                            : 01111000000000 : 1E00
 k :                            1  1  1  1    : 00000000011110 : 001E
 L :          1  1  1                         : 00011100000000 : 0700
 M :    1  1     1  1        1     1          : 01101100101000 : 1B28
 N :    1  1     1  1        1        1       : 01101100100100 : 1B24
 O : 1  1  1  1  1  1                         : 11111100000000 : 3F00
 P : 1  1        1  1  1  1                   : 11001111000000 : 33C0
 Q : 1  1  1  1  1  1                 1       : 11111100000100 : 3F04
 R : 1  1        1  1  1  1           1       : 11001111000100 : 33C4
 S : 1     1  1     1  1  1                   : 10110111000000 : 2DC0
 T : 1                          1        1    : 10000000010010 : 2012
 U :    1  1  1  1  1                         : 01111100000000 : 1F00
 V :             1  1              1        1 : 00001100001001 : 0309
 W :    1  1  1  1  1                    1    : 01111100000010 : 1F02
 X :                         1     1  1     1 : 00000000101101 : 002D
 Y :                         1     1     1    : 00000000101010 : 002A
 Z : 1        1                    1        1 : 10010000001001 : 2409
 */


uint16_t OSL20541::encode(char charactor){
  uint16_t charMap[_OSL20541_NUM_OF_CHARS] = {
    0x00C0, 0x3F24, 0x0012, 0x36C0, 0x3CC0, 0x19C0, 0x2DC0, 0x2FC0, 0x3900, 
    0x3FC0, 0x3DC0, 0x3BC0, 0x0FC0, 0x2700, 0x1EC0, 0x27C0, 0x23C0, 0x2F40, 
    0x1BC0, 0x2412, 0x1E00, 0x001E, 0x0700, 0x1B28, 0x1B24, 0x3F00, 0x33C0, 
    0x3F04, 0x33C4, 0x2DC0, 0x2012, 0x1F00, 0x0309, 0x1F02, 0x002D, 0x002A, 
    0x2409
  };
  if (charactor == 0) return 0;
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