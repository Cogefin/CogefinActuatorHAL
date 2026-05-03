#include "config.h"

#ifdef USE_WDT
#include "watchdog.h"

#ifdef USE_WDT_MBED
mbed::Watchdog &watchdog = mbed::Watchdog::get_instance();
#endif /* USE_WDT_MBED */

/*
 * watch dog timer
 */

int setupWDT(int t) {
#ifdef USE_WDT_NORMAL
  return Watchdog.enable(t);
#endif /* USE_WDT_NORMAL */
#ifdef USE_WDT_MBED
  if (watchdog.start(t)) {
    return t;
  }
  return 0;
#endif /* USE_WDT_MBED */
#ifdef USE_WDT_RENESAS
  if(WDT.begin(t)) {
    return t;
  }
  return 0;
#endif /* USE_WDT_RENESAS */
}

void resetWDT() {
#ifdef USE_WDT_NORMAL
  Watchdog.reset();
#endif /* USE_WDT_NORMAL */
#ifdef USE_WDT_MBED
  watchdog.kick();
#endif /* USE_WDT_MBED */
#ifdef USE_WDT_RENESAS
  WDT.refresh();
#endif /* USE_WDT_RENESAS */
}


#endif /* USE_WDT */