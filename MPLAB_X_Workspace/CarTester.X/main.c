/*********************************************************************
 * Car Tester simple application with microchip graphics.
 **********************************************************************/

/*
 *
*/

#include <stdlib.h>
#include <plib.h>
/* MIKROE PIC32MX multimedia card features. */
#include "../../Include/HardwareProfile/HardwareProfile.h"

#define __PIC32MX3XX_7XX__

// Device configuration register settings must be defined in the bootloader.
// Applications must just re-use these settings from bootloader.
    // #pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF
    // #pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1

#define mLED_1_On()         mLED_1 = 1;
#define mLED_2_On()         mLED_2 = 1;

#define mLED_1_Tgl()         mLED_1 = !mLED_1;

#define SYS_FREQ            (80000000L)

#define TOGGLES_PER_SEC         1000
#define CORE_TICK_RATE	       (SYS_FREQ/2/TOGGLES_PER_SEC)

int main(void)
{
//    unsigned int pb_clock;

    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    OpenCoreTimer(CORE_TICK_RATE);

    mConfigIntCoreTimer((CT_INT_ON | CT_INT_PRIOR_2 | CT_INT_SUB_PRIOR_0));

    INTEnableSystemMultiVectoredInt();

    InitLED();
    mLED_1_On();
    mLED_2_On();

    while(1)
    {
        mLED_1 = ((ReadCoreTimer() & 0x0800000) != 0);
    }
    return 0;
}

unsigned int core_counter = 0;

////////////////////////////////////////////////////////////
// Core Timer Interrupts
//
void __ISR(_CORE_TIMER_VECTOR, ipl2) CoreTimerHandler(void)
{
    // clear the interrupt flag
    mCTClearIntFlag();

    if ((core_counter++) == 1000)
    {
        mPORTDToggleBits(BIT_1);
        core_counter = 0;
    }
    // update the period
    UpdateCoreTimer(CORE_TICK_RATE);
}
