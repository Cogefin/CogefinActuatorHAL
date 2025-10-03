
#include "UnifiedCharacterDisplay.h"

#ifdef USE_CHARACTER_DISPLAY

#ifdef LCD_HAL_USE_GROVE
#ifdef __SAMD21G18A__
UnifiedLCD::UnifiedLCD(rgb_lcd* lcd, UnifiedLcdType type, arduino::TwoWire wire):
#else /*__SAMD21G18A__*/
UnifiedLCD::UnifiedLCD(rgb_lcd* lcd, UnifiedLcdType type, TwoWire wire):
#endif /* __SAMD21G18A__ */
  _lcd(lcd),
  _type(type),
  _i2c(wire)
{}
#endif /* LCD_HAL_USE_GROVE  */

#ifdef LCD_HAL_USE_ACM1602NI
#ifdef __AVR__
UnifiedLCD::UnifiedLCD(ACM1602NI* lcd, UnifiedLcdType type):
  _liquid_crystal_i2c(lcd),
  _type(type)
{}
#else /* __AVR__ */
#ifdef __SAMD21G18A__
UnifiedLCD::UnifiedLCD(ACM1602NI* lcd, UnifiedLcdType type, arduino::TwoWire wire):
#else /*__SAMD21G18A__*/
UnifiedLCD::UnifiedLCD(ACM1602NI* lcd, UnifiedLcdType type, TwoWire wire):
#endif /* __SAMD21G18A__ */
  _liquid_crystal_i2c(lcd),
  _type(type),
  _i2c(wire)
{}
#endif /* __AVR__ */
#endif /* LCD_HAL_USE_ACM1602NI */

#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
//#ifdef __AVR__
UnifiedLCD::UnifiedLCD(LiquidCrystal* lcd, UnifiedLcdType type):
  _liquid_crystal(lcd),
  _type(type)
{}
//#else /* __AVR__ */
//#ifdef __SAMD21G18A__
//UnifiedLCD::UnifiedLCD(LiquidCrystal* lcd, UnifiedLcdType type, arduino::TwoWire wire):
//#else /*__SAMD21G18A__*/
//UnifiedLCD::UnifiedLCD(LiquidCrystal* lcd, UnifiedLcdType type, TwoWire wire):
//#endif /* __SAMD21G18A__ */
//  _liquid_crystal(lcd),
//  _type(type),
//  _i2c(wire)
//{}
//#endif /* __AVR__ */
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */

lcdFunctionReturnValue UnifiedLCD::begin(uint8_t cols, uint8_t rows, uint8_t charsize) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->begin(cols, rows, charsize, _i2c);
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->begin(cols, rows);
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->begin(cols, rows, charsize);
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::clear(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->clear();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->clear();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->clear();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::home(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->home();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->home();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->home();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::setMode(UnifiedLcdMode mode) {
  switch(mode) {
    case NO_DISPLAY: return noDisplay();
    case ON_DISPLAY: return display();
    case NO_BLINK: return noBlink();
    case BLINK: return blink();
    case NO_CURSOR: return noCursor();
    case CURSOR: return cursor();
    case SCROLL_LEFT: return scrollDisplayLeft();
    case SCROLL_RIGHT: return scrollDisplayRight();
    case LEFT_TO_RIGHT: return leftToRight();
    case RIGHT_TO_LEFT: return rightToLeft();
    case AUTO_SCROLL: return autoscroll();
    case NO_AUTO_SCROLL: return noAutoscroll();
    case BLINK_BACKLIGHT: return blinkBacklight();
    case NO_BLINK_BACKLIGHT: return noBlinkBacklight();
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::noDisplay(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->noDisplay();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->noDisplay();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->noDisplay();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::display(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->display();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->display();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->display();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::noBlink(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->noBlink();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->noBlink();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->noBlink();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::blink(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->blink();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->blink();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->blink();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::noCursor(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->noCursor();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->noCursor();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->noCursor();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::cursor(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->cursor();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->cursor();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->cursor();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::scrollDisplayLeft(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->scrollDisplayLeft();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->scrollDisplayLeft();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->scrollDisplayLeft();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::scrollDisplayRight(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->scrollDisplayRight();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->scrollDisplayRight();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->scrollDisplayRight();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::leftToRight(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->leftToRight();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->leftToRight();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->leftToRight();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::rightToLeft(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->rightToLeft();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->rightToLeft();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->rightToLeft();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::autoscroll(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->autoscroll();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->autoscroll();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->autoscroll();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::noAutoscroll(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->noAutoscroll();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->noAutoscroll();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->noAutoscroll();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::createChar(uint8_t c, uint8_t data[]) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->createChar(c, data);
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->createChar(c, data);
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->createChar(c, data);
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::createCharFromProgmem(uint8_t c, const uint8_t * p) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->createCharFromProgmem(c, p);
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::setCursor(uint8_t col, uint8_t row) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->setCursor(col, row);
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->setCursor(col, row);
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->setCursor(col, row);
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

size_t UnifiedLCD::write(uint8_t value) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      return _lcd->write(value);
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      return _liquid_crystal_i2c->write(value);
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      return _liquid_crystal->write(value);
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return -1;
}

lcdFunctionReturnValue UnifiedLCD::command(uint8_t value) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->command(value);
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
#ifdef LCD_HAL_USE_ACM1602NI
    case ACM1602NI_TYPE:
      _liquid_crystal_i2c->command(value);
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_ACM1602NI */
#ifdef LCD_HAL_USE_LIQUID_CRYSTAL
    case LIQUID_CRYSTAL:
      _liquid_crystal->command(value);
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_LIQUID_CRYSTAL */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::setBacklightRGB(unsigned char r, unsigned char g, unsigned char b) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->setRGB(r, g, b);
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::blinkBacklight(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->blinkLED();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

lcdFunctionReturnValue UnifiedLCD::noBlinkBacklight(void) {
  switch(_type){
#ifdef LCD_HAL_USE_GROVE
    case GROVE_LCD_RGB_BACKLIGHT:
      _lcd->noBlinkLED();
      return LCD_FUNCTION_SUCCESS;
#endif /* LCD_HAL_USE_GROVE */
  }
  return LCD_FUNCTION_UNSUPPORTED;
}

#endif /* USE_CHARACTER_DISPLAY */

