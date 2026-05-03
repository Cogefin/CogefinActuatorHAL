
#include "./dateUtils.h"

void unixTimeToDate(unsigned long unixtime, date_t *date){
  uint32_t unixday, num;
  uint16_t year = 0;
  uint8_t  leap = 0, month, day;
  static const uint16_t monthday[] = { 0,31,61,92,122,153,184,214,245,275,306,337 };

  date->second = unixtime % 60;
  date->minute = (unixtime / 60) % 60;
  date->hour   = (unixtime / 3600) % 24;

  unixday    = (uint32_t)(unixtime / SECONDS_IN_A_DAY);
  date->wday = ((unixday + 4) % 7);   //  1970/1/1 is thursday
  unixday   += UNIX_EPOCH_DAY;        //  days from 0/3/1 to 1970/1/1 + 1970/1/1 to today

  year    += 400 * (unixday / DAYS_IN_400_YEAR);
  unixday %= DAYS_IN_400_YEAR;

  num      = unixday / DAYS_IN_100_YEAR;
  year    += num * 100;
  unixday %= DAYS_IN_100_YEAR;

  if (num == 4){
    leap = 1;
  } else {
    year    += 4 * (unixday / DAYS_IN_FOUR_YEAR);
    unixday %= DAYS_IN_FOUR_YEAR;

    num      = unixday / DAYS_IN_ONE_YEAR;
    year    += num;
    unixday %= DAYS_IN_ONE_YEAR;
    if (num == 4) leap = 1;
  }
  if (leap != 0) {
    month = 2;
    day   = 29;
  } else {
    month  = (unixday * 5 + 2) / 153;
    day    = unixday - monthday[month] + 1;    //  
    month += 3;
    if (month > 12) {
      ++year;
      month -= 12;
    }
  }
  date->year  = year;
  date->month = month;
  date->mday  = day;
}

/* 西暦元年から引数の年までの経過日数を求める */
unsigned int numOfDays(uint16_t year) {
  unsigned int result;
  if(year<0)return -numOfDays(-year)-366+365;
  else if(year==0)return 0;
  result=(unsigned int) year*365;
  result+=(unsigned int) year/4;   /* 通常の閏年 */
  result-=(unsigned int) year/100; /* 100年に一度は閏年ではない */
  result+=(unsigned int) year/400; /* 400年に一度は100の倍数だが，閏年 */
  return result;
}

unsigned long dateToUnixTime(date_t *dateTime) {
  const unsigned int monthDays[13]={
    0,31,59,90,120,151,181,212,243,273,304,334,365
  };/*その月までの日数の和（累積和）*/

  uint16_t  year = dateTime->year;
  uint8_t   month = dateTime->month;
  uint8_t   day = dateTime->mday;
  uint8_t   hour = dateTime->hour;
  uint8_t   minute = dateTime->minute;
  uint8_t   second = dateTime->second;

  unsigned long result;
  if (year < 1970) return 0;
  /* year年1月1日 00:00:00までの日数を求める*/
  result=numOfDays(year-1)-numOfDays(1969);
  /*秒に変換*/
  result*=SECONDS_IN_A_DAY;
  /*月の日数を秒に変換して足す*/
  result+=monthDays[month-1]*SECONDS_IN_A_DAY;
  /*閏年かつ3月以降なら1日足す*/
  if(year%400==0 || (year%4==0 && year%100!=0)) {
    if(month>=3)result+=SECONDS_IN_A_DAY;
  }
  /*その月の日数を秒に変換して足す*/
  result+=(day-1)*SECONDS_IN_A_DAY;
  result+=(unsigned long) hour*60*60;
  result+=(unsigned long) minute*60;
  result+=(unsigned long) second;
  return result;
}


String dateString(unsigned long unixTime, uint8_t format) {
  date_t date;
  unixTimeToDate(unixTime, &date);
  String result="";
  if (0!=(format&FORMAT_DATE)) {
    result=String(date.year)+"/"+String(date.month)+"/"+String(date.mday);
    if ((0!=(format&FORMAT_WDAY)) || (0!=(format&FORMAT_TIME))) result+=" ";
  }
  if (0!=(format&FORMAT_WDAY)) {
    switch(date.wday){
      case SUN: result+="SUN";break;
      case MON: result+="MON";break;
      case TUE: result+="TUE";break;
      case WED: result+="WED";break;
      case THU: result+="THU";break;
      case FRI: result+="FRI";break;
      case SAT: result+="SAT";break;
    }
    if (0!=(format&FORMAT_TIME)) result+=" ";
  }
  if (0!=(format&FORMAT_TIME)) {
    result=result+String(date.hour)+":"+String(date.minute)+":"+String(date.second);
  }
  return result;
}
