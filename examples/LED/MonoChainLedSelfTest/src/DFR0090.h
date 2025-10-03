#ifndef __DFR0090_H__
#define __DFR0090_H__
#include <stdint.h>
#include <Arduino.h>
#include "../config.h"

#ifdef USE_NSEG_LED

/*
 *
 * SPI(3線式) LED Module 8 Digital (8桁赤色7セグLEDモジュール)
 * https://akizukidenshi.com/catalog/g/g106681/
 */

//#define _DFR0090_PULL_UP   0
//#define _DFR0090_PULL_DOWN 1

#define _DFR0090_FUNCTION_FAIL      -1
#define _DFR0090_FUNCTION_SUCCESS    1
#define _DFR0090_FUNCTION_UNSUPPORT  2

//#define _DFR0090_BIT_DELAY   50
#define _DFR0090_MAX_DIGITS  64

//#define _DFR0090_CHAR_PINS  7
//#define _DFR0090_PIN_A_NUM 0
//#define _DFR0090_PIN_B_NUM 1
//#define _DFR0090_PIN_C_NUM 2
//#define _DFR0090_PIN_D_NUM 3
//#define _DFR0090_PIN_E_NUM 4
//#define _DFR0090_PIN_F_NUM 5
//#define _DFR0090_PIN_G_NUM 6
//#define _DFR0090_PIN_DP_NUM 7

//#define DFR0090_TYPE_CATHODE_COMMON true
//#define DFR0090_TYPE_ANODE_COMMON false

//#ifndef CATHODE_COMMON
//#define CATHODE_COMMON true
//#endif

//#ifndef ANODE_COMMON
//#define ANODE_COMMON false
//#endif

#define _DFR0090_NUM_OF_CHARS 13

class DFR0090 {
public:
  DFR0090(uint8_t clockPin, uint8_t latchPin, uint8_t dataPin, uint8_t num);
  uint8_t clear(void);
  uint8_t display(uint64_t points, const char dispData[]);
  void begin(void);
private:
  void setDataFormat(const char* strData,uint64_t points, byte *byteData);
  uint8_t _num_digits;
  uint8_t _latchPin, _clockPin, _dataPin;
};

#endif /* USE_NSEG_LED */

#endif /* __DFR0090_H__ */

