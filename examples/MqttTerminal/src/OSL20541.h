#ifndef __OSL20541_H__
#define __OSL20541_H__
#include <stdint.h>
#include <Arduino.h>
#include "../config.h"

#ifdef USE_NSEG_LED


/*
 *
 *
 * https://akizukidenshi.com/catalog/g/g117364/
 */




#define _OSL20541_PULL_UP   0
#define _OSL20541_PULL_DOWN 1

//#define _OSL20541_FUNCTION_FAIL       0
#define _OSL20541_FUNCTION_FAIL      -1
#define _OSL20541_FUNCTION_SUCCESS    1
#define _OSL20541_FUNCTION_UNSUPPORT  2

#define _OSL20541_BIT_DELAY   50
#define _OSL20541_MAX_DIGITS  64

#define _OSL20541_CHAR_PINS  14
#define _OSL20541_PIN_A_NUM 0
#define _OSL20541_PIN_B_NUM 1
#define _OSL20541_PIN_C_NUM 2
#define _OSL20541_PIN_D_NUM 3
#define _OSL20541_PIN_E_NUM 4
#define _OSL20541_PIN_F_NUM 5
#define _OSL20541_PIN_G1_NUM 6
#define _OSL20541_PIN_G2_NUM 7
#define _OSL20541_PIN_H_NUM 8
#define _OSL20541_PIN_J_NUM 9
#define _OSL20541_PIN_K_NUM 10
#define _OSL20541_PIN_L_NUM 11
#define _OSL20541_PIN_M_NUM 12
#define _OSL20541_PIN_N_NUM 13


#define OSL20541_TYPE_CATHODE_COMMON true
#define OSL20541_TYPE_ANODE_COMMON false

#ifndef CATHODE_COMMON
#define CATHODE_COMMON true
#endif

#ifndef ANODE_COMMON
#define ANODE_COMMON false
#endif

#define _OSL20541_NUM_OF_CHARS 37

class OSL20541 {
public:
  OSL20541(bool pin_mode, uint8_t * char_pin_list, uint8_t pin_dp, uint8_t num, uint8_t * ptr);
  uint8_t clear(void);
  uint8_t display(uint64_t points, const char dispData[]);
  void begin(void);
private:
  void pointOn(void);
  void pointOff(void);
  uint8_t digitOn(uint8_t n);
  uint8_t digitOff(uint8_t n);
  uint8_t displayOne(uint8_t n, bool point, char dispChar);
  uint16_t encode(char charactor);
//private:
  uint8_t _num_digits;
  uint8_t _char_pin[_OSL20541_CHAR_PINS];
  uint8_t _digit_pin[_OSL20541_MAX_DIGITS];
  bool _pin_mode;
  uint8_t _pin_dp;
  uint8_t * _pin_list;
  uint8_t * _char_pin_list;
};



#endif /* USE_NSEG_LED */
#endif /* __OSL20541_H__ */
