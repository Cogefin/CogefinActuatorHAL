# Hardware Abstraction Layer for LED.




```
{
    id : xxx,
    type: xxx,
    time: xxx,
    command: LED_COMMAND_SET_BRIGHTNESS,
    paramSize: 1,
    param: {
        brightness: x
    }
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    command: LED_COMMAND_SET_BRIGHTNESS_N,
    paramSize: 2,
    param: [
        [
            num: i
            brightness: x1
        ],
        [
            num: j
            brightness: x2
        ]
    ]
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    command: LED_COMMAND_SET_RGB,
    paramSize: 1,
    param: [
        red: r,
        green: g,
        blue: b
    ]
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    command: LED_COMMAND_SET_RGB_N,
    paramSize: 2,
    param: [
        [
            num: i,
            red: r1,
            green: g1,
            blue: b1
        ],
        [
            num: j,
            red: r2,
            green: g2,
            blue: b2
        ]
    ]
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    command: LED_COMMAND_CLEAR
    paramSize: 0
}
```

各コマンドの意味と値の関係は以下の通り．


|コマンド|シンボル|値|対応LED|
|---|---|---|---|
|消す|LED_COMMAND_CLEAR|1|すべて|
|明るさ設定|LED_COMMAND_SET_BRIGHTNESS|2|種別のシンボルがLED_TYPE_MONO_LEDのもののみ|
|N番目のLEDの明るさを設定*1|LED_COMMAND_SET_BRIGHTNESS_N|3|種別のシンボルがLED_TYPE_MONO_CHAIN_LEDのもののみ|
|表示する文字とピリオドの点灯状態を設定*2|LED_COMMAND_SET_RGB|4|種別のシンボルがLED_TYPE_COLOR_LEDのもののみ|
|表示する文字を指定*1|LED_COMMAND_SET_RGB_N|5|種別のシンボルがLED_TYPE_COLOR_CHAIN_LEDのもののみ|

上記JSON形式APIの``type``部分に入る値は下の表のいずれか．

|名称|シンボル|値|
|---|---|---|
|[Grove LED 赤 Arduino用][GroveRedLED]|LED_TYPE_MONO_LED|1|
|[Grove - Circular LED][GroveCircularLED]|LED_TYPE_MONO_CHAIN_LED|2|
|[Grove - LED Bar][GroveLEDBar]|LED_TYPE_MONO_CHAIN_LED|2|
|[RGBフルカラーLED 5mm OSTA5131A カソードコモン][OSTA5131A]|LED_TYPE_COLOR_LED|3|
|[チェーン接続可能 Grove RGB LED][GroveChainableRGB_Led]|LED_TYPE_COLOR_CHAIN_LED|4|
|[Grove RGB LED スティック][Grove_RGB_LEDスティック]|LED_TYPE_COLOR_CHAIN_LED|4|


##　コンパイルテスト

### モノクロLED

|機種名|[Grove LED 赤 Arduino用][GroveRedLED]|
|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|
|[Arduino Mega 2560][Mega2560]|◯|
|[Arduino M0 pro][M0Pro]|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|
|[Ardino MKR Zero][MKRZero]|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|◯|


### アノード/カソードコモンLED(フルカラー)


|機種名|[RGBフルカラーLED 5mm OSTA5131A カソードコモン][OSTA5131A]|
|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|
|[Arduino Mega 2560][Mega2560]|◯|
|[Arduino M0 pro][M0Pro]|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|
|[Ardino MKR Zero][MKRZero]|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|◯|



### ``MY9221``を搭載したモノクロLED ([Grove - Circular LED][GroveCircularLED]や[Grove - LED Bar][GroveLEDBar])


|機種名|[Grove - Circular LED][GroveCircularLED]|[Grove - LED Bar][GroveLEDBar]|
|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|◯|
|[Arduino Mega 2560][Mega2560]|◯|◯|
|[Arduino M0 pro][M0Pro]|◯|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|◯|
|[Ardino MKR Zero][MKRZero]|◯|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|◯|◯|



### [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)や[ChainableLED](https://github.com/pjpmarques/ChainableLED)を用いるLED



|機種名|[チェーン接続可能 Grove RGB LED][GroveChainableRGB_Led]|[Grove RGB LED スティック][Grove_RGB_LEDスティック]|
|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|◯|
|[Arduino Mega 2560][Mega2560]|◯|◯|
|[Arduino M0 pro][M0Pro]|◯|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|◯|
|[Ardino MKR Zero][MKRZero]|◯|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|◯|✕1|

- 1 : Adafruit Neo PixelがRP2040ではコンパイルできない


##　動作テスト

### モノクロLED

|機種名|[Grove LED 赤 Arduino用][GroveRedLED]|
|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|
|[Arduino Mega 2560][Mega2560]|◯|
|[Arduino M0 pro][M0Pro]|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|
|[Ardino MKR Zero][MKRZero]|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]||


|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|▲|一部の機能が動作しない|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|



### アノード/カソードコモンLED(フルカラー)


|機種名|[RGBフルカラーLED 5mm OSTA5131A カソードコモン][OSTA5131A]|
|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|
|[Arduino Mega 2560][Mega2560]|◯|
|[Arduino M0 pro][M0Pro]|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|
|[Ardino MKR Zero][MKRZero]|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]||


|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|▲|一部の機能が動作しない|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|



### ``MY9221``を搭載したモノクロLED ([Grove - Circular LED][GroveCircularLED]や[Grove - LED Bar][GroveLEDBar])


|機種名|[Grove - Circular LED][GroveCircularLED]|[Grove - LED Bar][GroveLEDBar]|
|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|◯|
|[Arduino Mega 2560][Mega2560]|▲1|◯|
|[Arduino M0 pro][M0Pro]|◯|✕|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|◯|
|[Ardino MKR Zero][MKRZero]|✕|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|||

- 1 : Mega 2560との組合せでcircular LEDの動作が不調(半分点灯せず)


|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|▲|一部の機能が動作しない|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|



### [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)や[ChainableLED](https://github.com/pjpmarques/ChainableLED)を用いるLED



|機種名|[チェーン接続可能 Grove RGB LED][GroveChainableRGB_Led]|[Grove RGB LED スティック][Grove_RGB_LEDスティック]|
|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|◯|
|[Arduino Mega 2560][Mega2560]|◯|◯|
|[Arduino M0 pro][M0Pro]|◯|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|◯|
|[Ardino MKR Zero][MKRZero]|◯|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|||


|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|▲|一部の機能が動作しない|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|



<!-- LED -->

|種類|名称|コントローラ|動作電圧(V)|
|---|---|---|---|
|モノクロLED|[Grove LED 赤 Arduino用][GroveRedLED]|なし|5|
||[Grove - Circular LED][GroveCircularLED]|MY9221|5|
||[Grove - LED Bar][GroveLEDBar]|MY9221|3.3/5|
|カラーLED|[RGBフルカラーLED 5mm OSTA5131A カソードコモン][OSTA5131A]|なし|5?|
||[チェーン接続可能 Grove RGB LED][GroveChainableRGB_Led]|P9813|5|
||[Grove RGB LED スティック][Grove_RGB_LEDスティック]|WS2813(NeoPixel)|3.3/5|

<!-- Grove LED 赤 Arduino用 -->
[GroveRedLED]: https://wiki.seeedstudio.com/ja/Grove-Red_LED/
<!-- Grove RGB LED スティック -->
[Grove_RGB_LEDスティック]: https://wiki.seeedstudio.com/ja/Grove-RGB_LED_Stick-10-WS2813_Mini/
<!-- チェーン接続可能 Grove RGB LED -->
[GroveChainableRGB_Led]: https://wiki.seeedstudio.com/Grove-Chainable_RGB_LED/
<!-- Grove - LED Bar -->
[GroveLEDBar]: https://wiki.seeedstudio.com/Grove-LED_Bar/
<!-- Grove - Circular LED -->
[GroveCircularLED]: https://wiki.seeedstudio.com/Grove-Circular_LED/
<!-- マイコン内蔵RGBLED 5mm PL9823-F5 -->
[PL9823F5]: https://akizukidenshi.com/catalog/g/g108411/
<!-- RGBフルカラーLED 5mm OSTA5131A カソードコモン -->
[OSTA5131A]: https://akizukidenshi.com/catalog/g/g102476/




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

