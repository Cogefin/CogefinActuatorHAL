
#include "ActuatorHAL.h"
#include <ArduinoJson.h>

#include <SD.h>

HardwareHelper hwHelper;

#ifdef USE_GIGA_DISPLAY_GFX
#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT  800

GigaDisplay_GFX tft; // create the object

UnifiedGraphicDisplay display = UnifiedGraphicDisplay(&tft,DISPLAY_TYPE_GIGA_DISPLAY_GFX);
#define DISPLAY_TYPE GRAPHIC_DISPLAY_TYPE_GIGA_DISPLAY
#endif /* USE_GIGA_DISPLAY_GFX */

#ifdef USE_BODMER_TFT_ESPI
#define DISPLAY_WIDTH
#define DISPLAY_HEIGHT

TFT_eSPI tft = TFT_eSPI();

UnifiedGraphicDisplay display = UnifiedGraphicDisplay(&tft,DISPLAY_TYPE_BODMER_TFT_ESPI);
#define DISPLAY_TYPE GRAPHIC_DISPLAY_TYPE_BODMER_TFT
#endif /* USE_BODMER_TFT_ESPI */

#ifdef USE_ADAFRUIT_GFX
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT  320

#ifdef TFT_ILI9341_TYPE_1
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_ILI9341_PIN_CS, TFT_ILI9341_PIN_DC, TFT_ILI9341_PIN_RST);
#endif /* TFT_ILI9341_TYPE_1 */
#ifdef TFT_ILI9341_TYPE_2
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_ILI9341_PIN_CS, TFT_ILI9341_PIN_DC, TFT_ILI9341_PIN_MOSI, TFT_ILI9341_PIN_CLK, TFT_ILI9341_PIN_RST, TFT_ILI9341_PIN_MISO);
#endif /* TFT_ILI9341_TYPE_2 */

UnifiedGraphicDisplay display = UnifiedGraphicDisplay(&tft,DISPLAY_TYPE_ADAFRUIT_GFX);
#define DISPLAY_TYPE GRAPHIC_DISPLAY_TYPE_ADAFRUIT_GFX
#endif /* USE_ADAFRUIT_GFX */

uint8_t deviceCounter=0;
uint8_t graphic_display_num=0;

#define MAX_TEST 3

struct testResultEntity {
  bool result;
  char about[BUFFER_SIZE];
  char comment[BUFFER_SIZE];
} testResult[MAX_TEST];

void graphic_fill(uint16_t color) {
  JsonDocument doc;
  doc["id"] = graphic_display_num;
  doc["type"] = DISPLAY_TYPE;
  doc["time"] = millis();
  doc["command"] = GRAPHIC_DISPLAY_COMMAND_FILL;
  doc["paramSize"] = 1;
  doc["param"][0]["color"] = color;
  if (false == controlActuator(doc)) {
    Serial.println("exec fill() : fail");
  }
}

void graphic_printString(uint16_t x, uint16_t y, uint16_t foreground, uint16_t background, uint8_t size, uint8_t wrap, char * text) {
  JsonDocument doc;
  doc["id"] = graphic_display_num;
  doc["type"] = DISPLAY_TYPE;
  doc["time"] = millis();
  doc["command"] = GRAPHIC_DISPLAY_COMMAND_STRING;
  doc["paramSize"] = 1;
  doc["param"][0]["x"] = x;
  doc["param"][0]["y"] = y;
  doc["param"][0]["fg"] = foreground;
  doc["param"][0]["bg"] = background;
  doc["param"][0]["size"] = size;
  doc["param"][0]["wrap"] = wrap;
  doc["param"][0]["text"] = text;
  if (false == controlActuator(doc)) {
    Serial.println("exec printString() : fail");
  }
}

void graphic_image(uint16_t x, uint16_t y, const char * filename) {
  JsonDocument doc;
  doc["id"] = graphic_display_num;
  doc["type"] = DISPLAY_TYPE;
  doc["time"] = millis();
  doc["command"] = GRAPHIC_DISPLAY_COMMAND_IMAGE;
  doc["paramSize"] = 1;
  doc["param"][0]["x"] = x;
  doc["param"][0]["y"] = y;
  doc["param"][0]["filename"] = filename;
  if (false == controlActuator(doc)) {
    Serial.println("exec printImage() : fail");
  }
}

enum functionList {
  FUNCTION_FILL_SCREEN = 0,
  FUNCTION_SET_TEXT_COLOR,
  FUNCTION_SET_CURSOR,
  FUNCTION_SET_TEXT_WRAP,
  FUNCTION_SET_TEXT_SIZE,
  FUNCTION_SET_FONT,
  FUNCTION_DRAW_RGB_BITMAP
};

String functionName[7] = {
  "fillScreen()",
  "setTextColor()",
  "setCursor()",
  "setTextWrap()",
  "setTextSize()",
  "setFont()",
  "drawRGBBitmap()"
};

void checkReturnValue(graphicFunctionReturnValue val, uint8_t funcType) {
  char buff[BUFFER_SIZE];
  memset(buff,0,BUFFER_SIZE);
  if (val == GFX_FUNCTION_UNSUPPORTED) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is unsupported.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
  if (val == GFX_FUNCTION_FAIL) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is failed.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
}

#ifdef USE_GRAPHIC_DISPLAY
bool display_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
  if ( y >= display.height() ) return 0;

#ifdef USE_BODMER_TFT_ESPI
  // This function will clip the image block rendering automatically at the TFT boundaries
  display.pushImage(x, y, w, h, bitmap);
#else /* USE_BODMER_TFT_ESPI */
  display.drawRGBBitmap(x, y, bitmap, w, h);
#endif /* USE_BODMER_TFT_ESPI */

  // Return 1 to decode next block
  return 1;
}
#endif /* USE_GRAPHIC_DISPLAY */

void setup_display(void) {

  Serial.println("");
  Serial.println("");
  Serial.println("device and device driver test of graphic display device.");

  // Initialise SD before TFT
  //if (!SD.begin(SD_CS_PIN)) {
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println(F("SD.begin failed!"));
    while (1) delay(0);
  }

  tft.begin();
  display.setTextColor(0xFFFF, 0x0000);
  display.fillScreen(TFT_BLACK);
#ifdef USE_BODMER_TFT_ESPI
  display.setSwapBytes(true); // We need to swap the colour bytes (endianess)
#endif /* USE_BODMER_TFT_ESPI */

  // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
  TJpgDec.setJpgScale(1);

  // The decoder must be given the exact name of the rendering function above
  TJpgDec.setCallback(display_output);

  updateDeviceTable(deviceCounter, DISPLAY_TYPE, &display);
  graphic_display_num = deviceCounter;
  deviceCounter++;
  Serial.print("graphic display : device No. ");Serial.println(graphic_display_num);
}


void printStartMessage(String about, uint8_t testNumber){
  char message[BUFFER_SIZE];
  for (int i=0; i<BUFFER_SIZE ; i++ ){
    message[i]=0;
  }
  sprintf(message,"Wait for start test No.%d (%s)",testNumber+1, about.c_str());
  Serial.println(message);
}

void waitForStart(void){
  while (true) {
    if (Serial.available()) {
      char input = Serial.read();
    } else {
      break;
    }
  }
  Serial.print("Please press Enter key to start test : ");
  while (true) {
    if (Serial.available()) {
      String input = Serial.readStringUntil('\n');  // Read until newline
      if (0==input.compareTo("")) {
        Serial.println("");
        break;
      } else {
        Serial.println("");
        Serial.println("Please press **Enter key Only** to start test : ");
      }
    }
  }
}

void checkTestResult(String about, uint8_t testNumber){
  char message[BUFFER_SIZE];
  for (int i=0; i<BUFFER_SIZE ; i++ ){
    message[i]=0;
    testResult[testNumber].about[i]=0;
    testResult[testNumber].comment[i]=0;
  }
  sprintf(message,"Please input the failure of test No.%d (%s), if the test is succeeded, press Enter only : ",testNumber+1, about.c_str());
  sprintf(testResult[testNumber].about,"%s", about.c_str());
  testResult[testNumber].result = true;
  Serial.print(message);
  int count =0;
  while (true) {
    if (Serial.available() > 0) {
      char input = Serial.read();
      if ((input != -1) && (input != '\n')) {
        testResult[testNumber].comment[count]=input;
        testResult[testNumber].result = false;
        count++;
        Serial.print(input);
      }
      if ((count == BUFFER_SIZE-2) || (input == '\n')) break;
    }
  }
  Serial.println("");
}

void sumTestResult(void){
  int count = 0;
  Serial.println("======== summary of tests ========");
  for (int i=0 ; i<MAX_TEST ; i++ ) {
    char message[BUFFER_SIZE];
    for (int i=0; i<BUFFER_SIZE; i++) {
      message[i]=0;
    }
    if (testResult[i].result) {
      sprintf(message,"Test result of test No.%d (%s) : Success.",i+1, testResult[i].about);
    } else {
      count++;
      sprintf(message,"Test result of test No.%d (%s) : %s",i+1, testResult[i].about, testResult[i].comment);
    }
    Serial.println(message);
  }
  Serial.println("");
  char finalMessage[BUFFER_SIZE];
  for (int i=0; i<BUFFER_SIZE; i++) {
    finalMessage[i]=0;
  }
  sprintf(finalMessage, "Test result : all(%d) , success(%d) , fail(%d)", MAX_TEST, MAX_TEST-count, count);
  Serial.println(finalMessage);
  Serial.println("");
}

#define COLOR16BIT_WHITE  0xffff
#define COLOR16BIT_GRAY   0x8410
#define COLOR16BIT_BLACK  0x0
#define COLOR16BIT_RED    0xf800
#define COLOR16BIT_GREEN  0x07e0
#define COLOR16BIT_BLUE   0x001f

void test1() {
  String about = "test1";
  printStartMessage(about, 0);
  // テスト内容の説明
  Serial.println("=== action ===");
  Serial.println("paint with color: white, gray, red, green, blue, black");
  Serial.println("");
  waitForStart();

  uint16_t colors[6] = {COLOR16BIT_WHITE, COLOR16BIT_GRAY, COLOR16BIT_RED, COLOR16BIT_GREEN, COLOR16BIT_BLUE, COLOR16BIT_BLACK};
  for (int i=0; i<6; i++) {
    graphic_fill(colors[i]);
    delay(3000);
  }

  checkTestResult(about, 0);
  Serial.println("");
  Serial.println("");

}

#define TEXT_SIZE_BASE 20

void test2() {
  String about = "test2";
  printStartMessage(about, 1);
  // テスト内容の説明
  Serial.println("=== action ===");
  Serial.println(" |0123456789");
  Serial.println("0|1   2   3 | black/white ,   red/gray  , blue/red");
  Serial.println("1|  4   5   | black/blue  ,   red/green");
  Serial.println("2|    6   7 | green/gray  , white/black");
  Serial.println("");
  waitForStart();
  Serial.println("start : test2");

  char text[]={0,0};
  text[0]='1';
  graphic_printString(0,0, COLOR16BIT_BLACK,COLOR16BIT_WHITE, 2 ,0, text);
  text[0]='2';
  graphic_printString(4*TEXT_SIZE_BASE,0, COLOR16BIT_RED,COLOR16BIT_GRAY, 2 ,0, text);
  text[0]='3';
  graphic_printString(8*TEXT_SIZE_BASE,0, COLOR16BIT_BLUE,COLOR16BIT_RED, 2 ,0, text);

  text[0]='4';
  graphic_printString(3*TEXT_SIZE_BASE,2*TEXT_SIZE_BASE, COLOR16BIT_BLACK,COLOR16BIT_BLUE, 3 ,0, text);
  text[0]='5';
  graphic_printString(6*TEXT_SIZE_BASE,2*TEXT_SIZE_BASE, COLOR16BIT_RED,COLOR16BIT_GREEN, 3 ,0, text);

  text[0]='6';
  graphic_printString(4*TEXT_SIZE_BASE,4*TEXT_SIZE_BASE, COLOR16BIT_GREEN,COLOR16BIT_GRAY, 4 ,0, text);
  text[0]='7';
  graphic_printString(8*TEXT_SIZE_BASE,4*TEXT_SIZE_BASE, COLOR16BIT_WHITE,COLOR16BIT_BLACK, 4 ,0, text);

  checkTestResult(about, 1);
  Serial.println("");
  Serial.println("");

  graphic_fill(COLOR16BIT_BLACK);

}


void test3() {
  String about = "test3";
  printStartMessage(about, 2);
  // テスト内容の説明
  Serial.println("=== action ===");
  Serial.println("display image file");
  Serial.println("");
  Serial.println("");
  waitForStart();
  Serial.println("start : test3");

  graphic_image(50, 50, "/panda.jpg");
  //graphic_image(0, 0, "/panda.jpg");

  checkTestResult(about, 2);
  Serial.println("");
  Serial.println("");


  graphic_fill(COLOR16BIT_BLACK);

}


void setup() {
  Serial.begin(9600);

  if (SERIAL_RESET) {
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB
    }
  } else {
    delay(3000);
  }

  setup_display();


  test1();
  test2();
  test3();
  sumTestResult();

}

void loop() {
}








