
#include "ActuatorHAL.h"
#include <ArduinoJson.h>

HardwareHelper hwHelper;


#ifdef USE_OSL20541
#define SEGMENT_NUM 14
#define PRINTABLE_CHAR_NUM 38

#define OSL20541_NUM_OF_CHAR_PINS _OSL20541_CHAR_PINS
#define DIGITS OSL20541_NUM_OF_DIGITS

uint8_t osl20541_charPins[OSL20541_NUM_OF_CHAR_PINS] = {
  OSL20541_PIN_A,
  OSL20541_PIN_B,
  OSL20541_PIN_C,
  OSL20541_PIN_D,
  OSL20541_PIN_E,
  OSL20541_PIN_F,
  OSL20541_PIN_G1,
  OSL20541_PIN_G2,
  OSL20541_PIN_H,
  OSL20541_PIN_J,
  OSL20541_PIN_K,
  OSL20541_PIN_L,
  OSL20541_PIN_M,
  OSL20541_PIN_N
};
uint8_t osl20541_digitPins[OSL20541_NUM_OF_DIGITS] = {OSL20541_PIN_DIGIT_1, OSL20541_PIN_DIGIT_2};

OSL20541 __osl20541(
  ANODE_COMMON,
  osl20541_charPins,
  OSL20541_PIN_DP,
  OSL20541_NUM_OF_DIGITS,
  osl20541_digitPins
);

UnifiedNSegLED nSegLed(&__osl20541, OSL20541_TYPE);
#define NSEG_LED_TYPE NSEG_LED_TYPE_OSL20541
#endif /* USE_OSL20541 */


#ifdef USE_OSL30561
#define SEGMENT_NUM 7
#define PRINTABLE_CHAR_NUM 18

#define DIGITS OSL30561_NUM_OF_DIGITS
uint8_t osl30561_digitPins[OSL30561_NUM_OF_DIGITS] = {OSL30561_PIN_DIGIT_1, OSL30561_PIN_DIGIT_2, OSL30561_PIN_DIGIT_3};

OSL30561 __osl30561(
  OSL30561_TYPE_ANODE_COMMON,
  OSL30561_PIN_A,
  OSL30561_PIN_B,
  OSL30561_PIN_C,
  OSL30561_PIN_D,
  OSL30561_PIN_E,
  OSL30561_PIN_F,
  OSL30561_PIN_G,
  OSL30561_PIN_DP,
  OSL30561_NUM_OF_DIGITS,
  osl30561_digitPins
);

UnifiedNSegLED nSegLed(&__osl30561, OSL30561_TYPE);
#define NSEG_LED_TYPE NSEG_LED_TYPE_OSL30561
#endif /* USE_OSL30561 */

#ifdef USE_DFR0090
#define DIGITS DFR0090_NUM_OF_DIGITS
#define PRINTABLE_CHAR_NUM 18

DFR0090 _dfr(DFR0090_CLOCK_PIN, DFR0090_LATCH_PIN, DFR0090_DATA_PIN, DFR0090_NUM_OF_DIGITS);

UnifiedNSegLED nSegLed(&_dfr, DFR0090_TYPE);
#define NSEG_LED_TYPE NSEG_LED_TYPE_DFR0090
#endif /* USE_DFR0090 */

uint8_t deviceCounter=0;
uint8_t nseg_led_num=0;

unsigned int stage=0;
unsigned int test=1;
unsigned long lastTime=0;

#define MAX_TEST 5

struct testResultEntity {
  bool result;
  char about[BUFFER_SIZE];
  char comment[BUFFER_SIZE];
} testResult[MAX_TEST];

void led_setColomn(uint8_t flag) {
  JsonDocument doc;
  doc["id"] = nseg_led_num;
  doc["type"] = NSEG_LED_TYPE;
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
  doc["type"] = NSEG_LED_TYPE;
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
  doc["type"] = NSEG_LED_TYPE;
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
  doc["type"] = NSEG_LED_TYPE;
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
  doc["type"] = NSEG_LED_TYPE;
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
  Serial.println("multipul digit n-seg led device driver test.");
  Serial.println("");

  nSegLedFunctionReturnValue value;

  value = nSegLed.begin();
  checkReturnValue(value, FUNCTION_BEGIN);
  value = nSegLed.clear();
  checkReturnValue(value, FUNCTION_CLEAR);

  updateDeviceTable(deviceCounter, NSEG_LED_TYPE, &nSegLed, DIGITS);
  nseg_led_num = deviceCounter;
  deviceCounter++;
  Serial.print("nseg led : device No. ");Serial.println(nseg_led_num);
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
  test++;
}

//
char dispData[DIGITS+1];

void clearDispData() {
  for (int i=0; i< (DIGITS+1); i++) {
    dispData[i]=' ';
  }
}



//  テストシナリオ1 : ピリオドの点灯/消灯

unsigned long test1_stage0() {
  //
  unsigned long retVal =1;
  for (int i=0; i<DIGITS; i++) {
    retVal=retVal*2;
  }

  // テスト内容の説明
  Serial.println("=== action ===");
  Serial.println("ON/OFF period 10 times");
  Serial.println("");
  waitForStart();

  Serial.println("test1 start.");
  stage = 1;

  return retVal;
}

void test1_stageX() {
  //nSegLed.clear();
  //led_display_with_period(stage, dispData);
  //led_display_with_period(stage, "01234567");
  led_display_with_period(stage, "        ");
}

unsigned long max_loop;

void test1() {
  String about = "test1";

  if (stage==0) {
    printStartMessage(about, 0);
    clearDispData();
    max_loop =test1_stage0();
    lastTime=millis();
    stage=1;
  } else if ((stage >0) && (stage < max_loop)) {
    test1_stageX();
    unsigned long currentTime=millis();
    if (500 < (currentTime - lastTime)) {
      lastTime = currentTime;
      stage++;
    };
  } else {
    checkTestResult(about, 0);
    Serial.println("");
    Serial.println("");

    led_clear();

    test++;
    stage=0;
  }
}


void test2_stage0() {
  // テスト内容の説明
  Serial.println("=== action ===");

#if PRINTABLE_CHAR_NUM==38
  Serial.println("x (x:-,0,1...,a,b,c...z)");
#else
  Serial.println("x (x:-,0,1...,a,b,c,d,e,f)");
#endif

  Serial.println("");
  waitForStart();

  Serial.println("test2 start.");
  stage =1;
}

void test2() {
  String about = "test2";

  if (stage==0) {
    printStartMessage(about, 1);
    clearDispData();
    test2_stage0();
    lastTime=millis();
  } else if ((stage>0) &&(stage <(PRINTABLE_CHAR_NUM+1))) {
    for (int j=0; j< DIGITS; j++) {
      switch(stage) {
        case 1: {dispData[j]=' ';break;}
        case 2: {dispData[j]='-';break;}
        case 3: {dispData[j]='0';break;}
        case 4: {dispData[j]='1';break;}
        case 5: {dispData[j]='2';break;}
        case 6: {dispData[j]='3';break;}
        case 7: {dispData[j]='4';break;}
        case 8: {dispData[j]='5';break;}
        case 9: {dispData[j]='6';break;}
        case 10: {dispData[j]='7';break;}
        case 11: {dispData[j]='8';break;}
        case 12: {dispData[j]='9';break;}
        case 13: {dispData[j]='a';break;}
        case 14: {dispData[j]='b';break;}
        case 15: {dispData[j]='c';break;}
        case 16: {dispData[j]='d';break;}
        case 17: {dispData[j]='e';break;}
        case 18: {dispData[j]='f';break;}
#if PRINTABLE_CHAR_NUM==38
        case 19: {dispData[j]='g';break;}
        case 20: {dispData[j]='h';break;}
        case 21: {dispData[j]='i';break;}
        case 22: {dispData[j]='j';break;}
        case 23: {dispData[j]='k';break;}
        case 24: {dispData[j]='l';break;}
        case 25: {dispData[j]='m';break;}
        case 26: {dispData[j]='n';break;}
        case 27: {dispData[j]='o';break;}
        case 28: {dispData[j]='p';break;}
        case 29: {dispData[j]='q';break;}
        case 30: {dispData[j]='r';break;}
        case 31: {dispData[j]='s';break;}
        case 32: {dispData[j]='t';break;}
        case 33: {dispData[j]='u';break;}
        case 34: {dispData[j]='v';break;}
        case 35: {dispData[j]='w';break;}
        case 36: {dispData[j]='x';break;}
        case 37: {dispData[j]='y';break;}
        case 38: {dispData[j]='z';break;}
#endif
      }
    }

    led_display_with_period(0, dispData);

    unsigned long currentTime=millis();
    if (500 < (currentTime - lastTime)) {
      lastTime = currentTime;
      stage++;
    };
  } else {
    checkTestResult(about, 1);
    Serial.println("");
    Serial.println("");

    led_clear();

    test++;
    stage=0;
    clearDispData();
  }
}


void test3_stage0() {
  // テスト内容の説明
  Serial.println("=== action ===");
#if PRINTABLE_CHAR_NUM==38
  Serial.println("x. (x:-,0,1...,a,b,c...z)");
#else
  Serial.println("x. (x:-,0,1...,a,b,c,d,e,f)");
#endif
  Serial.println("");
  waitForStart();

  Serial.println("test3 start.");
  stage =1;
}

void test3() {
  String about = "test3";

  if (stage==0) {
    printStartMessage(about, 2);
    clearDispData();
    test3_stage0();
    lastTime=millis();
  } else if ((stage>0) &&(stage <(PRINTABLE_CHAR_NUM+1))) {
    for (int j=0; j< DIGITS; j++) {
      switch(stage) {
        case 1: {dispData[j]=' ';break;}
        case 2: {dispData[j]='-';break;}
        case 3: {dispData[j]='0';break;}
        case 4: {dispData[j]='1';break;}
        case 5: {dispData[j]='2';break;}
        case 6: {dispData[j]='3';break;}
        case 7: {dispData[j]='4';break;}
        case 8: {dispData[j]='5';break;}
        case 9: {dispData[j]='6';break;}
        case 10: {dispData[j]='7';break;}
        case 11: {dispData[j]='8';break;}
        case 12: {dispData[j]='9';break;}
        case 13: {dispData[j]='a';break;}
        case 14: {dispData[j]='b';break;}
        case 15: {dispData[j]='c';break;}
        case 16: {dispData[j]='d';break;}
        case 17: {dispData[j]='e';break;}
        case 18: {dispData[j]='f';break;}
#if PRINTABLE_CHAR_NUM==38
        case 19: {dispData[j]='g';break;}
        case 20: {dispData[j]='h';break;}
        case 21: {dispData[j]='i';break;}
        case 22: {dispData[j]='j';break;}
        case 23: {dispData[j]='k';break;}
        case 24: {dispData[j]='l';break;}
        case 25: {dispData[j]='m';break;}
        case 26: {dispData[j]='n';break;}
        case 27: {dispData[j]='o';break;}
        case 28: {dispData[j]='p';break;}
        case 29: {dispData[j]='q';break;}
        case 30: {dispData[j]='r';break;}
        case 31: {dispData[j]='s';break;}
        case 32: {dispData[j]='t';break;}
        case 33: {dispData[j]='u';break;}
        case 34: {dispData[j]='v';break;}
        case 35: {dispData[j]='w';break;}
        case 36: {dispData[j]='x';break;}
        case 37: {dispData[j]='y';break;}
        case 38: {dispData[j]='z';break;}
#endif
      }
    }
    uint32_t flag = (stage-1) % max_loop ;

    led_display_with_period(flag, dispData);

    unsigned long currentTime=millis();
    if (1500 < (currentTime - lastTime)) {
      lastTime = currentTime;
      stage++;
    };
  } else {
    checkTestResult(about, 2);
    Serial.println("");
    Serial.println("");

    led_clear();

    test++;
    stage=0;
    clearDispData();
  }
}

void test4_stage0() {
  // テスト内容の説明
  Serial.println("=== action ===");
#if PRINTABLE_CHAR_NUM==38
  Serial.println("_x. (x:-,0,1...,a,b,c...z) _ means space");
#else
  Serial.println("_x. (x:-,0,1...,a,b,c,d,e,f) _ means space");
#endif
  Serial.println("");
  waitForStart();

  Serial.println("test4 start.");
  stage =1;
}

void test4() {
  nSegLedFunctionReturnValue value;
  String about = "test4";

  if (stage==0) {
    printStartMessage(about, 3);
    clearDispData();
    test4_stage0();
    lastTime=millis();
  } else if ((stage>0) &&(stage <(PRINTABLE_CHAR_NUM))) {
    for (int i=0; i< DIGITS;i++) {
      dispData[i]=' ';
    }
    int j=DIGITS-1;
    switch(stage) {
      case 1: {dispData[j]='-';break;}
      case 2: {dispData[j]='0';break;}
      case 3: {dispData[j]='1';break;}
      case 4: {dispData[j]='2';break;}
      case 5: {dispData[j]='3';break;}
      case 6: {dispData[j]='4';break;}
      case 7: {dispData[j]='5';break;}
      case 8: {dispData[j]='6';break;}
      case 9: {dispData[j]='7';break;}
      case 10: {dispData[j]='8';break;}
      case 11: {dispData[j]='9';break;}
      case 12: {dispData[j]='a';break;}
      case 13: {dispData[j]='b';break;}
      case 14: {dispData[j]='c';break;}
      case 15: {dispData[j]='d';break;}
      case 16: {dispData[j]='e';break;}
      case 17: {dispData[j]='f';break;}
#if PRINTABLE_CHAR_NUM==38
      case 18: {dispData[j]='g';break;}
      case 19: {dispData[j]='h';break;}
      case 20: {dispData[j]='i';break;}
      case 21: {dispData[j]='j';break;}
      case 22: {dispData[j]='k';break;}
      case 23: {dispData[j]='l';break;}
      case 24: {dispData[j]='m';break;}
      case 25: {dispData[j]='n';break;}
      case 26: {dispData[j]='o';break;}
      case 27: {dispData[j]='p';break;}
      case 28: {dispData[j]='q';break;}
      case 29: {dispData[j]='r';break;}
      case 30: {dispData[j]='s';break;}
      case 31: {dispData[j]='t';break;}
      case 32: {dispData[j]='u';break;}
      case 33: {dispData[j]='v';break;}
      case 34: {dispData[j]='w';break;}
      case 35: {dispData[j]='x';break;}
      case 36: {dispData[j]='y';break;}
      case 37: {dispData[j]='z';break;}
#endif
    }
    uint32_t flag = (stage-1) % max_loop ;

    led_display_with_period(flag, dispData);

    unsigned long currentTime=millis();
    if (1500 < (currentTime - lastTime)) {
      lastTime = currentTime;
      stage++;
    };
  } else {
    checkTestResult(about, 3);
    Serial.println("");
    Serial.println("");

    value = nSegLed.clear();
    checkReturnValue(value, FUNCTION_CLEAR);

    test++;
    stage=0;
    clearDispData();
  }
}


void test5_stage0() {
  // テスト内容の説明
  Serial.println("=== action ===");
#if PRINTABLE_CHAR_NUM==38
  Serial.println("x_. (x:-,0,1...,a,b,c...z) _ means space");
#else
  Serial.println("x_. (x:-,0,1...,a,b,c,d,e,f) _ means space");
#endif
  Serial.println("");
  waitForStart();

  Serial.println("test5 start.");
  stage =1;
}

void test5() {
  nSegLedFunctionReturnValue value;
  String about = "test5";

  if (stage==0) {
    printStartMessage(about, 4);
    clearDispData();
    test5_stage0();
    lastTime=millis();
  } else if ((stage>0) &&(stage <(PRINTABLE_CHAR_NUM))) {
    for (int i=0; i< DIGITS;i++) {
      dispData[i]=' ';
    }
    int j=DIGITS-1;
    switch(stage) {
      case 1: {dispData[0]='-';break;}
      case 2: {dispData[0]='0';break;}
      case 3: {dispData[0]='1';break;}
      case 4: {dispData[0]='2';break;}
      case 5: {dispData[0]='3';break;}
      case 6: {dispData[0]='4';break;}
      case 7: {dispData[0]='5';break;}
      case 8: {dispData[0]='6';break;}
      case 9: {dispData[0]='7';break;}
      case 10: {dispData[0]='8';break;}
      case 11: {dispData[0]='9';break;}
      case 12: {dispData[0]='a';break;}
      case 13: {dispData[0]='b';break;}
      case 14: {dispData[0]='c';break;}
      case 15: {dispData[0]='d';break;}
      case 16: {dispData[0]='e';break;}
      case 17: {dispData[0]='f';break;}
#if PRINTABLE_CHAR_NUM==38
      case 18: {dispData[0]='g';break;}
      case 19: {dispData[0]='h';break;}
      case 20: {dispData[0]='i';break;}
      case 21: {dispData[0]='j';break;}
      case 22: {dispData[0]='k';break;}
      case 23: {dispData[0]='l';break;}
      case 24: {dispData[0]='m';break;}
      case 25: {dispData[0]='n';break;}
      case 26: {dispData[0]='o';break;}
      case 27: {dispData[0]='p';break;}
      case 28: {dispData[0]='q';break;}
      case 29: {dispData[0]='r';break;}
      case 30: {dispData[0]='s';break;}
      case 31: {dispData[0]='t';break;}
      case 32: {dispData[0]='u';break;}
      case 33: {dispData[0]='v';break;}
      case 34: {dispData[0]='w';break;}
      case 35: {dispData[0]='x';break;}
      case 36: {dispData[0]='y';break;}
      case 37: {dispData[0]='z';break;}
#endif
    }
    uint32_t flag = (stage-1) % max_loop ;

    led_display_with_period(flag, dispData);

    unsigned long currentTime=millis();
    if (1500 < (currentTime - lastTime)) {
      lastTime = currentTime;
      stage++;
    };
  } else {
    checkTestResult(about, 4);
    Serial.println("");
    Serial.println("");

    value = nSegLed.clear();
    checkReturnValue(value, FUNCTION_CLEAR);

    test++;
    stage=0;
    clearDispData();
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

  setup_nseg_led();

  Serial.println("");
  Serial.println("");
  Serial.println("device and device driver test of nseg led.");

  clearDispData();

}

void loop() {
  switch(test){
    case 1: {
      test1();break;
    }
    case 2: {
      test2();break;
    }
    case 3: {
      test3();break;
    }
    case 4: {
      test4();break;
    }
    case 5: {
      test5();break;
    }
    case 6: {
      sumTestResult();break;
    }
  }
}







