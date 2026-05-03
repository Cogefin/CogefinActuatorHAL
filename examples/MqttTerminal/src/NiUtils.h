#ifndef _NI_UTILS_H_
#define _NI_UTILS_H_
#include <Arduino.h>
#include "./detectArduinoHardware.h"

#if EMBEDED_NETWORK==WIFI_NINA
#define USE_WIFI
#define USE_WIFI_NINA
#endif /* EMBEDED_NETWORK==WIFI_NINA */

#if EMBEDED_NETWORK==WIFI_NORMAL
#define USE_WIFI
#define USE_WIFI_NORMAL
#endif /* EMBEDED_NETWORK==WIFI_NORMAL */

#if EMBEDED_NETWORK==WIFI_WINC1500
#define USE_WIFI
#define USE_WIFI_WINC1500
#endif /* EMBEDED_NETWORK==WIFI_WINC1500 */

#if EMBEDED_NETWORK==ETHERNET_W5XXX
#define USE_ETHERNET
#define USE_ETHERNET_W5XXX
#endif /* EMBEDED_NETWORK==ETHERNET_W5XXX */

#ifdef USE_ETHERNET
#define UDP_CLASS    EthernetUDP
#define SERVER_CLASS EthernetServer
#define CLIENT_CLASS EthernetClient
#include <EthernetUtils.h>
#endif /* USE_ETHERNET */

#ifdef USE_WIFI
#ifndef USE_WIFI_WINC1500
#define UDP_CLASS    WiFiUDP
#endif /* USE_WIFI_WINC1500 */
#define SERVER_CLASS WiFiServer
#define CLIENT_CLASS WiFiClient
#include "./WiFiUtils.h"
#endif /* USE_WIFI */

#endif /* _NI_UTILS_H_ */
