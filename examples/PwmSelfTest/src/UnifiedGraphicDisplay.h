#ifndef __UNIFIED_GRAPHIC_DISPLAY_H__
#define __UNIFIED_GRAPHIC_DISPLAY_H__

#include "Arduino.h"
#include "../config.h"

#ifdef USE_GRAPHIC_DISPLAY

#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
#include "Arduino_GigaDisplay_GFX.h"
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */

#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
#include "SPI.h"
#include <TFT_eSPI.h>              // Hardware-specific library
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */

#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */

#ifndef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
#define TFT_BLACK       0x0000      /*   0,   0,   0 */
#define TFT_NAVY        0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TFT_MAROON      0x7800      /* 128,   0,   0 */
#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGREY   0xD69A      /* 211, 211, 211 */
#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define TFT_BLUE        0x001F      /*   0,   0, 255 */
#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
#define TFT_RED         0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
#define TFT_ORANGE      0xFDA0      /* 255, 180,   0 */
#define TFT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
#define TFT_PINK        0xFE19      /* 255, 192, 203 */ //Lighter pink, was 0xFC9F
#define TFT_BROWN       0x9A60      /* 150,  75,   0 */
#define TFT_GOLD        0xFEA0      /* 255, 215,   0 */
#define TFT_SILVER      0xC618      /* 192, 192, 192 */
#define TFT_SKYBLUE     0x867D      /* 135, 206, 235 */
#define TFT_VIOLET      0x915C      /* 180,  46, 226 */
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */

#include <TJpg_Decoder.h>

typedef enum {
  DISPLAY_TYPE_GIGA_DISPLAY_GFX =1,
  DISPLAY_TYPE_ADAFRUIT_GFX,
  DISPLAY_TYPE_BODMER_TFT_ESPI
} UnifiedDisplayType;

typedef enum {
  GFX_FUNCTION_UNSUPPORTED = 1,
  GFX_FUNCTION_SUCCESS,
  GFX_FUNCTION_FAIL,
} graphicFunctionReturnValue;

//class UnifiedGraphicDisplay  {
class UnifiedGraphicDisplay : public Print {
public:
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
  UnifiedGraphicDisplay(GigaDisplay_GFX *tft, UnifiedDisplayType type);
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
  UnifiedGraphicDisplay(TFT_eSPI *tft, UnifiedDisplayType type);
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
  UnifiedGraphicDisplay(Adafruit_ILI9341 *tft, UnifiedDisplayType type);
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
  graphicFunctionReturnValue fillScreen(uint16_t color);
  graphicFunctionReturnValue setTextColor(uint16_t fg, uint16_t bg);
  graphicFunctionReturnValue setCursor(int16_t x, int16_t y);
  graphicFunctionReturnValue setTextWrap(bool w);
  graphicFunctionReturnValue setTextSize(uint8_t s);
  graphicFunctionReturnValue setTextSize(uint8_t sx, uint8_t sy);
  graphicFunctionReturnValue setFont(const GFXfont *f=NULL);
  graphicFunctionReturnValue drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h);
  graphicFunctionReturnValue drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h);
  graphicFunctionReturnValue drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], const uint8_t mask[], int16_t w, int16_t h);
  graphicFunctionReturnValue drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, uint8_t *mask, int16_t w, int16_t h);
  uint16_t width(void);
  uint16_t height(void);
  size_t write(uint8_t c);

private:
  UnifiedDisplayType _type;
#ifdef GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX
  GigaDisplay_GFX *_tftGiga;
#endif /* GRAPHIC_DISPLAY_HAL_USE_GIGA_DISPLAY_GFX */
#ifdef GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI
  TFT_eSPI *_tft;
#endif /* GRAPHIC_DISPLAY_HAL_USE_BODMER_TFT_ESPI */
#ifdef GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX
  Adafruit_ILI9341 *_tftAda;
#endif /* GRAPHIC_DISPLAY_HAL_USE_ADAFRUIT_GFX */
};


#endif /* USE_GRAPHIC_DISPLAY */

#endif /* __UNIFIED_GRAPHIC_DISPLAY_H__ */



