# Hardware Abstraction Layer for character display.


## API一覧


この種のデバイスに利用可能なAPIは以下の3種類(JSON形式)．``id``は制御対象デバイスに
付与されている番号．``type``は種類を表す整数値，``time``は制御コマンドを
発行/作成したUNIX時間．``command``欄は名前を記入しているが，実際は各コマンドに
対応する整数値(下記の表を参照)．


```
{
    id : xxx,
    type: xxx,
    time: xxx,
    command: CHARACTER_DISPLAY_COMMAND_CLEAR,
    paramSize: 0
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    command: CHARACTER_DISPLAY_COMMAND_HOME,
    paramSize: 0
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    command: CHARACTER_DISPLAY_COMMAND_SET_MODE,
    paramSize: 1,
    param: [
        mode: x
    ]
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    command: CHARACTER_DISPLAY_COMMAND_PRINT,
    paramSize: 1,
    param: [
        text: xxxx
    ]
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    command: CHARACTER_DISPLAY_COMMAND_SET_CURSUR,
    paramSize: 1,
    param: [
        x: x,
        y: x
    ]
}

{
    id : xxx,
    type: xxx,
    time: xxx,
    command: CHARACTER_DISPLAY_COMMAND_SET_BACKLIGHT_RGB,
    paramSize: 1,
    param: [
        r: x,
        g: x,
        b: x
    ]
}


{
    id : xxx,
    type: xxx,
    time: xxx,
    command: CHARACTER_DISPLAY_COMMAND_SET_SIZE,
    paramSize: 1,
    param: [
        col: x,
        row: x,
        font: x
    ]
}
```


各コマンドの意味と値の関係は以下の通り．

|コマンド|シンボル|値|
|---|---|---|
|画面クリア|CHARACTER_DISPLAY_COMMAND_CLEAR|1|
|カーソルをホームポジションに設定|CHARACTER_DISPLAY_COMMAND_HOME|2|
|動作モード設定|CHARACTER_DISPLAY_COMMAND_SET_MODE|3|
|カーソルの位置設定|CHARACTER_DISPLAY_COMMAND_SET_CURSUR|4|
|画面サイズ設定|CHARACTER_DISPLAY_COMMAND_SET_SIZE|5|
|文字列印字|CHARACTER_DISPLAY_COMMAND_PRINT|6|
|バックライト色設定*1|CHARACTER_DISPLAY_COMMAND_SET_BACKLIGHT_RGB|7|

- *1 : [Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]のみ利用可能

上記JSON形式APIの``type``部分に入る値は下の表のいずれか．

|種別|シンボル|値|
|---|---|---|
|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT|101|
|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|CHARACTER_DISPLAY_TYPE_ACM1602NI|102|
|[LiquidCrystal][LiquidCrystal]を用いるLCD*2|CHARACTER_DISPLAY_TYPE_LIQUID_CRYSTAL|103|

- *2 : [LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]や[LCDキャラクターディスプレイモジュール 20×4行 バックライト付][SC2004CSLB]


### 動作モード


|モード|シンボル|値|
|---|---|---|
|表示を消す|NO_DISPLAY|1|
|表示を点灯|ON_DISPLAY|2|
|カーソルの点滅を止める|NO_BLINK|3|
|カーソルを点滅させる|BLINK|4|
|カーソルを消す|NO_CURSOR|5|
|カーソルを点ける|CURSOR|6|
|左にスクロール|SCROLL_LEFT|7|
|右にスクロール|SCROLL_RIGHT|8|
|印字を左から右に行う|LEFT_TO_RIGHT|9|
|印字を右から左に行う|RIGHT_TO_LEFT|10|
|オートスクロールを有効にする|AUTO_SCROLL|11|
|オートスクロールを無効にする|NO_AUTO_SCROLL|12|
|バックライトを点灯|BLINK_BACKLIGHT|13|
|バックライトを消灯|NO_BLINK_BACKLIGHT|14|


## コンパイルテスト
|機種名|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|[LCDキャラクターディスプレイモジュール 20×4行 バックライト付][SC2004CSLB]|
|---|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|◯|◯|◯|
|[Arduino Mega 2560][Mega2560]|◯|◯|◯|◯|
|[Arduino M0 pro][M0Pro]|◯|◯|◯|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|◯|◯|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|◯|◯|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|◯|◯|◯|◯|
|[Ardino MKR Zero][MKRZero]|◯|◯|◯|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|◯|◯|◯|◯|

## 動作テスト

|機種名|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|[LCDキャラクターディスプレイモジュール 20×4行 バックライト付][SC2004CSLB]|
|---|---|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|－|－|◯|－|
|[Arduino M0 pro][M0Pro]|－|－|✕|－|
|[Arduino UNO R4 Minima][UnoR4Minima]|✕|◯|－|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|－|－|✕|－|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|－|－|✕|－|
|[Ardino MKR Zero][MKRZero]|－|－|✕|－|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|||||

|内容|意味|
|---|---|
|◯|動作する|
|△|動作電圧の変換等を行えば動作する|
|▲|一部の機能が動作しない|
|✕|動作しない|
|-|原理的に互換性がない|
|未|未検証|

## 利用したデバイス


|名称|動作電圧(V)|
|---|---|
|[Grove - LCD RGB Backlight][Grove_LCD_RGB_Backlight]|5|
|[LCDキャラクターディスプレイモジュール(16×2行バックライト付)][SC1602BSLB]|5|
|[I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付][ACM1602NI]|3.3|
|[LCDキャラクターディスプレイモジュール 20×4行 バックライト付][SC2004CSLB]|5|



<!-- Grove - LCD RGB Backlight -->
[Grove_LCD_RGB_Backlight]:https://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/
<!-- LCDキャラクターディスプレイモジュール(16×2行バックライト付) -->
[SC1602BSLB]:https://akizukidenshi.com/catalog/g/g100038/
<!-- I2C接続キャラクターLCDモジュール 16×2行 白色バックライト付 -->
[ACM1602NI]:https://akizukidenshi.com/catalog/g/g105693/

<!-- LCDキャラクターディスプレイモジュール 20×4行 バックライト付 -->
[SC2004CSLB]:https://akizukidenshi.com/catalog/g/g100036/

<!-- LiquidCrystal -->
[LiquidCrystal]:https://docs.arduino.cc/libraries/liquidcrystal/

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



