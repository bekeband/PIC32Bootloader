

#include <plib.h>
#include "graphics.h"
#include "GenericTypeDefs.h"
#include "../../Include/HardwareProfile/HardwareProfile.h"
#include "delay.h"

#define PMPWaitBusy()   while(PMMODEbits.BUSY);

GFX_COLOR _color;

WORD SingleDeviceRead()
{ WORD value;
	value = PMDIN;
	PMPWaitBusy();
	return value;
}

void DeviceWrite(WORD data)
{
	PMDIN = data;
#ifndef TFT_NO_WAIT_BUSY
	PMPWaitBusy();
#endif
}

/* ResetLCD */
void ResetLCD()
{
  DisplayResetDisable();
  DelayMs(100);
  DisplayResetEnable();
  DelayMs(100);
  DisplayResetDisable();
  DelayMs(100);
}

void WriteCommand(int cmd)
{
  DisplaySetCommand();
  DeviceWrite(cmd);
}

void SoftResetLCD()
{
  WriteCommand(SOFT_RESET_REG);
  DelayMs(100);
}

void WriteData(unsigned int _data)
{
  DisplaySetData();
  DeviceWrite(_data);
}

void ILI9341_DisplayOff()
{
  WriteCommand(DisplayOff); // Display off
  DelayMs(20);
}

void ILI9341_DisplayOn()
{
  WriteCommand(DisplayOn); // Display on
}

void ILI9341_Enter_Sleep(void)
{
  ILI9341_DisplayOff();
  WriteCommand(EnterSleepMode); // Enter Sleep mode
}

void ILI9341_Exit_Sleep(void)
{
  WriteCommand(SleepOut); // Sleep out
  DelayMs(120);
  ILI9341_DisplayOn();
}

void ILI9341_Invert()
{
  WriteCommand(DisplayInversionOn);
}

void ILI9341_ReInvert()
{
  WriteCommand(DisplayInversionOff);
}

void ILI9341_SetBrightness(unsigned char brightness)
{
  WriteCommand(WriteDisplayBrightness);
  WriteData(brightness);
}

/*********************************************************************
* Function:  void SetRegion(SHORT xbeg, SHORT xend, SHORT ybeg, SHORT yend)
* Overview: Writes the region datas
* PreCondition: none
* Input: xbeg - horizontal begin pos, xend : horizontal end pos
*        ybeg - vertical begin pos, yend : vertical end pos.
* Output: none
* Side Effects: none
********************************************************************/

inline void SetRegion(SHORT xbeg, SHORT xend, SHORT ybeg, SHORT yend)
{
  WriteCommand(ColumnAddressSet);
  WriteData(((WORD_VAL) (WORD) xbeg).byte.HB);
  WriteData(((WORD_VAL) (WORD) xbeg).byte.LB);
  WriteData(((WORD_VAL) (WORD) xend).byte.HB);
  WriteData(((WORD_VAL) (WORD) xend).byte.LB);

  WriteCommand(PageAddressSet);
  WriteData(((WORD_VAL) (WORD) ybeg).byte.HB);
  WriteData(((WORD_VAL) (WORD) ybeg).byte.LB);
  WriteData(((WORD_VAL) (WORD) yend).byte.HB);
  WriteData(((WORD_VAL) (WORD) yend).byte.LB);

}
/*********************************************************************
* Function:  void SetAddress(SHORT x, SHORT y)
* Overview: Writes address pointer.
* PreCondition: none
* Input: x - horizontal position
*        y - vertical position
* Output: none
* Side Effects: none
********************************************************************/
inline void SetAddress(SHORT x, SHORT y)
{
  WriteCommand(ColumnAddressSet);
  WriteData(((WORD_VAL) (WORD) x).byte.HB);
  WriteData(((WORD_VAL) (WORD) x).byte.LB);
  WriteData(((WORD_VAL) (WORD) x).byte.HB);
  WriteData(((WORD_VAL) (WORD) x).byte.LB);

  WriteCommand(PageAddressSet);
  WriteData(((WORD_VAL) (WORD) y).byte.HB);
  WriteData(((WORD_VAL) (WORD) y).byte.LB);
  WriteData(((WORD_VAL) (WORD) y).byte.HB);
  WriteData(((WORD_VAL) (WORD) y).byte.LB);

}

/*********************************************************************
* Function:  void ResetDevice()
* PreCondition: none
* Input: none
* Output: none
* Side Effects: none
* Overview: resets LCD, initializes PMP
* Note: none
********************************************************************/
//#define LCD_nRESET LATCbits.LATC1

void ResetDevice()
{
	// Initialize the device

  DisplayResetConfig();               // enable RESET line
  DisplayCmdDataConfig();             // enable RS line
  DisplayDisable();                   // not selected by default
  DisplayConfig();                    // enable chip select line
  DisplayBacklightOff();              // initially set the backlight to off
  DisplayBacklightConfig();           // set the backlight control pin

  PMMODE = 0;
  PMAEN = 0;
  PMCON = 0;
  PMMODEbits.MODE = 2;                // Intel 80 master interface
  PMMODEbits.WAITB = PMP_Data_Setup_Wait_States;
  PMMODEbits.WAITM = PMP_Data_Strobe_Wait_States;
  PMMODEbits.WAITE = PMP_Data_Hold_After_Write_Strobe_Wait_States;
  PMMODEbits.MODE16 = 1;              // 16 bit mode
  PMCONbits.PTRDEN = 1;               // enable RD line
  PMCONbits.PTWREN = 1;               // enable WR line
  PMCONbits.PMPEN = 1;                // enable PMP

	DelayMs(1);				// Delay to let controller ready for next SetReg command

  ResetLCD();

  DisplayEnable();
  WriteCommand(PowerControlB);        //Power control B (CFh)
  WriteData(0x00);
  WriteData(0x81);
  WriteData(0X30);

  WriteCommand(PowerOnSequenceControl);
  WriteData(0x64);
  WriteData(0x03);
  WriteData(0X12);
  WriteData(0X81);

  WriteCommand(DriverTimingControlA);
  WriteData(0x85);
  WriteData(0x10);
  WriteData(0x78);

  WriteCommand(PowerControlA);
  WriteData(0x39);
  WriteData(0x2C);
  WriteData(0x00);
  WriteData(0x34);
  WriteData(0x02);

  WriteCommand(PumpRatioControl);
  WriteData(0x20);

  WriteCommand(DriverTimingControlB);
  WriteData(0x00);
  WriteData(0x00);

  WriteCommand(FrameRateControlInNormalModeFullColors);
  WriteData(0x00);
  WriteData(0x1B);

  WriteCommand(DisplayFunctionControl);        // Display Function Control
  WriteData(0x0A);
  WriteData(0xA2);

  WriteCommand(PowerControl1);         //Power control
  WriteData(0x21);            //VRH[5:0]

  WriteCommand(PowerControl2);         //Power control
  WriteData(0x11);            //SAP[2:0];BT[3:0]

  WriteCommand(VCOMControl1);          //VCM control
  WriteData(0x3F);
  WriteData(0x3C);

  WriteCommand(VCOMControl2);          //VCM control2
  WriteData(0Xb5);

  WriteCommand(PixelFormatSet);

#if defined (_64K_COLOR_MODE)
  WriteData(BITPERPIXEL16);
#elif defined (_256K_COLOR_MODE)
  WriteData(BITPERPIXEL18);
#endif

  WriteCommand(MemoryAccessControl);        // Memory Access Control
  WriteData(RGBSET | MVSET | MXSET);

  WriteCommand(InterfaceControl);        // Memory Access Control
  WriteData(0x01);
#if defined (_MDT00)
  WriteData(MDT00);
#elif defined (_MDT01)
  WriteData(MDT01);
#else
  #error "You must define the MDT parameter !"
#endif

  WriteData(0x00);

  WriteCommand(Enable3G);              // 3Gamma Function Disable
  WriteData(0x00);
  WriteCommand(GammaSet);              //Gamma curve selected
  WriteData(0x01);

  WriteCommand(PositiveGammaCorrection);        //Set Gamma
  WriteData(0x0F);
  WriteData(0x26);
  WriteData(0x24);
  WriteData(0x0B);
  WriteData(0x0E);
  WriteData(0x09);
  WriteData(0x54);
  WriteData(0XA8);
  WriteData(0x46);
  WriteData(0x0C);
  WriteData(0x17);
  WriteData(0x09);
  WriteData(0x0F);
  WriteData(0x07);
  WriteData(0x00);

  WriteCommand(NegativeGammaCorrection);        //Set Gamma
  WriteData(0x00);
  WriteData(0x19);
  WriteData(0x1B);
  WriteData(0x04);
  WriteData(0x10);
  WriteData(0x07);
  WriteData(0x2A);
  WriteData(0x47);
  WriteData(0x39);
  WriteData(0x03);
  WriteData(0x06);
  WriteData(0x06);
  WriteData(0x30);
  WriteData(0x38);
  WriteData(0x0F);

  WriteCommand(SleepOut);        //Exit Sleep
  DelayMs(120);
  WriteCommand(0x29);        //Display on

  DisplayDisable();
  DisplayBacklightOn();

}

/* Logical color converting to RGB pixel. The RGB pixel represents the TFT's RGB
 pixel. This struct depending from TFT color resolution, and addressing mode. */

RGBPIXEL ColorToPixel(GFX_COLOR ic)
{ RGBPIXEL result;
#if defined (_256K_COLOR_MODE)
  #if (COLOR_DEPTH == 16)
    result.B = ic565.B << 3;
    result.G = ic565.G << 2;
    result.R = ic565.R << 3;
  #elif (COLOR_DEPTH == 24)
    result.B = ic & 0xFF;
    result.G = (ic & 0xFF00) >> 8;
    result.R = (ic & 0xFF0000) >> 16;
  #endif
#else  //_64K_COLOR_MODE
  #if (COLOR_DEPTH == 16)
    result.D16 = ic;  // This is straight to int to int data copy.
  #elif (COLOR_DEPTH == 24)
    result.B = (ic & 0xF8) >> 3;
    result.G = (ic & 0xFC00) >> 10;
    result.R = (ic & 0xF80000) >> 19;
  #endif
#endif
  return result;
}

/*********************************************************************
* Function: void ClearDevice(void)
* PreCondition: none
* Input: none
* Output: none
* Side Effects: none
* Overview: clears screen with current color
* Note: none
********************************************************************/
void ClearDevice(void)
{   int x, y; RGBPIXEL p;
  p = ColorToPixel(_color);
  DisplayEnable();
  SetRegion(0, GetMaxX(), 0, GetMaxY());
  DisplaySetCommand();
  DeviceWrite(MemoryWrite);
  DisplaySetData();

  for (x = 0; x < GetMaxY() + 1; x++)
  {
    for (y = 0; y < GetMaxX() + 1; y++)
    {
#if defined (_256K_COLOR_MODE)
    DeviceWrite(p.L16);
    DeviceWrite(p.H16);
#else
    DeviceWrite(p.D16);
#endif
    }
  }

  DisplayDisable();
}

void GraphicsSystemInit()
{

  // Current line type
  SetLineType(SOLID_LINE);

  // Current line thickness
  SetLineThickness(NORMAL_LINE);

  // Current cursor coordinates to 0,0
  MoveTo(0, 0);

    /* Device reset */
  ResetDevice();
  /* Clear device for 50% gray color. */
  _color = GRAY128;
  ClearDevice();

}
