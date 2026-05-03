#ifndef _WIFI_UTILS_H_
#define _WIFI_UTILS_H_

#include "../config.h"

#ifdef USE_WIFI

#include <Arduino.h>
#include "./detectArduinoHardware.h"

#include "./NiUtils.h"

#ifdef USE_WIFI_NORMAL
//#include <WiFi.h>
#endif /* USE_WIFI_NORMAL */

#ifdef USE_WIFI_NINA
//#include <WiFiNINA.h>
#endif /* USE_WIFI_NINA */

#ifdef USE_WIFI_WINC1500
//#include <WiFi101.h>
#endif /* USE_WIFI_WINC1500 */

#ifdef USE_UDP
//#include <Udp.h>
#endif /* USE_UDP */

#include <ArduinoMqttClient.h>
#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_AVR_UNO_WIFI_REV2)
  #include <WiFiNINA.h>
#elif defined(ARDUINO_SAMD_MKR1000)
  #include <WiFi101.h>
#elif defined(ARDUINO_ARCH_ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_NICLA_VISION) || defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_GIGA) || defined(ARDUINO_OPTA)
  #include <WiFi.h>
#elif defined(ARDUINO_PORTENTA_C33)
  #include <WiFiC3.h>
#elif defined(ARDUINO_UNOR4_WIFI)
  #include <WiFiS3.h>
#endif

#define WIFI_RETRY_MAX 30
#define WIFI_TRY_INTERVAL 1000

uint8_t NifInitStatus(void);
void PrintNetworkStatus(void);
bool CheckNif(void);
String NetworkStatus(void);

#endif /* USE_WIFI */

#endif /* _WIFI_UTILS_H_ */
