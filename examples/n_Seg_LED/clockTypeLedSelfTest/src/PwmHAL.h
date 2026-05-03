
#ifndef __PWM_HAL_H__
#define __PWM_HAL_H__

#include <stdint.h>
#include <Arduino.h>

#include "../config.h"
#ifdef USE_PWM


typedef enum {
  PWM_FUNCTION_UNSUPPORTED = 1,
  PWM_FUNCTION_SUCCESS,
  PWM_FUNCTION_FAIL
} PwmFunctionReturnValue;

class PWM {
public:
  PWM(uint8_t pin);
  PwmFunctionReturnValue begin(void);
  PwmFunctionReturnValue apply(void);
  PwmFunctionReturnValue off(void);
  PwmFunctionReturnValue set(uint8_t level);
protected:
  uint8_t _pin;
  uint8_t _level;
};

#endif /* USE_PWM */
#endif /* __PWM_HAL_H__ */
