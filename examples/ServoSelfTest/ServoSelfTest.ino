
#include "ActuatorHAL.h"
#include <ArduinoJson.h>

HardwareHelper hwHelper;

/*
 * Arduino機種の選択
 */
#if CPU_TYPE==TYPE_ESP32
#define SERVO_HERZ 50
#define MIN_US 500
#define MAX_US 2400
#endif /* ARDUINO_NANO_ESP32 */

Servo myservo;
ServoHal servoHal(&myservo);

uint8_t deviceCounter=0;
uint8_t servo_num=0;

#define MAX_TEST 2

struct testResultEntity {
  bool result;
  char about[BUFFER_SIZE];
  char comment[BUFFER_SIZE];
} testResult[MAX_TEST];

void servo_write(int angle) {
  JsonDocument doc;
  doc["id"] = servo_num;
  doc["type"] = SERVO_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = SERVO_COMMAND_WRITE;
  doc["paramSize"] = 1;
  doc["param"][0]["angle"] = angle;
  if (false == controlActuator(doc)) {
    Serial.println("exec write() : fail");
  }
}

void servo_writeMS(int msec) {
  JsonDocument doc;
  doc["id"] = servo_num;
  doc["type"] = SERVO_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = SERVO_COMMAND_WRITE_MS;
  doc["paramSize"] = 1;
  doc["param"][0]["msec"] = msec;
  if (false == controlActuator(doc)) {
    Serial.println("exec writeMS() : fail");
  }
}

enum functionList {
  FUNCTION_WRITE = 0,
  FUNCTION_WRITE_MS
};

String functionName[2] = {
  "write()",
  "writeMS()"
};

void checkReturnValue(ServoHalFunctionReturnValue val, uint8_t funcType) {
  char buff[BUFFER_SIZE];
  memset(buff,0,BUFFER_SIZE);
  if (val == SERVO_FUNCTION_UNSUPPORTED) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is unsupported.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
  if (val == SERVO_FUNCTION_FAIL) {
    Serial.println("");
    sprintf(buff,"executed function \"%s\" is failed.",functionName[funcType].c_str());
    Serial.println(buff);
    return;
  }
}

void setup_Servo(void) {
  Serial.println("");
  Serial.println("");
  Serial.println("servo device driver test.");
  Serial.println("");


#if CPU_TYPE==TYPE_ESP32
  myservo.setPeriodHertz(SERVO_HERZ);      // Standard 50hz servo
  myservo.attach(SERVO_PIN, MIN_US, MAX_US);
  myservo.attach(SERVO_PIN);
#else /* ARDUINO_NANO_ESP32 */
  myservo.attach(SERVO_PIN);
#endif /* ARDUINO_NANO_ESP32 */

  updateDeviceTable(deviceCounter, SERVO_TYPE_SIMPLE, &servoHal);
  servo_num = deviceCounter;
  deviceCounter++;
  Serial.print("Servo : device No. ");Serial.println(servo_num);
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
  Serial.println("move 1 deg x 180 times (180deg)");
  Serial.println("=== 2nd action ===");
  Serial.println("move 5 deg x 36 times (180deg)");
  Serial.println("");
  waitForStart();

  // 1st action
  for (int i=0; i<180 ; i++) {
    servo_write(i);
    delay(50);
  }
  for (int i=180; i>=0 ; i--) {
    servo_write(i);
    delay(50);
  }
  // 2nd action
  for (int i=0; i<180 ; i+=5) {
    servo_write(i);
    delay(50);
  }
  for (int i=180; i>=0 ; i-=5) {
    servo_write(i);
    delay(50);
  }

  checkTestResult(about, 0);
  Serial.println("");
  Serial.println("");

  servo_write(0);

}

void test2() {
  String about = "test2";
  printStartMessage(about, 1);
  // テスト内容の説明
  Serial.println("=== action ===");
  Serial.println("move servo 700ms-1500ms");
  Serial.println("");
  waitForStart();


  // action
  for (int i=700; i<1501 ; i+=100) {
    servo_writeMS(i);
    delay(100);
  }

  checkTestResult(about, 1);
  Serial.println("");
  Serial.println("");
  servo_write(0);
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

  setup_Servo();

  Serial.println("");
  Serial.println("");
  Serial.println("device and device driver test of simple PMW.");

  test1();
  test2();
  sumTestResult();

}

void loop() {
}








