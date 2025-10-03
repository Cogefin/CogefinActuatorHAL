#include "UnifiedNSegLED.h"

#ifdef USE_NSEG_LED

UnifiedNSegLED::UnifiedNSegLED(OSL30561 * osl30561, UnifiedNSegLedType type):
  _osl30561(osl30561),
  _type(type)
{}

UnifiedNSegLED::UnifiedNSegLED(OSL20541 * osl20541, UnifiedNSegLedType type):
  _osl20541(osl20541),
  _type(type)
{}

UnifiedNSegLED::UnifiedNSegLED(OSL12306_16 * osl12306_16, UnifiedNSegLedType type):
  _osl12306_16(osl12306_16),
  _type(type)
{}

UnifiedNSegLED::UnifiedNSegLED(TM1637 * tm1637, UnifiedNSegLedType type):
  _tm1637(tm1637),
  _type(type)
{}

UnifiedNSegLED::UnifiedNSegLED(DFR0090 * dfr0090, UnifiedNSegLedType type):
  _dfr0090(dfr0090),
  _type(type)
{}

nSegLedFunctionReturnValue UnifiedNSegLED::begin(void) {
  switch(_type) {
    case OSL12306_16_TYPE:
      _osl12306_16->begin();
      return NSEGLED_FUNCTION_SUCCESS;
    case OSL20541_TYPE:
      _osl20541->begin();
      return NSEGLED_FUNCTION_SUCCESS;
    case OSL30561_TYPE:
      _osl30561->begin();
      return NSEGLED_FUNCTION_SUCCESS;
    case GROVE_TM1637_TYPE:
      _tm1637->init();
      return NSEGLED_FUNCTION_SUCCESS;
    case DFR0090_TYPE:
      _dfr0090->begin();
      return NSEGLED_FUNCTION_SUCCESS;
  }
  return NSEGLED_FUNCTION_UNSUPPORTED;
}


#define _FUNCTION_FAIL       0
#define _FUNCTION_SUCCESS    1
#define _FUNCTION_UNSUPPORT  2


nSegLedFunctionReturnValue UnifiedNSegLED::analyzeRstValue(uint8_t val) {
  switch(val) {
    case _FUNCTION_SUCCESS: return NSEGLED_FUNCTION_SUCCESS;
    case _FUNCTION_UNSUPPORT: return NSEGLED_FUNCTION_UNSUPPORTED;
  }
  return NSEGLED_FUNCTION_FAIL;
}

nSegLedFunctionReturnValue UnifiedNSegLED::clear(void) {
  uint8_t rst;
  switch(_type) {
    case OSL12306_16_TYPE:
      rst = _osl12306_16->clear();
      return analyzeRstValue(rst);
    case OSL20541_TYPE:
      rst = _osl20541->clear();
      return analyzeRstValue(rst);
    case OSL30561_TYPE:
      rst = _osl30561->clear();
      return analyzeRstValue(rst);
    case GROVE_TM1637_TYPE:
      _tm1637->clearDisplay();
      return NSEGLED_FUNCTION_SUCCESS;
    case DFR0090_TYPE:
      rst = _dfr0090->clear();
      return analyzeRstValue(rst);
  }
  return NSEGLED_FUNCTION_UNSUPPORTED;
}

nSegLedFunctionReturnValue UnifiedNSegLED::display(uint64_t points, const char dispData[]) {
  uint8_t rst;
  switch(_type) {
    case OSL12306_16_TYPE:
      rst = _osl12306_16->display(points, dispData);
      return analyzeRstValue(rst);
    case OSL20541_TYPE:
      rst = _osl20541->display(points, dispData);
      return analyzeRstValue(rst);
    case OSL30561_TYPE:
      rst = _osl30561->display(points, dispData);
      return analyzeRstValue(rst);
    case DFR0090_TYPE:
      rst = _dfr0090->display(points, dispData);
      return analyzeRstValue(rst);
  }
  return NSEGLED_FUNCTION_UNSUPPORTED;
}

int8_t UnifiedNSegLED::convChar(char data) {
  switch(data) {
    case '0' : return (int8_t) 0;
    case '1' : return (int8_t) 1;
    case '2' : return (int8_t) 2;
    case '3' : return (int8_t) 3;
    case '4' : return (int8_t) 4;
    case '5' : return (int8_t) 5;
    case '6' : return (int8_t) 6;
    case '7' : return (int8_t) 7;
    case '8' : return (int8_t) 8;
    case '9' : return (int8_t) 9;
    case 'a' : return (int8_t) 10;
    case 'A' : return (int8_t) 10;
    case 'b' : return (int8_t) 11;
    case 'B' : return (int8_t) 11;
    case 'c' : return (int8_t) 12;
    case 'C' : return (int8_t) 12;
    case 'd' : return (int8_t) 13;
    case 'D' : return (int8_t) 13;
    case 'e' : return (int8_t) 14;
    case 'E' : return (int8_t) 14;
    case 'f' : return (int8_t) 15;
    case 'F' : return (int8_t) 15;
  }
  return (int8_t) -1;
}

nSegLedFunctionReturnValue UnifiedNSegLED::display(const char dispData[]) {
  if (_type != GROVE_TM1637_TYPE) return NSEGLED_FUNCTION_UNSUPPORTED;
  for (int i=0; i< 4 ; i++) {
    int8_t data = convChar(dispData[i]);
    if (-1 != data ) {
      _tm1637->display(i,data);
    }
  }
  return NSEGLED_FUNCTION_SUCCESS;
}

nSegLedFunctionReturnValue UnifiedNSegLED::set(uint8_t brightness,uint8_t SetData,uint8_t SetAddr) {
  if (_type != GROVE_TM1637_TYPE) return NSEGLED_FUNCTION_UNSUPPORTED;
  _tm1637->set(brightness, SetData, SetAddr);
  return NSEGLED_FUNCTION_SUCCESS;
}

nSegLedFunctionReturnValue UnifiedNSegLED::setColomn(bool flag) {
  if (_type != GROVE_TM1637_TYPE) return NSEGLED_FUNCTION_UNSUPPORTED;
  _tm1637->point(flag);
  return NSEGLED_FUNCTION_SUCCESS;
}
#endif /* USE_NSEG_LED */