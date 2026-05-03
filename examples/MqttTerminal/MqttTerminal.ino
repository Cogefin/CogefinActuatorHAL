
#include "config.h"

#include "src/Syslog.h"

#include "ActuatorHAL.h"

#include "watchdog.h"

HardwareHelper hwHelper;

#ifdef USE_ETHERNET
#include <Ethernet.h>
#endif /* USE_ETHERNET */

#ifdef USE_WIFI
#include "src/WiFiUtils.h"
#endif /* USE_WIFI */

#if defined(USE_NTP) || defined(UPDATE_RTC_BY_NTP)
#ifdef USE_ETHERNET
#include <EthernetUdp.h>
#endif /* USE_ETHERNET */
#ifdef USE_WIFI
#include <WiFiUdp.h>
#endif /* USE_WIFI */
#include <NTPClient.h>
#endif /* USE_NTP or UPDATE_RTC_BY_NTP */

#include <ArduinoMqttClient.h>

// Include SD
#ifdef USE_SD
#ifdef USE_FS_H
#define FS_NO_GLOBALS
#include <FS.h>
#else /* USE_FS_H */
#include "SPI.h"
#include <SD.h>
#endif /* USE_FS_H */

#ifdef ESP32
#include "SPIFFS.h"  // ESP32 only
#endif

#endif /* USE_SD */

/*
 * ネットワーク関係定義
 */

IPAddress ip(SELF_IP_ADDRESS);
IPAddress dnsServer(DNS_SERVER_ADDRESS);
IPAddress gatewayAddress(GATEWAY_ADDRESS);
IPAddress netMask(NETMASK);

#ifdef USE_ETHERNET
byte mac[] = { FIX_MAC_ADDRESS };  //アドレスは手持ちのarduinoのものに変更すること
#endif                             /* USE_ETHERNET */

/*
   ネットワーク関係の設定
   注意 : DHCPでのアドレス取得失敗時の対策や，長時間経過後のアドレス再割当て等は対応していない
*/
char serverAddress[] = MQTT_SERVER_ADDR;  // server address
int port = MQTT_PORT;
char topic[] = MQTT_TOPIC;

#ifdef USE_DHCP
boolean useDhcp = true;  // DHCPでIPアドレスを設定
#else                    /* USE_DHCP */
boolean useDhcp = false;  // 固定IPアドレス
#endif                   /* USE_DHCP */

#ifdef USE_WIFI
char ssid[] = SSID_STR;   // your network SSID (name)
char pass[] = WIFI_PASS;  // your network password (use for WPA, or use as key for WEP)
#endif                    /* USE_WIFI */

#if defined(USE_NTP) || defined(USE_RTC)
unsigned long currentTime;
#endif /* USE_NTP or USE_RTC */

#if defined(USE_NTP) || defined(UPDATE_RTC_BY_NTP)
#ifdef USE_ETHERNET
EthernetUDP ntpUDP;
#endif /* USE_ETHERNET */
#ifdef USE_WIFI
WiFiUDP ntpUDP;
#endif                                      /* USE_WIFI */
NTPClient timeClient(ntpUDP, 9 * 60 * 60);  // JST
#endif                                      /* USE_NTP or UPDATE_RTC_BY_NTP */

#ifdef USE_ETHERNET
EthernetClient netClient;
#endif /* USE_ETHERNET */
#ifdef USE_WIFI
WiFiClient netClient;
#endif /* USE_WIFI */

/*
 * ログ関係の定義
 */
Syslog syslog(HOSTNAME, APP_NAME, LOG_KERN);

#ifdef USE_LOG_FILE
File logfile;
#endif /* USE_LOG_FILE */


MqttClient mqttClient(netClient);

#ifdef USE_LED_INDICATOR
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel indicator(1, LED_INDICATOR_PIN, NEO_GRB + NEO_KHZ800);
#endif /* USE_LED_INDICATOR */



char msgBuffer[BUFFER_SIZE];

void clearMsgBuffer(void) {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    msgBuffer[i] = 0;
  }
}

#ifdef USE_GROVE_LCD
rgb_lcd grove_lcd;
UnifiedLCD lcd(&(grove_lcd), GROVE_LCD_RGB_BACKLIGHT, Wire);
const int colorR = 0;
const int colorG = 255;
const int colorB = 0;
int grove_lcd_num = -1;
int grove_lcd_type = CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT;
#endif /* USE_GROVE_LCD */

#ifdef USE_LIQUID_CRYSTAL
LiquidCrystal liquid_crystal_h(LIQUID_CRYSTAL_PIN_RS, LIQUID_CRYSTAL_PIN_ES, LIQUID_CRYSTAL_PIN_D4, LIQUID_CRYSTAL_PIN_D5, LIQUID_CRYSTAL_PIN_D6, LIQUID_CRYSTAL_PIN_D7);
UnifiedLCD liquid_crystal(&liquid_crystal_h, LIQUID_CRYSTAL);
int liquid_crystal_num = -1;
int liquid_crystal_type = CHARACTER_DISPLAY_TYPE_LIQUID_CRYSTAL;
#endif /* USE_LIQUID_CRYSTAL */

#ifdef USE_ACM1602NI
ACM1602NI liquid_crystal_i2c_h;  // set the LCD address to 0x27 for a 16 chars and 2 line display
UnifiedLCD liquid_crystal_i2c(&liquid_crystal_i2c_h, ACM1602NI_TYPE);
int liquid_crystal_i2c_num = -1;
int liquid_crystal_i2c_type = CHARACTER_DISPLAY_TYPE_ACM1602NI;
#endif /* USE_ACM1602NI */

#ifdef USE_ACM2004
ACM1602NI liquid_crystal_i2c_h(ACM_TYPE_2004);
UnifiedLCD liquid_crystal_i2c(&liquid_crystal_i2c_h, ACM1602NI_TYPE);
int liquid_crystal_i2c_num = -1;
int liquid_crystal_i2c_type = CHARACTER_DISPLAY_TYPE_ACM1602NI;
#endif /* USE_ACM2004 */

#ifdef GROVE_LED_BAR
Grove_LED_Bar bar(GROVE_LED_BAR_PIN_CLK, GROVE_LED_BAR_PIN_DATA, GROVE_LED_BAR_DIRECTION, LED_BAR_10);
UnifiedLED ledBar(&(bar), LED_BAR, GROVE_LED_BAR_NUM_OF_LED, LED_FORWARD);
int grove_led_bar_num = -1;
#endif /* GROVE_LED_BAR */

#ifdef GROVE_LED_CIRCULAR
Grove_LED_Bar circle(GROVE_LED_CIRCLE_PIN_CLK, GROVE_LED_CIRCLE_PIN_DATA, GROVE_LED_CIRCLE_DIRECTION, LED_CIRCULAR_24);
UnifiedLED ledCircle(&(circle), LED_CIRCULAR, GROVE_LED_CIRCLE_NUM_OF_LED, LED_FORWARD);
int grove_led_circular = -1;
#endif /* GROVE_LED_CIRCULAR */


#ifdef GROVE_CHAINABLE_LED
ChainableLED chain(GROVE_CHAINABLE_LED_PIN_CLK, GROVE_CHAINABLE_LED_PIN_DATA, GROVE_CHAINABLE_LED_NUM_OF_LED);
UnifiedLED ledChain(&(chain), P98X3_LED, GROVE_CHAINABLE_LED_NUM_OF_LED);
int grove_chainable_led = -1;
#endif /* GROVE_CHAINABLE_LED */

#ifdef GROVE_NEO_PIXEL
Adafruit_NeoPixel strip(LED_NEO_PIXEL_NUM_OF_LED, LED_NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);
UnifiedLED neoPixel(&(strip), NEO_PIXEL_LED, LED_NEO_PIXEL_NUM_OF_LED);
int grove_neo_pixel = -1;
#endif /* GROVE_NEO_PIXEL */

#ifdef USE_SIMPLE_COLOR_LED
UnifiedLED cathodeCommon(SIMPLE_COLOR_LED_RED_PIN, SIMPLE_COLOR_LED_GREEN_PIN, SIMPLE_COLOR_LED_BLUE_PIN, USE_SIMPLE_COLOR_LED_PIN_TYPE);
int simple_color_led = -1;
#endif /* USE_SIMPLE_COLOR_LED */

#ifdef GROVE_MONO_LED
UnifiedLED mono_led(GROVE_MONO_LED_PIN, GROVE_MONO_LED_PIN_TYPE);
int simple_mono_led = -1;
#endif /* GROVE_MONO_LED */



#ifdef USE_OSL12306_16
#define OSL12306_16_NUM_OF_PINS _OSL12306_16_CHAR_PINS


uint8_t pins[OSL12306_16_NUM_OF_PINS] = {
  OSL12306_16_PIN_A1, OSL12306_16_PIN_A2, OSL12306_16_PIN_B, OSL12306_16_PIN_C, OSL12306_16_PIN_D1, OSL12306_16_PIN_D2, OSL12306_16_PIN_E, OSL12306_16_PIN_F,
  OSL12306_16_PIN_G1, OSL12306_16_PIN_G2, OSL12306_16_PIN_J, OSL12306_16_PIN_K, OSL12306_16_PIN_L, OSL12306_16_PIN_M, OSL12306_16_PIN_N, OSL12306_16_PIN_P
};

uint8_t digitPins[OSL12306_16_NUM_OF_DIGITS] = { OSL12306_16_PIN_DIGIT };

OSL12306_16 __osl12306_16(
  OSL12306_16_PIN_TYPE,
  pins,
  OSL12306_16_PIN_DP,
  OSL12306_16_NUM_OF_DIGITS,
  digitPins);

UnifiedNSegLED osl12306_16(&__osl12306_16, OSL12306_16_TYPE);
int osl12306_16_num = -1;
uint32_t osl12306_16_type = NSEG_LED_TYPE_OSL12306_16;
#endif /* USE_OSL12306_16 */


#ifdef USE_OSL20541
#define OSL20541_NUM_OF_CHAR_PINS _OSL20541_CHAR_PINS

uint8_t osl20541_charPins[OSL20541_NUM_OF_CHAR_PINS] = {
  OSL20541_PIN_A,
  OSL20541_PIN_B,
  OSL20541_PIN_C,
  OSL20541_PIN_D,
  OSL20541_PIN_E,
  OSL20541_PIN_F,
  OSL20541_PIN_G1,
  OSL20541_PIN_G2,
  OSL20541_PIN_H,
  OSL20541_PIN_J,
  OSL20541_PIN_K,
  OSL20541_PIN_L,
  OSL20541_PIN_M,
  OSL20541_PIN_N
};
uint8_t osl20541_digitPins[OSL20541_NUM_OF_DIGITS] = { OSL20541_PIN_DIGIT_1, OSL20541_PIN_DIGIT_2 };

OSL20541 __osl20541(
  OSL20541_PIN_TYPE,
  osl20541_charPins,
  OSL20541_PIN_DP,
  OSL20541_NUM_OF_DIGITS,
  osl20541_digitPins);

UnifiedNSegLED osl20541(&__osl20541, OSL20541_TYPE);

int osl20541_num = -1;
uint32_t osl20541_type = NSEG_LED_TYPE_OSL20541;
#endif /* USE_OSL20541 */

#ifdef USE_OSL30561

uint8_t osl30561_digitPins[OSL30561_NUM_OF_DIGITS] = { OSL30561_PIN_DIGIT_1, OSL30561_PIN_DIGIT_2, OSL30561_PIN_DIGIT_3 };

OSL30561 __osl30561(
  OSL30561_PIN_TYPE,
  OSL30561_PIN_A,
  OSL30561_PIN_B,
  OSL30561_PIN_C,
  OSL30561_PIN_D,
  OSL30561_PIN_E,
  OSL30561_PIN_F,
  OSL30561_PIN_G,
  OSL30561_PIN_DP,
  OSL30561_NUM_OF_DIGITS,
  osl30561_digitPins);

UnifiedNSegLED osl30561(&__osl30561, OSL30561_TYPE);
int osl30561_num = -1;
uint32_t osl30561_type = NSEG_LED_TYPE_OSL30561;
#endif /* USE_OSL30561 */

#ifdef USE_DFR0090
//#define DIGITS DFR0090_NUM_OF_DIGITS
//#define PRINTABLE_CHAR_NUM 18

DFR0090 _dfr(DFR0090_CLOCK_PIN, DFR0090_LATCH_PIN, DFR0090_DATA_PIN, DFR0090_NUM_OF_DIGITS);

UnifiedNSegLED dfr0090(&_dfr, DFR0090_TYPE);
int dfr0090_num = -1;
uint32_t dfr0090_type = NSEG_LED_TYPE_DFR0090;
#endif /* USE_DFR0090 */

#ifdef USE_GROVE_TM1637
TM1637 __tm1637(GROVE_NSEG_LED_PIN_CLK, GROVE_NSEG_LED_PIN_DATA);
UnifiedNSegLED tm1637(&__tm1637, GROVE_TM1637_TYPE);
int grove_tm1637_num = -1;
uint32_t grove_tm1637_type = NSEG_LED_TYPE_GROVE_TM1637;
#endif /* USE_GROVE_TM1637 */

#ifdef USE_SWITCH
Switch switch_device(SWITCH_PIN);
int switch_num = -1;
#endif /* USE_SWITCH */

#ifdef USE_SERVO
Servo myservo;
ServoHal servoHal(&myservo);

int servo_num = -1;
int pos = 0;
uint32_t servo_type = SERVO_TYPE_SIMPLE;
#endif /* USE_SERVO */

#ifdef USE_SIMPLE_SOUND
#ifdef SPEAKER
SimpleSound speaker(SPEAKER_PIN, SIMPLE_SOUND_TYPE_PULL_UP);
int speaker_num = -1;
#endif /* SPEAKER */

#ifdef BUZZER
SimpleSound buzzer(BUZZER_PIN, SIMPLE_SOUND_TYPE_PULL_UP);
int buzzer_num = -1;
#endif /* BUZZER */
#endif /* USE_SIMPLE_SOUND */

#ifdef USE_PMW
PMW sw(PMW_PIN);
int pmw_num = -1;
#endif /* USE_PMW */

#ifdef USE_IRDA
int irda_num = -1;
#endif /* USE_IRDA */




/* Mega 2560 */
#if CPU_ARCH == AVR_ARCH
#define COMSerial SSerial
#define ShowSerial Serial
#define _SET_SERIALS_
#endif /* CPU_ARCH == AVR_ARCH */

/* Uno R4 Series */
#if CPU_ARCH == RA4_ARCH
#define COMSerial Serial1  // 0/RX, 1/TX
#define ShowSerial Serial
#define _SET_SERIALS_
#endif /* CPU_ARCH == RA4_ARCH */

/* Nano RP2040 connect */
#if HARDWARE_TYPE == ARDUINO_NANO_RP2040_C
#define COMSerial Serial1
#define ShowSerial Serial
#define _SET_SERIALS_
#endif /* HARDWARE_TYPE==ARDUINO_NANO_RP2040_C */

/* Nano ESP32 */
#if HARDWARE_TYPE == ARDUINO_NANO_ESP32_S3
#define COMSerial SSerial
#define ShowSerial Serial
//  #define COMSerial Serial1  // D9/RX, D8/TX
//  #define ShowSerial Serial
#define _SET_SERIALS_
#endif /* HARDWARE_TYPE==ARDUINO_NANO_ESP32_S3 */

/* Arduino M0 pro */
#if HARDWARE_TYPE == ARDUINO_M0
#define COMSerial Serial1  // 0/RX, 1/TX
#define ShowSerial Serial
#define _SET_SERIALS_
#endif /* HARDWARE_TYPE==ARDUINO_M0 */

/* Arduino MKR Series */
#if (CPU_TYPE == TYPE_SAMD21G18A) && (FORM_FACTOR_TYPE == FORM_FACTOR_MKR)
#define COMSerial Serial1  // 13/RX, 14/TX
#define ShowSerial Serial
#define _SET_SERIALS_
#endif /* (CPU_TYPE==TYPE_SAMD21G18A) && ( FORM_FACTOR_TYPE==FORM_FACTOR_MKR) */

/* Nano 33 IoT */
#if HARDWARE_TYPE == ARDUINO_NANO_33_IOT
#define COMSerial Serial1
#define ShowSerial Serial
#define _SET_SERIALS_
#endif /* HARDWARE_TYPE==ARDUINO_NANO_33_IOT */

/* Arduino Giga */
#if (HARDWARE_TYPE == ARDUINO_GIGA_WIFI_MAIN) || (HARDWARE_TYPE == ARDUINO_GIGA_WIFI_SUB)
#define COMSerial Serial1  // D0/RX, D1/TX
#define ShowSerial Serial
#define _SET_SERIALS_
#endif /* (HARDWARE_TYPE==ARDUINO_GIGA_WIFI_MAIN) || (HARDWARE_TYPE==ARDUINO_GIGA_WIFI_SUB) */

/* Nano RP2040 Connect */
#if HARDWARE_TYPE == ARDUINO_NANO_RP2040_C
#define COMSerial Serial1
#define ShowSerial Serial
#define _SET_SERIALS_
#endif /* HARDWARE_TYPE==ARDUINO_NANO_RP2040_C */

#ifndef _SET_SERIALS_
#error "no serail information defined"
#endif /* _SET_SERIALS_ */


#ifdef __USE_WT2605C_PLAYER__
#define COMSERIAL_SPEED 115200
#ifdef _SOFTWARE_SERIAL_
#if HARDWARE_TYPE == ARDUINO_NANO_ESP32_S3
WT2605C<EspSoftwareSerial> wt2605c_player;
#else  /* HARDWARE_TYPE==ARDUINO_NANO_ESP32_S3 */
WT2605C<SoftwareSerial> wt2605c_player;
#endif /* HARDWARE_TYPE==ARDUINO_NANO_ESP32_S3 */
#else  /* _SOFTWARE_SERIAL_ */
WT2605C<HardwareSerial> wt2605c_player;
#endif /* _SOFTWARE_SERIAL_ */
UnifiedMP3 wt2605c(&wt2605c_player, WT2605C_PLAYER);
#define MP3_PLAYER_TYPE MP3_PLAYER_TYPE_WT2605C
#define USE_WT2605C_PLAYER
int grove_wt2605c_num = -1;
#endif /* __USE_WT2605C_PLAYER__ */

#ifdef __USE_DF_ROBOT_DF_PLAYER_MINI__
#define COMSERIAL_SPEED 9600
DFRobotDFPlayerMini myDFPlayer;
UnifiedMP3 dfplayer(&myDFPlayer, DF_ROBOT_DFP_PLAYER_MINI);
#define MP3_PLAYER_TYPE MP3_PLAYER_TYPE_DF_ROBOT_DFP
#define USE_DF_ROBOT_DF_PLAYER_MINI
int dfp_mp3_num = -1;
#endif /* __USE_DF_ROBOT_DF_PLAYER_MINI__ */

/*
#ifdef USE_WT2605C_PLAYER
SoftwareSerial wt2605cSerial(WT2605C_PLAYER_PIN_RX, WT2605C_PLAYER_PIN_TX); // RX, TX
WT2605C<SoftwareSerial> wt2605c_player;
UnifiedMP3 wt2605c(&wt2605c_player, WT2605C_PLAYER);
int grove_wt2605c_num = -1;
#endif

#ifdef USE_DF_ROBOT_DF_PLAYER_MINI
SoftwareSerial dfpSerial(DF_ROBOT_DF_PLAYER_MINI_PIN_RX, DF_ROBOT_DF_PLAYER_MINI_PIN_RX);
DFRobotDFPlayerMini myDFPlayer;
UnifiedMP3 dfplayer(&myDFPlayer, DF_ROBOT_DFP_PLAYER_MINI);
int dfp_mp3_num = -1;
#endif
*/

#ifdef USE_RTC /* RTC.cppの関数 */
extern void setupRTC(void);
unsigned long rtcDate(void);
#endif /* USE_RTC */

#ifdef UPDATE_RTC_BY_NTP
bool update_RTC_Time(unsigned long);
#endif /* UPDATE_RTC_BY_NTP */

#ifdef USE_GIGA_DISPLAY_GFX
GigaDisplay_GFX tft;  // create the object
int giga_display_num = -1;
int giga_display_type = GRAPHIC_DISPLAY_TYPE_GIGA_DISPLAY;

UnifiedGraphicDisplay display = UnifiedGraphicDisplay(&tft, DISPLAY_TYPE_GIGA_DISPLAY_GFX);
#endif /* USE_GIGA_DISPLAY_GFX */

#ifdef USE_BODMER_TFT_ESPI
TFT_eSPI tft = TFT_eSPI();
int bodmer_tft_num = -1;
int bodmer_tft_type = GRAPHIC_DISPLAY_TYPE_BODMER_TFT;

UnifiedGraphicDisplay display = UnifiedGraphicDisplay(&tft, DISPLAY_TYPE_BODMER_TFT_ESPI);
#endif /* USE_BODMER_TFT_ESPI */

#ifdef USE_ADAFRUIT_GFX
#ifdef TFT_ILI9341_TYPE_1
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_ILI9341_PIN_CS, TFT_ILI9341_PIN_DC, TFT_ILI9341_PIN_RST);
#endif /* TFT_ILI9341_TYPE_1 */
#ifdef TFT_ILI9341_TYPE_2
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_ILI9341_PIN_CS, TFT_ILI9341_PIN_DC, TFT_ILI9341_PIN_MOSI, TFT_ILI9341_PIN_CLK, TFT_ILI9341_PIN_RST, TFT_ILI9341_PIN_MISO);
#endif /* TFT_ILI9341_TYPE_2 */
int adafruit_gfx_num = -1;
int adafruit_gfx_type = GRAPHIC_DISPLAY_TYPE_ADAFRUIT_GFX;

UnifiedGraphicDisplay display = UnifiedGraphicDisplay(&tft, DISPLAY_TYPE_ADAFRUIT_GFX);
#endif /* USE_ADAFRUIT_GFX */


uint8_t deviceCounter = 0;



/*
 * Serialに書き出した内容を完全にフラッシュする
 */
void flushAll(void) {
  netClient.flush();
  Serial.flush();
#ifdef USE_LOG_FILE
  if (logfile) {
    logfile.flush();
  }
#endif /* USE_LOG_FILE */
}

/*
 * 再起動
 */
void reboot() {
  flushAll();
#ifdef USE_LOG_FILE
  if (logfile) {
    logfile.close();
  }
#endif /* USE_LOG_FILE */

#ifdef USE_WDT
  while (true) {
    delay(WDT_SHORT_DURATION);
    Serial.print(".");
  }
#else  /* USE_WDT */
  hwHelper.SoftwareReset();
#endif /* USE_WDT */
}

void setup() {
  clearMsgBuffer();

  initDeviceTable();

  Serial.begin(SERIAL_SPEED);
#ifdef DEBUG
  hwHelper.SerialWait();
#endif /* DEBUG */


#ifdef USE_LED_INDICATOR
  indicator.begin();
  indicator.clear();
  indicator.setPixelColor(0, indicator.Color(0, 0, 120));  //青
  indicator.show();                                        // Send the updated pixel colors to the hardware.
  delay(INDICATOR_SHORT_DURATION);
#endif /* USE_LED_INDICATOR */

#ifdef USE_WDT
  int countdownMS = setupWDT(WDT_DURATION);
#endif /* USE_WDT */

#ifdef DEBUG
  Serial.println("setup: start");
#endif /* DEBUG */



#ifdef USE_SD
  setup_sd();
#endif /* USE_SD */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_LOG_FILE
  prepare_logfile();
#endif /* USE_LOG_FILE */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_RTC
  setupRTC();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_RTC */

#ifdef USE_LED_INDICATOR
  indicator.setPixelColor(0, indicator.Color(128, 20, 128));  // 紫
  indicator.show();                                           // Send the updated pixel colors to the hardware.
  delay(INDICATOR_SHORT_DURATION);
#endif /* USE_LED_INDICATOR */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  outputBootlog(F("network setup start."));

  if (useDhcp) {
#ifdef USE_ETHERNET
    Ethernet.init(ETHERNET_CHIP_SELECT);
    if (Ethernet.begin(mac) == 0) {
      Serial.println(F("DHCP fail."));
#ifdef USE_LED_INDICATOR
      indicator.setPixelColor(0, indicator.Color(200, 40, 0));  // オレンジ
      indicator.show();                                         // Send the updated pixel colors to the hardware.
      delay(INDICATOR_SHORT_DURATION);
#endif /* USE_LED_INDICATOR */
      reboot();
    }
#endif /* USE_ETHERNET */

#ifdef USE_WIFI
    WiFi.begin(SSID_STR, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
#endif /* USE_WIFI */

  } else {
#ifdef USE_ETHERNET
    Ethernet.begin(mac, ip, dnsServer, gatewayAddress, netMask);
#endif /* USE_ETHERNET */
#ifdef USE_WIFI
    WiFi.config(ip, dnsServer, gatewayAddress, netMask);
    WiFi.begin(SSID_STR, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
#endif /* USE_WIFI */
  }
#ifdef USE_ETHERNET
  Serial.print(F("IP address : "));
  Serial.println(Ethernet.localIP());
#endif /* USE_ETHERNET */
#ifdef USE_WIFI
  Serial.print(F("IP address : "));
  Serial.println(WiFi.localIP());
#endif /* USE_WIFI */

  outputBootlog(F("network setup done"));

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#if defined(USE_NTP) || defined(UPDATE_RTC_BY_NTP)
  timeClient.begin();
  timeClient.update();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_NTP or UPDATE_RTC_BY_NTP */

#ifdef USE_NTP
  syslog.SetNTP(&timeClient, DATE_TIME);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_NTP */

#ifdef UPDATE_RTC_BY_NTP
  //unsigned long currentTime = timeClient.getEpochTime();
  currentTime = timeClient.getEpochTime();
  if (update_RTC_Time(currentTime)) {
    outputBootlog(F("update RTC time by NTP."));
  } else {
    outputBootlog(F("fail to update RTC time using NTP."));
  }
#endif /* UPDATE_RTC_BY_NTP */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_LOG_SERIAL
  if (SERIAL_RESET) {
    if (HARD_SERIAL) {
      syslog.SetSerial(&HARD_SERIAL);
    } else {
      outputBootlog(F("setup serial for syslog fail."));
    }
  } else {
    syslog.SetSerial(&HARD_SERIAL);
  }
#endif /* USE_LOG_SERIAL */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  mqttClient.setId(HOSTNAME);

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_MQTT_AUTH
  mqttClient.setUsernamePassword(MQTT_AUTH_USERNAME, MQTT_AUTH_PASSWORD);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_MQTT_AUTH */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  syslog.log(LOG_INFO, "Attempting to connect to the MQTT broker");

  if (!mqttClient.connect(serverAddress, port)) {
    syslog.logf(LOG_CRIT, "MQTT connection failed! Error code =  %d", mqttClient.connectError());
#ifdef USE_LED_INDICATOR
    indicator.setPixelColor(0, indicator.Color(200, 40, 0));  // オレンジ
    indicator.show();                                         // Send the updated pixel colors to the hardware.
    delay(INDICATOR_SHORT_DURATION);
#endif /* USE_LED_INDICATOR */
    reboot();
  }

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  syslog.log(LOG_INFO, "You're connected to the MQTT broker!");

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  syslog.logf(LOG_CRIT, "MQTT subscribe to topic: %s", topic);

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  // subscribe to a topic
  mqttClient.subscribe(topic);

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  syslog.logf(LOG_CRIT, "Waiting for MQTT message of topic: %s", topic);

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_CHARACTER_DISPLAY
  setup_character_display();
#endif /* USE_CHARACTER_DISPLAY */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_LED
  setup_led();
#endif /* USE_LED */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_NSEG_LED
  setup_nseg_led();
#endif /* USE_NSEG_LED */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_SWITCH
  setup_switch();
#endif /* USE_SWITCH */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_SERVO
  setup_servo();
#endif /* USE_SERVO */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_SIMPLE_SOUND
  setup_sound();
#endif /* USE_SIMPLE_SOUND */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_PMW
  setup_pmw();
#endif /* USE_PMW */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_IRDA
  setup_irda();
#endif /* USE_IRDA */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_MP3_PLAYER
  setup_mp3();
#endif /* USE_MP3_PLAYER */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_GRAPHIC_DISPLAY
  setup_graphic_display();
#endif /* USE_GRAPHIC_DISPLAY */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_LED_INDICATOR
  indicator.setPixelColor(0, indicator.Color(0, 0, 0));  // 消灯
  indicator.show();                                      // Send the updated pixel colors to the hardware.
#endif                                                   /* USE_LED_INDICATOR */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  dumpDeviceTable();

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  syslog.log(LOG_INFO, "setup: end");

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
}

void loop() {
  keepStateActuator();
  mqttClient.poll();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
}


void onMqttMessage(int messageSize) {
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#ifdef USE_LED_INDICATOR
  indicator.setPixelColor(0, indicator.Color(0, 128, 0));
  indicator.show();  // Send the updated pixel colors to the hardware.
  delay(INDICATOR_SHORT_DURATION);
#endif /* USE_LED_INDICATOR */
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  syslog.logf(LOG_INFO, "Received a message with topic: %s", mqttClient.messageTopic().c_str());
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  syslog.logf(LOG_INFO, "Message length: %d (byte)", messageSize);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  // use the Stream interface to print the contents
  int counter = 0;
  while (mqttClient.available()) {
    msgBuffer[counter] = (char)mqttClient.read();
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
    counter++;
  }
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  JsonDocument doc;
  deserializeJson(doc, msgBuffer);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  long time = doc["time"];
  uint8_t id = doc["id"];
  uint32_t type = doc["type"];
  uint8_t command = doc["command"];
  uint8_t paramSize = doc["paramSize"];

  syslog.logf(LOG_INFO, "Target actuator id: %d", id);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "Target actuator type: %lu", type);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "message time: %ld", time);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "actuator control command: %d", command);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "actuator control command parameter size: %d", paramSize);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  for (int i = 0; i < BUFFER_SIZE; i++) {
    if (msgBuffer[i] == 0) break;
    Serial.print((char)msgBuffer[i]);
    msgBuffer[i] = 0;
  }

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  controlActuator(doc);

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#ifdef USE_LED_INDICATOR
  indicator.setPixelColor(0, indicator.Color(0, 0, 0));
  indicator.show();  // Send the updated pixel colors to the hardware.
#endif               /* USE_LED_INDICATOR */

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
}

#ifdef USE_CHARACTER_DISPLAY
void setup_character_display(void) {
#ifdef USE_GROVE_LCD
  JsonDocument grove_rgb_lcd;
#endif /* USE_GROVE_LCD */

#ifdef USE_LIQUID_CRYSTAL
  JsonDocument liquidCrystal;
#endif /* USE_LIQUID_CRYSTAL */

#if defined(USE_ACM1602NI) || defined(USE_ACM2004)
  JsonDocument acm1602ni;
#endif /* USE_ACM1602NI or USE_ACM2004 */

  // set up the LCD's number of columns and rows:
#ifdef USE_GROVE_LCD
  updateDeviceTable(deviceCounter, CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT, &lcd);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  grove_lcd_num = deviceCounter;
  grove_rgb_lcd["id"] = grove_lcd_num;
  grove_rgb_lcd["type"] = CHARACTER_DISPLAY_TYPE_GROVE_LCD_RGB_BACKLIGHT;
  grove_rgb_lcd["time"] = millis();
  grove_rgb_lcd["command"] = CHARACTER_DISPLAY_COMMAND_SET_SIZE;
  grove_rgb_lcd["paramSize"] = 1;
  grove_rgb_lcd["param"][0]["col"] = CHARACTER_DISPLAY_GROVE_LCD_COLOMNS;
  grove_rgb_lcd["param"][0]["row"] = CHARACTER_DISPLAY_GROVE_LCD_LINES;
  grove_rgb_lcd["param"][0]["font"] = 0;
  if (false == controlActuator(grove_rgb_lcd)) {
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
    syslog.log(LOG_CRIT, "setSize() to Grove LCD RGB Backlight : fail");
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
  }
  deviceCounter++;
  syslog.logf(LOG_INFO, "Grove RGB backlight LCD : device No. %d", grove_lcd_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_GROVE_LCD */

#ifdef USE_LIQUID_CRYSTAL
  updateDeviceTable(deviceCounter, CHARACTER_DISPLAY_TYPE_LIQUID_CRYSTAL, &liquid_crystal);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  liquid_crystal_num = deviceCounter;
  liquidCrystal["id"] = liquid_crystal_num;
  liquidCrystal["type"] = CHARACTER_DISPLAY_TYPE_LIQUID_CRYSTAL;
  liquidCrystal["time"] = millis();
  liquidCrystal["command"] = CHARACTER_DISPLAY_COMMAND_SET_SIZE;
  liquidCrystal["paramSize"] = 1;
  liquidCrystal["param"][0]["col"] = CHARACTER_DISPLAY_LIQUID_CRYSTAL_COLOMNS;
  liquidCrystal["param"][0]["row"] = CHARACTER_DISPLAY_LIQUID_CRYSTAL_LINES;
  liquidCrystal["param"][0]["font"] = 0;
  if (false == controlActuator(liquidCrystal)) {
    syslog.log(LOG_CRIT, "setSize() to liquid crystal : fail");
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
  }
  deviceCounter++;
  syslog.logf(LOG_INFO, "Liquid crystal LCD : device No. %d", liquid_crystal_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_LIQUID_CRYSTAL */

#if defined(USE_ACM1602NI) || defined(USE_ACM2004)
  updateDeviceTable(deviceCounter, CHARACTER_DISPLAY_TYPE_ACM1602NI, &liquid_crystal_i2c);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  liquid_crystal_i2c_num = deviceCounter;
  acm1602ni["id"] = liquid_crystal_i2c_num;
  acm1602ni["type"] = CHARACTER_DISPLAY_TYPE_ACM1602NI;
  acm1602ni["time"] = millis();
  acm1602ni["command"] = CHARACTER_DISPLAY_COMMAND_SET_SIZE;
  acm1602ni["paramSize"] = 1;
  acm1602ni["param"][0]["col"] = CHARACTER_DISPLAY_ACM1602NI_COLOMNS;
  acm1602ni["param"][0]["row"] = CHARACTER_DISPLAY_ACM1602NI_LINES;
  acm1602ni["param"][0]["font"] = 0;
  if (false == controlActuator(acm1602ni)) {
    syslog.log(LOG_CRIT, "setSize() to ACM1602NI/ACM2004 : fail");
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
  }
  deviceCounter++;
  syslog.logf(LOG_INFO, "ACM1602NI/ACM2004 LCD : device No. %d", liquid_crystal_i2c_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_ACM1602NI or USE_ACM2004 */
}
#endif /* USE_CHARACTER_DISPLAY */



#ifdef USE_LED
void setup_led(void) {

#ifdef LED_HAL_USE_MY9221
#ifdef GROVE_LED_BAR
  ledBar.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.log(LOG_INFO, "led bar begin");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  ledBar.setOnce(0);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  ledBar.setMode(LED_FORWARD);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.log(LOG_INFO, "led bar set mode");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, LED_TYPE_MONO_CHAIN_LED, &ledBar);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  grove_led_bar_num = deviceCounter;
  deviceCounter++;
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "Grove LED Bar : device No.%d", grove_led_bar_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* GROVE_LED_BAR */
#ifdef GROVE_LED_CIRCULAR
  ledCircle.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.log(LOG_INFO, "led circle begin");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  ledCircle.setOnce(0);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  ledCircle.setMode(LED_FORWARD);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.log(LOG_INFO, "led circle set mode");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, LED_TYPE_MONO_CHAIN_LED, &ledCircle);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  grove_led_circular = deviceCounter;
  deviceCounter++;
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "Grove LED Circular : device No.%d", grove_led_circular);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* GROVE_LED_CIRCULAR */
#endif /* LED_HAL_USE_MY9221 */
#ifdef LED_HAL_USE_P98X3
#ifdef GROVE_CHAINABLE_LED
  ledChain.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  for (int i = 0; i < GROVE_CHAINABLE_LED_NUM_OF_LED; i++) {
    ledChain.setLed(i, 0, 0, 0);
  }
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.log(LOG_INFO, "full color led setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, LED_TYPE_COLOR_CHAIN_LED, &ledChain);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  grove_chainable_led = deviceCounter;
  deviceCounter++;
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "Grove RGB chainable LED : device No.%d", grove_chainable_led);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* GROVE_CHAINABLE_LED */
#endif /* LED_HAL_USE_P98X3 */
#ifdef LED_HAL_USE_NEO_PIXEL
#ifdef GROVE_NEO_PIXEL
  neoPixel.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  for (int i = 0; i < LED_NEO_PIXEL_NUM_OF_LED; i++) {
    neoPixel.setLed(i, 0, 0, 0);
  }
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.log(LOG_INFO, "neoPixel begin");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, LED_TYPE_COLOR_CHAIN_LED, &neoPixel);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  grove_neo_pixel = deviceCounter;
  deviceCounter++;
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "Neo pixel LED : device No.%d", grove_neo_pixel);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* GROVE_NEO_PIXEL */
#endif /* LED_HAL_USE_NEO_PIXEL */
#ifdef USE_SIMPLE_COLOR_LED
  syslog.log(LOG_INFO, "cathod/anode common led setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  cathodeCommon.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  cathodeCommon.setLed(0, 0, 0);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, LED_TYPE_COLOR_LED, &cathodeCommon);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  simple_color_led = deviceCounter;
  deviceCounter++;
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "Anode/Cathod common RGB LED : device No.%d", simple_color_led);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_SIMPLE_COLOR_LED */
#ifdef GROVE_MONO_LED
  syslog.log(LOG_INFO, "mono led setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  mono_led.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  mono_led.setLed(0);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, LED_TYPE_MONO_LED, &mono_led);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  simple_mono_led = deviceCounter;
  deviceCounter++;
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "Single mono LED : device No.%d", simple_mono_led);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* GROVE_MONO_LED */
}
#endif /* USE_LED */

#ifdef USE_NSEG_LED
void setup_nseg_led(void) {
  JsonDocument clear;
  clear["time"] = millis();
  clear["command"] = NSEG_LED_COMMAND_CLEAR;
  clear["paramSize"] = 0;

  //JsonDocument set;
  //set["time"] = millis();
  //set["command"] = NSEG_LED_COMMAND_SET;
  //set["paramSize"] = 1;

#ifdef USE_OSL12306_16
  syslog.log(LOG_INFO, "N-seg led OSL12306-16 setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  osl12306_16.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, osl12306_16_type, &osl12306_16, OSL12306_16_NUM_OF_DIGITS);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  osl12306_16_num = deviceCounter;
  deviceCounter++;

  clear["id"] = osl12306_16_num;
  clear["type"] = osl12306_16_type;
  controlActuator(clear);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  //set["id"] = osl12306_16_num;
  //set["type"] = osl12306_16_type;
  //set["param"][0]["period"] = 1;
  //set["param"][0]["text"] = "4";
  //controlActuator(set);
  //#ifdef USE_WDT
  //  resetWDT();
  //#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "N-seg LED OSL12306 16 : device No.%d", osl12306_16_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_OSL12306_16 */

#ifdef USE_OSL20541
  syslog.log(LOG_INFO, "N-seg led OSL20541 setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  osl20541.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, osl20541_type, &osl20541, OSL20541_NUM_OF_DIGITS);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  osl20541_num = deviceCounter;
  deviceCounter++;

  clear["id"] = osl20541_num;
  clear["type"] = osl20541_type;
  controlActuator(clear);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "N-seg LED OSL20541 : device No.%d", osl20541_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_OSL20541 */

#ifdef USE_OSL30561
  syslog.log(LOG_INFO, "N-seg led OSL30561 setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  osl30561.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, osl30561_type, &osl30561, OSL30561_NUM_OF_DIGITS);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  osl30561_num = deviceCounter;
  deviceCounter++;

  clear["id"] = osl30561_num;
  clear["type"] = osl30561_type;
  controlActuator(clear);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "N-seg LED OSL30561 : device No.%d", osl30561_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_OSL30561 */


#ifdef USE_DFR0090
  //#define DIGITS DFR0090_NUM_OF_DIGITS
  //#define PRINTABLE_CHAR_NUM 18
  //UnifiedNSegLED dfr0090(&_dfr, DFR0090_TYPE);
  //int dfr0090_num = -1;
  //uint32_t dfr0090_type = NSEG_LED_TYPE_DFR0090;
  syslog.log(LOG_INFO, "N-seg led dfr0090 setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  dfr0090.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, dfr0090_type, &dfr0090, DFR0090_NUM_OF_DIGITS);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  dfr0090_num = deviceCounter;
  deviceCounter++;

  clear["id"] = dfr0090_num;
  clear["type"] = dfr0090_type;
  controlActuator(clear);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "N-seg LED dfr0090 : device No.%d", dfr0090_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_DFR0090 */


#ifdef USE_GROVE_TM1637
  syslog.log(LOG_INFO, "N-seg led Grove TM1637 setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  tm1637.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, grove_tm1637_type, &tm1637, 0);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  grove_tm1637_num = deviceCounter;
  deviceCounter++;

  clear["id"] = grove_tm1637_num;
  clear["type"] = grove_tm1637_type;
  controlActuator(clear);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  JsonDocument setBrightness;
  setBrightness["id"] = grove_tm1637_num;
  setBrightness["type"] = grove_tm1637_type;
  setBrightness["time"] = millis();
  setBrightness["command"] = NSEG_LED_COMMAND_SET_BRIGHTNESS;
  setBrightness["paramSize"] = 1;
  setBrightness["param"][0]["brightness"] = BRIGHT_TYPICAL;  //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  controlActuator(setBrightness);

  JsonDocument setColon;
  setColon["id"] = grove_tm1637_num;
  setColon["type"] = grove_tm1637_type;
  setColon["time"] = millis();
  setColon["command"] = NSEG_LED_COMMAND_SET_COLON;
  setColon["paramSize"] = 1;
  setColon["param"][0]["flag"] = true;
  controlActuator(setColon);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "N-seg LED Grove TM1637 : device No.%d", grove_tm1637_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_GROVE_TM1637 */
}
#endif /* USE_NSEG_LED */

#ifdef USE_SWITCH
void setup_switch(void) {
  syslog.log(LOG_INFO, "Simple switch setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  switch_device.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, SIMPLE_SWITCH_TYPE_NORMAL, &switch_device);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  switch_num = deviceCounter;
  deviceCounter++;
  syslog.logf(LOG_INFO, "Simple switch device : device No.%d", switch_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
}
#endif /* USE_SWITCH */

#ifdef USE_SERVO
void setup_servo(void) {
  syslog.log(LOG_INFO, "Servo setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  myservo.attach(SERVO_PIN);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, servo_type, &servoHal);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  servo_num = deviceCounter;
  deviceCounter++;
  syslog.logf(LOG_INFO, "Servo device : device No.%d", servo_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
}
#endif /* USE_SERVO */

#ifdef USE_SIMPLE_SOUND
/*
{
  "id": 1,
  "type": SIMPLE_SOUND_TYPE_NORMAL,
  "time": 123456789,
  "paramSize": 0,
  "command": SIMPLE_SOUND_COMMAND_OFF,
}

"{\n  \"id\": 1,\n  \"type\": 601,\n  \"time\": 123456789,\n  \"paramSize\": 0,\n  \"command\": 2,\n}"

 */

void setup_sound(void) {
  syslog.log(LOG_INFO, "Sound device setup.");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  JsonDocument doc;
  doc["time"] = millis();
  doc["command"] = SIMPLE_SOUND_COMMAND_OFF;
  doc["paramSize"] = 0;
  doc["type"] = SIMPLE_SOUND_TYPE_NORMAL;

#ifdef SPEAKER
  syslog.log(LOG_INFO, "Speaker setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  speaker.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, SIMPLE_SOUND_TYPE_NORMAL, &speaker);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  speaker_num = deviceCounter;
  deviceCounter++;
  doc["id"] = speaker_num;
  controlActuator(doc);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "Simple sound Speaker : device No.%d", speaker_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* SPEAKER */

#ifdef BUZZER
  syslog.log(LOG_INFO, "Buzzer setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  buzzer.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, SIMPLE_SOUND_TYPE_NORMAL, &buzzer);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  buzzer_num = deviceCounter;
  deviceCounter++;
  doc["id"] = buzzer_num;
  controlActuator(doc);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  syslog.logf(LOG_INFO, "Simple sound Buzzer : device No.%d", buzzer_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* BUZZER */
  syslog.log(LOG_INFO, "Sound device setup done.");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
}
#endif /* USE_SIMPLE_SOUND */

#ifdef USE_PMW
void setup_pmw(void) {
  syslog.log(LOG_INFO, "Simple PMW device setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  sw.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, PMW_TYPE_SIMPLE, &sw);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  pmw_num = deviceCounter;
  deviceCounter++;
  syslog.logf(LOG_INFO, "Simple PMW device : device No.%d", pmw_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
}
#endif /* USE_PMW */


#ifdef USE_IRDA
void setup_irda(void) {
  syslog.log(LOG_INFO, "IRDA device setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  init_ir_sender(deviceCounter, IRDA_TYPE_SIMPLE, IR_PIN);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  irda_num = deviceCounter;
  deviceCounter++;
  syslog.logf(LOG_INFO, "Simple IRDA device : device No.%d", irda_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
}
#endif /* USE_IRDA */


#ifdef USE_MP3_PLAYER
void setup_mp3(void) {
  syslog.log(LOG_INFO, "MP3 player setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#ifdef USE_WT2605C_PLAYER
  syslog.log(LOG_INFO, "grove mp3 player wt2605c setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  COMSerial.begin(115200);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  wt2605c_player.init(COMSerial);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, MP3_PLAYER_TYPE_WT2605C, &wt2605c);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  grove_wt2605c_num = deviceCounter;
  deviceCounter++;

  JsonDocument wt2605_stop;
  wt2605_stop["id"] = grove_wt2605c_num;
  wt2605_stop["type"] = MP3_PLAYER_TYPE_WT2605C;
  wt2605_stop["time"] = millis();
  wt2605_stop["command"] = MP3_PLAYER_COMMAND_STOP;
  wt2605_stop["paramSize"] = 0;
  if (false == controlActuator(wt2605_stop)) {
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
    syslog.log(LOG_CRIT, "stop music with grove mp3 player wt2605c : fail");
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
  }
  syslog.logf(LOG_INFO, "grove mp3 player wt2605c : device No.%d", grove_wt2605c_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_WT2605C_PLAYER */

#ifdef USE_DF_ROBOT_DF_PLAYER_MINI
  syslog.log(LOG_INFO, "DF Robot MP3 player setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  COMSerial.begin(9600);
#ifdef USE_WDT
  resetWDT();
#endif                                                                         /* USE_WDT */
  if (!myDFPlayer.begin(COMSerial, /*isACK = */ true, /*doReset = */ true)) {  //Use serial to communicate with mp3.
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
    syslog.log(LOG_CRIT, "Unable to begin:");
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
    syslog.log(LOG_CRIT, "1.Please recheck the connection!");
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
    syslog.log(LOG_CRIT, "2.Please insert the SD card!");
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
    while (true) {
      delay(0);  // Code to compatible with ESP8266 watch dog.
    }
  }
  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, MP3_PLAYER_TYPE_DF_ROBOT_DFP, &dfplayer);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  dfp_mp3_num = deviceCounter;
  deviceCounter++;

  JsonDocument dfplayer_stop;
  dfplayer_stop["id"] = dfp_mp3_num;
  dfplayer_stop["type"] = MP3_PLAYER_TYPE_DF_ROBOT_DFP;
  dfplayer_stop["time"] = millis();
  dfplayer_stop["command"] = MP3_PLAYER_COMMAND_STOP;
  dfplayer_stop["paramSize"] = 0;
  if (false == controlActuator(dfplayer_stop)) {
    syslog.log(LOG_CRIT, "stop music with DF Robot df player : fail");
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
    while (true) {
      delay(0);  // Code to compatible with ESP8266 watch dog.
    }
  }
  syslog.logf(LOG_INFO, "DF Robot MP3 player : device No.%d", dfp_mp3_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_DF_ROBOT_DF_PLAYER_MINI */
  syslog.log(LOG_INFO, "MP3 player setup done.");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
}
#endif /* USE_MP3_PLAYER */



#ifdef USE_GRAPHIC_DISPLAY
bool display_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
  if (y >= display.height()) return 0;
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#ifdef USE_BODMER_TFT_ESPI
  // This function will clip the image block rendering automatically at the TFT boundaries
  display.pushImage(x, y, w, h, bitmap);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#else  /* USE_BODMER_TFT_ESPI */
  display.drawRGBBitmap(x, y, bitmap, w, h);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_BODMER_TFT_ESPI */

  // Return 1 to decode next block
  return 1;
}
#endif /* USE_GRAPHIC_DISPLAY */


#ifdef USE_GRAPHIC_DISPLAY
void setup_graphic_display(void) {
  syslog.log(LOG_INFO, "graphic display setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */


#ifdef USE_BODMER_TFT_ESPI
  syslog.log(LOG_INFO, "graphic display BODMER TFT eSPI setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, GRAPHIC_DISPLAY_TYPE_BODMER_TFT, &display);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  bodmer_tft_num = deviceCounter;
  deviceCounter++;

  syslog.logf(LOG_INFO, "graphic display BODMER TFT eSPI : device No.%d", bodmer_tft_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

#endif /* USE_BODMER_TFT_ESPI */

#ifdef USE_GIGA_DISPLAY_GFX
  syslog.log(LOG_INFO, "graphic display Arduino Giga display setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, GRAPHIC_DISPLAY_TYPE_GIGA_DISPLAY, &display);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  giga_display_num = deviceCounter;
  deviceCounter++;

  syslog.logf(LOG_INFO, "graphic display Arduino Giga display : device No.%d", giga_display_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_GIGA_DISPLAY_GFX */

#ifdef USE_ADAFRUIT_GFX
  syslog.log(LOG_INFO, "graphic display Adafruit GFX setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  updateDeviceTable(deviceCounter, GRAPHIC_DISPLAY_TYPE_ADAFRUIT_GFX, &display);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  adafruit_gfx_num = deviceCounter;
  deviceCounter++;

  syslog.logf(LOG_INFO, "ggraphic display Adafruit GFX : device No.%d", adafruit_gfx_num);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_ADAFRUIT_GFX */


  // Initialise the TFT
  tft.begin();
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */


  display.setTextColor(0xFFFF, 0x0000);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
  display.fillScreen(TFT_BLACK);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#ifdef USE_BODMER_TFT_ESPI
  display.setSwapBytes(true);  // We need to swap the colour bytes (endianess)
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#endif /* USE_BODMER_TFT_ESPI */

  // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
  TJpgDec.setJpgScale(1);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  // The decoder must be given the exact name of the rendering function above
  TJpgDec.setCallback(display_output);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  syslog.log(LOG_INFO, "graphic display setup done.");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
}
#endif /* USE_GRAPHIC_DISPLAY */

#ifdef USE_SD
void setup_sd(void) {
  syslog.log(LOG_INFO, "SD setup");
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  // Initialise SD before TFT
  if (!SD.begin(SD_CS_PIN)) {

    syslog.log(LOG_CRIT, "SD.begin(PIN) failed!");
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
    while (true) {
      delay(0);  // Code to compatible with ESP8266 watch dog.
    }
  }
}
#endif /* USE_SD */


/*
 * 初期化(syslog有効化前)時のログ出力
 */
void outputBootlog(const __FlashStringHelper* message) {

  Serial.println(message);

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
#ifdef USE_LOG_FILE
  if (logfile) {

    logfile.println(message);

#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */

#if CPU_ARCH != XTENSA_LX6_ARCH /* ESP32以外 */
    logfile.flush();
#endif /* ESP32以外 */
  }
#endif /* USE_LOG_FILE */
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */
}

/*
 * ログローテート
 */
#if defined(LOG_ROTATE) && defined(USE_LOG_FILE)
void logRotate() {
  String logFileName = LOGFILE_NAME_HEAD;
  logFileName += "9.txt";
  if (SD.exists(logFileName.c_str())) {
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
    SD.remove(logFileName.c_str());
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
  }
  for (int i = 8; i >= 0; i--) {
    int targetNum = i + 1;
    String targetFileName = LOGFILE_NAME_HEAD;
    targetFileName += targetNum;
    targetFileName += ".txt";
    logFileName = LOGFILE_NAME_HEAD;
    logFileName += i;
    logFileName += ".txt";
    if (SD.exists(logFileName.c_str())) {
#ifdef USE_WDT
      resetWDT();
#endif /* USE_WDT */
      SD.rename(logFileName.c_str(), targetFileName.c_str());
#ifdef USE_WDT
      resetWDT();
#endif /* USE_WDT */
    }
  }
  logFileName = LOGFILE_NAME_HEAD;
  logFileName += ".txt";
  String targetFileName = LOGFILE_NAME_HEAD;
  targetFileName += "0.txt";
  if (SD.exists(logFileName.c_str())) {
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
    SD.rename(logFileName.c_str(), targetFileName.c_str());
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
  }
}
#endif /* LOG_ROTATE && USE_LOG_FILE */

/*
 * ログファイルの初期化
 */
#ifdef USE_LOG_FILE
void prepare_logfile() {

  String logFileName = LOGFILE_NAME_HEAD;
  logFileName += ".txt";

  logfile = SD.open(logFileName.c_str(), FILE_WRITE);
#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  if (LOG_FILE_SIZE_MAX < logfile.size()) {
#ifdef LOG_ROTATE
    logRotate();
#else /* LOG_ROTATE */
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
    logfile.close();
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
    SD.remove(logFileName.c_str());
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
    logfile = SD.open(logFileName.c_str(), FILE_WRITE);
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
#endif /* LOG_ROTATE */
  }

  if (logfile) {
    syslog.SetFile(&logfile);
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
  } else {
    Serial.println("open logfile failure.");
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
  }
}
#endif /* USE_LOG_FILE */
