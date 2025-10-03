


#include "ActuatorHAL.h"
#include <ArduinoJson.h>

HardwareHelper hwHelper;

#ifdef GROVE_LED_BAR
#define LED_TYPE LED_BAR
Grove_LED_Bar bar(GROVE_LED_BAR_PIN_CLK, GROVE_LED_BAR_PIN_DATA, GROVE_LED_BAR_DIRECTION, LED_BAR_10);
UnifiedLED ledBar(&(bar),LED_BAR, GROVE_LED_BAR_NUM_OF_LED, LED_FORWARD);
#define LED_NUM GROVE_LED_BAR_NUM_OF_LED
#endif /* GROVE_LED_BAR */

#ifdef GROVE_LED_CIRCULAR
#define LED_TYPE LED_CIRCULAR
Grove_LED_Bar circle(GROVE_LED_CIRCLE_PIN_CLK, GROVE_LED_CIRCLE_PIN_DATA, GROVE_LED_BAR_DIRECTION, LED_CIRCULAR_24);
UnifiedLED ledCircle(&(circle),LED_CIRCULAR, GROVE_LED_CIRCLE_NUM_OF_LED, LED_FORWARD);
#define LED_NUM GROVE_LED_CIRCLE_NUM_OF_LED
#endif /* GROVE_LED_CIRCULAR */

uint8_t deviceCounter=0;
uint8_t led_num=0;

#define MAX_TEST 1

struct testResultEntity {
  bool result;
  char about[BUFFER_SIZE];
  char comment[BUFFER_SIZE];
} testResult[MAX_TEST];

void setLed(uint32_t ledNo, float brightness) {
  JsonDocument doc;
  doc["id"] = led_num;
  doc["type"] = LED_TYPE_MONO_CHAIN_LED;
  doc["time"] = millis();
  doc["command"] = LED_COMMAND_SET_BRIGHTNESS_N;
  doc["paramSize"] = 1;
  doc["param"][0]["num"] = ledNo;
  doc["param"][0]["brightness"] = brightness;
  if (false == controlActuator(doc)) {
    Serial.println("exec setLed() : fail");
  }
}

void setMode(UnifiedLedMode mode) {
  JsonDocument doc;
  doc["id"] = led_num;
  doc["type"] = LED_TYPE_MONO_CHAIN_LED;
  doc["time"] = millis();
  doc["command"] = LED_COMMAND_SET_MODE;
  doc["paramSize"] = 1;
  doc["param"][0]["mode"] = mode;
  if (false == controlActuator(doc)) {
    Serial.println("exec setMode() : fail");
  }
}

enum functionList {
  FUNCTION_SET_LEVEL = 0,
  FUNCTION_SET_MODE,
  FUNCTION_SET_LED_NUM,
  FUNCTION_SET_LED,
  FUNCTION_SET_ONCE,
  FUNCTION_BEGIN
};

String functionName[6] = {
  "setLevel()",
  "setMode()",
  "setLedNum()",
  "setLed()",
  "setOnce()",
  "begin()"
};

void checkReturnValue(ledFunctionReturnValue val, uint8_t funcType) {
  char buff[BUFFER_SIZE];
  memset(buff,0,BUFFER_SIZE);
  if (val == LED_FUNCTION_UNSUPPORTED) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is unsupported.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
  if (val == LED_FUNCTION_FAIL) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is failed.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
}

void setup_LED(void) {
  ledFunctionReturnValue value;

#ifdef GROVE_LED_BAR
  value = ledBar.begin();
  checkReturnValue(value, FUNCTION_BEGIN);
  value = ledBar.setMode(LED_FORWARD);
  checkReturnValue(value, FUNCTION_SET_MODE);
  updateDeviceTable(deviceCounter, LED_TYPE_MONO_CHAIN_LED, &ledBar);
#endif /* GROVE_LED_BAR */

#ifdef GROVE_LED_CIRCULAR
  value = ledCircle.begin();
  checkReturnValue(value, FUNCTION_BEGIN);
  value = ledCircle.setMode(LED_FORWARD);
  checkReturnValue(value, FUNCTION_SET_MODE);
  updateDeviceTable(deviceCounter, LED_TYPE_MONO_CHAIN_LED, &ledCircle);
#endif /* GROVE_LED_CIRCULAR */

  led_num = deviceCounter;
  deviceCounter++;
  Serial.print("Mono chain led : device No. ");Serial.println(led_num);
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
  Serial.println("put on led forward direction.");
  Serial.println("=== 2nd action ===");
  Serial.println("put on led reverse direction.");
  Serial.println("");
  waitForStart();

  Serial.println("1st action.");

  setMode(LED_FORWARD);

  for (int i=0; i<LED_NUM; i++) {
    setLed(i,1.0);
    delay(100);
  }

  for (int i=0; i<LED_NUM; i++) {
    setLed(i,0);
  }

  delay(3000);
  Serial.println("2nd action.");


  setMode(LED_REVERSE);

  for (int i=0; i<LED_NUM; i++) {
    setLed(i,1.0);
    delay(100);
  }

  checkTestResult(about, 0);
  Serial.println("");
  Serial.println("");

  for (int i=0; i<LED_NUM; i++) {
    setLed(i,0);
  }
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

  setup_LED();

  Serial.println("");
  Serial.println("");
  Serial.println("device and device driver test of simple mono led.");

  test1();
  sumTestResult();

}

void loop() {
}







