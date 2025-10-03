
# Hardware Abstraction Layer for MP3 player.


## API

この種のデバイスに利用可能なAPIは以下の17種類(JSON形式)．``id``は制御対象デバイスに
付与されている番号．``type``は種類を表す整数値，``time``は制御コマンドを
発行/作成したUNIX時間．``command``欄は名前を記入しているが，実際は各コマンドに
対応する整数値(下記の表を参照)．


```
{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_STOP,
    paramSize: 0
}

{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_NEXT,
    paramSize: 0
}


{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_PREVIOUS,
    paramSize: 0
}


{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_VOLUME,
    paramSize: 1,
    param: [
        vol: x  // uint8_t
    ]
}


{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_VOL_DOWN,
    paramSize: 0
}


{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_VOL_UP,
    paramSize: 0
}


{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_STORAGE,
    paramSize: 1,
    param: [
        storage: x  // uint8_t MP3_PLAYER_STORAGE_SD 1 , MP3_PLAYER_STORAGE_SPI 2, MP3_PLAYER_STORAGE_UDISK 3
    ]
}


{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_PAUSE,
    paramSize: 0
}


{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_START,
    paramSize: 0
}


{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_PLAY_BY_INDEX,
    paramSize: 1,
    param: [
        index: x, // uint32_t
        mode: x  // uint8_t CYCLE - 1, SINGLE_CYCLE - 2 , DIR_CYCLE - 3 , RANDOM - 4 , SINGLE_SHOT - 5
    ]
}


{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_PLAY_BY_NAME,
    paramSize: 1,
    param: [
        name: x, // const char*
        mode: x  // uint8_t CYCLE - 1, SINGLE_CYCLE - 2 , DIR_CYCLE - 3 , RANDOM - 4 , SINGLE_SHOT - 5
    ]
}


{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_PLAY_DIR_BY_NUM,
    paramSize: 1,
    param: [
        num: x, // uint8_t
        file: x, // uint32_t
        mode: x  // uint8_t CYCLE - 1, SINGLE_CYCLE - 2 , DIR_CYCLE - 3 , RANDOM - 4 , SINGLE_SHOT - 5
    ]
}


{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_PLAY_DIR_BY_NAME,
    paramSize: 1,
    param: [
        name: x, // const char*
        file: x, // uint32_t
        mode: x  // uint8_t CYCLE - 1, SINGLE_CYCLE - 2 , DIR_CYCLE - 3 , RANDOM - 4 , SINGLE_SHOT - 5
    ]
}


{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_LOOP_DIR,
    paramSize: 1,
    param: [
        index: x, // int
    ]
}


{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_PLAY_MP3_DIR,
    paramSize: 1,
    param: [
        index: x, // int
    ]
}


{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_CUT_IN_PLAY,
    paramSize: 1,
    param: [
        storage: x,  // uint8_t MP3_PLAYER_STORAGE_SD 1 , MP3_PLAYER_STORAGE_SPI 2, MP3_PLAYER_STORAGE_UDISK 3
        index: x // uint32_t
    ]
}


{
    id : xxx,
    type: x,
    time: xxx,
    command: MP3_PLAYER_COMMAND_SET_EQ,
    paramSize: 1,
    param: [
        eq: x  // uint8_t
    ]
}


```

各コマンドの意味と値，各コマンドが利用可能なデバイスの関係は以下の通り．

|コマンド|シンボル|値|[Grove - MP3 v4.0][GroveMP3v4]|[DFPlayer - A Mini MP3 Player][DFRobotDFPlayerMini]|
|---|---|---|---|---|
|再生終了|MP3_PLAYER_COMMAND_STOP|1|◯|◯|
|次の曲を再生|MP3_PLAYER_COMMAND_NEXT|2|◯|◯|
|前の曲を再生|MP3_PLAYER_COMMAND_PREVIOUS|3|◯|◯|
|ボリューム設定|MP3_PLAYER_COMMAND_VOLUME|4|◯|◯|
|ボリューム下げ|MP3_PLAYER_COMMAND_VOL_DOWN|5|◯|◯|
|ボリューム上げ|MP3_PLAYER_COMMAND_VOL_UP|6|◯|◯|
|ストレージ選定|MP3_PLAYER_COMMAND_STORAGE|7|◯|✕|
|一時停止|MP3_PLAYER_COMMAND_PAUSE|8|◯|◯|
|再生開始|MP3_PLAYER_COMMAND_START|9|◯|◯|
|指定番号の曲を再生|MP3_PLAYER_COMMAND_PLAY_BY_INDEX|10|◯|◯|
|指定した名前の曲を再生|MP3_PLAYER_COMMAND_PLAY_BY_NAME|11|◯|✕|
|ディレクトリと曲を番号で指定して再生|MP3_PLAYER_COMMAND_PLAY_DIR_BY_NUM|12|◯|◯|
|ディレクトリを名前で，曲を番号で指定して再生|MP3_PLAYER_COMMAND_PLAY_DIR_BY_NAME|13|◯|✕|
|指定したディレクトリ内の曲を繰り返し再生|MP3_PLAYER_COMMAND_LOOP_DIR|14|✕|◯|
|MP3という名前のディレクトリ内の特定の番号の曲を再生|MP3_PLAYER_COMMAND_PLAY_MP3_DIR|15|✕|◯|
|割り込み再生|MP3_PLAYER_COMMAND_CUT_IN_PLAY|16|◯|✕|
|イコライザ設定|MP3_PLAYER_COMMAND_SET_EQ|17|✕|◯|



上記JSON形式APIの``type``部分に入る値は下の表のいずれか．

|種別|シンボル|値|
|---|---|---|
|[Grove - MP3 v4.0][GroveMP3v4]|MP3_PLAYER_TYPE_WT2605C|903|
|[DFPlayer - A Mini MP3 Player][DFRobotDFPlayerMini]|MP3_PLAYER_TYPE_DF_ROBOT_DFP|904|



## コンパイルテスト

MP3プレーヤーはシリアルでArduinoと接続する必要があるため，ソフトウェアシリアルを利用しなければならない
機種ではコンパイルに失敗する．

|機種名|[Grove - MP3 v4.0][GroveMP3v4]|[DFPlayer - A Mini MP3 Player][DFRobotDFPlayerMini]|
|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|✕|✕|
|[Arduino Mega 2560][Mega2560]|✕|✕|
|[Arduino M0 pro][M0Pro]|◯|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|◯|
|[Ardino MKR Zero][MKRZero]|◯|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|✕|◯|



## 動作テスト

|機種名|[Grove - MP3 v4.0][GroveMP3v4]|[DFPlayer - A Mini MP3 Player][DFRobotDFPlayerMini]|
|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|－|－|
|[Arduino Mega 2560][Mega2560]|－|－|
|[Arduino M0 pro][M0Pro]||◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|◯|
|[Arduino Nano 33 IoT][Nano33IoT]||◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]||◯|
|[Ardino MKR Zero][MKRZero]||◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|－||

- 本HALはソフトウェアシリアルとの整合性がないため，ESP32とMega2560ではコンパイルできないことから検証対象外


## 利用デバイス


<!-- MP3プレーヤ -->

|名称|コントローラ|電圧(V)|
|---|---|---|
|[Grove - MP3 v2.0][GroveMP3v2]|KT403A|5|
|[Grove - MP3 v3.0][GroveMP3v3]|WT2003S-20SS|3.3/5|
|[Grove - MP3 v4.0][GroveMP3v4]|WT2605CX|5|
|[DFPlayer - A Mini MP3 Player][DFRobotDFPlayerMini]|DFROBOT LISP3|3.3/5|

<!-- Grove - MP3 v2.0 -->
[GroveMP3v2]:https://wiki.seeedstudio.com/Grove-MP3_v2.0/
<!-- Grove - MP3 v3.0 -->
[GroveMP3v3]:https://wiki.seeedstudio.com/Grove-MP3-v3/
<!-- Grove - MP3 v4.0 -->
[GroveMP3v4]:https://wiki.seeedstudio.com/grove_mp3_v4/
<!-- DFPlayer - A Mini MP3 Player -->
[DFRobotDFPlayerMini]:https://www.dfrobot.com/product-1121.html

<!-- SoftwareSerial Library -->
[SoftwareSerial]:https://docs.arduino.cc/learn/built-in-libraries/software-serial/

<!-- ESP SoftwareSerial Library -->
[EspSoftwareSerial]:https://docs.arduino.cc/libraries/espsoftwareserial/





<!-- Arduino 本体 -->

|機種名|コア|MCU|動作電圧|
|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|Xtensa LX6|ESP32-S3|3.3V|
|[Arduino Mega 2560][Mega2560]|AVR|ATmega2560|5V|
|[Arduino M0 pro][M0Pro]|ARM Cortex-M0+|ATSAMD21G18|3.3V|
|[Arduino UNO R4 WiFi][UnoR4WiFi]|ARM Cortex-M4|RA4M1|5V|
|[Arduino UNO R4 Minima][UnoR4Minima]|ARM Cortex-M4|RA4M1|5V|
|[Arduino Nano 33 IoT][Nano33IoT]|ARM Cortex-M0+|SAMD21|3.3V|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|ARM Cortex-M7|STM32H747XI|3.3V|
|[Arduino MKR WiFi 1010][MKRWiFi1010]|ARM Cortex-M0+|SAMD21|3.3V|
|[Ardino MKR Zero][MKRZero]|ARM Cortex-M0+|SAMD21|3.3V|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|ARM Cortex-M0+|Raspberry Pi RP2040|3.3V|

<!-- Arduino Nano ESP32 -->
[NanoESP32]:https://docs.arduino.cc/hardware/nano-esp32/
<!--Arduino Mega 2560-->
[Mega2560]:https://docs.arduino.cc/hardware/mega-2560/
<!--Arduino M0 pro-->
[M0Pro]:https://docs.arduino.cc/retired/boards/arduino-m0-pro/
<!--Arduino UNO R4 WiFi-->
[UnoR4WiFi]:https://docs.arduino.cc/hardware/uno-r4-wifi/
<!--Arduino UNO R4 Minima-->
[UnoR4Minima]:https://docs.arduino.cc/hardware/uno-r4-minima/
<!--Arduino Nano 33 IoT-->
[Nano33IoT]:https://docs.arduino.cc/hardware/nano-33-iot/
<!--Arduino Giga R1 Wifi-->
[GigaR1WiFi]:https://docs.arduino.cc/hardware/giga-r1-wifi/
<!--Arduino MKR WiFi 1010-->
[MKRWiFi1010]:https://docs.arduino.cc/hardware/mkr-wifi-1010/
<!--Ardino MKR Zero-->
[MKRZero]:https://docs.arduino.cc/hardware/mkr-zero/
<!--Arduino Nano RP2040 Connect-->
[NanoRP2040Connect]:https://docs.arduino.cc/hardware/nano-rp2040-connect/


