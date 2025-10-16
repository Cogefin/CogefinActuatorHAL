#ifndef __OSL12306_16_H__
#define __OSL12306_16_H__
#include <stdint.h>
#include <Arduino.h>
#include "../config.h"

#ifdef USE_NSEG_LED
/*
OSL12306_16  https://akizukidenshi.com/catalog/g/g114656/

 */

#define _OSL12306_16_PULL_UP   0
#define _OSL12306_16_PULL_DOWN 1

//#define _OSL12306_16_FUNCTION_FAIL       0
#define _OSL12306_16_FUNCTION_FAIL      -1
#define _OSL12306_16_FUNCTION_SUCCESS    1
#define _OSL12306_16_FUNCTION_UNSUPPORT  2

#define _OSL12306_16_BIT_DELAY   50
#define _OSL12306_16_MAX_DIGITS  16

#define _OSL12306_16_CHAR_PINS  16
#define _OSL12306_16_PIN_A1_NUM 0
#define _OSL12306_16_PIN_A2_NUM 1
#define _OSL12306_16_PIN_B_NUM 2
#define _OSL12306_16_PIN_C_NUM 3
#define _OSL12306_16_PIN_D1_NUM 4
#define _OSL12306_16_PIN_D2_NUM 5
#define _OSL12306_16_PIN_E_NUM 6
#define _OSL12306_16_PIN_F_NUM 7
#define _OSL12306_16_PIN_G1_NUM 8
#define _OSL12306_16_PIN_G2_NUM 9
#define _OSL12306_16_PIN_J_NUM 10
#define _OSL12306_16_PIN_K_NUM 11
#define _OSL12306_16_PIN_L_NUM 12
#define _OSL12306_16_PIN_M_NUM 13
#define _OSL12306_16_PIN_N_NUM 14
#define _OSL12306_16_PIN_P_NUM 15


#define OSL12306_16_TYPE_CATHODE_COMMON    true
#define OSL12306_16_TYPE_ANODE_COMMON  false


#ifndef CATHODE_COMMON
#define CATHODE_COMMON true
#endif

#ifndef ANODE_COMMON
#define ANODE_COMMON false
#endif

#define _OSL12306_16_NUM_OF_CHARS 37


class OSL12306_16 {
public:
  OSL12306_16(bool pin_mode, uint8_t * char_pin_list, uint8_t pin_dp, uint8_t num, uint8_t * digit_pin_list);
  uint8_t clear(void);
  uint8_t display(uint64_t points, const char dispData[]);
  void begin(void);
private:
  uint8_t displayOne(uint8_t n, bool point, char dispData);
  void pointOn(void);
  void pointOff(void);
  uint8_t digitOn(uint8_t n);
  uint8_t digitOff(uint8_t n);
  uint16_t encode(char charactor);
  uint8_t _char_pin[_OSL12306_16_CHAR_PINS];
  uint8_t _digit_pin[_OSL12306_16_MAX_DIGITS];
  uint8_t _dp_pin;
  bool _pin_mode;
  uint8_t * _pin_list;
  uint8_t * _digit_pin_list;
  uint8_t _num_digits;
};


#endif /* USE_NSEG_LED */

#endif /* __OSL12306_16_H__ */
