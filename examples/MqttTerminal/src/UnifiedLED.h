#ifndef __UNIFIED_LED_H__
#define __UNIFIED_LED_H__
#include "Arduino.h"
#include "../config.h"

#ifdef USE_LED
#ifdef LED_HAL_USE_MY9221
#include <Grove_LED_Bar.h>
#endif /* LED_HAL_USE_MY9221 */

#ifdef LED_HAL_USE_NEO_PIXEL
#include <Adafruit_NeoPixel.h>
#endif /* LED_HAL_USE_NEO_PIXEL */

#ifdef LED_HAL_USE_P98X3
#include <ChainableLED.h>
#endif /* LED_HAL_USE_P98X3 */


typedef enum {
  LED_BAR =1,
  LED_CIRCULAR,
  P98X3_LED,
  NEO_PIXEL_LED,
  SIMPLE_COLOR_LED,
  SIMPLE_MONO_LED
} UnifiedLedType;

typedef enum {
  LED_FORWARD = 1,
  LED_REVERSE,
  PULL_UP,
  PULL_DOWN
} UnifiedLedMode;

typedef enum {
  LED_FUNCTION_UNSUPPORTED = 1,
  LED_FUNCTION_SUCCESS,
  LED_FUNCTION_FAIL,
} ledFunctionReturnValue;

class UnifiedLED {
public:
#ifdef LED_HAL_USE_MY9221
  UnifiedLED(Grove_LED_Bar* bar, UnifiedLedType type, uint32_t leds, UnifiedLedMode mode);
#endif /* LED_HAL_USE_MY9221 */
#ifdef LED_HAL_USE_P98X3
  UnifiedLED(ChainableLED* chain, UnifiedLedType type, uint32_t leds);
#endif /* LED_HAL_USE_P98X3 */
#ifdef LED_HAL_USE_NEO_PIXEL
  UnifiedLED(Adafruit_NeoPixel* pixel, UnifiedLedType type, uint32_t leds);
#endif /* LED_HAL_USE_NEO_PIXEL */
  UnifiedLED(uint8_t pin, UnifiedLedMode mode);
  UnifiedLED(uint8_t r_pin, uint8_t g_pin, uint8_t b_pin, UnifiedLedMode mode);
  ledFunctionReturnValue begin();
  ledFunctionReturnValue clear();
  ledFunctionReturnValue setLevel(float level);
  ledFunctionReturnValue setMode(UnifiedLedMode mode);
  ledFunctionReturnValue setLedNum(uint32_t count);
  UnifiedLedType getType(void);
  ledFunctionReturnValue setLed(uint32_t ledNo, float brightness);
  ledFunctionReturnValue setLed(float brightness);
  ledFunctionReturnValue setLed(uint32_t ledNo, byte red, byte green, byte blue);
  ledFunctionReturnValue setLed(byte red, byte green, byte blue);
  ledFunctionReturnValue setOnce(uint32_t value);
  ledFunctionReturnValue setOnce(uint32_t value, byte red, byte green, byte blue);
protected:
  uint8_t _pin1, _pin2, _pin3;
  UnifiedLedType _type;
  uint32_t _num_of_led;
  UnifiedLedMode _led_mode;
#ifdef LED_HAL_USE_MY9221
  Grove_LED_Bar *my9221;
#endif /* LED_HAL_USE_MY9221 */
#ifdef LED_HAL_USE_P98X3
  ChainableLED *p98x3;
#endif /* LED_HAL_USE_P98X3 */
#ifdef LED_HAL_USE_NEO_PIXEL
  Adafruit_NeoPixel* neoPixel;
#endif /* LED_HAL_USE_NEO_PIXEL */
};


#endif /* USE_LED */

#endif /* __UNIFIED_LED_H__ */