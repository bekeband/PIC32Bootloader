

#include "delay.h"
#include <plib.h>

void Delay(int period)
{
  IFS0bits.T1IF = 0;
  OpenTimer1(T1_ON | T1_IDLE_CON | T1_TMWDIS_OFF | T1_SOURCE_INT | T1_PS_1_256, period);
  while (!IFS0bits.T1IF) ;
  CloseTimer1();
}

/* Max. 65536 / 156 ~ 420 msec delay. */

void DelayMs(int msec)
{
  Delay(msec * 156);
}

