
/*
 * デバイスの選択
 */
//#define USE_SPEAKER
#define USE_BOOZER

#include "ActuatorHAL.h"
#include <ArduinoJson.h>

HardwareHelper hwHelper;



/*
 * ピン番号の定義
 */
#ifdef USE_SPEAKER
#define PIN_NUM SPEAKER_PIN
#endif /* USE_SPEAKER */

#ifdef USE_BOOZER
#define PIN_NUM BUZZER_PIN
#endif /* USE_BOOZER */

SimpleSound ss(PIN_NUM, SIMPLE_SOUND_TYPE_PULL_UP);

uint8_t deviceCounter=0;
uint8_t simple_sound_num=0;

#define MAX_TEST 1

struct testResultEntity {
  bool result;
  char about[BUFFER_SIZE];
  char comment[BUFFER_SIZE];
} testResult[MAX_TEST];

void simple_sound_play(uint8_t iteration, int * bass, int * duration, int * interval) {
  JsonDocument doc;
  doc["id"] = simple_sound_num;
  doc["type"] = SIMPLE_SOUND_TYPE_NORMAL;
  doc["time"] = millis();
  doc["command"] = SIMPLE_SOUND_COMMAND_PLAY;
  doc["paramSize"] = 1;
  doc["param"][0]["iteration"] = iteration;
  for (int i=0; i<iteration; i++ ) {
    doc["param"][0]["bass"][i] = bass[i];
    doc["param"][0]["duration"][i] = duration[i];
    doc["param"][0]["interval"][i] = interval[i];
  }
  if (false == controlActuator(doc)) {
    Serial.println("exec play() : fail");
  }
}


enum functionList {
  FUNCTION_BEGIN = 0,
  FUNCTION_ON,
  FUNCTION_OFF,
  FUNCTION_PLAY
};

String functionName[4] = {
  "begin()",
  "on()",
  "off()",
  "play()"
};

void checkReturnValue(SimpleSoundFunctionReturnValue val, uint8_t funcType) {
  char buff[BUFFER_SIZE];
  memset(buff,0,BUFFER_SIZE);
  if (val == SSOUND_FUNCTION_UNSUPPORTED) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is unsupported.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
  if (val == SSOUND_FUNCTION_FAIL) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is failed.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
}

void setup_simple_sound(void) {
  SimpleSoundFunctionReturnValue value;

  value = ss.begin();
  checkReturnValue(value,FUNCTION_BEGIN);

  updateDeviceTable(deviceCounter, SIMPLE_SOUND_TYPE_NORMAL, &ss);
  simple_sound_num = deviceCounter;
  deviceCounter++;
  Serial.print("Simple sound device : device No. ");Serial.println(simple_sound_num);
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

int BassTab[]={SIMPLE_SOUND_C,SIMPLE_SOUND_D,SIMPLE_SOUND_E,SIMPLE_SOUND_F,SIMPLE_SOUND_G,SIMPLE_SOUND_A,SIMPLE_SOUND_B};
int durations[]={100,100,100,100,100,100,100};

int intervals[]={500,500,500,500,500,500,500};

void test1() {
  String about = "test1";
  printStartMessage(about, 0);
  // テスト内容の説明
  Serial.println("=== action ===");
  Serial.println("play sound scale.");
  waitForStart();

  simple_sound_play(7, BassTab, durations, intervals );

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

  setup_simple_sound();

  Serial.println("");
  Serial.println("");
  Serial.println("device and device driver test of simple sound device.");

  test1();
  sumTestResult();

}

void loop() {
}










