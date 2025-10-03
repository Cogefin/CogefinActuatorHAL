
#include "ActuatorHAL.h"
#include <ArduinoJson.h>

HardwareHelper hwHelper;


#ifdef USE_GROVE_TM1637
TM1637 __tm1637(GROVE_NSEG_LED_PIN_CLK, GROVE_NSEG_LED_PIN_DATA);
UnifiedNSegLED tm1637(&__tm1637, GROVE_TM1637_TYPE);
#endif /* USE_GROVE_TM1637 */

uint8_t deviceCounter=0;
uint8_t nseg_led_num=0;

#define MAX_TEST 3

struct testResultEntity {
  bool result;
  char about[BUFFER_SIZE];
  char comment[BUFFER_SIZE];
} testResult[MAX_TEST];

void led_setColomn(uint8_t flag) {
  JsonDocument doc;
  doc["id"] = nseg_led_num;
  doc["type"] = NSEG_LED_TYPE_GROVE_TM1637;
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
  doc["id"] = nseg_led_num;
  doc["type"] = NSEG_LED_TYPE_GROVE_TM1637;
  doc["time"] = millis();
  doc["command"] = NSEG_LED_COMMAND_CLEAR;
  doc["paramSize"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec clear() : fail");
  }
}

void led_display(const char dispData[]) {
  JsonDocument doc;
  doc["id"] = nseg_led_num;
  doc["type"] = NSEG_LED_TYPE_GROVE_TM1637;
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
  doc["id"] = nseg_led_num;
  doc["type"] = NSEG_LED_TYPE_GROVE_TM1637;
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
  doc["id"] = nseg_led_num;
  doc["type"] = NSEG_LED_TYPE_GROVE_TM1637;
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
  Serial.println("clock type n-seg led device driver test.");
  Serial.println("");

  nSegLedFunctionReturnValue value;

#ifdef USE_GROVE_TM1637
  value = tm1637.begin();
  checkReturnValue(value, FUNCTION_BEGIN);
  value = tm1637.clear();
  checkReturnValue(value, FUNCTION_CLEAR);
  value = tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  checkReturnValue(value, FUNCTION_SET);
  value = tm1637.setColomn(false);
  checkReturnValue(value, FUNCTION_SET_COLOMN);
#endif /* USE_GROVE_TM1637 */

  updateDeviceTable(deviceCounter, NSEG_LED_TYPE_GROVE_TM1637, &tm1637, MAX_DIGITS_OF_NSEG_LED);
  nseg_led_num = deviceCounter;
  deviceCounter++;
  Serial.print("clock type nseg led device : device No. ");Serial.println(nseg_led_num);
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
  Serial.println("=== action ===");
  Serial.println("ON/OFF colon 10 times");
  Serial.println("");
  waitForStart();

  Serial.println("test1 start.");

  bool flag = false;
  for (int i=0 ; i<10 ; i++) {
    if (flag) {
      flag = false;
    } else {
      flag = true;
    }
    char print_str[4] = {'0', '1', '2', '3'};
#ifdef USE_GROVE_TM1637
    led_setColomn(flag);
    led_display(print_str);
#endif /* USE_GROVE_TM1637 */
    delay(1000);
  }

  checkTestResult(about, 0);
  Serial.println("");
  Serial.println("");

#ifdef USE_GROVE_TM1637
  led_clear();
#endif /* USE_GROVE_TM1637 */

}

void test2() {
  String about = "test2";
  printStartMessage(about, 1);
  // テスト内容の説明
  Serial.println("=== 1st action ===");
  Serial.println("x___");
  Serial.println("_x__");
  Serial.println("__x_");
  Serial.println("___x");
  Serial.println("");
  Serial.println("=== 2nd action ===");
  Serial.println("xxxx");
  Serial.println("");
  waitForStart();

  Serial.println("test2 start.");

  //char print_str[4] = {0, 0, 0, 0};
  char print_str[5] = {0, 0, 0, 0, 0};
  for (int i=0; i<16; i++) {
    for (int j=0; j<4; j++) {
      for (int k=0; k<4; k++) {
        print_str[k]=',';
      }
      switch(i) {
        case 0: {print_str[j]='0';break;}
        case 1: {print_str[j]='1';break;}
        case 2: {print_str[j]='2';break;}
        case 3: {print_str[j]='3';break;}
        case 4: {print_str[j]='4';break;}
        case 5: {print_str[j]='5';break;}
        case 6: {print_str[j]='6';break;}
        case 7: {print_str[j]='7';break;}
        case 8: {print_str[j]='8';break;}
        case 9: {print_str[j]='9';break;}
        case 10: {print_str[j]='a';break;}
        case 11: {print_str[j]='b';break;}
        case 12: {print_str[j]='c';break;}
        case 13: {print_str[j]='d';break;}
        case 14: {print_str[j]='e';break;}
        case 15: {print_str[j]='f';break;}
      }
#ifdef USE_GROVE_TM1637
      led_clear();
      led_display(print_str);
      print_str[j]=0;
#endif /* USE_GROVE_TM1637 */
      delay(1000);
    }
  }
  for (int i=0; i<16; i++) {
    for (int j=0; j<4; j++) {
      switch(i) {
        case 0: {print_str[j]='0';break;}
        case 1: {print_str[j]='1';break;}
        case 2: {print_str[j]='2';break;}
        case 3: {print_str[j]='3';break;}
        case 4: {print_str[j]='4';break;}
        case 5: {print_str[j]='5';break;}
        case 6: {print_str[j]='6';break;}
        case 7: {print_str[j]='7';break;}
        case 8: {print_str[j]='8';break;}
        case 9: {print_str[j]='9';break;}
        case 10: {print_str[j]='a';break;}
        case 11: {print_str[j]='b';break;}
        case 12: {print_str[j]='c';break;}
        case 13: {print_str[j]='d';break;}
        case 14: {print_str[j]='e';break;}
        case 15: {print_str[j]='f';break;}
      }
    }
#ifdef USE_GROVE_TM1637
      led_clear();
      led_display(print_str);
#endif /* USE_GROVE_TM1637 */
    delay(1000);
  }

  checkTestResult(about, 1);
  Serial.println("");
  Serial.println("");

#ifdef USE_GROVE_TM1637
  led_clear();
#endif /* USE_GROVE_TM1637 */

}

void test3() {
  String about = "test3";
  printStartMessage(about, 2);
  // テスト内容の説明
  Serial.println("=== action ===");
  Serial.println("change brightness of LED (0 to 7) x 3times");
  Serial.println("");
  waitForStart();

  Serial.println("test3 start.");

  char print_str[4] = {'0', '1', '2', '3'};

#ifdef USE_GROVE_TM1637
  led_display(print_str);
#endif /* USE_GROVE_TM1637 */
  for (int i=0; i<3; i++) {
    Serial.print("round No.");Serial.println(i+1);
    for (int j=0; j<8; j++) {
      Serial.print("brightness : ");Serial.println(j);
#ifdef USE_GROVE_TM1637
      led_brightness(j);
      led_display(print_str);
#endif /* USE_GROVE_TM1637 */
      delay(3000);
    }
  }

  Serial.println("done.");

  checkTestResult(about, 2);
  Serial.println("");
  Serial.println("");

#ifdef USE_GROVE_TM1637
  led_clear();
#endif /* USE_GROVE_TM1637 */

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
  Serial.println("device and device driver test of clock type nseg LED.");

  test1();
  test2();
  test3();
  sumTestResult();

}

void loop() {
}








