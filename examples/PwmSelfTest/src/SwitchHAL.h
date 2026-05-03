
#ifndef __SWITCH_HAL_H__
#define __SWITCH_HAL_H__

#include <stdint.h>
#include <Arduino.h>
#include "../config.h"

#ifdef USE_SWITCH

typedef enum {
  SWITCH_TYPE_PULL_UP = 1,
  SWITCH_TYPE_PULL_DOWN
} SwitchType;

typedef enum {
  SW_FUNCTION_UNSUPPORTED = 1,
  SW_FUNCTION_SUCCESS,
  SW_FUNCTION_FAIL
} SwitchFunctionReturnValue;

class Switch {
public:
  Switch(uint8_t pin, SwitchType type = SWITCH_TYPE_PULL_UP);
  SwitchFunctionReturnValue begin(void);
  SwitchFunctionReturnValue on(void);
  SwitchFunctionReturnValue off(void);
protected:
  uint8_t _pin;
  SwitchType _type;
};

#endif /* USE_SWITCH */

#endif /* __SWITCH_HAL_H__ */
