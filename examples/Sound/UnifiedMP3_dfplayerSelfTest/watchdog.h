#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#ifdef USE_WDT_NORMAL
#include <Adafruit_SleepyDog.h>
#endif /* USE_WDT_NORMAL */
#ifdef USE_WDT_MBED
#include <mbed.h>
#endif /* USE_WDT_MBED */
#ifdef USE_WDT_RENESAS
#include <WDT.h>
#endif /* USE_WDT_RENESAS */

extern int setupWDT(int t);
extern void resetWDT();

#endif /* __WATCHDOG_H__ */