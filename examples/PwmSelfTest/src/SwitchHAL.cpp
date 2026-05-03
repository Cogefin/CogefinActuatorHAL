#include "SwitchHAL.h"

#ifdef USE_SWITCH

Switch::Switch(uint8_t pin, SwitchType type):
  _pin(pin),
  _type(type)
{}

SwitchFunctionReturnValue Switch::begin(void) {
  pinMode(_pin, OUTPUT);
  return off();
}

SwitchFunctionReturnValue Switch::on(void) {
  if (_type == SWITCH_TYPE_PULL_UP) {
    digitalWrite(_pin, HIGH);
  } else {
    digitalWrite(_pin, LOW);
  }
  return SW_FUNCTION_SUCCESS;
}

SwitchFunctionReturnValue Switch::off(void) {
  if (_type == SWITCH_TYPE_PULL_UP) {
    digitalWrite(_pin, LOW);
  } else {
    digitalWrite(_pin, HIGH);
  }
  return SW_FUNCTION_SUCCESS;
}
#endif /* USE_SWITCH */