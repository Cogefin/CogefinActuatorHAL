#ifndef __UNIFIED_MP3_H__
#define __UNIFIED_MP3_H__

#include "Arduino.h"
#include "../config.h"

#include "detectArduinoHardware.h"

#ifdef USE_MP3_PLAYER


/* Mega 2560 */
#if CPU_ARCH == AVR_ARCH
  #define _SOFTWARE_SERIAL_
#endif /* CPU_ARCH == AVR_ARCH */


/* Nano ESP32 */
#if HARDWARE_TYPE==ARDUINO_NANO_ESP32_S3
  #define _SOFTWARE_SERIAL_
#endif /* HARDWARE_TYPE==ARDUINO_NANO_ESP32_S3 */


#ifdef __USE_KT403A_PLAYER__  // Grove - MP3 v2.0  https://wiki.seeedstudio.com/Grove-MP3_v2.0/
#include "KT403A_Player.h"
#endif /* __USE_KT403A_PLAYER__ */

#ifdef __USE_WT2003S_PLAYER__  // Grove - MP3 v3.0  https://wiki.seeedstudio.com/Grove-MP3-v3/
#include "WT2003S_Player.h"
#endif /* __USE_WT2003S_PLAYER__ */

#ifdef __USE_WT2605C_PLAYER__  // Grove - MP3 v4.0  https://wiki.seeedstudio.com/grove_mp3_v4/
#include "WT2605C_Player.h"
#endif /* __USE_WT2605C_PLAYER__ */

#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
#include "DFRobotDFPlayerMini.h"
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */

#ifdef _SOFTWARE_SERIAL_
#include <SoftwareSerial.h>
  SoftwareSerial SSerial(SOFTWARE_SERIAL_PIN_RX, SOFTWARE_SERIAL_PIN_TX); // RX, TX
#endif /* _SOFTWARE_SERIAL_ */




//#define UNIFIED_MP3_UNSUPPORTED -1
//#define UNIFIED_MP3_SUCCESS      1
//#define UNIFIED_MP3_FAIL         0


typedef enum {
  MP3_FUNCTION_UNSUPPORTED = 1,
  MP3_FUNCTION_SUCCESS,
  MP3_FUNCTION_FAIL,
} mp3FunctionReturnValue;


typedef enum {
  KT403A_PLAYER = 1,
  WT2003S_PLAYER,
  WT2605C_PLAYER,
  DF_ROBOT_DFP_PLAYER_MINI
} UnifiedMp3PlayerType;

typedef enum {
  SD_STORAGE = 1,
  SPI_STORAGE,
  UDISK_STORAGE
} UnifiedMp3PlayerStorage;

typedef enum {
    MP3_MODE_CYCLE        = 0,
    MP3_MODE_SINGLE_CYCLE,
    MP3_MODE_DIR_CYCLE,
    MP3_MODE_RANDOM,
    MP3_MODE_SINGLE_SHOT
} UnifiedMp3PlayerMode;

class UnifiedMP3 {
public:
#ifdef __USE_KT403A_PLAYER__
#ifdef _SOFTWARE_SERIAL_
  UnifiedMP3(KT403A<SoftwareSerial> * kt403a, UnifiedMp3PlayerType type);
#else /* _SOFTWARE_SERIAL_ */
  UnifiedMP3(KT403A<HardwareSerial> * kt403a, UnifiedMp3PlayerType type);
#endif /* _SOFTWARE_SERIAL_ */
#endif /* __USE_KT403A_PLAYER__ */
#ifdef __USE_WT2003S_PLAYER__
#ifdef _SOFTWARE_SERIAL_
  UnifiedMP3(WT2003S<SoftwareSerial> * wt2003s, UnifiedMp3PlayerType type);
#else /* _SOFTWARE_SERIAL_ */
  UnifiedMP3(WT2003S<HardwareSerial> * wt2003s, UnifiedMp3PlayerType type);
#endif /* _SOFTWARE_SERIAL_ */
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
#ifdef _SOFTWARE_SERIAL_
  UnifiedMP3(WT2605C<SoftwareSerial> * wt2605c, UnifiedMp3PlayerType type);

#else /* _SOFTWARE_SERIAL_ */
  UnifiedMP3(WT2605C<HardwareSerial> * wt2605c, UnifiedMp3PlayerType type);
#endif /* _SOFTWARE_SERIAL_ */
#endif /* __USE_WT2605C_PLAYER__ */
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
  UnifiedMP3(DFRobotDFPlayerMini *dfr_player_mini, UnifiedMp3PlayerType type);
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
  mp3FunctionReturnValue stop(void);
  mp3FunctionReturnValue next(void);
  mp3FunctionReturnValue previous(void);
  mp3FunctionReturnValue volume(uint8_t volume);
  mp3FunctionReturnValue volumeDown(void);
  mp3FunctionReturnValue volumeUp(void);
  mp3FunctionReturnValue selectStorage(UnifiedMp3PlayerStorage storage);
  mp3FunctionReturnValue pause(void);
  mp3FunctionReturnValue start(void);
  mp3FunctionReturnValue playByIndex(uint32_t index, UnifiedMp3PlayerMode mode);
  mp3FunctionReturnValue playByName(const char* fileName, UnifiedMp3PlayerMode mode);
  mp3FunctionReturnValue playDirectoryByNumber(uint8_t folderNumber, uint32_t fileNumber, UnifiedMp3PlayerMode mode);
  mp3FunctionReturnValue playLargeDirectoryByNumber(uint8_t folderNumber, uint32_t fileNumber);
  mp3FunctionReturnValue playDirectoryByName(const char* dir, uint32_t fileNumber, UnifiedMp3PlayerMode mode);
  mp3FunctionReturnValue loopDirectory(int folderNumber);
  mp3FunctionReturnValue playMp3Directory(int fileNumber);
  mp3FunctionReturnValue cutInPlay(UnifiedMp3PlayerStorage device, uint32_t index);
  mp3FunctionReturnValue setEQ(uint8_t eq);

private:
  mp3FunctionReturnValue setMode(UnifiedMp3PlayerMode mode);
#if defined(__USE_WT2003S_PLAYER__) || defined(__USE_WT2605C_PLAYER__)
  UnifiedMp3PlayerStorage _storage_type;
#endif /* __USE_WT2003S_PLAYER__ || __USE_WT2605C_PLAYER__ */
  UnifiedMp3PlayerType _type;
#ifdef __USE_KT403A_PLAYER__
#ifdef _SOFTWARE_SERIAL_
  KT403A<SoftwareSerial> * _kt403a;
#else /* _SOFTWARE_SERIAL_ */
  KT403A<HardwareSerial> * _kt403a;
#endif /* _SOFTWARE_SERIAL_ */
#endif /* __USE_KT403A_PLAYER__ */
#ifdef __USE_WT2003S_PLAYER__
#ifdef _SOFTWARE_SERIAL_
  WT2003S<SoftwareSerial> * _wt2003s;
#else /* _SOFTWARE_SERIAL_ */
  WT2003S<HardwareSerial> * _wt2003s;
#endif /* _SOFTWARE_SERIAL_ */
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
#ifdef _SOFTWARE_SERIAL_
  WT2605C<SoftwareSerial> * _wt2605c;
#else /* _SOFTWARE_SERIAL_ */
  WT2605C<HardwareSerial> * _wt2605c;
#endif /* _SOFTWARE_SERIAL_ */
#endif /* __USE_WT2605C_PLAYER__ */
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
  DFRobotDFPlayerMini * _dfr_player_mini;
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
};

#endif /* USE_MP3_PLAYER */
#endif /* __UNIFIED_MP3_H__ */

#if defined(__USE_KT403A_PLAYER__) || defined(__USE_WT2003S_PLAYER__) || defined(__USE_WT2605C_PLAYER__)
#endif /* __USE_KT403A_PLAYER__ || __USE_WT2003S_PLAYER__ || __USE_WT2605C_PLAYER__ */


#ifdef __USE_KT403A_PLAYER__
#endif /* __USE_KT403A_PLAYER__ */
#ifdef __USE_WT2003S_PLAYER__
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
#endif /* __USE_WT2605C_PLAYER__ */
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */

