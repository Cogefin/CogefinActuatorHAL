#include "UnifiedMP3.h"

#ifdef USE_MP3_PLAYER

#ifdef __USE_KT403A_PLAYER__
#ifdef _SOFTWARE_SERIAL_
UnifiedMP3::UnifiedMP3(KT403A<SoftwareSerial> * kt403a, UnifiedMp3PlayerType type):
#else /* _SOFTWARE_SERIAL_ */
UnifiedMP3::UnifiedMP3(KT403A<HardwareSerial> * kt403a, UnifiedMp3PlayerType type):
#endif /* _SOFTWARE_SERIAL_ */
  _kt403a(kt403a),
  _type(type)
{
}
#endif /* __USE_KT403A_PLAYER__ */
#ifdef __USE_WT2003S_PLAYER__
#ifdef _SOFTWARE_SERIAL_
UnifiedMP3::UnifiedMP3(WT2003S<SoftwareSerial> * wt2003s, UnifiedMp3PlayerType type):
#else /* _SOFTWARE_SERIAL_ */
UnifiedMP3::UnifiedMP3(WT2003S<HardwareSerial> * wt2003s, UnifiedMp3PlayerType type):
#endif /* _SOFTWARE_SERIAL_ */
  _wt2003s(wt2003s),
  _type(type)
{
  _storage_type = SD_STORAGE;
}
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
#ifdef _SOFTWARE_SERIAL_
UnifiedMP3::UnifiedMP3(WT2605C<SoftwareSerial> * wt2605c, UnifiedMp3PlayerType type):
#else /* _SOFTWARE_SERIAL_ */
UnifiedMP3::UnifiedMP3(WT2605C<HardwareSerial> * wt2605c, UnifiedMp3PlayerType type):
#endif /* _SOFTWARE_SERIAL_ */
  _wt2605c(wt2605c),
  _type(type)
{
  _storage_type = SD_STORAGE;
}
#endif /* __USE_WT2605C_PLAYER__ */
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
#ifdef _SOFTWARE_SERIAL_
UnifiedMP3::UnifiedMP3(DFRobotDFPlayerMini *dfr_player_mini, UnifiedMp3PlayerType type):
#else /* _SOFTWARE_SERIAL_ */
UnifiedMP3::UnifiedMP3(DFRobotDFPlayerMini *dfr_player_mini, UnifiedMp3PlayerType type):
#endif /* _USE_SOFTWARE_SERIAL_ */
  _dfr_player_mini(dfr_player_mini),
  _type(type)
{
}
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */

mp3FunctionReturnValue UnifiedMP3::stop(void) {
  switch(_type) {
#ifdef __USE_KT403A_PLAYER__
    case KT403A_PLAYER: {
      uint8_t result = _kt403a->stop();
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_KT403A_PLAYER__ */
#ifdef __USE_WT2003S_PLAYER__
    case WT2003S_PLAYER: {
      uint8_t result = _wt2003s->stop();
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
    case WT2605C_PLAYER: {
      uint8_t result = _wt2605c->stop();
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_WT2605C_PLAYER__ */
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
    case DF_ROBOT_DFP_PLAYER_MINI: {
      _dfr_player_mini->stop();
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
    default: {
      return MP3_FUNCTION_UNSUPPORTED;
    }
  }
  return MP3_FUNCTION_UNSUPPORTED;
}

mp3FunctionReturnValue UnifiedMP3::next(void) {
  switch(_type) {
#ifdef __USE_KT403A_PLAYER__
    case KT403A_PLAYER: {
      uint8_t result = _kt403a->next();
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_KT403A_PLAYER__ */
#ifdef __USE_WT2003S_PLAYER__
    case WT2003S_PLAYER: {
      uint8_t result = _wt2003s->next();
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
    case WT2605C_PLAYER: {
      uint8_t result = _wt2605c->next();
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_WT2605C_PLAYER__ */
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
    case DF_ROBOT_DFP_PLAYER_MINI: {
      _dfr_player_mini->next();
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
    default: {
      return MP3_FUNCTION_UNSUPPORTED;
    }
  }
  return MP3_FUNCTION_UNSUPPORTED;
}

mp3FunctionReturnValue UnifiedMP3::previous(void) {
  switch(_type) {
#ifdef __USE_KT403A_PLAYER__
    case KT403A_PLAYER: {
      uint8_t result = _kt403a->previous();
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_KT403A_PLAYER__ */
#ifdef __USE_WT2003S_PLAYER__
    case WT2003S_PLAYER: {
      uint8_t result = _wt2003s->previous();
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
    case WT2605C_PLAYER: {
      uint8_t result = _wt2605c->previous();
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_WT2605C_PLAYER__ */
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
    case DF_ROBOT_DFP_PLAYER_MINI: {
      _dfr_player_mini->previous();
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
    default: {
      return MP3_FUNCTION_UNSUPPORTED;
    }
  }
  return MP3_FUNCTION_UNSUPPORTED;
}

mp3FunctionReturnValue UnifiedMP3::volume(uint8_t vol) {
  switch(_type) {
#ifdef __USE_KT403A_PLAYER__
    case KT403A_PLAYER: {
      uint8_t result = _kt403a->volume(vol);
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_KT403A_PLAYER__ */
#ifdef __USE_WT2003S_PLAYER__
    case WT2003S_PLAYER: {
      uint8_t result = _wt2003s->volume(vol);
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
    case WT2605C_PLAYER: {
      uint8_t result = _wt2605c->volume(vol);
      //Serial.print("result = ");Serial.println(result);
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      //Serial.println("bar");
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_WT2605C_PLAYER__ */
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
    case DF_ROBOT_DFP_PLAYER_MINI: {
      _dfr_player_mini->volume(vol);
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
    default: {
      return MP3_FUNCTION_UNSUPPORTED;
    }
  }
  return MP3_FUNCTION_UNSUPPORTED;
}

mp3FunctionReturnValue UnifiedMP3::volumeDown(void) {
  switch(_type) {
#ifdef __USE_KT403A_PLAYER__
    case KT403A_PLAYER: {
      uint8_t result = _kt403a->volumeDown();
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_KT403A_PLAYER__ */
#ifdef __USE_WT2003S_PLAYER__
    case WT2003S_PLAYER: {
      uint8_t result = _wt2003s->volumeDown();
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
    case WT2605C_PLAYER: {
      uint8_t result = _wt2605c->volumeDown();
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_WT2605C_PLAYER__ */
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
    case DF_ROBOT_DFP_PLAYER_MINI: {
      _dfr_player_mini->volumeDown();
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
    default: {
      return MP3_FUNCTION_UNSUPPORTED;
    }
  }
  return MP3_FUNCTION_UNSUPPORTED;
}

mp3FunctionReturnValue UnifiedMP3::volumeUp(void) {
  switch(_type) {
#ifdef __USE_KT403A_PLAYER__
    case KT403A_PLAYER: {
      uint8_t result = _kt403a->volumeUp();
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_KT403A_PLAYER__ */
#ifdef __USE_WT2003S_PLAYER__
    case WT2003S_PLAYER: {
      uint8_t result = _wt2003s->volumeUp();
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
    case WT2605C_PLAYER: {
      uint8_t result = _wt2605c->volumeUp();
      if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_WT2605C_PLAYER__ */
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
    case DF_ROBOT_DFP_PLAYER_MINI: {
      _dfr_player_mini->volumeUp();
      return MP3_FUNCTION_SUCCESS;
    }
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
    default: {
      return MP3_FUNCTION_UNSUPPORTED;
    }
  }
  return MP3_FUNCTION_UNSUPPORTED;
}

mp3FunctionReturnValue UnifiedMP3::selectStorage(UnifiedMp3PlayerStorage storage) {
#if defined(__USE_WT2003S_PLAYER__) || defined(__USE_WT2605C_PLAYER__)
  if ((_type == WT2003S_PLAYER) || (_type == WT2605C_PLAYER)) {
    _storage_type = storage;
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_WT2003S_PLAYER__ || __USE_WT2605C_PLAYER__ */
  return MP3_FUNCTION_UNSUPPORTED;
}

mp3FunctionReturnValue UnifiedMP3::pause(void) {
#ifdef __USE_KT403A_PLAYER__
  if (_type == KT403A_PLAYER) {
    uint8_t result = _kt403a->pause();
    if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_KT403A_PLAYER__ */
#ifdef __USE_WT2003S_PLAYER__
  if (_type == WT2003S_PLAYER) {
    _wt2003s->pause_or_play();
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
  if (_type == WT2605C_PLAYER) {
    _wt2605c->pause_or_play();
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_WT2605C_PLAYER__ */
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
  if (_type == DF_ROBOT_DFP_PLAYER_MINI) {
    _dfr_player_mini->pause();
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
  return MP3_FUNCTION_UNSUPPORTED;
}

mp3FunctionReturnValue UnifiedMP3::start(void) {
#ifdef __USE_KT403A_PLAYER__
#endif /* __USE_KT403A_PLAYER__ */
#ifdef __USE_WT2003S_PLAYER__
  if (_type == WT2003S_PLAYER) {
    _wt2003s->pause_or_play();
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
  if (_type == WT2605C_PLAYER) {
    _wt2605c->pause_or_play();
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_WT2605C_PLAYER__ */
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
  if (_type == DF_ROBOT_DFP_PLAYER_MINI) {
    _dfr_player_mini->start();
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
  return MP3_FUNCTION_UNSUPPORTED;
}

mp3FunctionReturnValue UnifiedMP3::setMode(UnifiedMp3PlayerMode mode) {
#ifdef __USE_WT2003S_PLAYER__
  uint8_t result;
  switch(mode) {
    case MP3_MODE_SINGLE_SHOT: {
      result = _wt2003s->playMode(WT2003S_SINGLE_SHOT);
      break;
    }
    case MP3_MODE_SINGLE_CYCLE: {
      result = _wt2003s->playMode(WT2003S_SINGLE_CYCLE);
      break;
    }
    case MP3_MODE_CYCLE: {
      result = _wt2003s->playMode(WT2003S_CYCLE);
      break;
    }
    case MP3_MODE_RANDOM: {
      result = _wt2003s->playMode(WT2003S_RANDOM);
      break;
    }
    default: {
      return MP3_FUNCTION_UNSUPPORTED;
    }
  }
  if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
  return MP3_FUNCTION_SUCCESS;
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
  uint8_t wt2605c_result;
  switch(mode) {
    case MP3_MODE_SINGLE_SHOT: {
      wt2605c_result = _wt2605c->playMode(WT2605C_SINGLE_SHOT);
      break;
    }
    case MP3_MODE_SINGLE_CYCLE: {
      wt2605c_result = _wt2605c->playMode(WT2605C_SINGLE_CYCLE);
      break;
    }
    case MP3_MODE_CYCLE: {
      wt2605c_result = _wt2605c->playMode(WT2605C_CYCLE);
      break;
    }
    case MP3_MODE_RANDOM: {
      wt2605c_result = _wt2605c->playMode(WT2605C_RANDOM);
      break;
    }
    case MP3_MODE_DIR_CYCLE: {
      wt2605c_result = _wt2605c->playMode(WT2605C_DIR_CYCLE);
      break;
    }
    default: {
      return MP3_FUNCTION_UNSUPPORTED;
    }
  }
  if (wt2605c_result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
  return MP3_FUNCTION_SUCCESS;
#endif /* __USE_WT2605C_PLAYER__ */
  return MP3_FUNCTION_UNSUPPORTED;
}

mp3FunctionReturnValue UnifiedMP3::playByIndex(uint32_t index, UnifiedMp3PlayerMode mode) {
#if defined(__USE_WT2003S_PLAYER__) || defined(__USE_WT2605C_PLAYER__)
  if ((_type == WT2003S_PLAYER) || (_type == WT2605C_PLAYER)) {
    switch(_storage_type) {
      case SD_STORAGE: {
        mp3FunctionReturnValue modeResult;
        uint8_t result;
#ifdef __USE_WT2003S_PLAYER__
        result = _wt2003s->playSDRootSong(index);
        if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
        modeResult = setMode(mode);
        if (MP3_FUNCTION_SUCCESS != modeResult) return modeResult;
        return MP3_FUNCTION_SUCCESS;
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
        result = _wt2605c->playSDRootSong(index);
        if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
        modeResult = setMode(mode);
        if (MP3_FUNCTION_SUCCESS != modeResult) return modeResult;
        return MP3_FUNCTION_SUCCESS;
#endif /* __USE_WT2605C_PLAYER__ */
      }
      case UDISK_STORAGE: {
        mp3FunctionReturnValue modeResult;
        uint8_t result;
#ifdef __USE_WT2003S_PLAYER__
        result = _wt2003s->playUDiskRootSong(index);
        if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
        modeResult = setMode(mode);
        if (MP3_FUNCTION_SUCCESS != modeResult) return modeResult;
        return MP3_FUNCTION_SUCCESS;
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
        result = _wt2605c->playUDiskRootSong(index);
        if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
        modeResult = setMode(mode);
        if (MP3_FUNCTION_SUCCESS != modeResult) return modeResult;
        return MP3_FUNCTION_SUCCESS;
#endif /* __USE_WT2605C_PLAYER__ */
      }
      case SPI_STORAGE: {
        uint16_t fileIndex = (uint16_t)index;
        mp3FunctionReturnValue modeResult;
        uint8_t result;
#ifdef __USE_WT2003S_PLAYER__
        result = _wt2003s->playSPIFlashSong(fileIndex);
        if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
        modeResult = setMode(mode);
        if (MP3_FUNCTION_SUCCESS != modeResult) return modeResult;
        return MP3_FUNCTION_SUCCESS;
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
        result = _wt2605c->playSPIFlashSong(fileIndex);
        if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
        modeResult = setMode(mode);
        if (MP3_FUNCTION_SUCCESS != modeResult) return modeResult;
        return MP3_FUNCTION_SUCCESS;
#endif /* __USE_WT2605C_PLAYER__ */
      }
      default: {
        return MP3_FUNCTION_UNSUPPORTED;
      }
    }
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_WT2003S_PLAYER__ || __USE_WT2605C_PLAYER__ */
#ifdef __USE_KT403A_PLAYER__
  if (_type == KT403A_PLAYER) {
    uint16_t fileIndex = (uint16_t)index;
    uint8_t result;
    switch(mode) {
      case MP3_MODE_SINGLE_SHOT: {
        result = _kt403a->playSongMP3(fileIndex);
        break;
      }
      default: {
        return MP3_FUNCTION_UNSUPPORTED;
      }
    }
    if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_KT403A_PLAYER__ */
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
  if (_type == DF_ROBOT_DFP_PLAYER_MINI) {
    int fileIndex = (int)index;
    //uint8_t result;
    switch(mode) {
      case MP3_MODE_SINGLE_SHOT: {
        //result = _dfr_player_mini->play(fileIndex);
        _dfr_player_mini->play(fileIndex);
        break;
      }
      case MP3_MODE_SINGLE_CYCLE: {
        //result = _dfr_player_mini->loop(fileIndex);
        _dfr_player_mini->loop(fileIndex);
        break;
      }
      default: {
        return MP3_FUNCTION_UNSUPPORTED;
      }
    }
    //if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
  return MP3_FUNCTION_UNSUPPORTED;
}

mp3FunctionReturnValue UnifiedMP3::playByName(const char* fileName, UnifiedMp3PlayerMode mode){
#ifdef __USE_WT2003S_PLAYER__
  if (_type == WT2003S_PLAYER) {
    mp3FunctionReturnValue modeResult = setMode(mode);
    if (MP3_FUNCTION_SUCCESS != modeResult) return modeResult;
    uint8_t result;
    switch(_storage_type) {
      case SD_STORAGE: {
        result = _wt2003s->playSDSong(fileName);
      }
      case UDISK_STORAGE: {
        result = _wt2003s->playUDiskSong(fileName);
      }
      default: {
        return MP3_FUNCTION_UNSUPPORTED;
      }
    }
    if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
  if (_type == WT2605C_PLAYER) {
    uint8_t result;
    switch(_storage_type) {
      case SD_STORAGE: {
        result = _wt2605c->playSDSong(fileName);
      }
      case UDISK_STORAGE: {
        result = _wt2605c->playUDiskSong(fileName);
      }
      default: {
        return MP3_FUNCTION_UNSUPPORTED;
      }
    }
    if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
    mp3FunctionReturnValue modeResult = setMode(mode);
    if (MP3_FUNCTION_SUCCESS != modeResult) return modeResult;
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_WT2605C_PLAYER__ */
  return MP3_FUNCTION_UNSUPPORTED;
}

mp3FunctionReturnValue UnifiedMP3::playDirectoryByNumber(uint8_t folderNumber, uint32_t fileNumber, UnifiedMp3PlayerMode mode){
#ifdef __USE_KT403A_PLAYER__
  if (_type == KT403A_PLAYER) {
    uint8_t fileIndexNumber = (uint8_t)fileNumber;
    int kt403a_result;
    switch(mode) {
      case MP3_MODE_SINGLE_SHOT: {
        kt403a_result = _kt403a->playSongSpecify(folderNumber, fileIndexNumber);
      }
      default: {
        return MP3_FUNCTION_UNSUPPORTED;
      }
    }
    if (kt403a_result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_KT403A_PLAYER__ */
#ifdef __USE_WT2003S_PLAYER__
  if (_type == WT2003S_PLAYER) {
    String dirName = String(folderNumber, DEC);
    int len = dirName.length() + 1;
    char result[len];
    dirName.toCharArray(result, len);
    uint8_t wt2003s_result;
    switch(_storage_type) {
      case SD_STORAGE: {
        uint16_t index = (uint16_t) fileNumber;
        wt2003s_result = _wt2003s->playSDDirectorySong(result, index);
      }
      case UDISK_STORAGE: {
        wt2003s_result = _wt2003s->playUDiskDirectorySong(result, fileNumber);
      }
      default: {
        return MP3_FUNCTION_UNSUPPORTED;
      }
    }
    if (wt2003s_result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
    mp3FunctionReturnValue modeResult = setMode(mode);
    if (MP3_FUNCTION_SUCCESS != modeResult) return modeResult;
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
  if (_type == WT2605C_PLAYER) {
    String dirName = String(folderNumber, DEC);
    int len = dirName.length() + 1;
    char result[len];
    for (int i=0;i<len;i++) {
      result[i]=0;
    }
    dirName.toCharArray(result, len);
    uint8_t wt2605c_result;
    switch(_storage_type) {
      case SD_STORAGE: {
        uint16_t index = (uint16_t) fileNumber;
        wt2605c_result = _wt2605c->playSDDirectorySong(result, index);
      }
      case UDISK_STORAGE: {
        wt2605c_result = _wt2605c->playUDiskDirectorySong(result, fileNumber);
      }
      default: {
        return MP3_FUNCTION_UNSUPPORTED;
      }
    }
    if (wt2605c_result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
    mp3FunctionReturnValue modeResult = setMode(mode);
    if (MP3_FUNCTION_SUCCESS != modeResult) return modeResult;
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_WT2605C_PLAYER__ */
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
  if (_type == DF_ROBOT_DFP_PLAYER_MINI) {
    if (mode != MP3_MODE_SINGLE_SHOT) return MP3_FUNCTION_UNSUPPORTED;
    uint16_t fileIndexNumber = (uint16_t)fileNumber;
    _dfr_player_mini->playFolder(folderNumber, fileIndexNumber);
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
  return MP3_FUNCTION_UNSUPPORTED;
}


mp3FunctionReturnValue UnifiedMP3::playLargeDirectoryByNumber(uint8_t folderNumber, uint32_t fileNumber){
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
  if (_type == DF_ROBOT_DFP_PLAYER_MINI) {
    uint16_t fileIndexNumber = (uint16_t)fileNumber;
    _dfr_player_mini->playLargeFolder(folderNumber, fileIndexNumber);
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
  return MP3_FUNCTION_UNSUPPORTED;
}

mp3FunctionReturnValue UnifiedMP3::playDirectoryByName(const char* dirName, uint32_t fileNumber, UnifiedMp3PlayerMode mode){
#ifdef __USE_WT2003S_PLAYER__
  if (_type == WT2003S_PLAYER) {
    uint8_t result;
    switch(_storage_type) {
      case SD_STORAGE: {
        uint16_t index = (uint16_t) fileNumber;
        result = _wt2003s->playSDDirectorySong(dirName, index);
      }
      case UDISK_STORAGE: {
        result = _wt2003s->playUDiskDirectorySong(dirName, fileNumber);
      }
      default: {
        return MP3_FUNCTION_UNSUPPORTED;
      }
    }
    if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
    mp3FunctionReturnValue modeResult = setMode(mode);
    if (MP3_FUNCTION_SUCCESS != modeResult) return modeResult;
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
  if (_type == WT2605C_PLAYER) {
    uint8_t wt2605c_result;
    switch(_storage_type) {
      case SD_STORAGE: {
        uint16_t index = (uint16_t) fileNumber;
        wt2605c_result = _wt2605c->playSDDirectorySong(dirName, index);
      }
      case UDISK_STORAGE: {
        wt2605c_result = _wt2605c->playUDiskDirectorySong(dirName, fileNumber);
      }
      default: {
        return MP3_FUNCTION_UNSUPPORTED;
      }
    }
    if (wt2605c_result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
    mp3FunctionReturnValue modeResult = setMode(mode);
    if (MP3_FUNCTION_SUCCESS != modeResult) return modeResult;
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_WT2605C_PLAYER__ */
  return MP3_FUNCTION_UNSUPPORTED;
}

mp3FunctionReturnValue UnifiedMP3::loopDirectory(int folderNumber) {
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
  _dfr_player_mini->loopFolder(folderNumber);
  return MP3_FUNCTION_SUCCESS;
#else /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
  return MP3_FUNCTION_UNSUPPORTED;
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
}

mp3FunctionReturnValue UnifiedMP3::playMp3Directory(int fileNumber) {
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
  _dfr_player_mini->playMp3Folder(fileNumber);
  return MP3_FUNCTION_SUCCESS;
#else /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
  return MP3_FUNCTION_UNSUPPORTED;
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
}

mp3FunctionReturnValue UnifiedMP3::cutInPlay(UnifiedMp3PlayerStorage device, uint32_t index){
#if defined(__USE_WT2003S_PLAYER__) || defined(__USE_WT2605C_PLAYER__)
  uint8_t result;
#ifdef __USE_WT2003S_PLAYER__
  switch(device) {
    case SD_STORAGE: {
      result = _wt2003s->cutInPlay(WT2003S_SD, index);
      break;
    }
    case SPI_STORAGE: {
      result = _wt2003s->cutInPlay(WT2003S_SPIFLASH, index);
      break;
    }
    case UDISK_STORAGE: {
      result = _wt2003s->cutInPlay(WT2003S_UDISK, index);
      break;
    }
    default: {
      return MP3_FUNCTION_UNSUPPORTED;
    }
  }
#endif /* __USE_WT2003S_PLAYER__ */
#ifdef __USE_WT2605C_PLAYER__
  switch(device) {
    case SD_STORAGE: {
      result = _wt2605c->cutInPlay(WT2605C_SD, index);
      break;
    }
    case SPI_STORAGE: {
      result = _wt2605c->cutInPlay(WT2605C_SPIFLASH, index);
      break;
    }
    case UDISK_STORAGE: {
      result = _wt2605c->cutInPlay(WT2605C_UDISK, index);
      break;
    }
    default: {
      return MP3_FUNCTION_UNSUPPORTED;
    }
  }
#endif /* __USE_WT2605C_PLAYER__ */
  if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
  return MP3_FUNCTION_SUCCESS;
#else /* defined(__USE_WT2003S_PLAYER__) || defined(__USE_WT2605C_PLAYER__) */
  return MP3_FUNCTION_UNSUPPORTED;
#endif /* defined(__USE_WT2003S_PLAYER__) || defined(__USE_WT2605C_PLAYER__) */
}

mp3FunctionReturnValue UnifiedMP3::setEQ(uint8_t eq) {
#ifdef __USE_KT403A_PLAYER__
  if (_type==KT403A_PLAYER) {
    uint8_t result;
    switch(eq) {
      case 0x00: {
        result = _kt403a->setEqualizer(NORMAL);
        break;
      }
      case 0x01: {
        result = _kt403a->setEqualizer(POP);
        break;
      }
      case 0x02: {
        result = _kt403a->setEqualizer(ROCK);
        break;
      }
      case 0x03: {
        result = _kt403a->setEqualizer(JAZZ);
        break;
      }
      case 0x04: {
        result = _kt403a->setEqualizer(CLASSIC);
        break;
      }
      case 0x05: {
        result = _kt403a->setEqualizer(BASS);
        break;
      }
      default: {
        return MP3_FUNCTION_UNSUPPORTED;
      }
    }
    if (result == (uint8_t) -1) return MP3_FUNCTION_FAIL;
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_KT403A_PLAYER__ */
#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
  if (_type==DF_ROBOT_DFP_PLAYER_MINI) {
    _dfr_player_mini->EQ(eq);
    return MP3_FUNCTION_SUCCESS;
  }
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */
  return MP3_FUNCTION_UNSUPPORTED;
}
#endif /* USE_MP3_PLAYER */