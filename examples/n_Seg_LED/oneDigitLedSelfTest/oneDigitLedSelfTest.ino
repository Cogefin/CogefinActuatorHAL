
#include "ActuatorHAL.h"
#include <ArduinoJson.h>

HardwareHelper hwHelper;

#ifdef USE_OSL12306_16
#define OSL12306_16_NUM_OF_PINS _OSL12306_16_CHAR_PINS
#define DIGITS OSL12306_16_NUM_OF_DIGITS

uint8_t pins[OSL12306_16_NUM_OF_PINS] = {
  OSL12306_16_PIN_A1 , OSL12306_16_PIN_A2 , OSL12306_16_PIN_B , OSL12306_16_PIN_C , OSL12306_16_PIN_D1 , OSL12306_16_PIN_D2 , OSL12306_16_PIN_E , OSL12306_16_PIN_F , 
  OSL12306_16_PIN_G1 , OSL12306_16_PIN_G2 , OSL12306_16_PIN_J , OSL12306_16_PIN_K , OSL12306_16_PIN_L , OSL12306_16_PIN_M , OSL12306_16_PIN_N , OSL12306_16_PIN_P
};

uint8_t digitPins[OSL12306_16_NUM_OF_DIGITS] = {OSL12306_16_PIN_DIGIT};

OSL12306_16 __osl12306_16(
  ANODE_COMMON,
  pins,
  OSL12306_16_PIN_DP,
  OSL12306_16_NUM_OF_DIGITS,
  digitPins
);

UnifiedNSegLED osl12306_16(&__osl12306_16, OSL12306_16_TYPE);
#endif /* USE_OSL12306_16 */



uint8_t deviceCounter=0;
uint8_t osl12306_16_num=0;

#define MAX_TEST 3

struct testResultEntity {
  bool result;
  char about[BUFFER_SIZE];
  char comment[BUFFER_SIZE];
} testResult[MAX_TEST];

void led_setColomn(uint8_t flag) {
  JsonDocument doc;
  doc["id"] = osl12306_16_num;
  doc["type"] = NSEG_LED_TYPE_OSL12306_16;
  doc["time"] = millis();
  doc["command"] = NSEG_LED_COMMAND_SET_COLON;
  doc["paramSize"] = 1;
  doc["param"][0]["flag"] = flag;
  if (false == controlActuator(doc)) {
    Serial.println("exec setColomn() : fail");
  }
}

void led_clear(void) {
  JsonDocument doc;
  doc["id"] = osl12306_16_num;
  doc["type"] = NSEG_LED_TYPE_OSL12306_16;
  doc["time"] = millis();
  doc["command"] = NSEG_LED_COMMAND_CLEAR;
  doc["paramSize"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec clear() : fail");
  }
}

void led_display(const char dispData[]) {
  JsonDocument doc;
  doc["id"] = osl12306_16_num;
  doc["type"] = NSEG_LED_TYPE_OSL12306_16;
  doc["time"] = millis();
  doc["command"] = NSEG_LED_COMMAND_SETC;
  doc["paramSize"] = 1;
  doc["param"][0]["text"] = dispData;
  if (false == controlActuator(doc)) {
    Serial.println("exec display(const char dispData[]) : fail");
  }
}

void led_display_with_period(uint32_t points, const char dispData[]) {
  JsonDocument doc;
  doc["id"] = osl12306_16_num;
  doc["type"] = NSEG_LED_TYPE_OSL12306_16;
  doc["time"] = millis();
  doc["command"] = NSEG_LED_COMMAND_SET;
  doc["paramSize"] = 1;
  doc["param"][0]["text"] = dispData;
  doc["param"][0]["period"] = points;
  if (false == controlActuator(doc)) {
    Serial.println("exec display(uint64_t points, const char dispData[]) : fail");
  }
}

void led_brightness(uint8_t brightness) {
  JsonDocument doc;
  doc["id"] = osl12306_16_num;
  doc["type"] = NSEG_LED_TYPE_OSL12306_16;
  doc["time"] = millis();
  doc["command"] = NSEG_LED_COMMAND_SET_BRIGHTNESS;
  doc["paramSize"] = 1;
  doc["param"][0]["brightness"] = brightness;
  if (false == controlActuator(doc)) {
    Serial.println("exec set() : fail");
  }
}

enum functionList {
  FUNCTION_SET = 0,
  FUNCTION_SET_COLOMN,
  FUNCTION_BEGIN,
  FUNCTION_CLEAR,
  FUNCTION_DISPLAY
};

String functionName[5] = {
  "set()",
  "setColomn()",
  "begin()",
  "clear()",
  "display()"
};

void checkReturnValue(nSegLedFunctionReturnValue val, uint8_t funcType) {
  char buff[BUFFER_SIZE];
  memset(buff,0,BUFFER_SIZE);
  if (val == NSEGLED_FUNCTION_UNSUPPORTED) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is unsupported.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
  if (val == NSEGLED_FUNCTION_FAIL) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is failed.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
}

void setup_nseg_led(void) {

  Serial.println("");
  Serial.println("");
  Serial.println("1 digit led device driver test.");
  Serial.println("");

  nSegLedFunctionReturnValue value;

#ifdef USE_OSL12306_16
  value = osl12306_16.begin();
  checkReturnValue(value, FUNCTION_BEGIN);
  value = osl12306_16.clear();
  checkReturnValue(value, FUNCTION_CLEAR);
#endif /* USE_OSL12306_16 */

  updateDeviceTable(deviceCounter, NSEG_LED_TYPE_OSL12306_16, &osl12306_16, DIGITS);
  osl12306_16_num = deviceCounter;
  deviceCounter++;
  Serial.print("nseg led OSL12306-16 : device No. ");Serial.println(osl12306_16_num);
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

//
char dispData[DIGITS+1];

void clearDispData() {
  for (int i=0; i< (DIGITS+1); i++) {
    dispData[i]=' ';
  }
}

void test1() {
  String about = "test1";
  printStartMessage(about, 0);
  clearDispData();
  Serial.println("=== action ===");
  Serial.println("ON/OFF period 10 times");
  Serial.println("");
  waitForStart();

  Serial.println("test1 start.");

  uint32_t flag=1;
  for (int i=0; i<10; i++) {
    if (flag==1) {
      flag = 0;
    } else {
      flag = 1;
    }
    led_display_with_period(flag, dispData);
    delay(1000);
  }

  checkTestResult(about, 0);
  Serial.println("");
  Serial.println("");

  led_clear();

}

void test2() {
  String about = "test2";
  printStartMessage(about, 1);
  clearDispData();
  // テスト内容の説明
  Serial.println("=== action ===");
  Serial.println("x (x:-,0,1...,a,b,c...z)");
  Serial.println("");
  waitForStart();

  Serial.println("test2 start.");

  for (int i=0; i< 39 ;i++) {
    switch(i) {
      case 1: {dispData[0]=0;break;}
      case 2: {dispData[0]='-';break;}
      case 3: {dispData[0]='0';break;}
      case 4: {dispData[0]='1';break;}
      case 5: {dispData[0]='2';break;}
      case 6: {dispData[0]='3';break;}
      case 7: {dispData[0]='4';break;}
      case 8: {dispData[0]='5';break;}
      case 9: {dispData[0]='6';break;}
      case 10: {dispData[0]='7';break;}
      case 11: {dispData[0]='8';break;}
      case 12: {dispData[0]='9';break;}
      case 13: {dispData[0]='a';break;}
      case 14: {dispData[0]='b';break;}
      case 15: {dispData[0]='c';break;}
      case 16: {dispData[0]='d';break;}
      case 17: {dispData[0]='e';break;}
      case 18: {dispData[0]='f';break;}
      case 19: {dispData[0]='g';break;}
      case 20: {dispData[0]='h';break;}
      case 21: {dispData[0]='i';break;}
      case 22: {dispData[0]='j';break;}
      case 23: {dispData[0]='k';break;}
      case 24: {dispData[0]='l';break;}
      case 25: {dispData[0]='m';break;}
      case 26: {dispData[0]='n';break;}
      case 27: {dispData[0]='o';break;}
      case 28: {dispData[0]='p';break;}
      case 29: {dispData[0]='q';break;}
      case 30: {dispData[0]='r';break;}
      case 31: {dispData[0]='s';break;}
      case 32: {dispData[0]='t';break;}
      case 33: {dispData[0]='u';break;}
      case 34: {dispData[0]='v';break;}
      case 35: {dispData[0]='w';break;}
      case 36: {dispData[0]='x';break;}
      case 37: {dispData[0]='y';break;}
      case 38: {dispData[0]='z';break;}
    }
    led_display_with_period(0, dispData);
    delay(1000);
    clearDispData();
    led_clear();
  }

  checkTestResult(about, 1);
  Serial.println("");
  Serial.println("");

  led_clear();

}

void test3() {
  String about = "test3";

  printStartMessage(about, 2);
  clearDispData();

  // テスト内容の説明
  Serial.println("=== action ===");
  Serial.println("x (x:-,0,1...,a,b,c...z)");
  Serial.println("");
  waitForStart();

  Serial.println("test3 start.");

  uint32_t flag=1;


  for (int i=0; i< 39 ;i++) {
    if (flag==1) {
      flag = 0;
    } else {
      flag = 1;
    }
    switch(i) {
      case 1: {dispData[0]=' ';break;}
      case 2: {dispData[0]='-';break;}
      case 3: {dispData[0]='0';break;}
      case 4: {dispData[0]='1';break;}
      case 5: {dispData[0]='2';break;}
      case 6: {dispData[0]='3';break;}
      case 7: {dispData[0]='4';break;}
      case 8: {dispData[0]='5';break;}
      case 9: {dispData[0]='6';break;}
      case 10: {dispData[0]='7';break;}
      case 11: {dispData[0]='8';break;}
      case 12: {dispData[0]='9';break;}
      case 13: {dispData[0]='a';break;}
      case 14: {dispData[0]='b';break;}
      case 15: {dispData[0]='c';break;}
      case 16: {dispData[0]='d';break;}
      case 17: {dispData[0]='e';break;}
      case 18: {dispData[0]='f';break;}
      case 19: {dispData[0]='g';break;}
      case 20: {dispData[0]='h';break;}
      case 21: {dispData[0]='i';break;}
      case 22: {dispData[0]='j';break;}
      case 23: {dispData[0]='k';break;}
      case 24: {dispData[0]='l';break;}
      case 25: {dispData[0]='m';break;}
      case 26: {dispData[0]='n';break;}
      case 27: {dispData[0]='o';break;}
      case 28: {dispData[0]='p';break;}
      case 29: {dispData[0]='q';break;}
      case 30: {dispData[0]='r';break;}
      case 31: {dispData[0]='s';break;}
      case 32: {dispData[0]='t';break;}
      case 33: {dispData[0]='u';break;}
      case 34: {dispData[0]='v';break;}
      case 35: {dispData[0]='w';break;}
      case 36: {dispData[0]='x';break;}
      case 37: {dispData[0]='y';break;}
      case 38: {dispData[0]='z';break;}
    }
    led_display_with_period(flag, dispData);
    delay(1000);
    clearDispData();
    led_clear();
  }

  checkTestResult(about, 2);
  Serial.println("");
  Serial.println("");

  led_clear();

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

  setup_nseg_led();

  Serial.println("");
  Serial.println("");
  Serial.println("device and device driver test of nseg led OSL12306-16.");

  test1();
  test2();
  test3();
  sumTestResult();

}

void loop() {
}








