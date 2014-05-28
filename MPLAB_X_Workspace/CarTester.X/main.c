/*********************************************************************
 * Car Tester simple application with microchip graphics.
 **********************************************************************/

/*
 *
*/

#include <stdlib.h>
#include <plib.h>
#include "graphics.h"
/* MIKROE PIC32MX multimedia card features. */
#include "../../Include/HardwareProfile/HardwareProfile.h"

#define __PIC32MX3XX_7XX__

// Device configuration register settings must be defined in the bootloader.
// Applications must just re-use these settings from bootloader.
    // #pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF
    // #pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1

#define mLED_1_On()         LED_1_LAT = 1;
#define mLED_2_On()         LED_2_LAT = 1;

#define mLED_1_Tgl()        LED_1_LAT = !LED_1_LAT;

#define SYS_FREQ            (80000000L)

#define TOGGLES_PER_SEC         1000
#define CORE_TICK_RATE	       (SYS_FREQ/2/TOGGLES_PER_SEC)

InitLEDPorts()
{
  AllLEDConfig();
  AllLEDOff();
}

InitBPortButton()
{
  TRISBbits.TRISB1 = 1;
  CNENbits.CNEN3 = 1;
  AD1PCFGbits.PCFG1 = 1;
  CNPUE = 0b0000000000001000;
}

int main(void)
{
//    unsigned int pb_clock;

    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    OpenCoreTimer(CORE_TICK_RATE);

    mConfigIntCoreTimer((CT_INT_ON | CT_INT_PRIOR_2 | CT_INT_SUB_PRIOR_0));

    INTEnableSystemMultiVectoredInt();
    DDPCONbits.JTAGEN = 0;  /* JTAG debug disabled */

    /* Initializing the LED, and button ports. */
    InitLEDPorts();
    InitBPortButton();

    GraphicsSystemInit();

    while(1)
    {
        LED_0_LAT = ((ReadCoreTimer() & 0x0800000) != 0);
        LED_3_LAT = PORTBbits.RB1;
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
        mLED_1_Tgl();
//        mPORTDToggleBits(BIT_1);
        core_counter = 0;
    }
    // update the period
    UpdateCoreTimer(CORE_TICK_RATE);
}
