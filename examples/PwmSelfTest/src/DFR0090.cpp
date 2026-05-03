#include "../config.h"

#ifdef USE_NSEG_LED

#include "DFR0090.h"

DFR0090::DFR0090(uint8_t clockPin, uint8_t latchPin, uint8_t dataPin, uint8_t num):
  _clockPin(clockPin),
  _latchPin(latchPin),
  _dataPin(dataPin),
  _num_digits(num)
{}

uint8_t DFR0090::clear(void) {
  digitalWrite(_latchPin, LOW);
  for(int i=_num_digits-1; i>=0; i--){
     shiftOut(_dataPin, _clockPin, MSBFIRST, 0xff);
  }
  digitalWrite(_latchPin, HIGH);
  return _DFR0090_FUNCTION_SUCCESS;
}

void DFR0090::begin(void) {
  pinMode(_latchPin, OUTPUT);
  pinMode(_dataPin, OUTPUT);  
  pinMode(_clockPin, OUTPUT);
}

uint8_t DFR0090::display(uint64_t points, const char dispData[]) {
  //byte byteData[_num_digits] = {0};
  byte byteData[_DFR0090_MAX_DIGITS] = {0};
  setDataFormat(dispData, points, byteData);
  digitalWrite(_latchPin, LOW);
  for(int i=_num_digits-1; i>=0; i--){
     shiftOut(_dataPin, _clockPin, MSBFIRST, byteData[i]);
  }
  digitalWrite(_latchPin, HIGH);
  return _DFR0090_FUNCTION_SUCCESS;
}

void DFR0090::setDataFormat(const char* strData,uint64_t points, byte *byteData) {
  for(int i=0; i<_num_digits; i++){
    switch(strData[i]){
      case 0:
        byteData[i]=0xff;
        break;
      case ' ':
        byteData[i]=0xff;
        break;
      case '0': 
        byteData[i]=0xc0;
        break;
      case '1':
        byteData[i]=0xf9;
        break;
      case '2':
        byteData[i]=0xa4;
        break;
      case '3':
        byteData[i]=0xb0;
        break;
      case '4':
        byteData[i]=0x99;
        break;
      case '5':
        byteData[i]=0x92;
        break;
      case '6':
        byteData[i]=0x82;
        break;
      case '7':
        byteData[i]=0xf8;
        break;
      case '8':
        byteData[i]=0x80;
        break;
      case '9':
        byteData[i]=0x90;
        break;
      case 'a':
        byteData[i]=0b10001000;
        break;
      case 'A':
        byteData[i]=0b10001000;
        break;
      case 'b':
        byteData[i]=0b10000011;
        break;
      case 'B':
        byteData[i]=0b10000011;
        break;
      case 'c':
        byteData[i]=0b11000110;
        break;
      case 'C':
        byteData[i]=0b11000110;
        break;
      case 'd':
        byteData[i]=0b10100001;
        break;
      case 'D':
        byteData[i]=0b10100001;
        break;
      case 'e':
        byteData[i]=0b10000110;
        break;
      case 'E':
        byteData[i]=0b10000110;
        break;
      case 'f':
        byteData[i]=0b10001110;
        break;
      case 'F':
        byteData[i]=0b10001110;
        break;
      case '-':
        byteData[i]=0xbf;
        break;
    }

  }

  for (int i=0; i< _num_digits;i++) {
    if ((0b1 & points) > 0) {
      byteData[_num_digits-i-1]=byteData[_num_digits-i-1] & 0b01111111;
      //byteData[i]=byteData[i] & 0b01111111;
    }
    points = points >> 1;
  }
}
#endif /* USE_NSEG_LED */