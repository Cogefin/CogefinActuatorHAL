


/* microSD filesystem structure

/-+-1-+-1.mp3  東京事変
  |   |
  |   +-2.mp3
  |   |
  |   +-3.mp3
  +-2---4.mp3    Sting
  |
  +-MP3-+-5.mp3  Hall and Oats
  |
  +-1.mp3 Shade
  |
  +-2.mp3
  |
  +-3.mp3
*/

/* microSD filesystem structure of DF player mini
/-+-01-+-001.mp3  東京事変
  |    |
  |    +-002.mp3
  |    |
  |    +-003.mp3
  |
  +-02-+-004.mp3    Sting
  |    |
  |    +-0999.mp3   Police
  |
  +-MP3-+-0005.mp3  Hall and Oats
  |
  +-1.mp3 Shade
  |
  +-2.mp3
  |
  +-3.mp3
*/

#include "ActuatorHAL.h"
#include <ArduinoJson.h>



/* Mega 2560 */
#if CPU_ARCH == AVR_ARCH
  #define COMSerial SSerial
  #define ShowSerial Serial
  #define _SET_SERIALS_
#endif /* CPU_ARCH == AVR_ARCH */

/* Uno R4 Series */
#if CPU_ARCH==RA4_ARCH
  #define COMSerial Serial1 // 0/RX, 1/TX
  #define ShowSerial Serial
  #define _SET_SERIALS_
#endif /* CPU_ARCH == RA4_ARCH */

/* Nano RP2040 connect */
#if HARDWARE_TYPE==ARDUINO_NANO_RP2040_C
  #define COMSerial Serial1
  #define ShowSerial Serial
  #define _SET_SERIALS_
#endif /* HARDWARE_TYPE==ARDUINO_NANO_RP2040_C */

/* Nano ESP32 */
#if HARDWARE_TYPE==ARDUINO_NANO_ESP32_S3
  #define COMSerial SSerial
  #define ShowSerial Serial
//  #define COMSerial Serial1  // D9/RX, D8/TX
//  #define ShowSerial Serial
  #define _SET_SERIALS_
#endif /* HARDWARE_TYPE==ARDUINO_NANO_ESP32_S3 */

/* Arduino M0 pro */
#if HARDWARE_TYPE==ARDUINO_M0
  #define COMSerial Serial1 // 0/RX, 1/TX
  #define ShowSerial Serial
  #define _SET_SERIALS_
#endif /* HARDWARE_TYPE==ARDUINO_M0 */

/* Arduino MKR Series */
#if (CPU_TYPE==TYPE_SAMD21G18A) && ( FORM_FACTOR_TYPE==FORM_FACTOR_MKR)
  #define COMSerial Serial1  // 13/RX, 14/TX
  #define ShowSerial Serial
  #define _SET_SERIALS_
#endif /* (CPU_TYPE==TYPE_SAMD21G18A) && ( FORM_FACTOR_TYPE==FORM_FACTOR_MKR) */

/* Nano 33 IoT */
#if HARDWARE_TYPE==ARDUINO_NANO_33_IOT
  #define COMSerial Serial1
  #define ShowSerial Serial
  #define _SET_SERIALS_
#endif /* HARDWARE_TYPE==ARDUINO_NANO_33_IOT */

/* Arduino Giga */
#if (HARDWARE_TYPE==ARDUINO_GIGA_WIFI_MAIN) || (HARDWARE_TYPE==ARDUINO_GIGA_WIFI_SUB)
  #define COMSerial Serial1 // D0/RX, D1/TX
  #define ShowSerial Serial
  #define _SET_SERIALS_
#endif /* (HARDWARE_TYPE==ARDUINO_GIGA_WIFI_MAIN) || (HARDWARE_TYPE==ARDUINO_GIGA_WIFI_SUB) */

/* Nano RP2040 Connect */
#if HARDWARE_TYPE==ARDUINO_NANO_RP2040_C
  #define COMSerial Serial1
  #define ShowSerial Serial
  #define _SET_SERIALS_
#endif /* HARDWARE_TYPE==ARDUINO_NANO_RP2040_C */

#ifndef _SET_SERIALS_
#error "no serail information defined"
#endif /* _SET_SERIALS_ */


#ifdef __USE_WT2605C_PLAYER__
#define COMSERIAL_SPEED 115200
#ifdef _SOFTWARE_SERIAL_
#if HARDWARE_TYPE==ARDUINO_NANO_ESP32_S3
WT2605C<EspSoftwareSerial> wt2605c_player;
#else /* HARDWARE_TYPE==ARDUINO_NANO_ESP32_S3 */
WT2605C<SoftwareSerial> wt2605c_player;
#endif /* HARDWARE_TYPE==ARDUINO_NANO_ESP32_S3 */
#else /* _SOFTWARE_SERIAL_ */
WT2605C<HardwareSerial> wt2605c_player;
#endif /* _SOFTWARE_SERIAL_ */
UnifiedMP3 Mp3Player(&wt2605c_player, WT2605C_PLAYER);
#define MP3_PLAYER_TYPE MP3_PLAYER_TYPE_WT2605C
#define USE_WT2605C_PLAYER
#endif /* __USE_WT2605C_PLAYER__ */

#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
#define COMSERIAL_SPEED 9600
DFRobotDFPlayerMini myDFPlayer;
UnifiedMP3 Mp3Player(&myDFPlayer, DF_ROBOT_DFP_PLAYER_MINI);
#define MP3_PLAYER_TYPE MP3_PLAYER_TYPE_DF_ROBOT_DFP
#define USE_DF_ROBOT_DF_PLAYER_MINI
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */

HardwareHelper hwHelper;

uint8_t deviceCounter=0;
uint8_t mp3_num=0;

#define MAX_TEST 4

struct testResultEntity {
  bool result;
  char about[BUFFER_SIZE];
  char comment[BUFFER_SIZE];
} testResult[MAX_TEST];

void mp3_stop(void) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_STOP;
  doc["paramSize"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec stop() : fail");
  }
}

void mp3_next(void) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_NEXT;
  doc["paramSize"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec next() : fail");
  }
}

void mp3_previous(void) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_PREVIOUS;
  doc["paramSize"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec previous() : fail");
  }
}

void mp3_volume(uint8_t vol) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_VOLUME;
  doc["paramSize"] = 1;
  doc["param"][0]["vol"] = vol;
  if (false == controlActuator(doc)) {
    Serial.println("exec volume() : fail");
  }
}

void mp3_volume_down(void) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_VOL_DOWN;
  doc["paramSize"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec volumeDown() : fail");
  }
}

void mp3_volume_up(void) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_VOL_UP;
  doc["paramSize"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec volumeUp() : fail");
  }
}

void mp3_pause(void) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_PAUSE;
  doc["paramSize"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec pause() : fail");
  }
}

void mp3_start(void) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_START;
  doc["paramSize"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec start() : fail");
  }
}

void mp3_play_by_index(uint32_t index, UnifiedMp3PlayerMode mode) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_PLAY_BY_INDEX;
  doc["paramSize"] = 1;
  doc["param"][0]["index"] = index;
  doc["param"][0]["mode"] = mode;
  if (false == controlActuator(doc)) {
    Serial.println("exec playByIndex() : fail");
  }
}

void mp3_play_by_name(const char* fileName, UnifiedMp3PlayerMode mode) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_PLAY_BY_NAME;
  doc["paramSize"] = 1;
  doc["param"][0]["name"] = fileName;
  doc["param"][0]["mode"] = mode;
  if (false == controlActuator(doc)) {
    Serial.println("exec playByName() : fail");
  }
}

void mp3_play_directory_by_number(uint8_t folderNumber, uint32_t fileNumber, UnifiedMp3PlayerMode mode) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_PLAY_DIR_BY_NUM;
  doc["paramSize"] = 1;
  doc["param"][0]["num"] = folderNumber;
  doc["param"][0]["file"] = fileNumber;
  doc["param"][0]["mode"] = mode;
  if (false == controlActuator(doc)) {
    Serial.println("exec playDirectoryByNumber() : fail");
  }
}

void mp3_play_directory_by_name(const char* dir, uint32_t fileNumber, UnifiedMp3PlayerMode mode) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_PLAY_DIR_BY_NAME;
  doc["paramSize"] = 1;
  doc["param"][0]["name"] = dir;
  doc["param"][0]["file"] = fileNumber;
  doc["param"][0]["mode"] = mode;
  if (false == controlActuator(doc)) {
    Serial.println("exec playDirectoryByName() : fail");
  }
}

void mp3_loop_dir(int folderNumber) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_LOOP_DIR;
  doc["paramSize"] = 1;
  doc["param"][0]["index"] = folderNumber;
  if (false == controlActuator(doc)) {
    Serial.println("exec loopDirectory() : fail");
  }
}

void mp3_play_mp3_dir(int folderNumber) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_PLAY_MP3_DIR;
  doc["paramSize"] = 1;
  doc["param"][0]["index"] = folderNumber;
  if (false == controlActuator(doc)) {
    Serial.println("exec playMp3Directory() : fail");
  }
}

void mp3_cut_in_play(UnifiedMp3PlayerStorage device, uint32_t index) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_CUT_IN_PLAY;
  doc["paramSize"] = 1;
  doc["param"][0]["storage"] = device;
  doc["param"][0]["index"] = index;
  if (false == controlActuator(doc)) {
    Serial.println("exec cutInPlay() : fail");
  }
}

void mp3_set_EQ(uint8_t eq) {
  JsonDocument doc;
  doc["id"] = mp3_num;
  doc["type"] = MP3_PLAYER_TYPE;
  doc["time"] = millis();
  doc["command"] = MP3_PLAYER_COMMAND_CUT_IN_PLAY;
  doc["paramSize"] = 1;
  doc["param"][0]["eq"] = eq;
  if (false == controlActuator(doc)) {
    Serial.println("exec setEQ() : fail");
  }
}

enum functionList {
  FUNCTION_STOP = 0,
  FUNCTION_NEXT,
  FUNCTION_PREVIOUS,
  FUNCTION_VOLUME,
  FUNCTION_VOLUME_DOWN,
  FUNCTION_VOLUME_UP,
  FUNCTION_SELECT_STORAGE,
  FUNCTION_PAUSE,
  FUNCTION_START,
  FUNCTION_PLAY_BY_INDEX,
  FUNCTION_PLAY_BY_NAME,
  FUNCTION_PLAY_DIR_BY_NUMBER,
  FUNCTION_PLAY_LARGE_DIR_BY_NUMBER,
  FUNCTION_PLAY_DIR_BY_NAME,
  FUNCTION_LOOP_DIR,
  FUNCTION_PLAY_MP3_DIR,
  FUNCTION_CUT_IN_PLAY,
  FUNCTION_SET_EQ
};

String functionName[FUNCTION_SET_EQ+1] = {
  "stop()",
  "next()",
  "previous()",
  "volume()",
  "volumeDown()",
  "volumeUp()",
  "selectStorage()",
  "pause()",
  "start()",
  "playByIndex()",
  "playByName()",
  "playDirectoryByNumber()",
  "playLargeDirectoryByNumber()",
  "playDirectoryByName()",
  "loopDirectory()",
  "playMp3Directory()",
  "cutInPlay()",
  "setEQ()"
};

void checkReturnValue(mp3FunctionReturnValue val, uint8_t funcType) {
  char buff[BUFFER_SIZE];
  memset(buff,0,BUFFER_SIZE);
  if (val == MP3_FUNCTION_UNSUPPORTED) {
    ShowSerial.println("");
    sprintf(buff,"executed function \"%s\" is unsupported.",functionName[funcType].c_str());
    ShowSerial.println(buff);
    return;
  }
  if (val == MP3_FUNCTION_FAIL) {
    ShowSerial.println("");
    sprintf(buff,"executed function \"%s\" is failed.",functionName[funcType].c_str());
    ShowSerial.println(buff);
    return;
  }
}

void setup_mp3(void) {
#ifdef USE_WT2605C_PLAYER
  wt2605c_player.init(COMSerial);
#endif /* USE_WT2605C_PLAYER */

#ifdef USE_DF_ROBOT_DF_PLAYER_MINI
  ShowSerial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(COMSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    ShowSerial.println(F("Unable to begin:"));
    ShowSerial.println(F("1.Please recheck the connection!"));
    ShowSerial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  ShowSerial.println(F("DFPlayer Mini online."));
#endif /* USE_DF_ROBOT_DF_PLAYER_MINI */

  mp3FunctionReturnValue value = Mp3Player.stop();
  checkReturnValue(value,FUNCTION_STOP);

  updateDeviceTable(deviceCounter, MP3_PLAYER_TYPE, &Mp3Player);
  mp3_num = deviceCounter;
  deviceCounter++;
  Serial.print("mp3 player device : device No. ");Serial.println(mp3_num);
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
  ShowSerial.println("=== action ===");
  ShowSerial.println("set volume : 25");
  ShowSerial.println("play num 1 of root directory");
  ShowSerial.println("wait 10 sec");
  ShowSerial.println("pause");
  ShowSerial.println("wait 10 sec");
  ShowSerial.println("re-start");
  ShowSerial.println("wait 10 sec");
  ShowSerial.println("stop");
  ShowSerial.println("");
  waitForStart();
  ShowSerial.println("start : test1");

  ShowSerial.println("play num 1 of root directory");
  ShowSerial.flush();
  mp3_play_by_index(1,MP3_MODE_SINGLE_SHOT);

  ShowSerial.println("set volume : 25");
  mp3_volume(25);

  ShowSerial.println("wait 10 sec");
  delay(10000);

  ShowSerial.println("pause");
  mp3_pause();

  ShowSerial.println("wait 10 sec");
  delay(10000);

  ShowSerial.println("re-start");
  mp3_start();

  ShowSerial.println("wait 10 sec");
  delay(10000);

  ShowSerial.println("stop");
  mp3_stop();

  checkTestResult(about, 0);
  ShowSerial.println("");
  ShowSerial.println("");

}

void test2() {
  String about = "test2";
  printStartMessage(about, 1);
  // テスト内容の説明
  ShowSerial.println("=== action ===");
  ShowSerial.println("set volume : 25");
  ShowSerial.println("play num 1 of root directory");
  ShowSerial.println("wait 10 sec");
  ShowSerial.println("next");
  ShowSerial.println("wait 10 sec");
  ShowSerial.println("next");
  ShowSerial.println("wait 10 sec");
  ShowSerial.println("prev");
  ShowSerial.println("wait 10 sec");
  ShowSerial.println("stop");
  ShowSerial.println("");
  waitForStart();
  ShowSerial.println("start : test2");

  ShowSerial.println("play num 1 of root directory");
  mp3_play_by_index(1,MP3_MODE_SINGLE_SHOT);

  ShowSerial.println("set volume : 25");
  mp3_volume(25);

  ShowSerial.println("wait 10 sec");
  delay(10000);

  ShowSerial.println("next");
  mp3_next();

  ShowSerial.println("wait 10 sec");
  delay(10000);

  ShowSerial.println("next");
  mp3_next();

  ShowSerial.println("wait 10 sec");
  delay(10000);

  ShowSerial.println("prev");
  mp3_previous();

  ShowSerial.println("wait 10 sec");
  delay(10000);

  ShowSerial.println("stop");
  mp3_stop();

  checkTestResult(about, 1);
  ShowSerial.println("");
  ShowSerial.println("");
}


#ifdef USE_WT2605C_PLAYER
#define LOOP_TIMES 4
#else
#define LOOP_TIMES 10
#endif

void test3() {
  String about = "test3";
  printStartMessage(about, 2);
  // テスト内容の説明
  ShowSerial.println("=== action ===");
  ShowSerial.println("set volume : 25");
  ShowSerial.println("play num 1 of root directory");
#ifdef USE_WT2605C_PLAYER
  ShowSerial.println("volume up and wait 5sec 4 times");
  ShowSerial.println("volume down and wait 5sec 4 times");
#else
  ShowSerial.println("volume up and wait 5sec 10times");
  ShowSerial.println("volume down and wait 5sec 10times");
#endif
  ShowSerial.println("stop");
  ShowSerial.println("");
  waitForStart();
  ShowSerial.println("start : test3");

  ShowSerial.println("play num 1 of root directory");
  mp3_play_by_index(1,MP3_MODE_SINGLE_SHOT);

  ShowSerial.println("set volume : 25");
  mp3_volume(25);
  delay(5000);

  for (int i=0; i< LOOP_TIMES ;i++) {
    ShowSerial.println("volume up and wait 5sec");
    mp3_volume_up();
    delay(5000);
  }
  for (int i=0; i< LOOP_TIMES ;i++) {
    ShowSerial.println("volume down and wait 5sec");
    mp3_volume_down();
    delay(5000);
  }

  ShowSerial.println("stop");
  mp3_stop();


  checkTestResult(about, 2);
  ShowSerial.println("");
  ShowSerial.println("");
}


void test4() {
  String about = "test4";
  printStartMessage(about, 3);
  // テスト内容の説明
  ShowSerial.println("=== action ===");

#ifdef USE_DF_ROBOT_DF_PLAYER_MINI
  ShowSerial.println("set volume : 25");
  ShowSerial.println("play file num 1 of dir num 1");
  ShowSerial.println("wait 10 sec");
  ShowSerial.println("play file num 2 of dir num 1");
  ShowSerial.println("wait 10 sec");
  ShowSerial.println("play file num 4 of dir num 2");
  ShowSerial.println("wait 10 sec");
#endif /* USE_DF_ROBOT_DF_PLAYER_MINI */
#ifdef USE_WT2605C_PLAYER
  ShowSerial.println("set volume : 10");
  ShowSerial.println("play file num 4 of dir num 1");
  ShowSerial.println("wait 10 sec");
  ShowSerial.println("play file num 5 of dir num 1");
  ShowSerial.println("wait 10 sec");
#endif /* USE_WT2605C_PLAYER */
  ShowSerial.println("stop");
  ShowSerial.println("");
  waitForStart();
  ShowSerial.println("start : test4");

#ifdef USE_DF_ROBOT_DF_PLAYER_MINI
  ShowSerial.println("set volume : 25");
  mp3_volume(25);

  ShowSerial.println("play file num 1 of dir num 1");
  mp3_play_directory_by_number(1,1,MP3_MODE_SINGLE_SHOT);

  ShowSerial.println("wait 10 sec");
  delay(10000);

  ShowSerial.println("play file num 2 of dir num 1");
  mp3_play_directory_by_number(1,2,MP3_MODE_SINGLE_SHOT);

  ShowSerial.println("wait 10 sec");
  delay(10000);

  ShowSerial.println("play file num 4 of dir num 2");
  mp3_play_directory_by_number(2,4,MP3_MODE_SINGLE_SHOT);

  ShowSerial.println("wait 10 sec");
  delay(10000);

  ShowSerial.println("stop");
  mp3_stop();
#endif /* USE_DF_ROBOT_DF_PLAYER_MINI */

#ifdef USE_WT2605C_PLAYER
  ShowSerial.println("play file index 4 of dir num 1");
  mp3_play_directory_by_number(4,1,MP3_MODE_SINGLE_SHOT);

  ShowSerial.println("set volume : 10");
  mp3_volume(10);

  ShowSerial.println("wait 10 sec");
  delay(10000);

  ShowSerial.println("play file index 5 of dir num 1");
  mp3_play_directory_by_number(5,1,MP3_MODE_SINGLE_SHOT);

  ShowSerial.println("wait 10 sec");
  delay(10000);

  ShowSerial.println("stop");
  mp3_stop();

#endif /* USE_WT2605C_PLAYER */

  checkTestResult(about, 3);
  ShowSerial.println("");
  ShowSerial.println("");
}

void setup() {
  COMSerial.begin(COMSERIAL_SPEED);
  ShowSerial.begin(9600);

  if (SERIAL_RESET) {
    while (!ShowSerial) {
      ; // wait for serial port to connect. Needed for native USB
    }
  } else {
    delay(3000);
  }

  ShowSerial.println("");
  ShowSerial.println("");
  ShowSerial.println("MP3 player device driver test.");
  ShowSerial.println("");

  setup_mp3();

  Serial.println("");
  Serial.println("");
  Serial.println("device and device driver test of simple sound device.");

  test1();
  test2();
  test3();
  test4();
  sumTestResult();

}

void loop() {
}










