# Hardware Abstraction Layer for PMW devices

[Arduino標準サーボ制御用ライブラリ][ArduinoServoLib]を利用するサーボを
制御するためのAPI．

## API

PMWデバイスに利用可能なAPIは以下の2種類(JSON形式)．``id``は制御対象PMWデバイスに
付与されている番号．``type``はデバイスの種類を表す整数値，``time``は制御コマンドを
発行/作成したUNIX時間．``command``欄は名前を記入しているが，実際は各コマンドに
対応する整数値(下記の表を参照)．

```
{
    id : xxx,
    type: xxx,
    time: xxx,
    command: write,
    paramSize: 1,
    param: [
        angle: x //(angle:0～180)
    ]
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    command: writeMS,
    paramSize: 1,
    param: [
        msec: x // 動作させる時間(ミリ秒)
    ]
}
```

|コマンド名|シンボル|値|
|---|---|---|
|write|SERVO_COMMAND_WRITE|1|
|writeMS|SERVO_COMMAND_WRITE_MS|2|

上記JSON形式APIの``type``部分に入る値は``SERVO_TYPE_SIMPLE(501)``限定．


## コンパイルテスト

|機種名|結果|
|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|
|[Arduino Mega 2560][Mega2560]|◯|
|[Arduino M0 pro][M0Pro]|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|✕|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|△1|
|[Ardino MKR Zero][MKRZero]|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|◯|

- 1 : MCUアーキテクチャに対する非対応の警告が出るものの，コンパイル自体はできる．

## 動作テスト
動作テストには，下のようにSeeed Studio社のGrove Servoを利用．

|機種名|[Grove Servo][GroveServo]|
|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|
|[Arduino Mega 2560][Mega2560]|◯|
|[Arduino M0 pro][M0Pro]|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|✕|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯1|
|[Ardino MKR Zero][MKRZero]|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]||

- 1 : サーボライブラリはGiga WiFiは動作保証外

<!-- Grove Servo -->
[GroveServo]:https://wiki.seeedstudio.com/ja/Grove-Servo/

<!-- Arduino Servoライブラリ -->
[ArduinoServoLib]:https://docs.arduino.cc/libraries/servo/

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
