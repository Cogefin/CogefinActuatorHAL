# Hardware Abstraction Layer for N-segment LED.


## API


```
{
    id : xxx,
    type: xxx,
    time: xxx,
    paramSize: 0,
    command: NSEG_LED_COMMAND_CLEAR
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    command: NSEG_LED_COMMAND_SET_BRIGHTNESS,
    paramSize: 1,
    param: [
        brightness: x
    ]
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    command: NSEG_LED_COMMAND_SET_COLON,
    paramSize: 1,
    param: [
        flag: x
    ]
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    command: NSEG_LED_COMMAND_SET,
    paramSize: 1,
    param: [
        period : x (2進数),
        text : "abc"
    ]
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    command: NSEG_LED_COMMAND_SETC,
    paramSize: 1,
    param: [
        text : "abc"
    ]
}
```


各コマンドの意味と値の関係は以下の通り．


|コマンド|シンボル|値|
|---|---|---|
|消す|NSEG_LED_COMMAND_CLEAR|1|
|明るさ設定|NSEG_LED_COMMAND_SET_BRIGHTNESS|2|
|コロンの点灯を設定*1|NSEG_LED_COMMAND_SET_COLON|3|
|表示する文字とピリオドの点灯状態を設定*2|NSEG_LED_COMMAND_SET|4|
|表示する文字を指定*1|NSEG_LED_COMMAND_SETC|5|

- *1 : 時計型のLED([Grove - 4-Digit Display][Grove4DigitLED])のみに対応
- *2 : 時計型のLED([Grove - 4-Digit Display][Grove4DigitLED])以外に対応

上記JSON形式APIの``type``部分に入る値は下の表のいずれか．

|種別|シンボル|値|
|---|---|---|
|[OSL12306-16-IRA(秋月電子)][OSL12306-16-IRA]|NSEG_LED_TYPE_OSL12306_16|301|
|[OSL20541-IR(秋月電子)][OSL20541IR]|NSEG_LED_TYPE_OSL20541|302|
|[OSL30561-IRA(秋月電子)][OSL30561IRA]|NSEG_LED_TYPE_OSL30561|303|
|[Grove - 4-Digit Display][Grove4DigitLED]|NSEG_LED_TYPE_GROVE_TM1637|304|
|[3-Wire LED Module DFR0090][DFR0090]|NSEG_LED_TYPE_DFR0090|305|



## コンパイルテスト


|機種名|[OSL20541-IR(秋月電子)][OSL20541IR]|[OSL30561-IRA(秋月電子)][OSL30561IRA]|[3-Wire LED Module DFR0090][DFR0090]|[OSL12306-16-IRA(秋月電子)][OSL12306-16-IRA]|[Grove - 4-Digit Display][Grove4DigitLED]|
|---|---|---|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|◯|◯|◯|◯|
|[Arduino Mega 2560][Mega2560]|◯|◯|◯|◯|◯|
|[Arduino M0 pro][M0Pro]|◯|◯|◯|◯|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|◯|◯|◯|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|◯|◯|◯|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|◯|◯|◯|◯|
|[Ardino MKR Zero][MKRZero]|◯|◯|◯|◯|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|◯|◯|◯|◯|◯|


## 動作テスト

|機種名|MCUコア|[3-Wire LED Module DFR0090][DFR0090]|[Grove - 4-Digit Display][Grove4DigitLED]|
|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|Xtensa LX6|✕2|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|ARM Cortex-M4|◯|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|ARM Cortex-M7|◯|◯|
|[Arduino M0 pro][M0Pro]|ARM Cortex-M0+|◯|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|ARM Cortex-M0+|▲5,6|◯|
|[Ardino MKR Zero][MKRZero]|ARM Cortex-M0+|▲5|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|ARM Cortex-M0+|||

|機種名|MCUコア|[OSL20541-IR(秋月電子)][OSL20541IR]|[OSL30561-IRA(秋月電子)][OSL30561IRA]|[OSL12306-16-IRA(秋月電子)][OSL12306-16-IRA]|
|---|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|Xtensa LX6|✕1|✕1||✕1|
|[Arduino UNO R4 Minima][UnoR4Minima]|ARM Cortex-M4|✕1|✕1|✕1|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|ARM Cortex-M7|◯|◯|▲4|
|[Arduino M0 pro][M0Pro]|ARM Cortex-M0+|✕1|✕1|✕1|
|[Arduino Nano 33 IoT][Nano33IoT]|ARM Cortex-M0+|✕1|✕1|✕1|
|[Ardino MKR Zero][MKRZero]|ARM Cortex-M0+|✕1|✕1|✕1|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|ARM Cortex-M0+||||

|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|▲|一部の機能が動作しない|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|

- 1 : 端子数が不足して接続できない/困難なため，未確認
- 2 : [3-Wire LED Module DFR0090][DFR0090]を接続した状態で，ArduinoをUSB接続してもPCではArduinoのUSB接続を認識できない．(電源容量の問題の可能性あり)
- 3 : 動作開始してしばらくすると，Arduino本体ごと，USBの認識ができなくなり，Arduinoの動作が止まる．(電源容量の問題の可能性あり)
- 4 : 動作はするが，電圧の関係で暗くて読み取ることがほぼ無理
- 5 : ACアダプタ等で給電しないと動作しない．また，USBによるプログラム書き込み時は，[3-Wire LED Module DFR0090][DFR0090]を外しておいた方が良い．
- 6 : 動作はするが，すごく暗い．

## デバイス


<!-- NセグメントLED -->

|セグメント数|桁数|種別番号|名称/型番|コントローラ|電圧(V)|
|---|---|---|---|---|---|
|16|1|2|[OSL12306-16-IRA(秋月電子)][OSL12306-16-IRA]|なし|3.6～5.0(逆電圧:10)|
|14|2|2|[OSL20541-IR(秋月電子)][OSL20541IR]|なし|2.1(逆電圧:5)|
|7|3|2|[OSL30561-IRA(秋月電子)][OSL30561IRA]|なし|2.1(逆電圧:5)|
|7|4|1|[Grove - 4-Digit Display][Grove4DigitLED]|TM1637|3.3～5.5|
|7|8|2|[3-Wire LED Module DFR0090][DFR0090]|74HC595||

|種別番号|コンマ/コロン/ピリオド等|
|---|---|
|1|時計タイプ(真ん中にセミコロン)|
|2|各桁にピリオド|

<!-- 16セグLED -->
[OSL12306-16-IRA]:https://akizukidenshi.com/catalog/g/g114656/
<!-- 2桁 14セグLED + 2*コンマ -->
[OSL20541IR]:https://akizukidenshi.com/catalog/g/g116389/
<!-- 3桁 7セグLED + 3*コンマ -->
[OSL30561IRA]:https://akizukidenshi.com/catalog/g/g117364/
<!-- 4桁 7セグLED + 1*コロン -->
[Grove4DigitLED]:https://wiki.seeedstudio.com/Grove-4-Digit_Display/
<!-- S3-Wire LED Module DFR0090 : SPI(3線式) LED Module 8 Digital (8桁赤色7セグLEDモジュール) -->
[DFR0090]:https://akizukidenshi.com/catalog/g/g106681/



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
