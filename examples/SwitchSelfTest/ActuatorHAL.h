
#ifndef __ACTUATOR_HAL_H__
#define __ACTUATOR_HAL_H__

#include "config.h"
#ifdef USE_IRDA
#define ARDUINOJSON_USE_LONG_LONG 1
#endif /* USE_IRDA */

#include "ArduinoJson.h"
#include "Arduino.h"

#ifdef USE_CHARACTER_DISPLAY
#include "src/UnifiedCharacterDisplay.h"
#endif /* USE_CHARACTER_DISPLAY */



#ifdef USE_LED
#include "src/UnifiedLED.h"
#endif /* USE_LED */

//#if defined(USE_OSL12306_16) || defined(USE_OSL20541) || defined(USE_OSL30561) || defined(USE_GROVE_TM1637) || defined(USE_DFR0090)
#ifdef USE_NSEG_LED
#include "src/UnifiedNSegLED.h"
#endif /* USE_NSEG_LED */
//#endif /* defined(USE_OSL12306_16) || defined(USE_OSL20541) || defined(USE_OSL30561) || defined(USE_GROVE_TM1637) || defined(USE_DFR0090) */

#ifdef USE_SWITCH
#include "src/SwitchHAL.h"
#endif /* USE_SWITCH */

#ifdef USE_SERVO
#include "src/ServoHAL.h"
#endif /* USE_SERVO */

#ifdef USE_SIMPLE_SOUND
#include "src/SimpleSound.h"
#endif /* USE_SIMPLE_SOUND */

#ifdef USE_PWM
#include "src/PwmHAL.h"
#endif /* USE_PWM */

#ifdef USE_MP3_PLAYER
#include "src/UnifiedMP3.h"
#endif /* USE_MP3_PLAYER */


#ifdef USE_GRAPHIC_DISPLAY
#include "src/UnifiedGraphicDisplay.h"
#endif /* USE_GRAPHIC_DISPLAY */

#define DEVICE_CATEGORY_UNKNOWN             0
#define DEVICE_CATEGORY_CHARACTER_DISPLAY   1
#define DEVICE_CATEGORY_LED                 2
#define DEVICE_CATEGORY_N_SEG_LED           3
#define DEVICE_CATEGORY_SIMPLE_SWITCH       4
#define DEVICE_CATEGORY_SERVO               5
#define DEVICE_CATEGORY_SIMPLE_SOUND        6
#define DEVICE_CATEGORY_SIMPLE_PWM          7
#define DEVICE_CATEGORY_SIMPLE_IRDA         8
#define DEVICE_CATEGORY_SIMPLE_MP3_PLAYER   9
#define DEVICE_CATEGORY_GRAPHIC_DISPLAY     10

#define CHARACTER_DISPLAY_TYPE_MIN                      100
#define CHARACTER_DISPLAY_TYPE_MAX                      104
#define CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT  101
#define CHARACTER_DISPLAY_TYPE_ACM1602NI                102
#define CHARACTER_DISPLAY_TYPE_LIQUID_CRYSTAL           103

#define LED_TYPE_MIN                200
#define LED_TYPE_MAX                205
#define LED_TYPE_MONO_LED           201
#define LED_TYPE_MONO_CHAIN_LED     202
#define LED_TYPE_COLOR_LED          203
#define LED_TYPE_COLOR_CHAIN_LED    204

#define NSEG_LED_TYPE_MIN           300
#define NSEG_LED_TYPE_OSL12306_16   301
#define NSEG_LED_TYPE_OSL20541      302
#define NSEG_LED_TYPE_OSL30561      303
#define NSEG_LED_TYPE_GROVE_TM1637  304
#define NSEG_LED_TYPE_DFR0090       305
#define NSEG_LED_TYPE_MAX           306

#define SIMPLE_SWITCH_TYPE_MIN      400
#define SIMPLE_SWITCH_TYPE_NORMAL   401
#define SIMPLE_SWITCH_TYPE_MAX      402

#define SERVO_TYPE_MIN              500
#define SERVO_TYPE_SIMPLE           501
#define SERVO_TYPE_MAX              502

#define SIMPLE_SOUND_TYPE_MIN       600
#define SIMPLE_SOUND_TYPE_NORMAL    601
#define SIMPLE_SOUND_TYPE_MAX       602

#define PWM_TYPE_MIN                700
#define PWM_TYPE_SIMPLE             701
#define PWM_TYPE_MAX                702

#define IRDA_TYPE_MIN               800
#define IRDA_TYPE_SIMPLE            801
#define IRDA_TYPE_MAX               802

#define MP3_PLAYER_TYPE_MIN           900
#define MP3_PLAYER_TYPE_KT403A        901
#define MP3_PLAYER_TYPE_WT2003S       902
#define MP3_PLAYER_TYPE_WT2605C       903
#define MP3_PLAYER_TYPE_DF_ROBOT_DFP  904
#define MP3_PLAYER_TYPE_MAX           905

#define GRAPHIC_DISPLAY_TYPE_MIN            1000
#define GRAPHIC_DISPLAY_TYPE_U8G2           1001
#define GRAPHIC_DISPLAY_TYPE_GIGA_DISPLAY   1002
#define GRAPHIC_DISPLAY_TYPE_BODMER_TFT     1003
#define GRAPHIC_DISPLAY_TYPE_ADAFRUIT_GFX   1004
#define GRAPHIC_DISPLAY_TYPE_MAX            1005

#define CHARACTER_DISPLAY_COMMAND_CLEAR             1
#define CHARACTER_DISPLAY_COMMAND_HOME              2
#define CHARACTER_DISPLAY_COMMAND_SET_MODE          3
#define CHARACTER_DISPLAY_COMMAND_SET_CURSUR        4
#define CHARACTER_DISPLAY_COMMAND_SET_SIZE          5
#define CHARACTER_DISPLAY_COMMAND_PRINT             6
#define CHARACTER_DISPLAY_COMMAND_SET_BACKLIGHT_RGB 7

#define CHARACTER_DISPLAY_MODE_NO_DISPLAY          1
#define CHARACTER_DISPLAY_MODE_ON_DISPLAY          2
#define CHARACTER_DISPLAY_MODE_NO_BLINK            3
#define CHARACTER_DISPLAY_MODE_BLINK               4
#define CHARACTER_DISPLAY_MODE_NO_CURSOR           5
#define CHARACTER_DISPLAY_MODE_CURSOR              6
#define CHARACTER_DISPLAY_MODE_SCROLL_LEFT         7
#define CHARACTER_DISPLAY_MODE_SCROLL_RIGHT        8
#define CHARACTER_DISPLAY_MODE_LEFT_TO_RIGHT       9
#define CHARACTER_DISPLAY_MODE_RIGHT_TO_LEFT      10
#define CHARACTER_DISPLAY_MODE_AUTO_SCROLL        11
#define CHARACTER_DISPLAY_MODE_NO_AUTO_SCROLL     12
#define CHARACTER_DISPLAY_MODE_BLINK_BACKLIGHT    13
#define CHARACTER_DISPLAY_MODE_NO_BLINK_BACKLIGHT 14

#define LED_COMMAND_CLEAR               1
#define LED_COMMAND_SET_BRIGHTNESS      2
#define LED_COMMAND_SET_BRIGHTNESS_N    3
#define LED_COMMAND_SET_RGB             4
#define LED_COMMAND_SET_RGB_N           5
#define LED_COMMAND_SET_MODE            6

#define NSEG_LED_COMMAND_CLEAR          1
#define NSEG_LED_COMMAND_SET_BRIGHTNESS 2
#define NSEG_LED_COMMAND_SET_COLON      3
#define NSEG_LED_COMMAND_SET            4
#define NSEG_LED_COMMAND_SETC           5


#define SIMPLE_SWITCH_COMMAND_ON     1
#define SIMPLE_SWITCH_COMMAND_OFF    2

#define SERVO_COMMAND_WRITE     1
#define SERVO_COMMAND_WRITE_MS  2

#define SIMPLE_SOUND_COMMAND_ON     1
#define SIMPLE_SOUND_COMMAND_OFF    2
#define SIMPLE_SOUND_COMMAND_PLAY   3

#define PWM_COMMAND_APPLY 1
#define PWM_COMMAND_OFF   2
#define PWM_COMMAND_SET   3

#define IRDA_COMMAND_BANG_OLUFSEN        10
#define IRDA_COMMAND_BANG_OLUFSEN_LINK   11
#define IRDA_COMMAND_BOSE_WAVE           20
#define IRDA_COMMAND_SHARP               30
#define IRDA_COMMAND_DENON               31
#define IRDA_COMMAND_FAST                40
#define IRDA_COMMAND_JVC                 50
#define IRDA_COMMAND_KASEIKYO            60
#define IRDA_COMMAND_KASEIKYO_JVC        61
#define IRDA_COMMAND_KASEIKYO_DENON      62
#define IRDA_COMMAND_KASEIKYO_SHARP      63
#define IRDA_COMMAND_KASEIKYO_MITSUBISHI 64
#define IRDA_COMMAND_LG                  70
#define IRDA_COMMAND_LG_2                71
#define IRDA_COMMAND_LEGO                80
#define IRDA_COMMAND_LEGO_2              81
#define IRDA_COMMAND_MAGIC_QUEST         90
#define IRDA_COMMAND_NEC                100
#define IRDA_COMMAND_NEC_2              101
#define IRDA_COMMAND_ONKYO              102
#define IRDA_COMMAND_APPLE              103
#define IRDA_COMMAND_RC5                110
#define IRDA_COMMAND_RC6                111
#define IRDA_COMMAND_RC6_2              112
#define IRDA_COMMAND_RC6_3              113
#define IRDA_COMMAND_RC6_A              114
#define IRDA_COMMAND_SAMSUNG            120
#define IRDA_COMMAND_SAMSUNG_LG         121
#define IRDA_COMMAND_SAMSUNG_48         122
#define IRDA_COMMAND_SONY               130
#define IRDA_COMMAND_DISH               140
#define IRDA_COMMAND_WHYNTER            141
#define IRDA_COMMAND_PRONTO             150
#define IRDA_COMMAND_PRONTO_2           151
#define IRDA_COMMAND_PRONTO_3           152
#define IRDA_COMMAND_PRONTO_P           153
#define IRDA_COMMAND_PANASONIC          160

#define MP3_PLAYER_COMMAND_STOP             1
#define MP3_PLAYER_COMMAND_NEXT             2
#define MP3_PLAYER_COMMAND_PREVIOUS         3
#define MP3_PLAYER_COMMAND_VOLUME           4
#define MP3_PLAYER_COMMAND_VOL_DOWN         5
#define MP3_PLAYER_COMMAND_VOL_UP           6
#define MP3_PLAYER_COMMAND_STORAGE          7
#define MP3_PLAYER_COMMAND_PAUSE            8
#define MP3_PLAYER_COMMAND_START            9
#define MP3_PLAYER_COMMAND_PLAY_BY_INDEX    10
#define MP3_PLAYER_COMMAND_PLAY_BY_NAME     11
#define MP3_PLAYER_COMMAND_PLAY_DIR_BY_NUM  12
#define MP3_PLAYER_COMMAND_PLAY_DIR_BY_NAME 13
#define MP3_PLAYER_COMMAND_LOOP_DIR         14
#define MP3_PLAYER_COMMAND_PLAY_MP3_DIR     15
#define MP3_PLAYER_COMMAND_CUT_IN_PLAY      16
#define MP3_PLAYER_COMMAND_SET_EQ           17

#define MP3_PLAYER_STORAGE_SD     1
#define MP3_PLAYER_STORAGE_SPI    2
#define MP3_PLAYER_STORAGE_UDISK  3

#define MP3_PLAYER_MODE_CYCLE         0
#define MP3_PLAYER_MODE_SINGLE_CYCLE  1
#define MP3_PLAYER_MODE_DIR_CYCLE     2
#define MP3_PLAYER_MODE_RANDOM        3
#define MP3_PLAYER_MODE_SINGLE_SHOT   4

#define GRAPHIC_DISPLAY_COMMAND_FILL    1
#define GRAPHIC_DISPLAY_COMMAND_STRING  2
#define GRAPHIC_DISPLAY_COMMAND_IMAGE   3

#ifdef USE_CHARACTER_DISPLAY
extern void updateDeviceTable(uint8_t id, uint32_t type, UnifiedLCD * characterDisplay_pointer);
#endif /* USE_CHARACTER_DISPLAY */

#ifdef USE_LED
extern void updateDeviceTable(uint8_t id, uint32_t type, UnifiedLED * led);
#endif /* USE_LED */

#ifdef USE_SWITCH
extern void updateDeviceTable(uint8_t id, uint32_t type, Switch * ss);
#endif /* USE_SWITCH */

#ifdef USE_SERVO
extern void updateDeviceTable(uint8_t id, uint32_t type, ServoHal * ss);
#endif /* USE_SERVO */

#ifdef USE_SIMPLE_SOUND
extern void updateDeviceTable(uint8_t id, uint32_t type, SimpleSound * ss);
#endif /* USE_SIMPLE_SOUND */

#ifdef USE_PWM
extern void updateDeviceTable(uint8_t id, uint32_t type, PWM *  ss);
#endif /* USE_PWM */

#ifdef USE_IRDA
//extern void updateDeviceTable(uint8_t id, uint32_t type, IRsend * ss) ;
//extern void updateDeviceTable(uint8_t id, uint32_t type) ;
//extern void init_ir_sender(uint8_t pin, uint8_t id);
extern void init_ir_sender(uint8_t id, uint32_t type, uint8_t pin);
#endif /* USE_IRDA */

#ifdef USE_NSEG_LED
extern void updateDeviceTable(uint8_t id, uint32_t type, UnifiedNSegLED * nseg, uint8_t digits);
#endif /* USE_NSEG_LED */

#ifdef USE_MP3_PLAYER
extern void updateDeviceTable(uint8_t id, uint32_t type, UnifiedMP3 *  ss);
#endif /* USE_MP3_PLAYER */

#ifdef USE_GRAPHIC_DISPLAY
extern void updateDeviceTable(uint8_t id, uint32_t type, UnifiedGraphicDisplay *  display);
#endif /* USE_GRAPHIC_DISPLAY */

extern bool controlActuator(JsonDocument doc);
extern void keepStateActuator(void);

extern void initDeviceTable(void);
extern void dumpDeviceTable(void);

#endif /* __ACTUATOR_HAL_H__ */


