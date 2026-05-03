#ifndef __UNIFIED_CHARACTER_DISPLAY_H__
#define __UNIFIED_CHARACTER_DISPLAY_H__

#include "Arduino.h"
#include "../config.h"

#ifdef USE_CHARACTER_DISPLAY


#ifdef LCD_HAL_USE_GROVE
#include <Wire.h>
#include "rgb_lcd.h"
#endif /* LCD_HAL_USE_GROVE */

#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
#ifndef __AVR__
#include <Wire.h>
#endif /* __AVR__ */
#include "LiquidCrystal.h"
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */

#ifdef LCD_HAL_USE_ACM1602NI
#include <Wire.h>
#include "ACM1602NI.h"
#endif /* LCD_HAL_USE_ACM1602NI */


typedef enum {
  GROVE_LCD_RGB_BACKLIGHT =1, // https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight/
  LIQUID_CRYSTAL,             // LiquidCrystal Library for Arduino https://github.com/arduino-libraries/LiquidCrystal
  ACM1602NI_TYPE              // https://github.com/furushei/ACM1602NI-Arduino
} UnifiedLcdType;

typedef enum {
  NO_DISPLAY = 1 ,
  ON_DISPLAY,
  NO_BLINK,
  BLINK,
  NO_CURSOR,
  CURSOR,
  SCROLL_LEFT,
  SCROLL_RIGHT,
  LEFT_TO_RIGHT,
  RIGHT_TO_LEFT,
  AUTO_SCROLL,
  NO_AUTO_SCROLL,
  BLINK_BACKLIGHT,
  NO_BLINK_BACKLIGHT
} UnifiedLcdMode;

typedef enum {
  LCD_FUNCTION_UNSUPPORTED = 1,
  LCD_FUNCTION_SUCCESS,
  LCD_FUNCTION_FAIL,
} lcdFunctionReturnValue;

class UnifiedLCD : public Print {
public:
#ifdef LCD_HAL_USE_GROVE
#ifdef __SAMD21G18A__
  UnifiedLCD(rgb_lcd* lcd, UnifiedLcdType type, arduino::TwoWire  wire);
#else /*__SAMD21G18A__*/
  UnifiedLCD(rgb_lcd* lcd, UnifiedLcdType type, TwoWire  wire);
#endif /* __SAMD21G18A__ */
#endif /* LCD_HAL_USE_GROVE  */

#ifdef LCD_HAL_USE_ACM1602NI
#ifdef __AVR__
  UnifiedLCD(ACM1602NI * lcd, UnifiedLcdType type);
#else /* __AVR__ */
#ifdef __SAMD21G18A__
  UnifiedLCD(ACM1602NI * lcd, UnifiedLcdType type, arduino::TwoWire  wire=Wire);
#else /*__SAMD21G18A__*/
  UnifiedLCD(ACM1602NI * lcd, UnifiedLcdType type, TwoWire  wire=Wire);
#endif /* __SAMD21G18A__ */
#endif /* __AVR__ */
#endif /* LCD_HAL_USE_ACM1602NI */

#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
//#ifdef __AVR__
  UnifiedLCD(LiquidCrystal* lcd, UnifiedLcdType type);
//#else /* __AVR__ */
//#ifdef __SAMD21G18A__
//  UnifiedLCD(LiquidCrystal* lcd, UnifiedLcdType type, arduino::TwoWire  wire=Wire);
//#else /*__SAMD21G18A__*/
//  UnifiedLCD(LiquidCrystal* lcd, UnifiedLcdType type, TwoWire  wire=Wire);
//#endif /* __SAMD21G18A__ */
//#endif /* __AVR__ */
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */

#if defined(LCD_HAL_USE_GROVE) || defined(LCD_HAL_USE_LIQUID_CRYSTAL)
  lcdFunctionReturnValue begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
#else /* LCD_HAL_USE_GROVE || LCD_HAL_USE_LIQUID_CRYSTAL */
  lcdFunctionReturnValue begin(uint8_t cols, uint8_t rows, uint8_t charsize = 0);
#endif /* LCD_HAL_USE_GROVE || LCD_HAL_USE_LIQUID_CRYSTAL */

  lcdFunctionReturnValue clear(void);
  lcdFunctionReturnValue home(void);
  lcdFunctionReturnValue setMode(UnifiedLcdMode mode);
  lcdFunctionReturnValue createChar(uint8_t, uint8_t[]);
  lcdFunctionReturnValue createCharFromProgmem(uint8_t, const uint8_t *);
  lcdFunctionReturnValue setCursor(uint8_t, uint8_t);
  size_t write(uint8_t);
  lcdFunctionReturnValue command(uint8_t);
  //lcdFunctionReturnValue setBrightness(uint8_t = 2, uint8_t = 0x40, uint8_t = 0xc0); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  // color control
  lcdFunctionReturnValue setBacklightRGB(unsigned char r, unsigned char g, unsigned char b); // set rgb


private:
  lcdFunctionReturnValue noDisplay(void);
  lcdFunctionReturnValue display(void);
  lcdFunctionReturnValue noBlink(void);
  lcdFunctionReturnValue blink(void);
  lcdFunctionReturnValue noCursor(void);
  lcdFunctionReturnValue cursor(void);
  lcdFunctionReturnValue scrollDisplayLeft(void);
  lcdFunctionReturnValue scrollDisplayRight(void);
  lcdFunctionReturnValue leftToRight(void);
  lcdFunctionReturnValue rightToLeft(void);
  lcdFunctionReturnValue autoscroll(void);
  lcdFunctionReturnValue noAutoscroll(void);
  // blink the LED backlight
  lcdFunctionReturnValue blinkBacklight(void);
  lcdFunctionReturnValue noBlinkBacklight(void);
#if defined(LCD_HAL_USE_GROVE) || defined(LCD_HAL_USE_ACM1602NI)
#ifdef __SAMD21G18A__
  arduino::TwoWire  _i2c;
#else /* __SAMD21G18A__ */
  TwoWire  _i2c;
#endif /* __SAMD21G18A__ */
#endif /* LCD_HAL_USE_GROVE || LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_GROVE
  rgb_lcd* _lcd;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
  ACM1602NI* _liquid_crystal_i2c;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
  LiquidCrystal* _liquid_crystal;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  UnifiedLcdType _type;
};

#endif /* USE_CHARACTER_DISPLAY */


#endif /* __UNIFIED_CHARACTER_DISPLAY_H__ */

