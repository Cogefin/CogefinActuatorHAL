/*
 * SimpleReceiverWithCallback.cpp
 *
 * Demonstrates receiving NEC IR codes with IRrecv
 *
 *  This file is part of Arduino-IRremote https://github.com/Arduino-IRremote/Arduino-IRremote.
 *
 ************************************************************************************
 * MIT License
 *
 * Copyright (c) 2022 Armin Joachimsmeyer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 ************************************************************************************
 */


#include <Arduino.h>

#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>

/*
 * For callback
 */
#define PROCESS_IR_RESULT_IN_MAIN_LOOP
#if defined(PROCESS_IR_RESULT_IN_MAIN_LOOP) || defined(ARDUINO_ARCH_MBED) || defined(ESP32)
volatile bool sIRDataJustReceived = false;
#endif
void ReceiveCompleteCallbackHandler();

uint8_t checkResult[FAST+1];

void setupCorrectData() {
  for (int i=0; i< (FAST+1); i++) {
    checkResult[i]=0;
  }
}

void dumpIrData(IRData data) {
  Serial.print("protocol        (decode_type_t) : ");Serial.println(data.protocol);
  Serial.print("address         (uint16_t)      : ");Serial.println(data.address,HEX);
  Serial.print("command         (uint16_t)      : ");Serial.println(data.command,HEX);
  Serial.print("extra           (uint16_t)      : ");Serial.println(data.extra,HEX);
  Serial.print("numberOfBits    (uint16_t)      : ");Serial.println(data.numberOfBits);
  Serial.print("flags           (uint8_t)       : ");Serial.println(data.flags,HEX);
  Serial.print("rawlen          (IRRawlenType)  : ");Serial.println(data.rawlen);
  Serial.print("initialGapTicks (uint16_t)      : ");Serial.println(data.initialGapTicks,HEX);
  Serial.print("decodedRawData  (IRRawDataType) : ");Serial.println(data.decodedRawData,HEX);
}

void setup() {
  Serial.begin(9600);
  setupCorrectData();

  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  IrReceiver.registerReceiveCompleteCallback(ReceiveCompleteCallbackHandler);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
}

void printIrData() {
  IrReceiver.printIRResultShort(&Serial);
  IrReceiver.printIRSendUsage(&Serial);
  Serial.println();
}

uint8_t checkData(IRData data) {
  if ((data.address == 0) && (data.command == 1)) return 1;
  return 2;
}

uint8_t checkDataWithExtra(IRData data, uint16_t extra) {
  if ((data.address == 0) && (data.command == 1) && (data.extra == extra)) return 1;
  return 2;
}

uint8_t checkCommandOnly(IRData data, uint16_t command) {
  if (data.command == command) return 1;
  return 2;
}

uint8_t checkRawDataOnly(IRData data, uint32_t value) {
  if (data.decodedRawData == value) return 1;
  return 2;
}


String protocolName[] = {
  "UNKOWN",
  "Pulse Width",
  "Pulse Distance",
  "Apple",
  "Denon",
  "JVC",
  "LG",
  "LG2",
  "NEC",
  "NEC2",
  "Onkyo",
  "Panasonic",
  "Kaseikyo",
  "Kaseikyo Denon",
  "Kaseikyo Sharp",
  "Kaseikyo JVC",
  "Kaseikyo Mitsubishi",
  "RC5",
  "RC6",
  "RC6A",
  "Samsung",
  "Samsung/LG",
  "Samsung48",
  "Sharp",
  "Sony",
  "Bang Olufsen",
  "Bose Wave",
  "Lego PF",
  "Magi Quest",
  "Whynter",
  "Fast",
  "Other"
};

void final() {
  uint8_t success=0;
  uint8_t skip = 0;
  uint8_t error = 0;
  for (int i=3; i< 31; i++) {
    Serial.print("Protocol - ");Serial.print(protocolName[i]);Serial.print(" : ");
    if (checkResult[i]==2) {
      Serial.println("***error***");
      error ++;
    } else if (checkResult[i]==1) {
      Serial.println("***test success***");
      success++;
    } else {
      Serial.println("***test skip***");
      skip++;
    }
  }
  Serial.println("");
  Serial.println("Total result:");
  Serial.print("Success : ");Serial.println(success);
  Serial.print("Skip    : ");Serial.println(skip);
  Serial.print("Error   : ");Serial.println(error);
}

void loop() {
  /*
   * Print in loop (interrupts are enabled here) if received data is available.
   */
  if (sIRDataJustReceived) {
    sIRDataJustReceived = false;
    // Print a summary of received data
    switch(IrReceiver.decodedIRData.protocol) {
      case APPLE: {
        if (checkResult[APPLE]!=1) {
          checkResult[APPLE]=checkData(IrReceiver.decodedIRData);
        };
        IrReceiver.stop();
        printIrData();
        final();
        return ;
        //break;
      };
      case DENON: {
        if (checkResult[DENON]!=1) {
          checkResult[DENON]=checkData(IrReceiver.decodedIRData);
        };
        break;
      };
      case JVC: {
        if (checkResult[JVC]!=1) {
          checkResult[JVC]=checkData(IrReceiver.decodedIRData);
        };
        dumpIrData(IrReceiver.decodedIRData);
        break;
      };
      case LG: {
        if (checkResult[LG]!=1) {
          checkResult[LG]=checkData(IrReceiver.decodedIRData);
        };
        break;
      };
      case LG2: {
        if (checkResult[LG2]!=1) {
          checkResult[LG2]=checkData(IrReceiver.decodedIRData);
        };
        dumpIrData(IrReceiver.decodedIRData);
        break;
      };
      case NEC: {
        if (checkResult[NEC]!=1) {
          checkResult[NEC]=checkData(IrReceiver.decodedIRData);
        };
        break;
      };
      case NEC2: {
        if (checkResult[NEC2]!=1) {
          checkResult[NEC2]=checkData(IrReceiver.decodedIRData);
        };
        break;
      };
      case ONKYO: {
        if (checkResult[ONKYO]!=1) {
          checkResult[ONKYO]=checkData(IrReceiver.decodedIRData);
        };
        break;
      };
      case PANASONIC: {
        if (checkResult[PANASONIC]!=1) {
          checkResult[PANASONIC]=checkData(IrReceiver.decodedIRData);
        }
        break;
      };
      case KASEIKYO_DENON: {
        if (checkResult[KASEIKYO_DENON]!=1) {
          checkResult[KASEIKYO_DENON]=checkData(IrReceiver.decodedIRData);
        };
        break;
      };
      case KASEIKYO_SHARP: {
        if (checkResult[KASEIKYO_SHARP]!=1) {
          checkResult[KASEIKYO_SHARP]=checkData(IrReceiver.decodedIRData);
        };
        break;
      };
      case KASEIKYO_JVC: {
        if (checkResult[KASEIKYO_JVC]!=1) {
          checkResult[KASEIKYO_JVC]=checkData(IrReceiver.decodedIRData);
        };
        break;
      };
      case KASEIKYO_MITSUBISHI: {
        if (checkResult[KASEIKYO_MITSUBISHI]!=1) {
          checkResult[KASEIKYO_MITSUBISHI]=checkData(IrReceiver.decodedIRData);
        };
        break;
      };
      case RC5: {
        if (checkResult[RC5]!=1) {
          checkResult[RC5]=checkData(IrReceiver.decodedIRData);
        };
        break;
      };
      case RC6: {
        if (checkResult[RC6]!=1) {
          checkResult[RC6]=checkData(IrReceiver.decodedIRData);
        };
        break;
      };
      case SAMSUNG: {
        if (checkResult[SAMSUNG]!=1) {
          checkResult[SAMSUNG]=checkData(IrReceiver.decodedIRData);
        };
        break;
      };
      case SAMSUNGLG: {
        if (checkResult[SAMSUNGLG]!=1) {
          checkResult[SAMSUNGLG]=checkData(IrReceiver.decodedIRData);
        };
        break;
      };
      case SAMSUNG48: {
        if (checkResult[SAMSUNG48]!=1) {
          checkResult[SAMSUNG48]=checkData(IrReceiver.decodedIRData);
        };
        break;
      };
      case SHARP: {
        if (checkResult[SHARP]!=1) {
          //IrReceiver.decodedIRData.command = ~IrReceiver.decodedIRData.command;
          checkResult[SHARP]=checkData(IrReceiver.decodedIRData);
        };
        dumpIrData(IrReceiver.decodedIRData);
        break;
      };
      case SONY: {
        if (checkResult[SONY]!=1) {
          checkResult[SONY]=checkData(IrReceiver.decodedIRData);
        };
        break;
      };
      case BANG_OLUFSEN: {
        if (checkResult[BANG_OLUFSEN]!=1) {
          checkResult[BANG_OLUFSEN]=checkData(IrReceiver.decodedIRData);
        };
        dumpIrData(IrReceiver.decodedIRData);
        break;
      };
      /* Exiotic Protocols */
      case KASEIKYO: { // checkDataWithExtra
        if (checkResult[KASEIKYO]!=1) {
          checkResult[KASEIKYO]=checkDataWithExtra(IrReceiver.decodedIRData, 0xFFFF);
        };
        //Serial.println("detect : *KASEIKYO*");
        //dumpIrData(IrReceiver.decodedIRData);
        break;
      };
      case RC6A: {
        if (checkResult[RC6A]!=1) {
          checkResult[RC6A]=checkDataWithExtra(IrReceiver.decodedIRData, 0x0FFF); // extraの最大値は0x3FFF
        };
        //checkResult[RC6A]=checkDataWithExtra(IrReceiver.decodedIRData, 0x0FFF); // extraの最大値は0x3FFF
        //Serial.println("detect : *RC6A*");
        //dumpIrData(IrReceiver.decodedIRData);
        break;
      };
      case WHYNTER: { // checkRawDataOnly
        if (checkResult[WHYNTER]!=1) {
          checkResult[WHYNTER]=checkRawDataOnly(IrReceiver.decodedIRData,(uint32_t) 0x10F230F4);
        };
        //checkResult[WHYNTER]=checkRawDataOnly(IrReceiver.decodedIRData, 0x10F230F4);
        //Serial.println("detect : *WHYNTER*");
        //dumpIrData(IrReceiver.decodedIRData);
        break;
      };
      case BOSEWAVE: { // checkCommandOnly
        if (checkResult[BOSEWAVE]!=1) {
          checkResult[BOSEWAVE]=checkCommandOnly(IrReceiver.decodedIRData, 0x01);
        };
        //checkResult[BOSEWAVE]=checkCommandOnly(IrReceiver.decodedIRData, 0x01);
        //Serial.println("detect : *BOSEWAVE*");
        //dumpIrData(IrReceiver.decodedIRData);
        break;
      };
      case MAGIQUEST: {
        if (checkResult[MAGIQUEST]!=1) {
          checkResult[MAGIQUEST]=checkData(IrReceiver.decodedIRData);
        };
        //checkResult[MAGIQUEST]=checkData(IrReceiver.decodedIRData);
        //Serial.println("detect : *MAGIQUEST*");
        //dumpIrData(IrReceiver.decodedIRData);
        break;
      };
      case FAST: {
        if (checkResult[FAST]!=1) {
          checkResult[FAST]=checkCommandOnly(IrReceiver.decodedIRData, 0xFF);
        };
        //checkResult[FAST]=checkCommandOnly(IrReceiver.decodedIRData, 0x2F);
        //Serial.println("detect : *FAST*");
        //dumpIrData(IrReceiver.decodedIRData);
        break;
      };
      case LEGO_PF: {
        Serial.println("detect : *LEGO_PF*");
        if (checkResult[LEGO_PF]!=1) {
          checkResult[LEGO_PF]=1;
        };
        //dumpIrData(IrReceiver.decodedIRData);
        //checkResult[LEGO_PF]=checkData(IrReceiver.decodedIRData);
        break;
      };
      case PULSE_WIDTH: {
        Serial.println("detect : *PULSE_WIDTH*");
        dumpIrData(IrReceiver.decodedIRData);
        break;
      };
      case PULSE_DISTANCE: {
        Serial.println("detect : *PULSE_DISTANCE*");
        dumpIrData(IrReceiver.decodedIRData);
        break;
      };
    };
    if (IrReceiver.decodedIRData.protocol != UNKNOWN) {
      printIrData();
    };
  };
};

/*
 * Callback function
 */
#if defined(ESP32) || defined(ESP8266)
IRAM_ATTR
# endif
void ReceiveCompleteCallbackHandler() {
  IrReceiver.decode(); // fill IrReceiver.decodedIRData

  IrReceiver.resume();


  sIRDataJustReceived = true;
};