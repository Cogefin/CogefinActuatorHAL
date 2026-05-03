
#include "../config.h"

#ifdef USE_SIMPLE_SOUND

#include "SimpleSound.h"

SimpleSound::SimpleSound(uint8_t pin, SimpleSoundType type):
  _pin(pin),
  _type(type)
{}

SimpleSoundFunctionReturnValue SimpleSound::begin(void) {
  pinMode(_pin, OUTPUT);
  return off();
}

SimpleSoundFunctionReturnValue SimpleSound::on(void) {
  if (_type == SIMPLE_SOUND_TYPE_PULL_UP) {
    digitalWrite(_pin, HIGH);
  } else {
    digitalWrite(_pin, LOW);
  }
  return SSOUND_FUNCTION_SUCCESS;
}

SimpleSoundFunctionReturnValue SimpleSound::off(void) {
  if (_type == SIMPLE_SOUND_TYPE_PULL_UP) {
    digitalWrite(_pin, LOW);
  } else {
    digitalWrite(_pin, HIGH);
  }
  return SSOUND_FUNCTION_SUCCESS;
}

SimpleSoundFunctionReturnValue SimpleSound::play(int bass, int duration) {
  for(int i=0;i<duration;i++) {
    on();
    delayMicroseconds(bass);
    off();
    delayMicroseconds(bass);
  }
  return SSOUND_FUNCTION_SUCCESS;
}

#endif /* USE_SIMPLE_SOUND */
