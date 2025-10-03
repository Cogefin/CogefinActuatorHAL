#include "UnifiedGraphicDisplay.h"

#ifdef USE_GRAPHIC_DISPLAY
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
UnifiedGraphicDisplay::UnifiedGraphicDisplay(GigaDisplay_GFX *tft, UnifiedDisplayType type):
  _tftGiga(tft),
  _type(type)
{}
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */

#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
UnifiedGraphicDisplay::UnifiedGraphicDisplay(TFT_eSPI *tft, UnifiedDisplayType type):
  _tft(tft),
  _type(type)
{}
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */

#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
UnifiedGraphicDisplay::UnifiedGraphicDisplay(Adafruit_ILI9341 *tft, UnifiedDisplayType type):
  _tftAda(tft),
  _type(type)
{}
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */

graphicFunctionReturnValue UnifiedGraphicDisplay::fillScreen(uint16_t color) {
  switch(_type) {
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
    case DISPLAY_TYPE_GIGA_DISPLAY_GFX: {
      _tftGiga->fillScreen(color);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
    case DISPLAY_TYPE_BODMER_TFT_ESPI: {
      _tft->fillScreen(color);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
    case DISPLAY_TYPE_ADAFRUIT_GFX: {
      _tftAda->fillScreen(color);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
  }
  return GFX_FUNCTION_UNSUPPORTED;
}

graphicFunctionReturnValue UnifiedGraphicDisplay::setTextColor(uint16_t fg, uint16_t bg) {
  switch(_type) {
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
    case DISPLAY_TYPE_GIGA_DISPLAY_GFX: {
      _tftGiga->setTextColor(fg, bg);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
    case DISPLAY_TYPE_BODMER_TFT_ESPI: {
      _tft->setTextColor(fg, bg);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
    case DISPLAY_TYPE_ADAFRUIT_GFX: {
      _tftAda->setTextColor(fg, bg);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
  }
  return GFX_FUNCTION_UNSUPPORTED;
}

graphicFunctionReturnValue UnifiedGraphicDisplay::setCursor(int16_t x, int16_t y){
  switch(_type) {
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
    case DISPLAY_TYPE_GIGA_DISPLAY_GFX: {
      _tftGiga->setCursor(x, y);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
    case DISPLAY_TYPE_BODMER_TFT_ESPI: {
      _tft->setCursor(x, y);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
    case DISPLAY_TYPE_ADAFRUIT_GFX: {
      _tftAda->setCursor(x, y);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
  }
  return GFX_FUNCTION_UNSUPPORTED;
}

graphicFunctionReturnValue UnifiedGraphicDisplay::setTextWrap(bool w) {
  switch(_type) {
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
    case DISPLAY_TYPE_GIGA_DISPLAY_GFX: {
      _tftGiga->setTextWrap(w);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
    case DISPLAY_TYPE_BODMER_TFT_ESPI: {
      _tft->setTextWrap(w);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
    case DISPLAY_TYPE_ADAFRUIT_GFX: {
      _tftAda->setTextWrap(w);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
  }
  return GFX_FUNCTION_UNSUPPORTED;
}

graphicFunctionReturnValue UnifiedGraphicDisplay::setTextSize(uint8_t s) {
  switch(_type) {
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
    case DISPLAY_TYPE_GIGA_DISPLAY_GFX: {
      _tftGiga->setTextSize(s);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
    case DISPLAY_TYPE_BODMER_TFT_ESPI: {
      _tft->setTextSize(s);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
    case DISPLAY_TYPE_ADAFRUIT_GFX: {
      _tftAda->setTextSize(s);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
  }
  return GFX_FUNCTION_UNSUPPORTED;
}

graphicFunctionReturnValue UnifiedGraphicDisplay::setTextSize(uint8_t x, uint8_t y) {
  switch(_type) {
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
    case DISPLAY_TYPE_GIGA_DISPLAY_GFX: {
      _tftGiga->setTextSize(x, y);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
    case DISPLAY_TYPE_BODMER_TFT_ESPI: {
      _tft->setTextSize(x, y);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
    case DISPLAY_TYPE_ADAFRUIT_GFX: {
      _tftAda->setTextSize(x, y);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
  }
  return GFX_FUNCTION_UNSUPPORTED;
}

graphicFunctionReturnValue UnifiedGraphicDisplay::setFont(const GFXfont *f) {
  switch(_type) {
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
    case DISPLAY_TYPE_GIGA_DISPLAY_GFX: {
      _tftGiga->setFont(f);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
    case DISPLAY_TYPE_BODMER_TFT_ESPI: {
      _tft->setFont(f);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
    case DISPLAY_TYPE_ADAFRUIT_GFX: {
      _tftAda->setFont(f);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
  }
  return GFX_FUNCTION_UNSUPPORTED;
}

graphicFunctionReturnValue UnifiedGraphicDisplay::drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h){
  switch(_type) {
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
    case DISPLAY_TYPE_GIGA_DISPLAY_GFX: {
      _tftGiga->drawRGBBitmap(x,y,bitmap,w,h);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
    case DISPLAY_TYPE_BODMER_TFT_ESPI: {
      _tft->drawRGBBitmap(x,y,bitmap,w,h);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
    case DISPLAY_TYPE_ADAFRUIT_GFX: {
      _tftAda->drawRGBBitmap(x,y,bitmap,w,h);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
  }
  return GFX_FUNCTION_UNSUPPORTED;
}

graphicFunctionReturnValue UnifiedGraphicDisplay::drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h) {
  switch(_type) {
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
    case DISPLAY_TYPE_GIGA_DISPLAY_GFX: {
      _tftGiga->drawRGBBitmap(x,y,bitmap,w,h);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
    case DISPLAY_TYPE_BODMER_TFT_ESPI: {
      _tft->drawRGBBitmap(x,y,bitmap,w,h);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
    case DISPLAY_TYPE_ADAFRUIT_GFX: {
      _tftAda->drawRGBBitmap(x,y,bitmap,w,h);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
  }
  return GFX_FUNCTION_UNSUPPORTED;
}

graphicFunctionReturnValue UnifiedGraphicDisplay::drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], const uint8_t mask[], int16_t w, int16_t h) {
  switch(_type) {
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
    case DISPLAY_TYPE_GIGA_DISPLAY_GFX: {
      _tftGiga->drawRGBBitmap(x,y,bitmap,mask,w,h);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
    case DISPLAY_TYPE_BODMER_TFT_ESPI: {
      _tft->drawRGBBitmap(x,y,bitmap,mask,w,h);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
    case DISPLAY_TYPE_ADAFRUIT_GFX: {
      _tftAda->drawRGBBitmap(x,y,bitmap,mask,w,h);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
  }
  return GFX_FUNCTION_UNSUPPORTED;
}

graphicFunctionReturnValue UnifiedGraphicDisplay::drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, uint8_t *mask, int16_t w, int16_t h){
  switch(_type) {
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
    case DISPLAY_TYPE_GIGA_DISPLAY_GFX: {
      _tftGiga->drawRGBBitmap(x,y,bitmap,mask,w,h);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
    case DISPLAY_TYPE_BODMER_TFT_ESPI: {
      _tft->drawRGBBitmap(x,y,bitmap,mask,w,h);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
    case DISPLAY_TYPE_ADAFRUIT_GFX: {
      _tftAda->drawRGBBitmap(x,y,bitmap,mask,w,h);
      return GFX_FUNCTION_SUCCESS;
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
  }
  return GFX_FUNCTION_UNSUPPORTED;
}

uint16_t UnifiedGraphicDisplay::width(void) {
  switch(_type) {
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
    case DISPLAY_TYPE_GIGA_DISPLAY_GFX: {
      return _tftGiga->width();
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
    case DISPLAY_TYPE_BODMER_TFT_ESPI: {
      return _tft->width();
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
    case DISPLAY_TYPE_ADAFRUIT_GFX: {
      return _tftAda->width();
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
  }
  return 0;
}

uint16_t UnifiedGraphicDisplay::height(void) {
  switch(_type) {
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
    case DISPLAY_TYPE_GIGA_DISPLAY_GFX: {
      return _tftGiga->height();
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
    case DISPLAY_TYPE_BODMER_TFT_ESPI: {
      return _tft->height();
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
    case DISPLAY_TYPE_ADAFRUIT_GFX: {
      return _tftAda->height();
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
  }
  return 0;
}

size_t UnifiedGraphicDisplay::write(uint8_t c) {
  switch(_type) {
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
    case DISPLAY_TYPE_GIGA_DISPLAY_GFX: {
      return _tftGiga->write(c);
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
    case DISPLAY_TYPE_BODMER_TFT_ESPI: {
      return _tft->write(c);
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
    case DISPLAY_TYPE_ADAFRUIT_GFX: {
      return _tftAda->write(c);
    }
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
  }
  return 0;
}
#endif /* USE_GRAPHIC_DISPLAY */