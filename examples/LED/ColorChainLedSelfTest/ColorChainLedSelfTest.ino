


#include "ActuatorHAL.h"
#include <ArduinoJson.h>

HardwareHelper hwHelper;

#ifdef GROVE_CHAINABLE_LED
#define LED_TYPE_NUM P98X3_LED
#define NUM_LED GROVE_CHAINABLE_LED_NUM_OF_LED
ChainableLED chain(GROVE_CHAINABLE_LED_PIN_CLK, GROVE_CHAINABLE_LED_PIN_DATA, NUM_LED);
UnifiedLED ledChain(&(chain), P98X3_LED, NUM_LED);
#endif /* GROVE_CHAINABLE_LED */

#ifdef GROVE_NEO_PIXEL
#define LED_TYPE_NUM NEO_PIXEL_LED
#define NUM_LED LED_NEO_PIXEL_NUM_OF_LED
Adafruit_NeoPixel strip(NUM_LED, LED_NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);
UnifiedLED neoPixel(&(strip), NEO_PIXEL_LED, NUM_LED);
#endif /* GROVE_NEO_PIXEL */

uint8_t deviceCounter=0;
uint8_t led_num=0;

#define MAX_TEST 1
#define INTERVAL 1

struct testResultEntity {
  bool result;
  char about[BUFFER_SIZE];
  char comment[BUFFER_SIZE];
} testResult[MAX_TEST];

void setLed(uint32_t ledNo, byte red, byte green, byte blue) {
  JsonDocument doc;
  doc["id"] = led_num;
  doc["type"] = LED_TYPE_COLOR_CHAIN_LED;
  doc["time"] = millis();
  doc["command"] = LED_COMMAND_SET_RGB_N;
  doc["paramSize"] = 1;
  doc["param"][0]["num"] = ledNo;
  doc["param"][0]["red"] = red;
  doc["param"][0]["green"] = green;
  doc["param"][0]["blue"] = blue;
  if (false == controlActuator(doc)) {
    Serial.println("exec setLed() : fail");
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

  Serial.println("");
  Serial.println("");
  Serial.println("color chain led device driver test.");
  Serial.println("");

  ledFunctionReturnValue value;

#ifdef GROVE_CHAINABLE_LED
  value = ledChain.begin();
  checkReturnValue(value, FUNCTION_BEGIN);
  for (int i=0; i< NUM_LED; i++) {
    value = ledChain.setLed(i,0,0,0);
    checkReturnValue(value, FUNCTION_SET_LED);
  }
  updateDeviceTable(deviceCounter, LED_TYPE_COLOR_CHAIN_LED, &ledChain);
#endif /* GROVE_CHAINABLE_LED */
#ifdef GROVE_NEO_PIXEL
  value = neoPixel.begin();
  checkReturnValue(value, FUNCTION_BEGIN);
  for (int i=0; i< NUM_LED; i++) {
    value = neoPixel.setLed(i,0,0,0);
    checkReturnValue(value, FUNCTION_SET_LED);
  }
  updateDeviceTable(deviceCounter, LED_TYPE_COLOR_CHAIN_LED, &neoPixel);
#endif /* GROVE_NEO_PIXEL */

  led_num = deviceCounter;
  deviceCounter++;
  Serial.print("Color chain led : device No. ");Serial.println(led_num);
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
  Serial.println("change color : r,g,b,white using setLed()");
  Serial.println("");
  waitForStart();

  Serial.println("test1 start.");

  for (int i=0; i<NUM_LED; i++) {
    for (int j=0; j<256;j++) {
      setLed(i,j,0,0);
      delay(INTERVAL);
    }
    for (int j=0; j<256;j++) {
      setLed(i,0,j,0);
      delay(INTERVAL);
    }
    for (int j=0; j<256;j++) {
      setLed(i,0,0,j);
      delay(INTERVAL);
    }
    for (int j=0; j<256;j++) {
      setLed(i,j,j,j);
      delay(INTERVAL);
    }
  }


  checkTestResult(about, 0);
  Serial.println("");
  Serial.println("");

  for (int i=0; i<NUM_LED; i++) {
    setLed(i,0,0,0);
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
  Serial.println("device and device driver test of chain color led.");

  test1();
  sumTestResult();

}

void loop() {
}







