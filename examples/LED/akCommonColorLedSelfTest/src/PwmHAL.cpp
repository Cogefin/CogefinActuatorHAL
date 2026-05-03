#include "../config.h"
#ifdef USE_PWM


#include "./PwmHAL.h"

PWM::PWM(uint8_t pin):
  _pin(pin)
{}

PwmFunctionReturnValue PWM::begin(void) {
  _level = 0;
  return off();
}

PwmFunctionReturnValue PWM::apply(void) {
  analogWrite(_pin, _level);
  return PWM_FUNCTION_SUCCESS;
}

PwmFunctionReturnValue PWM::off(void) {
  analogWrite(_pin, 0);
  return PWM_FUNCTION_SUCCESS;
}

PwmFunctionReturnValue PWM::set(uint8_t level) {
  _level = level;
  return PWM_FUNCTION_SUCCESS;
}


#endif /* USE_PWM */
