# Hardware Abstraction Layer for Infra Red LED.


## API

この種のデバイスに利用可能なAPIは以下のとおり(JSON形式)．``id``は制御対象デバイスに
付与されている番号．``type``は種類を表す整数値，``time``は制御コマンドを
発行/作成したUNIX時間．``command``欄は名前を記入しているが，実際は各コマンドに
対応する整数値(下記の表を参照)．

```
{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_BANG_OLUFSEN,
    paramSize: 1,
    param: {
        header: x, // uint16_t
        data:x,    // uint8_t
        repeats:x,  // int_fast8_t
        bits:x     // int8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_BANG_OLUFSEN_LINK,
    paramSize: 1,
    param: {
        header: x, // uint32_t
        data:x,    // uint8_t
        repeats:x,  // int_fast8_t
        bits:x     // int8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_BOSE_WAVE,
    paramSize: 1,
    param: {
        command: x, // uint8_t
        repeats:x   // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_SHARP,
    paramSize: 1,
    param: {
        address: x, // uint8_t
        command: x, // uint8_t
        repeats:x   // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_DENON,
    paramSize: 1,
    param: {
        address: x, // uint8_t
        command: x, // uint8_t
        repeats:x,  // int_fast8_t
        flag:x      // 0 or 1 (bool)
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_FAST,
    paramSize: 1,
    param: {
        command: x, // uint8_t
        repeats:x   // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_JVC,
    paramSize: 1,
    param: {
        address: x, // uint8_t
        command: x, // uint8_t
        repeats:x   // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_KASEIKYO,
    paramSize: 1,
    param: {
        address: x, // uint16_t
        command: x, // uint8_t
        repeats:x,  // int_fast8_t
        vendor:x    //uint16_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_KASEIKYO_JVC,
    paramSize: 1,
    param: {
        address: x, // uint16_t
        command: x, // uint8_t
        repeats:x,  // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_KASEIKYO_DENON,
    paramSize: 1,
    param: {
        address: x, // uint16_t
        command: x, // uint8_t
        repeats:x,  // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_KASEIKYO_SHARP,
    paramSize: 1,
    param: {
        address: x, // uint16_t
        command: x, // uint8_t
        repeats:x,  // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_KASEIKYO_MITSUBISHI,
    paramSize: 1,
    param: {
        address: x, // uint16_t
        command: x, // uint8_t
        repeats:x,  // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_LG,
    paramSize: 1,
    param: {
        address: x, // uint8_t
        command: x, // uint16_t
        repeats:x   // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_LG_2,
    paramSize: 1,
    param: {
        address: x, // uint8_t
        command: x, // uint16_t
        repeats:x   // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_LEGO,
    paramSize: 1,
    param: {
        channel: x, // uint8_t
        command: x, // uint8_t
        mode:x,     // uint8_t
        flag:x      // 0 or 1 (bool)
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_LEGO_2,
    paramSize: 1,
    param: {
        data:x,     // uint16_t
        channel: x, // uint8_t
        flag:x      // 0 or 1 (bool)
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_MAGIC_QUEST,
    paramSize: 1,
    param: {
        wid:x,       // uint32_t
        magnitude: x // uint16_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_NEC,
    paramSize: 1,
    param: {
        address: x, // uint16_t
        command: x, // uint16_t
        repeats:x   // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_NEC_2,
    paramSize: 1,
    param: {
        address: x, // uint16_t
        command: x, // uint16_t
        repeats:x   // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_ONKYO,
    paramSize: 1,
    param: {
        address: x, // uint16_t
        command: x, // uint16_t
        repeats:x   // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_APPLE,
    paramSize: 1,
    param: {
        did: x,     // uint8_t
        command: x, // uint16_t
        repeats:x   // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_RC5,
    paramSize: 1,
    param: {
        address: x, // uint8_t
        command: x, // uint8_t
        repeats:x,  // int_fast8_t
        flag:x      // 0 or 1 (bool)
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_RC6,
    paramSize: 1,
    param: {
        data: x,    // uint32_t
        bits:x      // uint8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_RC6_2,
    paramSize: 1,
    param: {
        data: x,    // uint64_t
        bits:x      // uint8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_RC6_3,
    paramSize: 1,
    param: {
        address: x, // uint8_t
        command: x, // uint8_t
        repeats:x,  // int_fast8_t
        flag:x      // 0 or 1 (bool)
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_RC6_A,
    paramSize: 1,
    param: {
        address: x, // uint8_t
        command: x, // uint8_t
        repeats:x,  // int_fast8_t
        customer:x, // uint16_t
        flag:x      // 0 or 1 (bool)
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_SAMSUNG,
    paramSize: 1,
    param: {
        address: x, // uint16_t
        command: x, // uint8_t
        repeats:x   // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_SAMSUNG_LG,
    paramSize: 1,
    param: {
        address: x, // uint16_t
        command: x, // uint8_t
        repeats:x   // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_SAMSUNG_48,
    paramSize: 1,
    param: {
        address: x, // uint16_t
        command: x, // uint32_t
        repeats:x   // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_SONY,
    paramSize: 1,
    param: {
        address: x, // uint16_t
        command: x, // uint8_t
        repeats:x,  // int_fast8_t
        bits:x      // uint8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_DISH,
    paramSize: 1,
    param: {
        data: x // uint16_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_WHYNTER,
    paramSize: 1,
    param: {
        data: x, // uint32_t
        repeats:x   // int_fast8_t
    }
}

{
    id : xxx,
    type: IRDA_TYPE_SIMPLE,
    time: xxx,
    command: IRDA_COMMAND_PANASONIC,
    paramSize: 1,
    param: {
        address: x, // uint16_t
        command: x, // uint32_t
        repeats:x   // int_fast8_t
    }
}

```


|シンボル|値|
|---|---|
|IRDA_COMMAND_BANG_OLUFSEN|10|
|IRDA_COMMAND_BANG_OLUFSEN_LINK|11|
|IRDA_COMMAND_BOSE_WAVE|20|
|IRDA_COMMAND_SHARP|30|
|IRDA_COMMAND_DENON|31|
|IRDA_COMMAND_FAST|40|
|IRDA_COMMAND_JVC|50|
|IRDA_COMMAND_KASEIKYO|60|
|IRDA_COMMAND_KASEIKYO_JVC|61|
|IRDA_COMMAND_KASEIKYO_DENON|62|
|IRDA_COMMAND_KASEIKYO_SHARP|63|
|IRDA_COMMAND_KASEIKYO_MITSUBISHI|64|
|IRDA_COMMAND_LG|70|
|IRDA_COMMAND_LG_2|71|
|IRDA_COMMAND_LEGO|80|
|IRDA_COMMAND_LEGO_2|81|
|IRDA_COMMAND_MAGIC_QUEST|90|
|IRDA_COMMAND_NEC|100|
|IRDA_COMMAND_NEC_2|101|
|IRDA_COMMAND_ONKYO|102|
|IRDA_COMMAND_APPLE|103|
|IRDA_COMMAND_RC5|110|
|IRDA_COMMAND_RC6|111|
|IRDA_COMMAND_RC6_2|112|
|IRDA_COMMAND_RC6_3|113|
|IRDA_COMMAND_RC6_A|114|
|IRDA_COMMAND_SAMSUNG|120|
|IRDA_COMMAND_SAMSUNG_LG|121|
|IRDA_COMMAND_SAMSUNG_48|122|
|IRDA_COMMAND_SONY|130|
|IRDA_COMMAND_DISH|140|
|IRDA_COMMAND_WHYNTER|141|
|IRDA_COMMAND_PANASONIC|160|



上記JSON形式APIの``type``部分に入る値は``IRDA_TYPE_SIMPLE(801)``限定．


## コンパイルテスト

|機種名|結果|
|---|---|
|[Arduino Nano ESP32][NanoESP32]|◯|
|[Arduino Mega 2560][Mega2560]|◯|
|[Arduino M0 pro][M0Pro]|◯|
|[Arduino UNO R4 Minima][UnoR4Minima]|◯|
|[Arduino Nano 33 IoT][Nano33IoT]|◯|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|△1|
|[Ardino MKR Zero][MKRZero]|◯|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|◯|

- 1 : MCUのアーキテクチャに関する警告は出るが，一応コンパイルはできる．

## 動作テスト


動作確認は，Arduinoと[Grove - Infrared Receiver][GroveInfraredReceiver]を用いて認識できるか否かで判定した．

以下の表の「△」印は完全に動作するわけではなく，一部のプロトコル(下記参照)はテスト用受信プログラムでは
認識できないなどの問題点を持つ．

|機種名|結果|LEDピン番号|
|---|---|---|
|[Arduino Nano ESP32][NanoESP32]|△1|D4|
|[Arduino Mega 2560][Mega2560]|△1|D3|
|[Arduino M0 pro][M0Pro]|✕3||
|[Arduino UNO R4 Minima][UnoR4Minima]|△1|D3|
|[Arduino Nano 33 IoT][Nano33IoT]|△1|D3|
|[Arduino Giga R1 Wifi][GigaR1WiFi]|✕2||
|[Ardino MKR Zero][MKRZero]|△1|D3|
|[Arduino Nano RP2040 Connect][NanoRP2040Connect]|||

- 2 : 赤外線リモコンのライブラリ(IRremote)がGigaはサポート範囲外の上，スケッチ動作開始しても，受信側では何も受信できない．
- 3 : スケッチ動作開始時から，シリアルが動作しなくなる．

### 注1
以下のプロトコルは受信側Arduinoでは認識できない/認識に失敗しやすい
- Bang Olufsen : 全く認識されない
- JVC : 全く認識されない
- LG2 : PULSE_DISTANCEと認識される
- Lego PF : プロトコル番号は認識されるが中身(各種パラメータ)が独自のエンコードがされており，確認が困難なため，中身の確認はしていない
- シャープ : bit単位の認識のミスでエラーになりやすい
- Denon : 認識に失敗する確率が高い


<!-- IRデバイス -->

|名称|動作電圧(V)|
|---|---|
|[Grove - 赤外線エミッター][GroveInfraredEmitter]|3.3/5V|
|[Grove - Infrared Receiver][GroveInfraredReceiver]|3.3/5V|


[GroveInfraredEmitter]:https://wiki.seeedstudio.com/ja/Grove-Infrared_Emitter/
[GroveInfraredReceiver]:https://wiki.seeedstudio.com/Grove-Infrared_Receiver/

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


<!--

Protocol - Apple : ***test success***
Protocol - Denon : ***test success***
Protocol - JVC : ***test skip***
Protocol - LG : ***test success***
Protocol - LG2 : ***test skip***
Protocol - NEC : ***test success***
Protocol - NEC2 : ***test success***
Protocol - Onkyo : ***test skip***
Protocol - Panasonic : ***test success***
Protocol - Kaseikyo : ***test success***
Protocol - Kaseikyo Denon : ***test success***
Protocol - Kaseikyo Sharp : ***test success***
Protocol - Kaseikyo JVC : ***test success***
Protocol - Kaseikyo Mitsubishi : ***test success***
Protocol - RC5 : ***test success***
Protocol - RC6 : ***test success***
Protocol - RC6A : ***test success***
Protocol - Samsung : ***test success***
Protocol - Samsung/LG : ***test success***
Protocol - Samsung48 : ***test success***
Protocol - Sharp : ***test success***
Protocol - Sony : ***test success***
Protocol - Bang Olufsen : ***test skip***
Protocol - Bose Wave : ***test success***
Protocol - Lego PF : ***test skip***
Protocol - Magi Quest : ***test success***
Protocol - Whynter : ***test success***
Protocol - ^ : ***test success***

Total result:
Success : 23
Skip    : 5
Error   : 0


device and device driver test of IRDA.
Send IR signals at pin 3
IRDA device : device No. 0
Please press Enter key to start test : 
Send Whynter
Send BoseWave
Send Magi Quest
Send Fast
Send PowerFunctions
Send LG2 with 8 bit address
Send Sharp with 8 bit address
Send BangOlufsen with 16 bit address
Send standard NEC with 8 bit address
Send standard Samsung with 8 bit address
Send Samsung48 with 8 bit address
Send Samsung/LG with 8 bit address
Send Sony with 8 bit address
Send panasonic with 8 bit address
Send Denon with 8 bit address
Send LG with 8 bit address
Send JVC with 8 bit address
Send RC5 with 8 bit address
Send RC6 with 8 bit address
Send RC6A
Send Kaseikyo
Send Kaseikyo JVC with 16 bit address
Send Kaseikyo Denon with 16 bit address
Send Kaseikyo Sharp with 16 bit address
Send Kaseikyo Mitsubishi with 16 bit address
Send Onkyo with 16 bit address
Send NEC rev.2 protocol with 16 bit address
Send Apple with 8 bit address


JVC : 全く認識されない
LG2 : PULSE_DISTANCEと認識される
Bang Olufsen : 全く認識されない
Onkyo : NECもしくはNECv2と誤認される
Lego PF : プロトコル番号は認識されるが中身(各種パラメータ)が独自のエンコードがされており，確認が困難なため，中身の確認はしていない

Protocol - JVC : ***test skip***
Protocol - LG2 : ***test skip***
Protocol - Onkyo : ***test skip***
Protocol - Bang Olufsen : ***test skip***


-->