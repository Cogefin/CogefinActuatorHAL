
#include "config.h"

#include "ActuatorHAL.h"

#ifdef USE_IRDA
#ifdef DEBUG
#undef DEBUG
#include <IRremote.hpp>
#define DEBUG
#else /* DEBUG */
#include <IRremote.hpp>
#endif /* DEBUG */
#endif /* USE_IRDA */





typedef struct deviceManagementTable {
  uint32_t type;
#ifdef USE_CHARACTER_DISPLAY
  UnifiedLCD * characterDisplay;
#endif /* USE_CHARACTER_DISPLAY */
#ifdef USE_LED
  UnifiedLED * led;
#endif /* USE_LED */
#ifdef USE_NSEG_LED
  UnifiedNSegLED * nseg;
  uint32_t nseg_period;
  uint8_t nseg_digits;
  uint8_t nseg_brightness;
  char nseg_text[MAX_DIGITS_OF_NSEG_LED];
#endif /* USE_NSEG_LED */
#ifdef USE_SWITCH
  Switch * simpleSwitch;
#endif /* USE_SWITCH */
#ifdef USE_SERVO
  ServoHal * servo;
#endif /* USE_SERVO */
#ifdef USE_SIMPLE_SOUND
  SimpleSound * simpleSound;
#endif /* USE_SIMPLE_SOUND */
#ifdef USE_PWM
  PWM * pwm;
#endif /* USE_PWM */
//#ifdef USE_IRDA
//  IRsend * ir_sender;
//#endif /* USE_IRDA */
#ifdef USE_MP3_PLAYER
  //char fileName[MP3_PLAYER_FILE_NAME_MAX_LENGTH];
  UnifiedMP3 * mp3_player;
#endif /* USE_MP3_PLAYER */
#ifdef USE_GRAPHIC_DISPLAY
  UnifiedGraphicDisplay * graphicDisplay;
#endif /* USE_GRAPHIC_DISPLAY */
} DeviceManagementTable;

DeviceManagementTable deviceTable[NUM_OF_DEVICES];

void initDeviceTable(void) {
  for (int i=0; i<NUM_OF_DEVICES; i++ ) {
    deviceTable[i].type=0;
  }
}

void dumpDeviceTable(void) {
  Serial.println("");
  for (int i=0; i<NUM_OF_DEVICES; i++ ) {
    switch(deviceTable[i].type) {
      case CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT");break;
      }
      case CHARACTER_DISPLAY_TYPE_ACM1602NI: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("CHARACTER_DISPLAY_TYPE_ACM1602NI");break;
      }
      case CHARACTER_DISPLAY_TYPE_LIQUID_CRYSTAL: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("CHARACTER_DISPLAY_TYPE_LIQUID_CRYSTAL");break;
      }
      case LED_TYPE_MONO_LED: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("LED_TYPE_MONO_LED");break;
      }
      case LED_TYPE_MONO_CHAIN_LED: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("LED_TYPE_MONO_CHAIN_LED");break;
      }
      case LED_TYPE_COLOR_LED: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("LED_TYPE_COLOR_LED");break;
      }
      case LED_TYPE_COLOR_CHAIN_LED: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("LED_TYPE_COLOR_CHAIN_LED");break;
      }
      case NSEG_LED_TYPE_OSL12306_16: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("NSEG_LED_TYPE_OSL12306_16");break;
      }
      case NSEG_LED_TYPE_OSL20541: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("NSEG_LED_TYPE_OSL20541");break;
      }
      case NSEG_LED_TYPE_OSL30561: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("NSEG_LED_TYPE_OSL30561");break;
      }
      case NSEG_LED_TYPE_GROVE_TM1637: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("NSEG_LED_TYPE_GROVE_TM1637");break;
      }
      case NSEG_LED_TYPE_DFR0090: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("NSEG_LED_TYPE_DFR0090");break;
      }
      case SIMPLE_SWITCH_TYPE_NORMAL: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("SIMPLE_SWITCH_TYPE_NORMAL");break;
      }
      case SERVO_TYPE_SIMPLE: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("SERVO_TYPE_SIMPLE");break;
      }
      case SIMPLE_SOUND_TYPE_NORMAL: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("SIMPLE_SOUND_TYPE_NORMAL");break;
      }
      case PWM_TYPE_SIMPLE: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("PWM_TYPE_SIMPLE");break;
      }
      case IRDA_TYPE_SIMPLE: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("IRDA_TYPE_SIMPLE");break;
      }
      case MP3_PLAYER_TYPE_KT403A: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("MP3_PLAYER_TYPE_KT403A");break;
      }
      case MP3_PLAYER_TYPE_WT2003S: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("MP3_PLAYER_TYPE_WT2003S");break;
      }
      case MP3_PLAYER_TYPE_WT2605C: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("MP3_PLAYER_TYPE_WT2605C");break;
      }
      case MP3_PLAYER_TYPE_DF_ROBOT_DFP: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("MP3_PLAYER_TYPE_DF_ROBOT_DFP");break;
      }
      case GRAPHIC_DISPLAY_TYPE_U8G2: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("GRAPHIC_DISPLAY_TYPE_U8G2");break;
      }
      case GRAPHIC_DISPLAY_TYPE_GIGA_DISPLAY: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("GRAPHIC_DISPLAY_TYPE_GIGA_DISPLAY");break;
      }
      case GRAPHIC_DISPLAY_TYPE_BODMER_TFT: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("GRAPHIC_DISPLAY_TYPE_BODMER_TFT");break;
      }
      case GRAPHIC_DISPLAY_TYPE_ADAFRUIT_GFX: {
        Serial.print("device id=");Serial.print(i);Serial.print(", type=");Serial.println("GRAPHIC_DISPLAY_TYPE_ADAFRUIT_GFX");break;
      }
    }
  }
  Serial.println("");
}

#ifdef USE_CHARACTER_DISPLAY
void updateDeviceTable(uint8_t id, uint32_t type, UnifiedLCD * characterDisplay_pointer) {
  deviceTable[id].type = type;
  deviceTable[id].characterDisplay = characterDisplay_pointer;
}
#endif /* USE_CHARACTER_DISPLAY */

#ifdef USE_LED
void updateDeviceTable(uint8_t id, uint32_t type, UnifiedLED * led_pointer) {
  deviceTable[id].type = type;
  deviceTable[id].led = led_pointer;
}
#endif /* USE_LED */

#ifdef USE_SWITCH
void updateDeviceTable(uint8_t id, uint32_t type, Switch * ss) {
  deviceTable[id].type = type;
  deviceTable[id].simpleSwitch = ss;
}
#endif /* USE_SWITCH */

#ifdef USE_SERVO
void updateDeviceTable(uint8_t id, uint32_t type, ServoHal * ss) {
  deviceTable[id].type = type;
  deviceTable[id].servo = ss;
}
#endif /* USE_SERVO */

#ifdef USE_SIMPLE_SOUND
void updateDeviceTable(uint8_t id, uint32_t type, SimpleSound * ss) {
  deviceTable[id].type = type;
  deviceTable[id].simpleSound = ss;
}
#endif /* USE_SIMPLE_SOUND */

#ifdef USE_PWM
void updateDeviceTable(uint8_t id, uint32_t type, PWM *  ss) {
  deviceTable[id].type = type;
  deviceTable[id].pwm = ss;
}
#endif /* USE_PWM */

#ifdef USE_IRDA
//void updateDeviceTable(uint8_t id, uint32_t type, IRsend * ss) {
//  deviceTable[id].type = type;
//  deviceTable[id].ir_sender = ss;
//}
void updateDeviceTable(uint8_t id, uint32_t type) {
  deviceTable[id].type = type;
}
#endif /* USE_IRDA */

#ifdef USE_MP3_PLAYER
void updateDeviceTable(uint8_t id, uint32_t type, UnifiedMP3 * ss) {
  deviceTable[id].type = type;
  deviceTable[id].mp3_player = ss;
}
#endif /* USE_MP3_PLAYER */

#ifdef USE_NSEG_LED
void updateDeviceTable(uint8_t id, uint32_t type_num, UnifiedNSegLED * ss, uint8_t digits) {
  if (type_num == NSEG_LED_TYPE_GROVE_TM1637) {
    deviceTable[id].type = type_num;
    deviceTable[id].nseg = ss;
    return;
  }
  deviceTable[id].type = type_num;
  deviceTable[id].nseg = ss;
  deviceTable[id].nseg_period = 0;
  deviceTable[id].nseg_digits = digits;
  deviceTable[id].nseg_brightness = 0;
  for (int i=0; i < digits; i++) {
    deviceTable[id].nseg_text[i] = 0;
  }
}
#endif /* USE_NSEG_LED */

#ifdef USE_GRAPHIC_DISPLAY
void updateDeviceTable(uint8_t id, uint32_t type, UnifiedGraphicDisplay * display) {
  deviceTable[id].type = type;
  deviceTable[id].graphicDisplay = display;
}
#endif /* USE_GRAPHIC_DISPLAY */

bool checkDeviceTable(uint8_t _id, uint32_t _type) {
  if (_type == deviceTable[_id].type) return true;
  return false;
}

uint8_t getDeviceCategory(uint32_t type) {
  if ((type > CHARACTER_DISPLAY_TYPE_MIN) && (type < CHARACTER_DISPLAY_TYPE_MAX)) {
    return DEVICE_CATEGORY_CHARACTER_DISPLAY;
  };
  if ((type > LED_TYPE_MIN) && (type < LED_TYPE_MAX)) {
    return DEVICE_CATEGORY_LED;
  };
  if ((type > NSEG_LED_TYPE_MIN) && (type < NSEG_LED_TYPE_MAX)) {
    return DEVICE_CATEGORY_N_SEG_LED;
  };
  if ((type > SIMPLE_SWITCH_TYPE_MIN) && (type < SIMPLE_SWITCH_TYPE_MAX)) {
    return DEVICE_CATEGORY_SIMPLE_SWITCH;
  };
  if ((type > SERVO_TYPE_MIN) && (type < SERVO_TYPE_MAX)) {
    return DEVICE_CATEGORY_SERVO;
  };
  if ((type > SIMPLE_SOUND_TYPE_MIN) && (type < SIMPLE_SOUND_TYPE_MAX)) {
    return DEVICE_CATEGORY_SIMPLE_SOUND;
  };
  if ((type > PWM_TYPE_MIN) && (type < PWM_TYPE_MAX)) {
    return DEVICE_CATEGORY_SIMPLE_PWM;
  };
  if ((type > IRDA_TYPE_MIN) && (type < IRDA_TYPE_MAX)) {
    return DEVICE_CATEGORY_SIMPLE_IRDA;
  };
  if ((type > MP3_PLAYER_TYPE_MIN) && (type < MP3_PLAYER_TYPE_MAX)) {
    return DEVICE_CATEGORY_SIMPLE_MP3_PLAYER;
  };
  if ((type > GRAPHIC_DISPLAY_TYPE_MIN) && (type < GRAPHIC_DISPLAY_TYPE_MAX)) {
    return DEVICE_CATEGORY_GRAPHIC_DISPLAY;
  };
  return DEVICE_CATEGORY_UNKNOWN;
}

#ifdef USE_CHARACTER_DISPLAY
void characterDisplayClear(uint8_t id) {
  deviceTable[id].characterDisplay->clear();
}
#endif /* USE_CHARACTER_DISPLAY */

#ifdef USE_CHARACTER_DISPLAY
void characterDisplayHome(uint8_t id) {
  deviceTable[id].characterDisplay->home();
}
#endif /* USE_CHARACTER_DISPLAY */

#ifdef USE_CHARACTER_DISPLAY
void characterDisplayMode(uint8_t id, UnifiedLcdMode mode) {
  deviceTable[id].characterDisplay->setMode(mode);
}
#endif /* USE_CHARACTER_DISPLAY */

#ifdef USE_CHARACTER_DISPLAY
void characterDisplaySetCursor(uint8_t id, uint8_t x, uint8_t y) {
  deviceTable[id].characterDisplay->setCursor(x, y);
}
#endif /* USE_CHARACTER_DISPLAY */

#ifdef USE_CHARACTER_DISPLAY
void characterDisplaySetSize(uint8_t id, uint8_t col, uint8_t row, uint8_t size) {
  if (0 < size ) {
    deviceTable[id].characterDisplay->begin(col, row, size);
  } else {
    deviceTable[id].characterDisplay->begin(col, row);
  }
}
#endif /* USE_CHARACTER_DISPLAY */

#ifdef USE_CHARACTER_DISPLAY
void characterDisplaySetRGB(uint8_t id, unsigned char r, unsigned char g, unsigned char b) {
  deviceTable[id].characterDisplay->setBacklightRGB(r, g, b);
}
#endif /* USE_CHARACTER_DISPLAY */

bool controlCharacterDisplay(JsonDocument doc) {
#ifdef USE_CHARACTER_DISPLAY
  uint8_t command = doc["command"];
  uint8_t id = doc["id"];
  switch(command) {
    case CHARACTER_DISPLAY_COMMAND_CLEAR: {
      characterDisplayClear(id);
      break;
    }
    case CHARACTER_DISPLAY_COMMAND_HOME: {
      characterDisplayHome(id);
      break;
    }
    case CHARACTER_DISPLAY_COMMAND_SET_MODE: {
      characterDisplayMode(id, doc["param"][0]["mode"]);
      break;
    }
    case CHARACTER_DISPLAY_COMMAND_SET_CURSUR: {
      characterDisplaySetCursor(id, doc["param"][0]["x"], doc["param"][0]["y"]);
      break;
    }
    case CHARACTER_DISPLAY_COMMAND_SET_SIZE: {
      characterDisplaySetSize(id, doc["param"][0]["col"], doc["param"][0]["row"], doc["param"][0]["font"]);
      break;
    }
    case CHARACTER_DISPLAY_COMMAND_SET_BACKLIGHT_RGB: {
      if (CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT != doc["type"]) return false;
      characterDisplaySetRGB(id, doc["param"][0]["r"], doc["param"][0]["g"], doc["param"][0]["b"]);
      break;
    }
    case CHARACTER_DISPLAY_COMMAND_PRINT: {
      const char* text = doc["param"][0]["text"];
      deviceTable[id].characterDisplay->print(text);
      break;
    }
    default: return false;
  }
  return true;
#else /* USE_CHARACTER_DISPLAY */
  return false;
#endif /* USE_CHARACTER_DISPLAY */
}

#ifdef USE_LED
void ledClear(uint8_t id) {
  deviceTable[id].led->clear();
}
#endif /* USE_LED */

#ifdef USE_LED
void ledSetBrightness(uint8_t id, float brightness) {
  deviceTable[id].led->setLed(brightness);
}
#endif /* USE_LED */

#ifdef USE_LED
void ledSetRGB(uint8_t id, byte r, byte g, byte b) {
  deviceTable[id].led->setLed(r, g, b);
}
#endif /* USE_LED */

#ifdef USE_LED
void ledSetBrightness_N(uint8_t id, JsonDocument doc) {
  uint8_t params = doc["paramSize"];
  for (uint8_t i=0 ; i < params; i++) {
    uint8_t num = doc["param"][i]["num"];
    float brightness  = doc["param"][i]["brightness"];
    deviceTable[id].led->setLed(num, brightness);
  }
}
#endif /* USE_LED */

#ifdef USE_LED
void ledSetRGB_N(uint8_t id, JsonDocument doc) {
  uint8_t params = doc["paramSize"];
  for (uint8_t i=0 ; i < params; i++) {
    uint8_t num = doc["param"][i]["num"];
    uint8_t red  = doc["param"][i]["red"];
    uint8_t green  = doc["param"][i]["green"];
    uint8_t blue  = doc["param"][i]["blue"];
    deviceTable[id].led->setLed(num, red, green, blue);
  }
}
#endif /* USE_LED */

#ifdef USE_LED
void ledSetMode(uint8_t id, UnifiedLedMode mode) {
  deviceTable[id].led->setMode(mode);
}
#endif /* USE_LED */

bool controlLED(JsonDocument doc) {
#ifdef USE_LED
  uint8_t command = doc["command"];
  uint8_t id = doc["id"];
  switch(command) {
    case LED_COMMAND_CLEAR: {
      ledClear(id);
      break;
    }
    case LED_COMMAND_SET_BRIGHTNESS: {
      ledSetBrightness(id, doc["param"][0]["brightness"]);
      break;
    }
    case LED_COMMAND_SET_BRIGHTNESS_N: {
      ledSetBrightness_N(id, doc);
      break;
    }
    case LED_COMMAND_SET_RGB: {
      ledSetRGB(id, doc["param"][0]["red"], doc["param"][0]["green"], doc["param"][0]["blue"]);
      break;
    }
    case LED_COMMAND_SET_RGB_N: {
      ledSetRGB_N(id, doc);
      break;
    }
    case LED_COMMAND_SET_MODE: {
      ledSetMode(id, doc["param"][0]["mode"]);
      break;
    }
    default: return false;
  }
  return true;
#else /* USE_LED */
  return false;
#endif /* USE_LED */
}

void keepStateNsegLED(uint8_t id) {
#ifdef USE_NSEG_LED
  if (deviceTable[id].type==NSEG_LED_TYPE_GROVE_TM1637) return;
  deviceTable[id].nseg->display(deviceTable[id].nseg_period, deviceTable[id].nseg_text);
  deviceTable[id].nseg->set(deviceTable[id].nseg_brightness);
#else /* USE_NSEG_LED */
  return ;
#endif /* USE_NSEG_LED */
}

bool controlNsegLED(JsonDocument doc) {
#ifdef USE_NSEG_LED
  uint8_t command = doc["command"];
  uint8_t id = doc["id"];
  switch(command) {
    case NSEG_LED_COMMAND_CLEAR: {
      deviceTable[id].nseg->clear();
      deviceTable[id].nseg_brightness = 0;
      deviceTable[id].nseg_period = 0;
      for (int i=0; i < deviceTable[id].nseg_digits; i++) {
        deviceTable[id].nseg_text[i] = 0;
      }
      break;
    }
    case NSEG_LED_COMMAND_SET_BRIGHTNESS: {
      uint8_t brightness = doc["param"][0]["brightness"];
      deviceTable[id].nseg->set(brightness);
      deviceTable[id].nseg_brightness = brightness;
      break;
    }
    case NSEG_LED_COMMAND_SET_COLON: {
      uint8_t val = doc["param"][0]["flag"];
      bool flag;
      if (0!=val) {
        flag = false;
      } else {
        flag = true;
      }
      deviceTable[id].nseg->setColomn(flag);
      break;
    }
    case NSEG_LED_COMMAND_SET: {
      const char* text = doc["param"][0]["text"];
      //char* text = (char *) doc["param"][0]["text"];
      uint32_t period = doc["param"][0]["period"];
      deviceTable[id].nseg->display(period, text);
      deviceTable[id].nseg_period = period;
      for (int i=0; i < deviceTable[id].nseg_digits; i++) {
        deviceTable[id].nseg_text[i] = text[i];
      }
      break;
    }
    case NSEG_LED_COMMAND_SETC: {
      const char* text = doc["param"][0]["text"];
      //char* text = (char *) doc["param"][0]["text"];
      deviceTable[id].nseg->display(text);
      break;
    }
    default: return false;
  }
  return true;
#else /* USE_NSEG_LED */
  return false;
#endif /* USE_NSEG_LED */
}

#ifdef USE_SWITCH
void simpleSwitchON(uint8_t id) {
  deviceTable[id].simpleSwitch->on();
}
#endif /* USE_SWITCH */

#ifdef USE_SWITCH
void simpleSwitchOFF(uint8_t id) {
  deviceTable[id].simpleSwitch->off();
}
#endif /* USE_SWITCH */

bool controlSimpleSwitch(JsonDocument doc) {
#ifdef USE_SWITCH
  uint8_t command = doc["command"];
  uint8_t id = doc["id"];
  switch(command) {
    case SIMPLE_SWITCH_COMMAND_ON: {
      simpleSwitchON(id);
      break;
    }
    case SIMPLE_SWITCH_COMMAND_OFF: {
      simpleSwitchOFF(id);
      break;
    }
    default: return false;
  }
  return true;
#else /* USE_SWITCH */
  return false;
#endif /* USE_SWITCH */
}

bool controlServo(JsonDocument doc) {
#ifdef USE_SERVO
  uint8_t command = doc["command"];
  uint8_t id = doc["id"];
  switch(command) {
    case SERVO_COMMAND_WRITE: {
      int angle = doc["param"][0]["angle"];
      deviceTable[id].servo->write(angle);
      break;
    }
    case SERVO_COMMAND_WRITE_MS: {
      int msec = doc["param"][0]["msec"];
      deviceTable[id].servo->writeMS(msec);
      break;
    }
    default: return false;
  }
  return true;
#else /* USE_SERVO */
  return false;
#endif /* USE_SERVO */
}

#ifdef USE_SIMPLE_SOUND
void simpleSoundON(uint8_t id) {
  deviceTable[id].simpleSound->on();
}
#endif /* USE_SIMPLE_SOUND */

#ifdef USE_SIMPLE_SOUND
void simpleSoundOFF(uint8_t id) {
  deviceTable[id].simpleSound->off();
}
#endif /* USE_SIMPLE_SOUND */

#ifdef USE_SIMPLE_SOUND
void simpleSoundPlay(uint8_t id, JsonDocument doc) {
  uint8_t iteration = doc["param"][0]["iteration"];
  for (int i=0; i< iteration; i++) {
    int bass = doc["param"][0]["bass"][i];
    int duration = doc["param"][0]["duration"][i];
    int interval = doc["param"][0]["interval"][i];
    deviceTable[id].simpleSound->play(bass, duration);
    delay(interval);
  }
}
#endif /* USE_SIMPLE_SOUND */


bool controlSimpleSound(JsonDocument doc) {
#ifdef USE_SIMPLE_SOUND
  uint8_t command = doc["command"];
  uint8_t id = doc["id"];
  switch(command) {
    case SIMPLE_SOUND_COMMAND_ON: {
      simpleSoundON(id);
      break;
    }
    case SIMPLE_SOUND_COMMAND_OFF: {
      simpleSoundOFF(id);
      break;
    }
    case SIMPLE_SOUND_COMMAND_PLAY: {
      simpleSoundPlay(id, doc);
      break;
    }
    default: return false;
  }
  return true;
#else /* USE_SIMPLE_SOUND */
  return false;
#endif /* USE_SIMPLE_SOUND */
}

#ifdef USE_PWM
void pwmApply(uint8_t id) {
  deviceTable[id].pwm->apply();
}
#endif /* USE_PWM */

#ifdef USE_PWM
void pwmOFF(uint8_t id) {
  deviceTable[id].pwm->off();
}
#endif /* USE_PWM */

#ifdef USE_PWM
void pwmSet(uint8_t id, uint8_t level) {
  deviceTable[id].pwm->set(level);
}
#endif /* USE_PWM */

bool controlPWM(JsonDocument doc) {
#ifdef USE_PWM
  uint8_t command = doc["command"];
  uint8_t id = doc["id"];
  switch(command) {
    case PWM_COMMAND_APPLY: {
      pwmApply(id);
      break;
    }
    case PWM_COMMAND_OFF: {
      pwmOFF(id);
      break;
    }
    case PWM_COMMAND_SET: {
      uint8_t level = doc["param"][0]["value"];
      pwmSet(id, level);
      break;
    }
    default: return false;
  }
  return true;
#else /* USE_PWM */
  return false;
#endif /* USE_PWM */
}

bool controlIRDA(JsonDocument doc) {
#ifdef USE_IRDA
  uint8_t command = doc["command"];
  uint8_t id = doc["id"];
  switch(command) {
    case IRDA_COMMAND_BANG_OLUFSEN: {
      uint16_t header = doc["param"][0]["header"];
      uint8_t data = doc["param"][0]["data"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      int8_t bits = doc["param"][0]["bits"];
      IrSender.sendBangOlufsen(header, data, repeats, bits);
      //deviceTable[id].ir_sender->sendBangOlufsen(header, data, repeats, bits);
      break;
    }
    case IRDA_COMMAND_BANG_OLUFSEN_LINK: {
      uint32_t header = doc["param"][0]["header"];
      uint8_t data = doc["param"][0]["data"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      int8_t bits = doc["param"][0]["bits"];
      IrSender.sendBangOlufsenDataLink(header, data, repeats, bits);
      //deviceTable[id].ir_sender->sendBangOlufsenDataLink(header, data, repeats, bits);
      break;
    }
    case IRDA_COMMAND_BOSE_WAVE: {
      uint8_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      IrSender.sendBoseWave(comm, repeats);
      break;
    }
    case IRDA_COMMAND_SHARP: {
      uint8_t address = doc["param"][0]["address"];
      uint8_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      IrSender.sendSharp2(address, comm, repeats);
      //deviceTable[id].ir_sender->sendSharp(address, comm, repeats);
      break;
    }
    case IRDA_COMMAND_DENON: {
      uint8_t address = doc["param"][0]["address"];
      uint8_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      uint8_t val = doc["param"][0]["flag"];
      bool flag;
      if (val != 0) {
        flag = true;
      } else {
        flag = false;
      }
      IrSender.sendDenon(address, comm, repeats, flag);
      //deviceTable[id].ir_sender->sendDenon(address, comm, repeats, flag);
      break;
    }
    case IRDA_COMMAND_FAST: {
      uint8_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      IrSender.sendFAST(comm, repeats);
      //deviceTable[id].ir_sender->sendFAST(comm, repeats);
      break;
    }
    case IRDA_COMMAND_JVC: {
      uint8_t address = doc["param"][0]["address"];
      uint8_t command = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      IrSender.sendJVC(address, command, repeats);
      //deviceTable[id].ir_sender->sendJVC(address, comm, repeats);
      break;
    }
    case IRDA_COMMAND_KASEIKYO: {
      uint16_t address = doc["param"][0]["address"];
      uint8_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      uint16_t vendor = doc["param"][0]["vendor"];
      IrSender.sendKaseikyo(address, comm, repeats, vendor);
      //deviceTable[id].ir_sender->sendKaseikyo(address, comm, repeats, vendor);
      break;
    }
    case IRDA_COMMAND_KASEIKYO_JVC: {
      uint16_t address = doc["param"][0]["address"];
      uint8_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      IrSender.sendKaseikyo_JVC(address, comm, repeats);
      break;
    }
    case IRDA_COMMAND_KASEIKYO_DENON: {
      uint16_t addr = doc["param"][0]["address"];
      uint8_t sCommand = doc["param"][0]["command"];
      int_fast8_t sRepeats = doc["param"][0]["repeats"];
      IrSender.sendKaseikyo_Denon(addr, sCommand, sRepeats);
      break;
    }
    case IRDA_COMMAND_KASEIKYO_SHARP: {
      uint16_t addr = doc["param"][0]["address"];
      uint8_t sCommand = doc["param"][0]["command"];
      int_fast8_t sRepeats = doc["param"][0]["repeats"];
      IrSender.sendKaseikyo_Sharp(addr, sCommand, sRepeats);
      break;
    }
    case IRDA_COMMAND_KASEIKYO_MITSUBISHI: {
      uint16_t addr = doc["param"][0]["address"];
      uint8_t sCommand = doc["param"][0]["command"];
      int_fast8_t sRepeats = doc["param"][0]["repeats"];
      IrSender.sendKaseikyo_Mitsubishi(addr, sCommand, sRepeats);
      break;
    }
    case IRDA_COMMAND_LG: {
      uint8_t address = doc["param"][0]["address"];
      uint16_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      IrSender.sendLG(address, comm, repeats);
      //deviceTable[id].ir_sender->sendLG(address, comm, repeats);
      break;
    }
    case IRDA_COMMAND_LG_2: {
      uint8_t address = doc["param"][0]["address"];
      uint16_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      IrSender.sendLG2(address, comm, repeats);
      //deviceTable[id].ir_sender->sendLG(address, comm, repeats);
      break;
    }
    case IRDA_COMMAND_LEGO: {
      uint8_t channel = doc["param"][0]["channel"];
      uint8_t comm = doc["param"][0]["command"];
      uint8_t mode = doc["param"][0]["mode"];
      uint8_t val = doc["param"][0]["flag"];
      bool flag;
      if (val != 0) {
        flag = true;
      } else {
        flag = false;
      }
      IrSender.sendLegoPowerFunctions(channel, comm, mode, flag);
      //deviceTable[id].ir_sender->sendLegoPowerFunctions(channel, comm, mode, flag);
      break;
    }
    case IRDA_COMMAND_LEGO_2: {
      uint16_t data = doc["param"][0]["data"];
      uint8_t channel = doc["param"][0]["channel"];
      uint8_t val = doc["param"][0]["flag"];
      bool flag;
      if (val != 0) {
        flag = true;
      } else {
        flag = false;
      }
      IrSender.sendLegoPowerFunctions(data, channel, flag);
      //deviceTable[id].ir_sender->sendLegoPowerFunctions(data, channel, flag);
      break;
    }
    case IRDA_COMMAND_MAGIC_QUEST: {
      uint32_t wid = doc["param"][0]["wid"];
      uint16_t magnitude = doc["param"][0]["magnitude"];
      IrSender.sendMagiQuest(wid, magnitude);
      //deviceTable[id].ir_sender->sendMagiQuest(wid, magnitude);
      break;
    }
    case IRDA_COMMAND_NEC: {
      uint16_t address = doc["param"][0]["address"];
      uint16_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      IrSender.sendNEC(address, comm, repeats);
      //deviceTable[id].ir_sender->sendNEC(address, comm, repeats);
      break;
    }
    case IRDA_COMMAND_NEC_2: {
      uint16_t address = doc["param"][0]["address"];
      uint16_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      IrSender.sendNEC2(address, comm, repeats);
      //deviceTable[id].ir_sender->sendNEC2(address, comm, repeats);
      break;
    }
    case IRDA_COMMAND_ONKYO: {
      uint16_t  address = doc["param"][0]["address"];
      uint16_t command = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      IrSender.sendOnkyo(address, command, repeats);
      //deviceTable[id].ir_sender->sendOnkyo(did, comm, repeats);
      break;
    }
    case IRDA_COMMAND_APPLE: {
      uint8_t did = doc["param"][0]["did"];
      uint8_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      IrSender.sendApple(did, comm, repeats);
      //deviceTable[id].ir_sender->sendApple(address, comm, repeats);
      break;
    }
    case IRDA_COMMAND_RC5: {
      uint8_t address = doc["param"][0]["address"];
      uint8_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      uint8_t val = doc["param"][0]["flag"];
      bool flag;
      if (val != 0) {
        flag = true;
      } else {
        flag = false;
      }
      IrSender.sendRC5(address, comm, repeats, flag);
      //deviceTable[id].ir_sender->sendRC5(address, comm, repeats, flag);
      break;
    }
    case IRDA_COMMAND_RC6: {
      uint32_t data = doc["param"][0]["data"];
      uint8_t bits = doc["param"][0]["bits"];
      IrSender.sendRC6Raw(data, bits);
      //deviceTable[id].ir_sender->sendRC6Raw(data, bits);
      break;
    }
    case IRDA_COMMAND_RC6_2: {
      uint64_t data = doc["param"][0]["data"];
      uint8_t bits = doc["param"][0]["bits"];
      IrSender.sendRC6Raw(data, bits);
      //deviceTable[id].ir_sender->sendRC6Raw(data, bits);
      break;
    }
    case IRDA_COMMAND_RC6_3: {
      uint8_t address = doc["param"][0]["address"];
      uint8_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      uint8_t val = doc["param"][0]["flag"];
      bool flag;
      if (val != 0) {
        flag = true;
      } else {
        flag = false;
      }
      IrSender.sendRC6(address, comm, repeats, flag);
      //deviceTable[id].ir_sender->sendRC6(address, comm, repeats, flag);
      break;
    }
    case IRDA_COMMAND_RC6_A: {
      uint8_t address = doc["param"][0]["address"];
      uint8_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      uint16_t customer = doc["param"][0]["customer"];
      uint8_t val = doc["param"][0]["flag"];
      bool flag;
      if (val != 0) {
        flag = true;
      } else {
        flag = false;
      }
      IrSender.sendRC6A(address, comm, repeats, customer, flag);
      //deviceTable[id].ir_sender->sendRC6A(address, comm, repeats, customer, flag);
      break;
    }
    case IRDA_COMMAND_SAMSUNG: {
      uint16_t address = doc["param"][0]["address"];
      uint8_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      IrSender.sendSamsung(address, comm, repeats);
      //deviceTable[id].ir_sender->sendSamsung(address, comm, repeats);
      break;
    }
    case IRDA_COMMAND_SAMSUNG_LG: {
      uint16_t address = doc["param"][0]["address"];
      uint8_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      IrSender.sendSamsungLG(address, comm, repeats);
      //deviceTable[id].ir_sender->sendSamsungLG(address, comm, repeats);
      break;
    }
    case IRDA_COMMAND_SAMSUNG_48: {
      uint16_t address = doc["param"][0]["address"];
      uint32_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      IrSender.sendSamsung48(address, comm, repeats);
      //deviceTable[id].ir_sender->sendSamsung48(address, comm, repeats);
      break;
    }
    case IRDA_COMMAND_SONY: {
      uint16_t address = doc["param"][0]["address"];
      uint8_t comm = doc["param"][0]["command"];
      int_fast8_t repeats = doc["param"][0]["repeats"];
      uint8_t bits = doc["param"][0]["bits"];
      IrSender.sendSony(address, comm, repeats, bits);
      //deviceTable[id].ir_sender->sendSony(address, comm, repeats, bits);
      break;
    }
    case IRDA_COMMAND_DISH: {
      uint16_t data = doc["param"][0]["data"];
      IrSender.sendDish(data);
      //deviceTable[id].ir_sender->sendDish(data);
      break;
    }
    case IRDA_COMMAND_WHYNTER: {
      uint32_t data = doc["param"][0]["data"];
      int_fast8_t sRepeats = doc["param"][0]["repeats"];
      IrSender.sendWhynter(data, sRepeats);
      //deviceTable[id].ir_sender->sendWhynter(data, bits);
      break;
    }
    case IRDA_COMMAND_PANASONIC: {
      uint16_t addr = doc["param"][0]["address"];
      uint8_t sCommand = doc["param"][0]["command"];
      int_fast8_t sRepeats = doc["param"][0]["repeats"];
      IrSender.sendPanasonic(addr, sCommand, sRepeats);
      //deviceTable[id].ir_sender->sendWhynter(data, bits);
      break;
    }
    default: return false;
  }
  return true;
#else /* USE_IRDA */
  return false;
#endif /* USE_IRDA */
}

bool controlMp3Player(JsonDocument doc) {
#ifdef USE_MP3_PLAYER
  uint8_t command = doc["command"];
  uint8_t id = doc["id"];
  //Serial.print("command = "); Serial.println(command);
  switch(command) {
    case MP3_PLAYER_COMMAND_STOP: {
      deviceTable[id].mp3_player->stop();
      break;
    }
    case MP3_PLAYER_COMMAND_NEXT: {
      deviceTable[id].mp3_player->next();
      break;
    }
    case MP3_PLAYER_COMMAND_PREVIOUS: {
      deviceTable[id].mp3_player->previous();
      break;
    }
    case MP3_PLAYER_COMMAND_VOLUME: {
      uint8_t vol = doc["param"][0]["vol"];
      deviceTable[id].mp3_player->volume(vol);
      break;
    }
    case MP3_PLAYER_COMMAND_VOL_DOWN: {
      deviceTable[id].mp3_player->volumeDown();
      break;
    }
    case MP3_PLAYER_COMMAND_VOL_UP: {
      deviceTable[id].mp3_player->volumeUp();
      break;
    }
    case MP3_PLAYER_COMMAND_STORAGE: {
      uint8_t storage_type = doc["param"][0]["storage"];
      switch(storage_type) {
        case 1: {
          deviceTable[id].mp3_player->selectStorage(SD_STORAGE);
          break;
        }
        case 2: {
          deviceTable[id].mp3_player->selectStorage(SPI_STORAGE);
          break;
        }
        case 3: {
          deviceTable[id].mp3_player->selectStorage(UDISK_STORAGE);
          break;
        }
        default: {
          return false;
        }
      }
      break;
    }
    case MP3_PLAYER_COMMAND_PAUSE: {
      deviceTable[id].mp3_player->pause();
      break;
    }
    case MP3_PLAYER_COMMAND_START: {
      deviceTable[id].mp3_player->start();
      break;
    }
    case MP3_PLAYER_COMMAND_PLAY_BY_INDEX: {
      uint32_t index = doc["param"][0]["index"];
      uint8_t mode = doc["param"][0]["mode"];
      switch(mode) {
        case 0: {
          deviceTable[id].mp3_player->playByIndex(index, MP3_MODE_CYCLE);
          break;
        }
        case 1: {
          deviceTable[id].mp3_player->playByIndex(index, MP3_MODE_SINGLE_CYCLE);
          break;
        }
        case 2: {
          deviceTable[id].mp3_player->playByIndex(index, MP3_MODE_DIR_CYCLE);
          break;
        }
        case 3: {
          deviceTable[id].mp3_player->playByIndex(index, MP3_MODE_RANDOM);
          break;
        }
        case 4: {
          deviceTable[id].mp3_player->playByIndex(index, MP3_MODE_SINGLE_SHOT);
          break;
        }
        default: {
          return false;
        }
      }
      break;
    }
    case MP3_PLAYER_COMMAND_PLAY_BY_NAME: {
      uint8_t mode = doc["mode"];
      const char* name = doc["param"][0]["name"];
      switch(mode) {
        case 0: {
          deviceTable[id].mp3_player->playByName(name, MP3_MODE_CYCLE);
          break;
        }
        case 1: {
          deviceTable[id].mp3_player->playByName(name, MP3_MODE_SINGLE_CYCLE);
          break;
        }
        case 2: {
          deviceTable[id].mp3_player->playByName(name, MP3_MODE_DIR_CYCLE);
          break;
        }
        case 3: {
          deviceTable[id].mp3_player->playByName(name, MP3_MODE_RANDOM);
          break;
        }
        case 4: {
          deviceTable[id].mp3_player->playByName(name, MP3_MODE_SINGLE_SHOT);
          break;
        }
        default: {
          return false;
        }
      }
      break;
    }
    case MP3_PLAYER_COMMAND_PLAY_DIR_BY_NUM: {
      uint8_t mode = doc["param"][0]["mode"];
      uint8_t dir = doc["param"][0]["num"];
      uint32_t file = doc["param"][0]["file"];
      switch(mode) {
        case 0: {
          deviceTable[id].mp3_player->playDirectoryByNumber(dir, file, MP3_MODE_CYCLE);
          break;
        }
        case 1: {
          deviceTable[id].mp3_player->playDirectoryByNumber(dir, file, MP3_MODE_SINGLE_CYCLE);
          break;
        }
        case 2: {
          deviceTable[id].mp3_player->playDirectoryByNumber(dir, file, MP3_MODE_DIR_CYCLE);
          break;
        }
        case 3: {
          deviceTable[id].mp3_player->playDirectoryByNumber(dir, file, MP3_MODE_RANDOM);
          break;
        }
        case 4: {
          deviceTable[id].mp3_player->playDirectoryByNumber(dir, file, MP3_MODE_SINGLE_SHOT);
          break;
        }
        default: {
          return false;
        }
      }
      break;
    }
    case MP3_PLAYER_COMMAND_PLAY_DIR_BY_NAME: {
      uint8_t mode = doc["param"][0]["mode"];
      const char* dir = doc["param"][0]["name"];
      uint32_t file = doc["param"][0]["file"];
      switch(mode) {
        case 0: {
          deviceTable[id].mp3_player->playDirectoryByName(dir, file, MP3_MODE_CYCLE);
          break;
        }
        case 1: {
          deviceTable[id].mp3_player->playDirectoryByName(dir, file, MP3_MODE_SINGLE_CYCLE);
          break;
        }
        case 2: {
          deviceTable[id].mp3_player->playDirectoryByName(dir, file, MP3_MODE_DIR_CYCLE);
          break;
        }
        case 3: {
          deviceTable[id].mp3_player->playDirectoryByName(dir, file, MP3_MODE_RANDOM);
          break;
        }
        case 4: {
          deviceTable[id].mp3_player->playDirectoryByName(dir, file, MP3_MODE_SINGLE_SHOT);
          break;
        }
        default: {
          return false;
        }
      }
      break;
    }
    case MP3_PLAYER_COMMAND_LOOP_DIR: {
      int index = doc["param"][0]["index"];
      deviceTable[id].mp3_player->loopDirectory(index);
      break;
    }
    case MP3_PLAYER_COMMAND_PLAY_MP3_DIR: {
      int index = doc["param"][0]["index"];
      deviceTable[id].mp3_player->playMp3Directory(index);
      break;
    }
    case MP3_PLAYER_COMMAND_CUT_IN_PLAY: {
      uint8_t storage_type = doc["param"][0]["storage"];
      uint32_t index = doc["param"][0]["index"];
      switch(storage_type) {
        case 1: {
          deviceTable[id].mp3_player->cutInPlay(SD_STORAGE, index);
          break;
        }
        case 2: {
          deviceTable[id].mp3_player->cutInPlay(SPI_STORAGE, index);
          break;
        }
        case 3: {
          deviceTable[id].mp3_player->cutInPlay(UDISK_STORAGE, index);
          break;
        }
        default: {
          return false;
        }
      }
      break;
    }
    case MP3_PLAYER_COMMAND_SET_EQ: {
      int eq = doc["param"][0]["eq"];
      deviceTable[id].mp3_player->setEQ(eq);
      break;
    }
    default: return false;
  }
  return true;
#else /* USE_MP3_PLAYER */
  return false;
#endif /* USE_MP3_PLAYER */
}


#ifdef USE_GRAPHIC_DISPLAY
bool graphicDisplayFillScreen(uint8_t id, uint16_t color) {
  int val = deviceTable[id].graphicDisplay->fillScreen(color);
  if (val <0 ) { return false;};
  return true;
}
#endif /* USE_GRAPHIC_DISPLAY */

#ifdef USE_GRAPHIC_DISPLAY
bool graphicDisplayPrintString(uint8_t id, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, uint8_t size, bool wrap, const char* text ) {
  int val;
  val = deviceTable[id].graphicDisplay->setCursor(x, y);
  if (val <0 ) { return false;};
  val = deviceTable[id].graphicDisplay->setTextColor(fg,bg);
  if (val <0 ) { return false;};
  val = deviceTable[id].graphicDisplay->setTextSize(size);
  if (val <0 ) { return false;};
  val = deviceTable[id].graphicDisplay->setTextWrap(wrap);
  if (val <0 ) { return false;};
  deviceTable[id].graphicDisplay->print(text);
  return true;
}
#endif /* USE_GRAPHIC_DISPLAY */

#ifdef USE_GRAPHIC_DISPLAY
void graphicDisplayPrintJPEG(uint16_t x, uint16_t y, const char* filename ) {
  TJpgDec.drawSdJpg(x, y, filename);
}
#endif /* USE_GRAPHIC_DISPLAY */

bool controlGraphicDisplay(JsonDocument doc) {
#ifdef USE_GRAPHIC_DISPLAY
  uint8_t command = doc["command"];
  uint8_t id = doc["id"];
  switch(command) {
    case GRAPHIC_DISPLAY_COMMAND_FILL: {
      uint16_t color = doc["param"][0]["color"];
      return graphicDisplayFillScreen(id, color);
    }
    case GRAPHIC_DISPLAY_COMMAND_STRING: {
      uint16_t x = doc["param"][0]["x"];
      uint16_t y = doc["param"][0]["y"];
      uint16_t fg = doc["param"][0]["fg"];
      uint16_t bg = doc["param"][0]["bg"];
      uint8_t size = doc["param"][0]["size"];
      uint8_t flag = doc["param"][0]["wrap"];
      bool wrap = true;
      if (flag ==0) {wrap = false;};
      const char* text = doc["param"][0]["text"];
      return graphicDisplayPrintString(id, x, y, fg, bg, size, wrap, text );
      break;
    }
    case GRAPHIC_DISPLAY_COMMAND_IMAGE: {
      uint16_t x = doc["param"][0]["x"];
      uint16_t y = doc["param"][0]["y"];
      const char* filename = doc["param"][0]["filename"];
      graphicDisplayPrintJPEG(x,y, filename);
      return true;
      break;
    }
    default: return false;
  }
#endif /* USE_GRAPHIC_DISPLAY */
  return false;
}

bool controlActuator(JsonDocument doc) {
  uint8_t id = doc["id"];
  uint32_t type = doc["type"];
  if ( false == checkDeviceTable(id, type)) return false;
  uint8_t deviceCategory = getDeviceCategory(type);
  bool flag = false;
  switch(deviceCategory) {
    case DEVICE_CATEGORY_CHARACTER_DISPLAY: {
      flag = controlCharacterDisplay(doc);
      break;
    }
    case DEVICE_CATEGORY_LED: {
      flag = controlLED(doc);
      break;
    }
    case DEVICE_CATEGORY_N_SEG_LED: {
      flag = controlNsegLED(doc);
      break;
    }
    case DEVICE_CATEGORY_SERVO: {
      flag = controlServo(doc);
      break;
    }
    case DEVICE_CATEGORY_SIMPLE_SWITCH: {
      flag = controlSimpleSwitch(doc);
      break;
    }
    case DEVICE_CATEGORY_SIMPLE_SOUND: {
      flag = controlSimpleSound(doc);
      break;
    }
    case DEVICE_CATEGORY_SIMPLE_PWM: {
      flag = controlPWM(doc);
      break;
    }
    case DEVICE_CATEGORY_SIMPLE_IRDA: {
      flag = controlIRDA(doc);
      break;
    }
    case DEVICE_CATEGORY_SIMPLE_MP3_PLAYER: {
      flag = controlMp3Player(doc);
      break;
    }
    case DEVICE_CATEGORY_GRAPHIC_DISPLAY: {
      flag = controlGraphicDisplay(doc);
      break;
    }
    default: return flag;
  }
  return flag;
}

void keepStateActuator() {
  for (int i=0; i< NUM_OF_DEVICES; i++) {
    uint8_t deviceCategory = getDeviceCategory(deviceTable[i].type);
    switch(deviceCategory) {
      case DEVICE_CATEGORY_N_SEG_LED: {
        keepStateNsegLED(i);
      }
    }
  }
}

#ifdef USE_IRDA
void init_ir_sender(uint8_t id, uint32_t type, uint8_t pin) {
  IrSender.begin(pin);
  disableLEDFeedback();
  //updateDeviceTable(id, IRDA_TYPE_SIMPLE, &IrSender);
  updateDeviceTable(id, type);
}
#endif /* USE_IRDA */
