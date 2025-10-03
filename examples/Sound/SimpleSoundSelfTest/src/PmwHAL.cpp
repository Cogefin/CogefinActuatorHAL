#include "../config.h"
#ifdef USE_PMW

#include "PmwHAL.h"


PMW::PMW(uint8_t pin):
  _pin(pin)
{}

PmwFunctionReturnValue PMW::begin(void) {
  _level = 0;
  return off();
}

PmwFunctionReturnValue PMW::apply(void) {
  analogWrite(_pin, _level);
  return PMW_FUNCTION_SUCCESS;
}

PmwFunctionReturnValue PMW::off(void) {
  analogWrite(_pin, 0);
  return PMW_FUNCTION_SUCCESS;
}

PmwFunctionReturnValue PMW::set(uint8_t level) {
  _level = level;
  return PMW_FUNCTION_SUCCESS;
}

#endif /* USE_PMW */
