#ifndef _DATE_UTILS_H_
#define _DATE_UTILS_H_

#include <Arduino.h>


enum {
  SUN = 0,
  MON = 1,
  TUE = 2,
  WED = 3,
  THU = 4,
  FRI = 5,
  SAT = 6
};

typedef struct  {
  uint16_t  year;
  uint8_t   month;
  uint8_t   mday;
  uint8_t   wday;
  uint8_t   hour;
  uint8_t   minute;
  uint8_t   second;
  int16_t   millisecond;
} date_t;

#define SECONDS_IN_A_DAY  86400   //(24*60*60) sec
#define UNIX_EPOCH_DAY    719468L // days from 0000/03/01 to 1970/01/01
#define DAYS_IN_ONE_YEAR  365
#define DAYS_IN_FOUR_YEAR 1461    // DAYS_IN_ONE_YEAR * 4 + 1
#define DAYS_IN_100_YEAR  36524   // DAYS_IN_FOUR_YEAR * 25 - 1
#define DAYS_IN_400_YEAR  146097  // DAYS_IN_100_YEAR * 4 + 1

#define FORMAT_WDAY 0b010
#define FORMAT_TIME 0b001
#define FORMAT_DATE 0b100
#define FORMAT_ALL  0b111

void unixTimeToDate(unsigned long unixtime, date_t *date);
unsigned int numOfDays(uint16_t year);
unsigned long dateToUnixTime(date_t *dateTime);
String dateString(unsigned long unixTime, uint8_t format=FORMAT_ALL);

#endif /* _DATE_UTILS_H_ */
