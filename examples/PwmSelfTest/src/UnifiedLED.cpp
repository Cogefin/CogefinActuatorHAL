#include "UnifiedLED.h"

#ifdef USE_LED

#ifdef LED_HAL_USE_MY9221
UnifiedLED::UnifiedLED(Grove_LED_Bar* bar, UnifiedLedType type, uint32_t leds, UnifiedLedMode mode):
  my9221(bar),
  _type(type),
  _num_of_led(leds),
  _led_mode(mode)
{}
#endif /* LED_HAL_USE_MY9221 */

#ifdef LED_HAL_USE_P98X3
UnifiedLED::UnifiedLED(ChainableLED* chain, UnifiedLedType type, uint32_t leds):
  p98x3(chain),
  _type(type),
  _num_of_led(leds)
{}
#endif /* LED_HAL_USE_P98X3 */

#ifdef LED_HAL_USE_NEO_PIXEL
UnifiedLED::UnifiedLED(Adafruit_NeoPixel* pixel, UnifiedLedType type, uint32_t leds):
  neoPixel(pixel),
  _type(type),
  _num_of_led(leds)
{}
#endif /* LED_HAL_USE_NEO_PIXEL */

UnifiedLED::UnifiedLED(uint8_t pin, UnifiedLedMode mode):
  _pin1(pin),
  _type(SIMPLE_MONO_LED),
  _led_mode(mode)
{}

UnifiedLED::UnifiedLED(uint8_t r_pin, uint8_t g_pin, uint8_t b_pin, UnifiedLedMode mode):
  _pin1(r_pin),
  _pin2(g_pin),
  _pin3(b_pin),
  _type(SIMPLE_COLOR_LED),
  _led_mode(mode)
{}

ledFunctionReturnValue UnifiedLED::setLevel(float level) {
  switch(_type){
#ifdef LED_HAL_USE_MY9221
    case LED_BAR:
    case LED_CIRCULAR:
      my9221->setLevel(level+1);
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_MY9221 */
#ifdef LED_HAL_USE_P98X3
    case P98X3_LED: /* todo */
      /* return LED_FUNCTION_SUCCESS; */
      return LED_FUNCTION_UNSUPPORTED;
#endif /* LED_HAL_USE_P98X3 */
  }
  return LED_FUNCTION_UNSUPPORTED;
}

ledFunctionReturnValue UnifiedLED::setLedNum(uint32_t count) {
  switch(_type){
#ifdef LED_HAL_USE_MY9221
    case LED_BAR:
    case LED_CIRCULAR:
      _num_of_led = count;
      my9221->setLedNum(count);
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_MY9221 */
#ifdef LED_HAL_USE_P98X3
    case P98X3_LED:
      _num_of_led = count;
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_P98X3 */
#ifdef LED_HAL_USE_NEO_PIXEL
    case NEO_PIXEL_LED:
      if (count > 0xFFFF) return LED_FUNCTION_FAIL;
      _num_of_led = count;
      neoPixel->updateLength((uint16_t)count);
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_NEO_PIXEL */
  }
  return LED_FUNCTION_UNSUPPORTED;
}

ledFunctionReturnValue UnifiedLED::setMode(UnifiedLedMode mode) {
  switch(_type){
#ifdef LED_HAL_USE_MY9221
    case LED_BAR:
    case LED_CIRCULAR:
      if (mode==LED_FORWARD) {
        my9221->setGreenToRed(true);
      } else if (mode==LED_REVERSE) {
        my9221->setGreenToRed(false);
      } else {
        return LED_FUNCTION_UNSUPPORTED;
      }
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_MY9221 */
#ifdef LED_HAL_USE_P98X3
    case P98X3_LED:
      return LED_FUNCTION_UNSUPPORTED;
#endif /* LED_HAL_USE_P98X3 */
  }
  return LED_FUNCTION_UNSUPPORTED;
}

UnifiedLedType UnifiedLED::getType(void) {
  return _type;
}

ledFunctionReturnValue UnifiedLED::setLed(uint32_t ledNo, float brightness) {
  switch(_type){
#ifdef LED_HAL_USE_MY9221
    case LED_BAR:
    case LED_CIRCULAR:
      my9221->setLed(ledNo+1, brightness);
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_MY9221 */
    case SIMPLE_MONO_LED:
      if (ledNo ==0) {
        uint8_t ledValue;
        if (_led_mode == PULL_UP) {
          ledValue = brightness * 255;
        } else {
          ledValue = 255 - brightness * 255;
        }
        analogWrite(_pin1, ledValue);
        return LED_FUNCTION_SUCCESS;
      }
  }
  return LED_FUNCTION_UNSUPPORTED;
}

ledFunctionReturnValue UnifiedLED::setLed(float brightness) {
  switch(_type){
    case SIMPLE_MONO_LED:
      uint8_t ledValue;
      if (_led_mode == PULL_UP) {
        ledValue = brightness * 255;
      } else {
        ledValue = 255 - brightness * 255;
      }
      analogWrite(_pin1, ledValue);
      return LED_FUNCTION_SUCCESS;
  }
  return LED_FUNCTION_UNSUPPORTED;
}

ledFunctionReturnValue UnifiedLED::clear(void) {
  switch(_type){
    case SIMPLE_MONO_LED:
      setLed(0);
      return LED_FUNCTION_SUCCESS;
#ifdef LED_HAL_USE_MY9221
    case LED_BAR:
    case LED_CIRCULAR:
      setOnce(0);
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_MY9221 */
#ifdef LED_HAL_USE_P98X3
    case P98X3_LED:
      for (int i=0; i< _num_of_led; i++) {
        p98x3->setColorRGB(i, 0, 0, 0);
      }
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_P98X3 */
#ifdef LED_HAL_USE_NEO_PIXEL
    case NEO_PIXEL_LED:
      for (int i=0; i< _num_of_led; i++) {
        neoPixel->setPixelColor(i, 0, 0, 0);
      }
      neoPixel->show();
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_NEO_PIXEL */
    case SIMPLE_COLOR_LED:
      setLed(0,0,0);
      return LED_FUNCTION_SUCCESS;
  }
  return LED_FUNCTION_UNSUPPORTED;
}

ledFunctionReturnValue UnifiedLED::setLed(uint32_t ledNo, byte red, byte green, byte blue) {
  switch(_type){
#ifdef LED_HAL_USE_MY9221
    case LED_BAR:
    case LED_CIRCULAR:
      return LED_FUNCTION_UNSUPPORTED;
#endif /* LED_HAL_USE_MY9221 */
#ifdef LED_HAL_USE_P98X3
    case P98X3_LED:
      if (ledNo >= _num_of_led) return LED_FUNCTION_FAIL;
      p98x3->setColorRGB(ledNo, red, green, blue);
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_P98X3 */
#ifdef LED_HAL_USE_NEO_PIXEL
    case NEO_PIXEL_LED:
      if (ledNo >= _num_of_led) return LED_FUNCTION_FAIL;
      neoPixel->setPixelColor((uint16_t)ledNo, (uint8_t) red, (uint8_t) green, (uint8_t) blue);
      neoPixel->show();
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_NEO_PIXEL */
    case SIMPLE_COLOR_LED:
      if (ledNo ==0) {
        uint8_t r_level, g_level, b_level;
        if (_led_mode == PULL_UP) {
          r_level = red;
          g_level = green;
          b_level = blue;
        } else {
          r_level = 255 - red;
          g_level = 255 - green;
          b_level = 255 - blue;
        }
        analogWrite(_pin1, r_level);
        analogWrite(_pin2, green);
        analogWrite(_pin3, b_level);
        return LED_FUNCTION_SUCCESS;
      }
  }
  return LED_FUNCTION_UNSUPPORTED;
}

ledFunctionReturnValue UnifiedLED::setLed(byte red, byte green, byte blue) {
  switch(_type){
    case SIMPLE_COLOR_LED:
      uint8_t r_level, g_level, b_level;
      if (_led_mode == PULL_UP) {
        r_level = red;
        g_level = green;
        b_level = blue;
      } else {
        r_level = 255 - red;
        g_level = 255 - green;
        b_level = 255 - blue;
      }
      analogWrite(_pin1, r_level);
      analogWrite(_pin2, green);
      analogWrite(_pin3, b_level);
      return LED_FUNCTION_SUCCESS;
  }
  return LED_FUNCTION_UNSUPPORTED;
}

ledFunctionReturnValue UnifiedLED::setOnce(uint32_t value) {
  switch(_type){
#ifdef LED_HAL_USE_MY9221
    case LED_BAR:
    case LED_CIRCULAR:
      my9221->setBits(value);
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_MY9221 */
    case SIMPLE_MONO_LED:
      if ((value & 0b1)>0) {
        uint8_t ledValue;
        if (_led_mode == PULL_UP) {
          ledValue = value;
        } else {
          ledValue = 255 - value;
        }
        analogWrite(_pin1, ledValue);
        return LED_FUNCTION_SUCCESS;
      }
      return LED_FUNCTION_SUCCESS;
  }
  return LED_FUNCTION_UNSUPPORTED;
}

ledFunctionReturnValue UnifiedLED::setOnce(uint32_t value, byte red, byte green, byte blue) {
  switch(_type){
#ifdef LED_HAL_USE_MY9221
    case LED_BAR:
    case LED_CIRCULAR:
      return LED_FUNCTION_UNSUPPORTED;
#endif /* LED_HAL_USE_MY9221 */
#ifdef LED_HAL_USE_P98X3
    case P98X3_LED:
      //uint32_t tmp = value;
      //uint32_t mask = 0b1;
      for (int i=0; i<_num_of_led; i++ ) {
        if ((0b1 & value)>0) {
          p98x3->setColorRGB(i, red, green, blue);
        } else {
          p98x3->setColorRGB(i, 0, 0, 0);
        }
        value = value >> 1;
      };
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_P98X3 */
#ifdef LED_HAL_USE_NEO_PIXEL
    case NEO_PIXEL_LED:
      //uint32_t tmp2 = value;
      //uint32_t mask2 = 0b1;
      for (uint16_t i=0; i<_num_of_led; i++ ) {
        if ((0b1 & value)>0) {
          neoPixel->setPixelColor(i, red, green, blue);
        } else {
          neoPixel->setPixelColor(i, 0, 0, 0);
        }
        neoPixel->show();
        value = value >> 1;
      };
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_NEO_PIXEL */
    case SIMPLE_COLOR_LED:
      /*
      if ((value & 0b1)>0) {
        uint8_t r_level, g_level, b_level;
        if (_led_mode == PULL_UP) {
          r_level = red;
          g_level = green;
          b_level = blue;
        } else {
          r_level = 255 - red;
          g_level = 255 - green;
          b_level = 255 - blue;
        }
        analogWrite(_pin1, r_level);
        analogWrite(_pin2, g_level);
        analogWrite(_pin3, b_level);
        return LED_FUNCTION_SUCCESS;
      }
      return LED_FUNCTION_SUCCESS;
      */
      return LED_FUNCTION_UNSUPPORTED;
  }
  return LED_FUNCTION_UNSUPPORTED;
}

ledFunctionReturnValue UnifiedLED::begin() {
  switch(_type) {
#ifdef LED_HAL_USE_MY9221
    case LED_BAR:
      my9221->begin();
      return LED_FUNCTION_SUCCESS;
    case LED_CIRCULAR:
      my9221->begin();
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_MY9221 */
//#ifdef LED_HAL_USE_P98X3
//    case P98X3_LED:
//      p98x3->init();
//      return LED_FUNCTION_SUCCESS;
//#endif /* LED_HAL_USE_P98X3 */
#ifdef LED_HAL_USE_NEO_PIXEL
    case NEO_PIXEL_LED:
      neoPixel->begin();
      neoPixel->show();
      return LED_FUNCTION_SUCCESS;
#endif /* LED_HAL_USE_NEO_PIXEL */
    case SIMPLE_COLOR_LED:
      pinMode(_pin1,OUTPUT);
      pinMode(_pin2,OUTPUT);
      pinMode(_pin3,OUTPUT);
      if (_led_mode == PULL_DOWN) {
        analogWrite(_pin1, 255);
        analogWrite(_pin2, 255);
        analogWrite(_pin3, 255);
      }
      return LED_FUNCTION_SUCCESS;
    case SIMPLE_MONO_LED:
      pinMode(_pin1,OUTPUT);
      if (_led_mode == PULL_DOWN) {
        analogWrite(_pin1, 255);
      }
      return LED_FUNCTION_SUCCESS;
  }
  return LED_FUNCTION_UNSUPPORTED;
}
#endif /* USE_LED */