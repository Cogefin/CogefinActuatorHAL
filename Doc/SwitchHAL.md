# Hardware Abstraction Layer for simple digital device.


## API

この種のデバイスに利用可能なAPIは以下の2種類(JSON形式)．``id``は制御対象デバイスに
付与されている番号．``type``は種類を表す整数値，``time``は制御コマンドを
発行/作成したUNIX時間．``command``欄は名前を記入しているが，実際は各コマンドに
対応する整数値(下記の表を参照)．

```
{
    id : xxx,
    type: xxx,
    time: xxx,
    paramSize: 0,
    command: SIMPLE_SWITCH_COMMAND_ON
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    paramSize: 0,
    command: SIMPLE_SWITCH_COMMAND_OFF
}
```


|コマンド名|シンボル|値|
|---|---|---|
|on|SIMPLE_SWITCH_COMMAND_ON|1|
|off|SIMPLE_SWITCH_COMMAND_OFF|2|


上記JSON形式APIの``type``部分に入る値は``SIMPLE_SWITCH_TYPE_NORMAL(401)``限定．


### クラスオブジェクト作成時の注意
接続するデバイスをONにするために必要な操作が「電圧をかける」，もしくは「電圧をアースレベルに落とす」の
いずれのタイプの回路構成になっているかで，クラスのオブジェクトを生成する際に引数に与える必要がある．
引数なしの場合は，電圧をかけた場合にONになるものを指定したことになる．
```
typedef enum {
  SWITCH_TYPE_PULL_UP = 1,
  SWITCH_TYPE_PULL_DOWN
} SwitchType;

Switch(uint8_t pin, SwitchType type = SWITCH_TYPE_PULL_UP);
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
単純なON/OFFデバイスとして，LEDを用いて動作を確認．


|機種名|結果|
|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|
|[Arduino Mega 2560][Mega2560]|◯|
|[Arduino M0 pro][M0Pro]|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|
|[Ardino MKR Zero][MKRZero]|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]||



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
