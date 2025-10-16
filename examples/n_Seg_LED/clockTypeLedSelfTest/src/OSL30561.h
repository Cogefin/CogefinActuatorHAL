#ifndef __OSL30561_H__
#define __OSL30561_H__
#include <stdint.h>
#include <Arduino.h>

#include "../config.h"

#ifdef USE_NSEG_LED

/*
 *
 *
 * https://akizukidenshi.com/catalog/g/g117364/
 */






#define _OSL30561_PULL_UP   0
#define _OSL30561_PULL_DOWN 1

//#define _OSL30561_FUNCTION_FAIL       0
#define _OSL30561_FUNCTION_FAIL      -1
#define _OSL30561_FUNCTION_SUCCESS    1
#define _OSL30561_FUNCTION_UNSUPPORT  2

#define _OSL30561_BIT_DELAY   50
#define _OSL30561_MAX_DIGITS  64

#define _OSL30561_CHAR_PINS  7
#define _OSL30561_PIN_A_NUM 0
#define _OSL30561_PIN_B_NUM 1
#define _OSL30561_PIN_C_NUM 2
#define _OSL30561_PIN_D_NUM 3
#define _OSL30561_PIN_E_NUM 4
#define _OSL30561_PIN_F_NUM 5
#define _OSL30561_PIN_G_NUM 6
#define _OSL30561_PIN_DP_NUM 7

#define OSL30561_TYPE_CATHODE_COMMON true
#define OSL30561_TYPE_ANODE_COMMON false

#ifndef CATHODE_COMMON
#define CATHODE_COMMON true
#endif

#ifndef ANODE_COMMON
#define ANODE_COMMON false
#endif

#define _OSL30561_NUM_OF_CHARS 17

class OSL30561 {
public:
  OSL30561(bool type, uint8_t pin_a, uint8_t pin_b, uint8_t pin_c, uint8_t pin_d, uint8_t pin_e, uint8_t pin_f, uint8_t pin_g, uint8_t pin_dp, uint8_t num, uint8_t * ptr);
  uint8_t clear(void);
  uint8_t display(uint64_t points, const char dispData[]);
  void begin(void);
private:
  void pointOn(void);
  void pointOff(void);
  uint8_t digitOn(uint8_t n);
  uint8_t digitOff(uint8_t n);
  uint8_t displayOne(uint8_t n, bool point, char dispChar);
  uint8_t encode(char charactor);
  uint8_t _num_digits;
  uint8_t _char_pin[_OSL30561_CHAR_PINS];
  uint8_t _digit_pin[_OSL30561_MAX_DIGITS];
  bool _pin_mode;
  uint8_t _pin_a, _pin_b, _pin_c, _pin_d, _pin_e, _pin_f, _pin_g, _pin_dp;
  uint8_t * _pin_list;
};


#endif /* USE_NSEG_LED */

#endif /* __OSL30561_H__ */
