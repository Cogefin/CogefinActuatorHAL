


#define INTERVAL 2000

#define REPEAT_NUM 2
//#define REPEAT_NUM NO_REPEATS


#if !defined(ARDUINO_ESP32C3_DEV) // This is due to a bug in RISC-V compiler, which requires unused function sections :-(.
#define DISABLE_CODE_FOR_RECEIVER // Disables static receiver code like receive timer ISR handler and static IRReceiver and irparams data. Saves 450 bytes program memory and 269 bytes RAM if receiving functions are not required.
#endif
//#define SEND_PWM_BY_TIMER         // Disable carrier PWM generation in software and use (restricted) hardware PWM.
//#define USE_NO_SEND_PWM           // Use no carrier PWM, just simulate an active low receiver signal. Overrides SEND_PWM_BY_TIMER definition

/*
 * This include defines the actual pin number for pins like IR_RECEIVE_PIN, IR_SEND_PIN for many different boards and architectures
 */

#include "PinDefinitionsAndMore.h"
//#include <IRremote.hpp>

#include "ActuatorHAL.h"
#include <ArduinoJson.h>

HardwareHelper hwHelper;


uint8_t deviceCounter=0;
uint8_t irda_num=0;




/*
 * Set up the data to be sent.
 * For most protocols, the data is build up with a constant 8 (or 16 byte) address
 * and a variable 8 bit command.
 * There are exceptions like Sony and Denon, which have 5 bit address.
 */


void sendNEC() {
  //uint8_t sCommand = 0x34;
  //uint8_t sRepeats = REPEAT_NUM;
  uint16_t addr = 0;
  uint16_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;

  Serial.println(F("Send standard NEC with 8 bit address"));
  Serial.flush();

  // Receiver output for the first loop must be: Protocol=NEC Address=0x102 Command=0x34 Raw-Data=0xCB340102 (32 bits)
  //IrSender.sendNEC(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_NEC;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = REPEAT_NUM;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendNEC() : fail");
  }
}

void sendSamsung() {
  uint16_t addr = 0;
  uint16_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send standard Samsung with 8 bit address"));
  Serial.flush();

  // Receiver output for the first loop must be: Protocol=NEC Address=0x102 Command=0x34 Raw-Data=0xCB340102 (32 bits)
  //IrSender.sendSamsung(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_SAMSUNG;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendSamsung() : fail");
  }
}

void sendSamsung48() {
  uint16_t addr = 0;
  uint32_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send Samsung48 with 8 bit address"));
  Serial.flush();

  // Receiver output for the first loop must be: Protocol=NEC Address=0x102 Command=0x34 Raw-Data=0xCB340102 (32 bits)
  //IrSender.sendSamsung48(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_SAMSUNG_48;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendSamsung() : fail");
  }
}

void sendSamsungLG() {
  uint16_t addr = 0;
  uint16_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send Samsung/LG with 8 bit address"));
  Serial.flush();

  // Receiver output for the first loop must be: Protocol=NEC Address=0x102 Command=0x34 Raw-Data=0xCB340102 (32 bits)
  //IrSender.sendSamsungLG(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_SAMSUNG_LG;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendSamsungLG() : fail");
  }
}

void sendSony() {
  uint16_t addr = 0;
  uint8_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  uint8_t bits=12;
  Serial.println(F("Send Sony with 8 bit address"));
  Serial.flush();

  //IrSender.sendSony(addr, sCommand, sRepeats, bits);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_SONY;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  doc["param"][0]["bits"] = bits;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendSony() : fail");
  }
}

void sendPanasonic() {
  uint16_t addr = 0;
  uint8_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send panasonic with 8 bit address"));
  Serial.flush();

  //IrSender.sendPanasonic(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_PANASONIC;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendPanasonic() : fail");
  }
}

void sendDenon() {
  uint8_t addr = 0;
  uint8_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send Denon with 8 bit address"));
  Serial.flush();

  //IrSender.sendDenon(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_DENON;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  doc["param"][0]["flag"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendDenon() : fail");
  }
}

void sendSharp() {
  uint8_t addr = 0;
  uint8_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send Sharp with 8 bit address"));
  Serial.flush();

  //IrSender.sendSharp(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_SHARP;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendSharp() : fail");
  }
}

void sendLG() {
  uint8_t addr = 0;
  uint16_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send LG with 8 bit address"));
  Serial.flush();

  //IrSender.sendLG(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_LG;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendLG() : fail");
  }
}

void sendJVC() {
  uint8_t address = 0;
  uint8_t command = 0x1;
  int_fast8_t repeats = REPEAT_NUM;
  Serial.println(F("Send JVC with 8 bit address"));
  Serial.flush();

  //IrSender.sendJVC(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_LG;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = address;
  doc["param"][0]["command"] = command;
  doc["param"][0]["repeats"] = repeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendJVC() : fail");
  }
}

void sendRC5() {
  uint8_t addr = 0;
  uint8_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send RC5 with 8 bit address"));
  Serial.flush();

  //IrSender.sendRC5(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_RC5;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  doc["param"][0]["flag"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendRC5() : fail");
  }
}

void sendRC6() {
  uint8_t addr = 0;
  uint8_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send RC6 with 8 bit address"));
  Serial.flush();

  //IrSender.sendRC6(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_RC6_3;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  doc["param"][0]["flag"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendRC6() : fail");
  }
}

void sendKaseikyoJVC() {
  uint16_t addr = 0;
  uint8_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send Kaseikyo JVC with 16 bit address"));
  Serial.flush();

  //IrSender.sendKaseikyo_JVC(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_KASEIKYO_JVC;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendKaseikyo_JVC() : fail");
  }
}

void sendKaseikyoDenon() {
  uint16_t addr = 0;
  uint8_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send Kaseikyo Denon with 16 bit address"));
  Serial.flush();

  //IrSender.sendKaseikyo_Denon(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_KASEIKYO_DENON;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendKaseikyo_Denon() : fail");
  }
}

void sendKaseikyoSharp() {
  uint16_t addr = 0;
  uint8_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send Kaseikyo Sharp with 16 bit address"));
  Serial.flush();

  //IrSender.sendKaseikyo_Sharp(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_KASEIKYO_SHARP;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendKaseikyo_Sharp() : fail");
  }
}

void sendKaseikyoMitsubishi() {
  uint16_t addr = 0;
  uint8_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send Kaseikyo Mitsubishi with 16 bit address"));
  Serial.flush();

  //IrSender.sendKaseikyo_Mitsubishi(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_KASEIKYO_MITSUBISHI;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendKaseikyo_Mitsubishi() : fail");
  }
}

void sendNEC2() {
  uint16_t addr = 0;
  uint16_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send NEC rev.2 protocol with 16 bit address"));
  Serial.flush();

  //IrSender.sendNEC2(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_NEC_2;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendNEC2() : fail");
  }
}

void sendOnkyo() {
  uint16_t addr = 0;
  uint16_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send Onkyo with 16 bit address"));
  Serial.flush();

  //IrSender.sendOnkyo(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_ONKYO;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendOnkyo() : fail");
  }
}

void sendApple() {
  uint8_t addr = 0;
  uint8_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send Apple with 8 bit address"));
  Serial.flush();

  //IrSender.sendApple(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_APPLE;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendApple() : fail");
  }
}

void sendLG2() {
  uint8_t addr = 0;
  uint16_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send LG2 with 8 bit address"));
  Serial.flush();

  //IrSender.sendLG2(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_LG_2;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendLG2() : fail");
  }
}

void sendBangOlufsen() {
  uint16_t header = 0;
  uint8_t data = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  int8_t bits = 8;
  Serial.println(F("Send BangOlufsen with 16 bit address"));
  Serial.flush();

  //IrSender.sendBangOlufsen(addr, sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_BANG_OLUFSEN;
  doc["paramSize"] = 1;
  doc["param"][0]["header"] = header;
  doc["param"][0]["data"] = data;
  doc["param"][0]["repeats"] = sRepeats;
  doc["param"][0]["bits"] = bits;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendBangOlufsen() : fail");
  }
}
/*
 * exotic protocols
 */
void sendKaseikyo() {
  uint16_t addr = 0;
  uint8_t data = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  uint16_t vendor = 0xFFFF;
  Serial.println(F("Send Kaseikyo"));
  Serial.flush();

  //IrSender.sendKaseikyo(addr, data, sRepeats, vendor);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_KASEIKYO;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = data;
  doc["param"][0]["repeats"] = sRepeats;
  doc["param"][0]["vendor"] = vendor;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendKaseikyo() : fail");
  }
}

void sendRC6A() {
  uint8_t addr = 0;
  uint8_t command = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  uint16_t customer = 0x0FFF;
  Serial.println(F("Send RC6A"));
  Serial.flush();

  //IrSender.sendRC6A(addr, command, sRepeats, customer);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_RC6_A;
  doc["paramSize"] = 1;
  doc["param"][0]["address"] = addr;
  doc["param"][0]["command"] = command;
  doc["param"][0]["repeats"] = sRepeats;
  doc["param"][0]["customer"] = customer;
  doc["param"][0]["flag"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendRC6A() : fail");
  }
}

void sendWhynter() {
  uint32_t data = 0x10F230F4;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send Whynter"));
  Serial.flush();

  //IrSender.sendWhynter(data, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_WHYNTER;
  doc["paramSize"] = 1;
  doc["param"][0]["data"] = data;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendWhynter() : fail");
  }
}

void sendBoseWave() {
  uint8_t sCommand = 0x1;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send BoseWave"));
  Serial.flush();

  //IrSender.sendBoseWave(sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_BOSE_WAVE;
  doc["paramSize"] = 1;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendBoseWave() : fail");
  }
}

void sendMagiQuest() {
  uint32_t wid = 0;
  uint16_t magnitude = 0x1;
  Serial.println(F("Send Magi Quest"));
  Serial.flush();

  //IrSender.sendMagiQuest(addr, sCommand);
  //delay(INTERVAL);
  //IrSender.sendMagiQuest(addr, sCommand);
  //delay(INTERVAL);
  //IrSender.sendMagiQuest(addr, sCommand);
  for (int i=0; i<REPEAT_NUM; i++) {
    JsonDocument doc;
    doc["id"] = irda_num;
    doc["type"] = IRDA_TYPE_SIMPLE;
    doc["time"] = millis();
    doc["command"] = IRDA_COMMAND_MAGIC_QUEST;
    doc["paramSize"] = 1;
    doc["param"][0]["wid"] = wid;
    doc["param"][0]["magnitude"] = magnitude;
    if (false == controlActuator(doc)) {
      Serial.println("exec sendMagiQuest() : fail");
    }
    delay(INTERVAL);
  }
}

void sendFast() {
  //uint16_t sCommand = 0x012F;
  uint16_t sCommand = 0xFF;
  int_fast8_t sRepeats = REPEAT_NUM;
  Serial.println(F("Send Fast"));
  Serial.flush();

  //IrSender.sendFAST(sCommand, sRepeats);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_FAST;
  doc["paramSize"] = 1;
  doc["param"][0]["command"] = sCommand;
  doc["param"][0]["repeats"] = sRepeats;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendFAST() : fail");
  }
}

void sendLegoPowerFunctions() {
  uint8_t channel = 0x0F;
  uint8_t command = 0x01;
  uint8_t mode = 0xFF;
  Serial.println(F("Send PowerFunctions"));
  Serial.flush();

  //IrSender.sendLegoPowerFunctions(channel, command, mode, true);
  JsonDocument doc;
  doc["id"] = irda_num;
  doc["type"] = IRDA_TYPE_SIMPLE;
  doc["time"] = millis();
  doc["command"] = IRDA_COMMAND_LEGO;
  doc["paramSize"] = 1;
  doc["param"][0]["channel"] = channel;
  doc["param"][0]["command"] = command;
  doc["param"][0]["mode"] = mode;
  doc["param"][0]["flag"] = 0;
  if (false == controlActuator(doc)) {
    Serial.println("exec sendLegoPowerFunctions() : fail");
  }
}

void runTest() {
  /*
   * exotic protocols
   */
  sendWhynter();
  delay(INTERVAL);
  sendBoseWave();
  delay(INTERVAL);
  sendMagiQuest();
  delay(INTERVAL);
  sendFast();
  delay(INTERVAL);
  sendLegoPowerFunctions();
  delay(INTERVAL);
  /*
   * unstable implementation
   */
  sendLG2();
  delay(INTERVAL);
  sendSharp();
  delay(INTERVAL);
  sendBangOlufsen();
  delay(INTERVAL);
  /*
   * real test target
   */
  sendNEC();
  delay(INTERVAL);
  sendSamsung();
  delay(INTERVAL);
  sendSamsung48();
  delay(INTERVAL);
  sendSamsungLG();
  delay(INTERVAL);
  sendSony();
  delay(INTERVAL);
  sendDenon();
  delay(INTERVAL);
  sendLG();
  delay(INTERVAL);
  sendJVC();
  delay(INTERVAL);
  sendRC5();
  delay(INTERVAL);
  sendRC6();
  delay(INTERVAL);
  sendRC6A();
  delay(INTERVAL);
  sendKaseikyo();
  delay(INTERVAL);
  sendKaseikyoJVC();
  delay(INTERVAL);
  sendKaseikyoDenon();
  delay(INTERVAL);
  sendKaseikyoSharp();
  delay(INTERVAL);
  sendKaseikyoMitsubishi();
  delay(INTERVAL);
  sendOnkyo();
  delay(INTERVAL);
  sendNEC2();
  delay(INTERVAL);
  sendApple();
  delay(INTERVAL);
  sendPanasonic();
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

void printStartMessage(String about, uint8_t testNumber){
  char message[BUFFER_SIZE];
  for (int i=0; i<BUFFER_SIZE ; i++ ){
    message[i]=0;
  }
  sprintf(message,"Wait for start test No.%d (%s)",testNumber+1, about.c_str());
  Serial.println(message);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);


  if (SERIAL_RESET) {
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB
    }
  } else {
    delay(3000);
  }


  Serial.println("");
  Serial.println("");
  Serial.println("device and device driver test of IRDA.");

  // Just to know which program is running on my Arduino
  //Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
  Serial.print(F("Send IR signals at pin "));
  Serial.println(IR_SEND_PIN);

  /*
   * The IR library setup. That's all!
   */
  //init_ir_sender(IR_SEND_PIN,deviceCounter);
  init_ir_sender(deviceCounter, IRDA_TYPE_SIMPLE, IR_SEND_PIN);
  //init_ir_sender(3,deviceCounter);
  //IrSender.begin(); // Start with IR_SEND_PIN -which is defined in PinDefinitionsAndMore.h- as send pin and enable feedback LED at default feedback LED pin
  //disableLEDFeedback(); // Disable feedback LED at default feedback LED pin

  //updateDeviceTable(deviceCounter, IRDA_TYPE_SIMPLE, &IrSender);
  //updateDeviceTable(deviceCounter, IRDA_TYPE_SIMPLE);
  irda_num = deviceCounter;
  deviceCounter++;
  Serial.print("IRDA device : device No. ");Serial.println(irda_num);

  waitForStart();

  runTest();
}

void loop() {
}
