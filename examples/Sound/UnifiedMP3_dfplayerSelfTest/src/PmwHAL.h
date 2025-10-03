
#ifndef __PMW_HAL_H__
#define __PMW_HAL_H__

#include <stdint.h>
#include <Arduino.h>

#include "../config.h"
#ifdef USE_PMW

typedef enum {
  PMW_FUNCTION_UNSUPPORTED = 1,
  PMW_FUNCTION_SUCCESS,
  PMW_FUNCTION_FAIL
} PmwFunctionReturnValue;

class PMW {
public:
  PMW(uint8_t pin);
  PmwFunctionReturnValue begin(void);
  PmwFunctionReturnValue apply(void);
  PmwFunctionReturnValue off(void);
  PmwFunctionReturnValue set(uint8_t level);
protected:
  uint8_t _pin;
  uint8_t _level;
};

#endif /* USE_PMW */
#endif /* __PMW_HAL_H__ */
