
#include "ActuatorHAL.h"
#include <ArduinoJson.h>

HardwareHelper hwHelper;

PWM pwm(PWM_PIN);

uint8_t deviceCounter=0;
uint8_t pwm_num=0;

#define MAX_TEST 1

struct testResultEntity {
  bool result;
  char about[BUFFER_SIZE];
  char comment[BUFFER_SIZE];
} testResult[MAX_TEST];

void pwm_off(void) {
  JsonDocument doc;
  doc["id"] = pwm_num;
  doc["type"] = PWM_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = PWM_COMMAND_OFF;
  doc["paramSize"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec off() : fail");
  }
}

void pwm_apply(void) {
  JsonDocument doc;
  doc["id"] = pwm_num;
  doc["type"] = PWM_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = PWM_COMMAND_APPLY;
  doc["paramSize"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec apply() : fail");
  }
}

void pwm_set(uint8_t val) {
  JsonDocument doc;
  doc["id"] = pwm_num;
  doc["type"] = PWM_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = PWM_COMMAND_SET;
  doc["paramSize"] = 1;
  doc["param"][0]["value"] = val;
  if (false == controlActuator(doc)) {
    Serial.println("exec set() : fail");
  }
}

enum functionList {
  FUNCTION_BEGIN = 0,
  FUNCTION_APPLY,
  FUNCTION_OFF,
  FUNCTION_SET
};

String functionName[4] = {
  "begin()",
  "apply()",
  "off()",
  "set()"
};


void checkReturnValue(PwmFunctionReturnValue val, uint8_t funcType) {
  char buff[BUFFER_SIZE];
  memset(buff,0,BUFFER_SIZE);
  if (val == PWM_FUNCTION_UNSUPPORTED) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is unsupported.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
  if (val == PWM_FUNCTION_FAIL) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is failed.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
}

void setup_PWM(void) {
  PwmFunctionReturnValue value;

  value = pwm.begin();
  checkReturnValue(value,FUNCTION_BEGIN);

  updateDeviceTable(deviceCounter, PWM_TYPE_SIMPLE, &pwm);
  pwm_num = deviceCounter;
  deviceCounter++;
  Serial.print("Simple PWM device : device No. ");Serial.println(pwm_num);
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
  Serial.println("set level of PWM to 15, 35, 55, ... 255 (3sec)");
  waitForStart();

  for (int i=1; i< 14; i++) {
    int level = i*20-5;
    Serial.print("level = ");Serial.println(level);
    pwm_set(level);
    pwm_apply();
    delay(3000);
    pwm_off();
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

  setup_PWM();

  Serial.println("");
  Serial.println("");
  Serial.println("device and device driver test of simple PWM.");

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








