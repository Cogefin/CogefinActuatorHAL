# Hardware Abstraction Layer for graphic display.


## API

この種のデバイスに利用可能なAPIは以下の3種類(JSON形式)．``id``は制御対象デバイスに
付与されている番号．``type``は種類を表す整数値，``time``は制御コマンドを
発行/作成したUNIX時間．``command``欄は名前を記入しているが，実際は各コマンドに
対応する整数値(下記の表を参照)．


```
{
    id : xxx,
    type: x,
    time: xxx,
    command: GRAPHIC_DISPLAY_COMMAND_FILL,
    paramSize: 1,
    param: [
        color: x // uint16_t
    ]
}

{
    id : xxx,
    type: x,
    time: xxx,
    command: GRAPHIC_DISPLAY_COMMAND_STRING,
    paramSize: 1,
    param: [
        x: x,  // int16_t
        y: x,  // int16_t
        foreground: x, // int16_t
        background: x, // int16_t
        size: x, // int8_t
        wrap: x, // uint8_t 0,1
        text: x // char *
    ]
}

{
    id : xxx,
    type: x,
    time: xxx,
    command: GRAPHIC_DISPLAY_COMMAND_IMAGE,
    paramSize: 1,
    param: [
        x: x,  // int16_t
        y: x,  // int16_t
        filename: x // char *
    ]
}

```
各コマンドの意味と値の関係は以下の通り．

|コマンド|シンボル|値|
|---|---|---|
|塗りつぶし|GRAPHIC_DISPLAY_COMMAND_FILL|1|
|文字列の表示|GRAPHIC_DISPLAY_COMMAND_STRING|2|
|イメージファイルの表示|GRAPHIC_DISPLAY_COMMAND_IMAGE|3|


上記JSON形式APIの``type``部分に入る値は下の表のいずれか．

|種別|シンボル|値|
|---|---|---|
|[Arduino GigaDisplay GFX][Arduino_GigaDisplay_GFX]|GRAPHIC_DISPLAY_TYPE_GIGA_DISPLAY|1002|
|[Adafruit GFX Library][Adafruit GFX Library]|GRAPHIC_DISPLAY_TYPE_ADAFRUIT_GFX|1004|


### 色の値
色は16bitカラーで定義する必要があるが，代表的な色については下のように定義済みであるため，それを利用できる．
```
#define TFT_BLACK       0x0000      /*   0,   0,   0 */
#define TFT_NAVY        0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TFT_MAROON      0x7800      /* 128,   0,   0 */
#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGREY   0xD69A      /* 211, 211, 211 */
#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define TFT_BLUE        0x001F      /*   0,   0, 255 */
#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
#define TFT_RED         0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
#define TFT_ORANGE      0xFDA0      /* 255, 180,   0 */
#define TFT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
#define TFT_PINK        0xFE19      /* 255, 192, 203 */ //Lighter pink, was 0xFC9F
#define TFT_BROWN       0x9A60      /* 150,  75,   0 */
#define TFT_GOLD        0xFEA0      /* 255, 215,   0 */
#define TFT_SILVER      0xC618      /* 192, 192, 192 */
#define TFT_SKYBLUE     0x867D      /* 135, 206, 235 */
#define TFT_VIOLET      0x915C      /* 180,  46, 226 */
```

## コンパイルテスト

|機種名|[Arduino GigaDisplay GFX][Arduino_GigaDisplay_GFX]|[Adafruit GFX Library][Adafruit GFX Library]|
|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|-|◯|
|[Arduino Mega 2560][Mega2560]|-|✕1|
|[Arduino M0 pro][M0Pro]|-|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|-|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|-|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|◯|
|[Ardino MKR Zero][MKRZero]|-|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|-|✕2|

- 1 : メモリ(SRAM)領域不足
- 2 : JPEGなどのイメージを利用可能にするライブラリ(TJpg_Decoder)がファイルシステム(FS.h)を使うが，RP2040ではFS.hが存在しないため．

[Arduino GigaDisplay GFX][Arduino_GigaDisplay_GFX]は[Arduino Giga R1 Wifi][GigaR1WiFi]専用のデバイスであるため，
[Arduino Giga R1 Wifi][GigaR1WiFi]のみでテストを実施．

## 動作テスト
各ライブラリに対応する実デバイスは以下の表の通り．
|ライブラリ|デバイス|
|---|---|
|[Arduino GigaDisplay GFX][Arduino_GigaDisplay_GFX]|[GIGA Display Shield][GigaDisplayShield]|
|[Adafruit GFX Library][Adafruit GFX Library]|[ILI9341搭載2.8インチSPI制御タッチパネル付TFT液晶][MSP2807]|



|機種名|[GIGA Display Shield][GigaDisplayShield]|[ILI9341搭載2.8インチSPI制御タッチパネル付TFT液晶][MSP2807]|
|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|-|◯|
|[Arduino M0 pro][M0Pro]|-|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|-|-|
|[Arduino Nano 33 IoT][Nano33IoT]|-|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|✕1|
|[Ardino MKR Zero][MKRZero]|-|✕2|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|-||

|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|▲|一部の機能が動作しない|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|

- 1 : [ILI9341搭載2.8インチSPI制御タッチパネル付TFT液晶][MSP2807]付属のSDスロットへのアクセスでシステムが止まる．
- 2 : MKR Zeroだけでなく，MKRシリーズは[ILI9341搭載2.8インチSPI制御タッチパネル付TFT液晶][MSP2807]付属のSDスロットへのアクセスで失敗する．

## 利用デバイス

|名称|電圧(V)|
|---|---|
|[GIGA Display Shield][GigaDisplayShield]|3.3|
|[ILI9341搭載2.8インチSPI制御タッチパネル付TFT液晶][MSP2807]|3.3|

<!-- |モノクロ|[Grove OLED  v1.1][GroveOLEDv1.1]|3.3～5.5| -->

<!-- GIGA Display Shield -->
[GigaDisplayShield]:https://docs.arduino.cc/hardware/giga-display-shield/
<!-- ILI9341搭載2.8インチSPI制御タッチパネル付TFT液晶 MSP2807 -->
[MSP2807]:https://akizukidenshi.com/catalog/g/g116265/
<!-- Grove OLED  v1.1 -->
[GroveOLEDv1.1]:https://wiki.seeedstudio.com/ja/Grove-OLED_Display_0.96inch/

<!-- LCD Wiki of MSP2807 -->
[MSP2807_Wiki]:https://www.lcdwiki.com/2.8inch_SPI_Module_ILI9341_SKU:MSP2807

<!-- Arduino_GigaDisplay_GFX -->
[Arduino_GigaDisplay_GFX]:https://github.com/arduino-libraries/Arduino_GigaDisplay_GFX

<!-- Arduino_GigaDisplay_GFX -->
[Adafruit GFX Library]:https://github.com/adafruit/Adafruit-GFX-Library

<!-- Adafruit ILI9341 Arduino Library -->
[Adafruit ILI9341 Arduino Library]:https://github.com/adafruit/Adafruit_ILI9341

<!-- Bodmer/TFT_eSPI -->
[Bodmer_TFT_eSPI]:https://github.com/Bodmer/TFT_eSPI

<!-- ST touch GFX -->
[RGB565]:https://support.touchgfx.com/ja/docs/basic-concepts/color-formats



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
