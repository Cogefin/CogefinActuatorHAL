#include "config.h"

#ifdef USE_RTC
#include "RTC_Utils.h"
#else /* USE_RTC */
#include "RTC_U.h"
/*#define I2C_IF Wire*/
#endif /* USE_RTC */

#ifdef USE_WDT
//#include <Adafruit_SleepyDog.h>
#include "watchdog.h"
#endif /* USE_WDT */

#include "src/Syslog.h"
//#include "AusExOutputPlugin.h"

//extern AuxExSensorIO outputDevice;
extern Syslog syslog;

#ifdef USE_LED_INDICATOR
#include <ChainableLED.h>
extern ChainableLED indicator;
#endif  /* USE_LED_INDICATOR */

/* スケッチ本体で定義 */

void outputBootlog(const __FlashStringHelper *message);
void reboot(void);

/*
 * rtcの時刻レジスタの設定が正しいものになっているか否かを確認
 */
#define TIME_IS_VALID 1
#define TIME_IS_INVALID 0




#ifdef USE_RTC
RTC_CLASS rtc = RTC_CLASS(&I2C_IF);
#endif /* USE_RTC */

/*
 * RTCの時刻設定
 */
#if defined(UPDATE_RTC_BY_NTP) && defined(USE_RTC)
bool update_RTC_Time(unsigned long epochTime) {
  date_t date;
  rtc.convertEpochTime(&date, epochTime);
  if (!rtc.setTime(&date)) {
    return false;
  } else {
    return true;
  }
}

#endif /* UPDATE_RTC_BY_NTP && USE_RTC */


/*
 * RTCの時刻設定確認
 */
#ifdef USE_RTC
int timeValidity() {
#if defined(USE_RTC8564NB) || defined(USE_DS3231)
  int flag=rtc.checkLowPower();
  if (flag < 0) return flag;
  if (0==flag) return TIME_IS_VALID;
  return TIME_IS_INVALID;
#endif

#ifdef USE_DS1307
  int flag=rtc.checkLowPower();
  if (flag < 0) return flag;
  if (0==flag) return TIME_IS_INVALID;
  return TIME_IS_VALID;
#endif /* USE_DS1307 */

#ifdef USE_PCF8523
  int flag=rtc.checkLowPower();
  if (flag < 0) return flag;
  flag = flag & 0b10000000;
  if (0==flag) return TIME_IS_VALID;
  return TIME_IS_INVALID;
#endif /* USE_PCF8523 */

#ifdef USE_RV8803
  int flag=rtc.checkLowPower();
  if (flag < 0) return flag;
  if (0b00==flag) return TIME_IS_VALID;
  return TIME_IS_INVALID;
#endif /* USE_RV8803 */

#ifdef USE_RX8900
  int flag=rtc.checkLowPower();
  if (flag < 0) return flag;
  if (0b00==flag) return TIME_IS_VALID;
  return TIME_IS_INVALID;
#endif /* USE_RX8900 */

#ifdef USE_RX8025
  int flag=rtc.checkLowPower();
  if (flag < 0) return flag;
  if (0b010==flag) return TIME_IS_VALID;
  return TIME_IS_INVALID;
#endif /* USE_RX8025 */

}
#endif /* USE_RTC */




#ifdef USE_RTC
void setupRTC(void) {
  //date_t dateTime;
  if (rtc.begin(false)) {
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */

    outputBootlog(F("Successful initialization of the RTC"));

#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */

    syslog.SetRtc(&rtc,DATE_TIME);
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */

  } else {
    outputBootlog(F("Failed initialization of the RTC"));
  #ifdef USE_COLOR_LED
    indicator.setColorRGB(0, 128, 0, 0);  //赤
  #endif /* USE_COLOR_LED */
    reboot();
  }

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  int flag = timeValidity();

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  int clear_flag =rtc.clearPowerFlag();

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  if (RTC_U_SUCCESS==clear_flag) {
    outputBootlog(F("Success : clear power flag."));
  } else if (RTC_U_UNSUPPORTED==clear_flag) {
    outputBootlog(F("Skip : rtc does not support power related function."));
    flag=TIME_IS_INVALID;
  } else {
    outputBootlog(F("Error: fail to clear power flag."));
  }

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */

  if (flag < 0) {
    outputBootlog(F("Error: fail to get power flag"));
    reboot();
  } else if (flag == TIME_IS_INVALID) {
    outputBootlog(F("Time of RTC setting is invalid."));
#ifdef USE_WDT
    resetWDT();
#endif /* USE_WDT */
    date_t date;
    date.year=2001;
    date.month=1;
    date.mday=1;
    date.wday=MON;
    date.hour=0;
    date.minute=0;
    date.second=0;
    date.millisecond=0;
    outputBootlog(F("setting time."));
    if (!rtc.setTime(&date)) {
      outputBootlog(F("set time to RTC fail."));     // 初期化失敗
      reboot();
    } else {
      outputBootlog(F("set time to RTC success.")); // 初期化成功
    }
  } else {
    outputBootlog(F("Time of RTC setting is valid."));
  }

#ifdef USE_WDT
  resetWDT();
#endif /* USE_WDT */


}
#endif /* USE_RTC */

#ifdef USE_RTC
unsigned long rtcDate(void) {
  date_t dateTime;
  rtc.getTime(&dateTime);
  return rtc.convertDateToEpoch(dateTime);
}
#endif /* USE_RTC */