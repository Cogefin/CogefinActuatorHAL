#ifndef __SIMPLE_SOUND_HAL_H__
#define __SIMPLE_SOUND_HAL_H__

#include <stdint.h>
#include <Arduino.h>
#include "../config.h"

#ifdef USE_SIMPLE_SOUND
typedef enum {
  SIMPLE_SOUND_TYPE_PULL_UP = 1,
  SIMPLE_SOUND_TYPE_PULL_DOWN
} SimpleSoundType;

typedef enum {
  SSOUND_FUNCTION_UNSUPPORTED = 1,
  SSOUND_FUNCTION_SUCCESS,
  SSOUND_FUNCTION_FAIL
} SimpleSoundFunctionReturnValue;

class SimpleSound {
public:
  SimpleSound(uint8_t pin, SimpleSoundType type = SIMPLE_SOUND_TYPE_PULL_UP);
  SimpleSoundFunctionReturnValue begin(void);
  SimpleSoundFunctionReturnValue on(void);
  SimpleSoundFunctionReturnValue off(void);
  SimpleSoundFunctionReturnValue play(int bass, int duration);
protected:
  uint8_t _pin;
  SimpleSoundType _type;
};

#define SIMPLE_SOUND_C 1911
#define SIMPLE_SOUND_D 1702
#define SIMPLE_SOUND_E 1516
#define SIMPLE_SOUND_F 1431
#define SIMPLE_SOUND_G 1275
#define SIMPLE_SOUND_A 1136
#define SIMPLE_SOUND_B 1012

#endif /* USE_SIMPLE_SOUND */

#endif /* __SIMPLE_SOUND_HAL_H__ */