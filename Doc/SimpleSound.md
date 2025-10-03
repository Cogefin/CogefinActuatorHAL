# Hardware Abstraction Layer for Simple Sound devices

スピーカーやブザーのように，デジタル端子のON/OFFで音を出すような
デバイスを制御するためのAPI．

## API



```
{
    id : xxx,
    type: xxx,
    time: xxx,
    paramSize: 0,
    command: on
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    paramSize: 0,
    command: off
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    command: play,
    paramSize: 1,
    param: [
        iteration : 3
        bass: [x1, x2, x3]
        duration: [x1, x2, x3]
        interval : [x1,x2,x3]
    ]
}
```

|コマンド名|シンボル|値|
|---|---|---|
|ON|SIMPLE_SOUND_COMMAND_ON|1|
|OFF|SIMPLE_SOUND_COMMAND_OFF|2|
|PLAY|SIMPLE_SOUND_COMMAND_PLAY|3|

上記JSON形式APIの``type``部分に入る値は``SIMPLE_SOUND_TYPE_NORMAL(601)``限定．

### クラスオブジェクト作成時の注意
接続するデバイスをONにするために必要な操作が「電圧をかける」，もしくは「電圧をアースレベルに落とす」の
いずれのタイプの回路構成になっているかで，クラスのオブジェクトを生成する際に引数に与える必要がある．
引数なしの場合は，電圧をかけた場合にONになるものを指定したことになる．
```
typedef enum {
  SIMPLE_SOUND_TYPE_PULL_UP = 1,
  SIMPLE_SOUND_TYPE_PULL_DOWN
} SimpleSoundType;

SimpleSound(uint8_t pin, SimpleSoundType type = SIMPLE_SOUND_TYPE_PULL_UP);
```


### 参考(ドレミ)
playの引数として，ドレミを与えるために，以下のような定数が定義済み．使い方は``SimpleSoundSelfTest.ino``を参照．
```
#define SIMPLE_SOUND_C 1911
#define SIMPLE_SOUND_D 1702
#define SIMPLE_SOUND_E 1516
#define SIMPLE_SOUND_F 1431
#define SIMPLE_SOUND_G 1275
#define SIMPLE_SOUND_A 1136
#define SIMPLE_SOUND_B 1012
```



## コンパイルテスト

|機種名|結果|
|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|
|[Arduino Mega 2560][Mega2560]|◯|
|[Arduino M0 pro][M0Pro]|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|
|[Ardino MKR Zero][MKRZero]|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|◯|


## 動作テスト
動作の確認には，[Groveスピーカー][GroveSpeaker]と[Groveブザー][GroveBuzzer]を利用したが，
デバイスの特性上，ON/OFFのみでは動作の確認ができないため，playのみを検証した．

|機種名|[Groveスピーカー][GroveSpeaker]|[Groveブザー][GroveBuzzer]|
|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|◯|
|[Arduino Mega 2560][Mega2560]|◯|◯|
|[Arduino M0 pro][M0Pro]|✕|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|✕|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|◯|
|[Ardino MKR Zero][MKRZero]|✕|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|||


<!-- Groveスピーカー -->
[GroveSpeaker]:https://wiki.seeedstudio.com/ja/Grove-Speaker/

<!-- Groveブザー -->
[GroveBuzzer]:https://wiki.seeedstudio.com/ja/Grove-Buzzer/

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
