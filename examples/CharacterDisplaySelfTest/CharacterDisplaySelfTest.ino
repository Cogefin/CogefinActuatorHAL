#if 0
#include "config.h"

#include "src/Syslog.h"

#include "ActuatorHAL.h"

#include "src/arduinoHardwareHelper.h"
#include "src/detectArduinoHardware.h"

#else
#include "ActuatorHAL.h"
#include <ArduinoJson.h>
#endif


/*
 * 行と列数の定義
 */
#ifdef USE_LIQUID_CRYSTAL
#ifdef USE_SC2004CSLB
#define LCD_MAX_ROW 4
#define LCD_MAX_COLS 20
#else /* USE_SC2004CSLB */
#define LCD_MAX_ROW 2
#define LCD_MAX_COLS 16
#endif /* USE_SC2004CSLB */
#else /* USE_LIQUID_CRYSTAL */
#define LCD_MAX_ROW 2
#define LCD_MAX_COLS 16
#endif /* USE_LIQUID_CRYSTAL */

HardwareHelper hwHelper;

#ifdef USE_GROVE_LCD
rgb_lcd grove_lcd;
UnifiedLCD lcd(&(grove_lcd), GROVE_LCD_RGB_BACKLIGHT, Wire);
const int colorR = 0;
const int colorG = 255;
const int colorB = 0;
int grove_lcd_num = 0;
int grove_lcd_type = CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT;
#endif /* USE_GROVE_LCD */

#ifdef USE_LIQUID_CRYSTAL
LiquidCrystal liquid_crystal_h(LIQUID_CRYSTAL_PIN_RS, LIQUID_CRYSTAL_PIN_ES, LIQUID_CRYSTAL_PIN_D4, LIQUID_CRYSTAL_PIN_D5, LIQUID_CRYSTAL_PIN_D6, LIQUID_CRYSTAL_PIN_D7);
UnifiedLCD liquid_crystal(&liquid_crystal_h, LIQUID_CRYSTAL);
int liquid_crystal_num = 0;
int liquid_crystal_type = CHARACTER_DISPLAY_TYPE_LIQUID_CRYSTAL;
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
ACM1602NI liquid_crystal_i2c_h;  // set the LCD address to 0x27 for a 16 chars and 2 line display
UnifiedLCD liquid_crystal_i2c(&liquid_crystal_i2c_h, ACM1602NI_TYPE);
int liquid_crystal_i2c_num = 0;
int liquid_crystal_i2c_type = CHARACTER_DISPLAY_TYPE_ACM1602NI;
#endif /* USE_ACM1602NI */

uint8_t deviceCounter=0;

#ifdef USE_GROVE
#define MAX_TEST 7
#else
#define MAX_TEST 6
#endif

struct testResultEntity {
  bool result;
  char about[BUFFER_SIZE];
  char comment[BUFFER_SIZE];
} testResult[MAX_TEST];


void home(void) {
  JsonDocument doc;

#ifdef USE_GROVE_LCD
  doc["id"] = grove_lcd_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT;
#endif /* USE_GROVE_LCD */
#ifdef USE_ACM1602NI
  doc["id"] = liquid_crystal_i2c_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_ACM1602NI;
#endif /* USE_ACM1602NI */
#ifdef USE_LIQUID_CRYSTAL
  doc["id"] = liquid_crystal_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_LIQUID_CRYSTAL;
#endif /* USE_LIQUID_CRYSTAL */
  doc["time"] = millis();
  doc["command"] = CHARACTER_DISPLAY_COMMAND_HOME;
  doc["paramSize"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec home() : fail");
  }
}

void clearDisplay(void){
  JsonDocument doc;

  home();

#ifdef USE_GROVE_LCD
  doc["id"] = grove_lcd_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT;
  doc["time"] = millis();
  doc["command"] = CHARACTER_DISPLAY_COMMAND_SET_BACKLIGHT_RGB;
  doc["paramSize"] = 1;
  doc["param"][0]["r"] = 255;
  doc["param"][0]["g"] = 255;
  doc["param"][0]["b"] = 255;
  if (false == controlActuator(doc)) {
    Serial.println("exec setBacklightRGB(255,255,255) : fail");
  }
#endif /* USE_GROVE_LCD */

#ifdef USE_GROVE_LCD
  doc["id"] = grove_lcd_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT;
#endif /* USE_GROVE_LCD */
#ifdef USE_ACM1602NI
  doc["id"] = liquid_crystal_i2c_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_ACM1602NI;
#endif /* USE_ACM1602NI */
#ifdef USE_LIQUID_CRYSTAL
  doc["id"] = liquid_crystal_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_LIQUID_CRYSTAL;
#endif /* USE_LIQUID_CRYSTAL */
  doc["time"] = millis();
  doc["command"] = CHARACTER_DISPLAY_COMMAND_CLEAR;
  doc["paramSize"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec clear() : fail");
  }
}

void setMode(UnifiedLcdMode mode){
  JsonDocument doc;
#ifdef USE_GROVE_LCD
  doc["id"] = grove_lcd_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT;
#endif /* USE_GROVE_LCD */
#ifdef USE_ACM1602NI
  doc["id"] = liquid_crystal_i2c_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_ACM1602NI;
#endif /* USE_ACM1602NI */
#ifdef USE_LIQUID_CRYSTAL
  doc["id"] = liquid_crystal_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_LIQUID_CRYSTAL;
#endif /* USE_LIQUID_CRYSTAL */
  doc["time"] = millis();
  doc["command"] = CHARACTER_DISPLAY_COMMAND_SET_MODE;
  doc["paramSize"] = 1;
  doc["param"][0]["mode"] = mode;
  if (false == controlActuator(doc)) {
    Serial.println("exec setMode() : fail");
  }
}

void setCursor(uint8_t x, uint8_t y){
  JsonDocument doc;
#ifdef USE_GROVE_LCD
  doc["id"] = grove_lcd_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT;
#endif /* USE_GROVE_LCD */
#ifdef USE_ACM1602NI
  doc["id"] = liquid_crystal_i2c_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_ACM1602NI;
#endif /* USE_ACM1602NI */
#ifdef USE_LIQUID_CRYSTAL
  doc["id"] = liquid_crystal_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_LIQUID_CRYSTAL;
#endif /* USE_LIQUID_CRYSTAL */
  doc["time"] = millis();
  doc["command"] = CHARACTER_DISPLAY_COMMAND_SET_CURSUR;
  doc["paramSize"] = 1;
  doc["param"][0]["x"] = x;
  doc["param"][0]["y"] = y;
  if (false == controlActuator(doc)) {
    Serial.println("exec setCursor() : fail");
  }
}

void setSize(uint8_t x, uint8_t y, uint8_t size){
  JsonDocument doc;
#ifdef USE_GROVE_LCD
  doc["id"] = grove_lcd_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT;
#endif /* USE_GROVE_LCD */
#ifdef USE_ACM1602NI
  doc["id"] = liquid_crystal_i2c_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_ACM1602NI;
#endif /* USE_ACM1602NI */
#ifdef USE_LIQUID_CRYSTAL
  doc["id"] = liquid_crystal_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_LIQUID_CRYSTAL;
#endif /* USE_LIQUID_CRYSTAL */
  doc["time"] = millis();
  doc["command"] = CHARACTER_DISPLAY_COMMAND_SET_SIZE;
  doc["paramSize"] = 1;
  doc["param"][0]["x"] = x;
  doc["param"][0]["y"] = y;
  doc["param"][0]["font"] = size;
  if (false == controlActuator(doc)) {
    Serial.println("exec setSize() : fail");
  }
}

void printText(const char * text) {
  JsonDocument doc;
#ifdef USE_GROVE_LCD
  doc["id"] = grove_lcd_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT;
#endif /* USE_GROVE_LCD */
#ifdef USE_ACM1602NI
  doc["id"] = liquid_crystal_i2c_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_ACM1602NI;
#endif /* USE_ACM1602NI */
#ifdef USE_LIQUID_CRYSTAL
  doc["id"] = liquid_crystal_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_LIQUID_CRYSTAL;
#endif /* USE_LIQUID_CRYSTAL */
  doc["time"] = millis();
  doc["command"] = CHARACTER_DISPLAY_COMMAND_PRINT;
  doc["paramSize"] = 1;
  doc["param"][0]["text"] = text;
  if (false == controlActuator(doc)) {
    Serial.println("exec print() : fail");
  }
}

#ifdef USE_GROVE_LCD
void setBacklightRGB(unsigned char r, unsigned char g, unsigned char b) {
  JsonDocument doc;

  doc["id"] = grove_lcd_num;
  doc["type"] = CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT;
  doc["time"] = millis();
  doc["command"] = CHARACTER_DISPLAY_COMMAND_SET_BACKLIGHT_RGB;
  doc["paramSize"] = 1;
  doc["param"][0]["r"] = r;
  doc["param"][0]["g"] = g;
  doc["param"][0]["b"] = b;
  if (false == controlActuator(doc)) {
    Serial.println("exec setBacklightRGB() : fail");
  }
}
#endif /* USE_GROVE_LCD */

void setup_character_display(void) {
  // set up the LCD's number of columns and rows:
#ifdef USE_GROVE_LCD
  lcd.begin(LCD_MAX_COLS, LCD_MAX_ROW);
  updateDeviceTable(deviceCounter, CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT, &lcd);

  //setSize(LCD_MAX_COLS, LCD_MAX_ROW, 0);
  grove_lcd_num = deviceCounter;
  deviceCounter++;
  
  Serial.print("Grove RGB backlight LCD : device No. ");Serial.println(grove_lcd_num);
#endif /* USE_GROVE_LCD */

#ifdef USE_LIQUID_CRYSTAL
  liquid_crystal.begin(LCD_MAX_COLS, LCD_MAX_ROW);
  updateDeviceTable(deviceCounter, CHARACTER_DISPLAY_TYPE_LIQUID_CRYSTAL, &liquid_crystal);

  //setSize(LCD_MAX_COLS, LCD_MAX_ROW, 0);

  liquid_crystal_num = deviceCounter;
  deviceCounter++;

  Serial.print("Liquid crystal LCD : device No. ");Serial.println(liquid_crystal_num);
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
  liquid_crystal_i2c.begin(LCD_MAX_COLS, LCD_MAX_ROW);
  updateDeviceTable(deviceCounter, CHARACTER_DISPLAY_TYPE_ACM1602NI, &liquid_crystal_i2c);

  //setSize(LCD_MAX_COLS, LCD_MAX_ROW, 0);

  liquid_crystal_i2c_num = deviceCounter;
  deviceCounter++;
  Serial.print("ACM1602NI LCD : device No. ");Serial.println(liquid_crystal_i2c_num);

#endif /* USE_ACM1602NI */
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

void test1() {
  String about = "test1";
  printStartMessage(about, 0);
  // テスト内容の説明
  Serial.println("=== 1st action ===");
  Serial.println("0");
  Serial.println("1");
  Serial.println("=== 2nd action ===");
  Serial.println("0123456789");
  Serial.println("1");
  Serial.println("=== 3rd action ===");
  Serial.println("0123456789");
  Serial.println("1  3");
  Serial.println("");
  clearDisplay();
  waitForStart();
  Serial.println("start : test1");

  // 1st action
  setCursor(0,0);
  printText("0");
  delay(1000);
  setCursor(0,1);
  printText("1");
  delay(3000);

  // 2nd action
  clearDisplay();
  for (int i=0; i<10;i++) {
    char buff[2];
    buff[0]=0;
    buff[1]=0;
    sprintf(buff,"%d",i);
    setCursor(i,0);
    printText(buff);
    delay(500);
  }
  setCursor(0,1);
  printText("1");
  delay(3000);

  // 3rd action
  clearDisplay();

  for (int i=0; i<10;i++) {
    char buff[2];
    buff[0]=0;
    buff[1]=0;
    sprintf(buff,"%d",i);
    setCursor(i,0);

    printText(buff);
    delay(500);
  }
  setCursor(0,1);

  printText("1");
  setCursor(3,1);
  printText("3");

  home();
  checkTestResult(about, 0);
  Serial.println("");
  Serial.println("");
}

void test2() {
  String about = "test2";
  printStartMessage(about, 1);
  // テスト内容の説明
  Serial.println("=== 1st action (5sec) ===");
  Serial.println("0123456789");
  Serial.println("0123456789");
  Serial.println("0123456789");
  Serial.println("0123456789");
  Serial.println("=== 2nd action (5sec) ===");
  Serial.println("switch off the lcd(NO_DISPLAY).");
  Serial.println("=== 3rd action ===");
  Serial.println("switch on the lcd(ON_DISPLAY).");
  Serial.println("");

  clearDisplay();
  waitForStart();
  Serial.println("start : test2");

  // 1st action
  for (int i=0; i<10;i++) {
    char buff[2];
    buff[0]=0;
    buff[1]=0;
    sprintf(buff,"%d",i);
    for (int j=0; j<LCD_MAX_ROW; j++) {
      setCursor(i,j);
      printText(buff);
    }
  }
  delay(5000);
  // 2nd action
  setMode(NO_DISPLAY);

  delay(5000);
  // 3rd action
  setMode(ON_DISPLAY);

  checkTestResult(about, 1);
  Serial.println("");
  Serial.println("");
}

void test3() {
  String about = "test3";
  printStartMessage(about, 2);
  // テスト内容の説明
  Serial.println("=== 1st action defult (5sec) ===");
  Serial.println("default");
  Serial.println("=== 2nd action BLINK (5sec) ===");
  Serial.println("blink");
  Serial.println("=== 3rd action CURSOR (5sec) ===");
  Serial.println("cursur");
  Serial.println("=== 4th action NO_CURSOR (5sec) ===");
  Serial.println("no cursor");
  Serial.println("=== 5th action NO_BLINK (5sec) ===");
  Serial.println("no blink");
  Serial.println("");

  clearDisplay();
  waitForStart();
  Serial.println("start : test3");

  // 1st action normal
  clearDisplay();
  printText("default");
  delay(5000);
  // 2nd action
  clearDisplay();
  setMode(BLINK);

  printText("blink");
  delay(5000);
  clearDisplay();
  setMode(CURSOR);

  printText("cursor");
  delay(5000);
  clearDisplay();
  setMode(NO_CURSOR);

  printText("no cursor");
  delay(5000);
  clearDisplay();
  setMode(NO_BLINK);
  printText("no blink");

  checkTestResult(about, 2);
  Serial.println("");
  Serial.println("");

  // 復旧
  clearDisplay();
}

void test4() {
  String about = "test4";
  printStartMessage(about, 3);
  // テスト内容の説明
  Serial.println("=== 1st action ===");
  Serial.println("0123456789");
  Serial.println("0123456789");
  Serial.println("0123456789");
  Serial.println("0123456789");
  Serial.println("=== 2nd action ===");
  Serial.println("scroll left (SCROLL_LEFT) 4times.");
  Serial.println("=== 3rd action ===");
  Serial.println("scroll right (SCROLL_RIGHT) 4times.");
  Serial.println("");

  clearDisplay();
  waitForStart();
  Serial.println("start : test4");

  // 1st action
  for (int i=0; i<10;i++) {
    char buff[2];
    buff[0]=0;
    buff[1]=0;
    sprintf(buff,"%d",i);
    for (int j=0; j<LCD_MAX_ROW; j++) {
      setCursor(i,j);
      printText(buff);
    }
  }
  delay(5000);
  // 2nd action
  for (int i=0; i<4; i++) {
    setMode(SCROLL_LEFT);
    delay(2000);
  }
  delay(5000);
  // 2nd action
  for (int i=0; i<4; i++) {
    setMode(SCROLL_RIGHT);
    delay(2000);
  }

  checkTestResult(about, 3);
  Serial.println("");
  Serial.println("");

}

void test5() {
  String about = "test5";
  printStartMessage(about, 4);
  // テスト内容の説明
  Serial.println("=== action ===");
  Serial.println("      Hello (left to right)");
  Serial.println("      olleH (right to left)");
  Serial.println("");

  clearDisplay();
  waitForStart();
  Serial.println("start : test5");

  // 1st action
  setCursor(6,0);
  setMode(LEFT_TO_RIGHT);
  printText("Hello");

  delay(5000);

  setCursor(6,1);
  setMode(RIGHT_TO_LEFT);
  printText("Hello");

  checkTestResult(about, 4);
  Serial.println("");
  Serial.println("");

  // 復旧
  clearDisplay();
  setMode(LEFT_TO_RIGHT);
}

void test6() {
  String about = "test6";
  printStartMessage(about, 5);
  // テスト内容の説明
  Serial.println("=== 1st action ===");
  Serial.println("No auto scroll");
  Serial.println("012345678901234......");
  Serial.println("=== 2nd action ===");
  Serial.println("auto scroll");
  Serial.println("012345678901234......");
  Serial.println("");

  clearDisplay();
  waitForStart();
  Serial.println("start : test6");

  // 1st action
  printText("No auto scroll");
  setMode(NO_AUTO_SCROLL);
  setCursor(0,1);

  for (int i=0; i<LCD_MAX_COLS*2; i++) {
    char buff[2]={0,0};
    int val = i%10;
    sprintf(buff,"%d",val);
    printText(buff);
    delay(1000);
  }

  // 2nd action
  clearDisplay();
  printText("Auto scroll");
  setCursor(0,1);

  int counter = 0;
  for (int i=0; i<LCD_MAX_COLS; i++) {
    counter = i;
    char buff[2]={0,0};
    int val = i%10;
    sprintf(buff,"%d",val);
    printText(buff);
    delay(1000);
  }
  setMode(AUTO_SCROLL);
  for (int i=counter+1; i<LCD_MAX_COLS*2; i++) {
    char buff[2]={0,0};
    int val = i%10;
    sprintf(buff,"%d",val);
    printText(buff);
    delay(1000);
  }

  checkTestResult(about, 5);
  Serial.println("");
  Serial.println("");

  // 復旧
  clearDisplay();
  setCursor(0,0);

}


#ifdef USE_GROVE
void test7() {
  String about = "test7";
  printStartMessage(about, 6);
  // テスト内容の説明
  Serial.println("=== action ===");
  Serial.println("change backlight color of LED :");
  Serial.println("red, green, blue, yellow, purple, light blue, white (5sec each)");
  Serial.println("");

  clearDisplay();
  waitForStart();
  Serial.println("start : test7");

  // 1st action
  setBacklightRGB(255,0,0);
  delay(5000);
  setBacklightRGB(0,255,0);
  delay(5000);
  setBacklightRGB(0,0,255);
  delay(5000);
  setBacklightRGB(255,255,0);
  delay(5000);
  setBacklightRGB(255,0,255);
  delay(5000);
  setBacklightRGB(0,255,255);
  delay(5000);
  setBacklightRGB(255,255,255);

  checkTestResult(about, 6);
  Serial.println("");
  Serial.println("");

  // 復旧
  setBacklightRGB(0,0,0);

}
#endif /* USE_GROVE */

void setup() {
  Serial.begin(9600);

  if (SERIAL_RESET) {
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB
    }
  } else {
    delay(3000);
  }

  setup_character_display();

  Serial.println("");
  Serial.println("");
  Serial.println("device and device driver test of character LCD.");

  clearDisplay();
  test1();
  clearDisplay();
  test2();
  clearDisplay();
  test3();
  clearDisplay();
  test4();
  clearDisplay();
  test5();
  clearDisplay();
  test6();
  clearDisplay();
#ifdef USE_GROVE
  test7();
#endif /* USE_GROVE */
  sumTestResult();

}

void loop() {
}




#ifdef USE_GROVE_LCD
#endif /* USE_GROVE_LCD */

#ifdef USE_ACM1602NI
#endif /* USE_ACM1602NI */

#ifdef USE_SC1602BSLB
#endif /* USE_SC1602BSLB */

#ifdef USE_SC2004CSLB
#endif /* USE_SC2004CSLB */

#ifdef USE_LIQUID_CRYSTAL
#endif /* USE_LIQUID_CRYSTAL */








