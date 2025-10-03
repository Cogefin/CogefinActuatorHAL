
#include "ActuatorHAL.h"
#include <ArduinoJson.h>

HardwareHelper hwHelper;

Switch sw(SWITCH_PIN);

uint8_t deviceCounter=0;
uint8_t switch_num=0;

#define MAX_TEST 1

struct testResultEntity {
  bool result;
  char about[BUFFER_SIZE];
  char comment[BUFFER_SIZE];
} testResult[MAX_TEST];

void switch_off(void) {
  JsonDocument doc;
  doc["id"] = switch_num;
  doc["type"] = SIMPLE_SWITCH_TYPE_NORMAL;
  doc["time"] = millis();
  doc["command"] = SIMPLE_SWITCH_COMMAND_OFF;
  doc["paramSize"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec off() : fail");
  }
}

void switch_on(void) {
  JsonDocument doc;
  doc["id"] = switch_num;
  doc["type"] = SIMPLE_SWITCH_TYPE_NORMAL;
  doc["time"] = millis();
  doc["command"] = SIMPLE_SWITCH_COMMAND_ON;
  doc["paramSize"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec on() : fail");
  }
}

enum functionList {
  FUNCTION_BEGIN = 0,
  FUNCTION_ON,
  FUNCTION_OFF
};

String functionName[3] = {
  "begin()",
  "on()",
  "off()"
};

void checkReturnValue(SwitchFunctionReturnValue val, uint8_t funcType) {
  char buff[BUFFER_SIZE];
  memset(buff,0,BUFFER_SIZE);
  if (val == SW_FUNCTION_UNSUPPORTED) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is unsupported.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
  if (val == SW_FUNCTION_FAIL) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is failed.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
}

void setup_switch(void) {
  SwitchFunctionReturnValue value;

  value = sw.begin();
  checkReturnValue(value,FUNCTION_BEGIN);

  updateDeviceTable(deviceCounter, SIMPLE_SWITCH_TYPE_NORMAL, &sw);
  switch_num = deviceCounter;
  deviceCounter++;
  Serial.print("Simple digital device : device No. ");Serial.println(switch_num);
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
  Serial.println("change switch state on/off 10 times (3sec)");
  waitForStart();

  switch_off();
  delay(1000);
  for (int i=0; i< 10; i++) {
    switch_on();
    delay(3000);
    switch_off();
    delay(3000);
  }

  checkTestResult(about, 0);
  Serial.println("");
  Serial.println("");

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

  setup_switch();

  Serial.println("");
  Serial.println("");
  Serial.println("device and device driver test of simple digital device.");

  test1();
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








