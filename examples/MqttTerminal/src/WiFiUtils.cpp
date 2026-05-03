#include "./WiFiUtils.h"

#ifdef USE_WIFI

/*
 * bool CheckNif(void)
 * 
 */
bool CheckNif(void) {
#if (CPU_TYPE==TYPE_ESP32) || (CPU_TYPE==TYPE_ESP8266)
  return true;
#else /* CPU == ESP32 || CPU == ESP8266 */
  if (WiFi.status() == WL_NO_SHIELD) {
    return false;
  }
  return true;
#endif /* CPU == ESP32 || CPU == ESP8266 */
}

/*
 * uint8_t NifInitStatus(void)
 * 返り値
 * 0 : 成功
 * 1 : CONNECTION_FAILURE
 */
uint8_t NifInitStatus(void) {
  int retry=0;
  while (WiFi.status() != WL_CONNECTED) {
    if (retry > WIFI_RETRY_MAX) return 1;
    retry++;
    delay(WIFI_TRY_INTERVAL);
  }
  return 0;
}

void PrintNetworkStatus(void) {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

#if CPU_TYPE==TYPE_ESP32
String NetworkStatus(void) {
  String result="SSID: "+WiFi.SSID()+" , "+"IPaddress: "+WiFi.localIP().toString()+" , "+"RSSI: "+String(WiFi.RSSI());
  return result;
}

#else /* CPU_TYPE==TYPE_ESP32 */

String NetworkStatus(void) {
  IPAddress address = WiFi.localIP();
  String ssid=String(WiFi.SSID());
  String ipaddr=String(address[0]) + "." + String(address[1]) + "." + String(address[2]) + "." + String(address[3]);
  String result="SSID: "+ssid+" , "+"IPaddress: "+ipaddr+" , "+"RSSI: "+String(WiFi.RSSI());
  return result;
}
#endif /* CPU_TYPE==TYPE_ESP32 */

#endif /* USE_WIFI */