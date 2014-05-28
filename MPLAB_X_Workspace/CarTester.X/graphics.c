

#include "graphics.h"

#define PMPWaitBusy()   while(PMMODEbits.BUSY);

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


void GraphicsSystemInit()
{

}
