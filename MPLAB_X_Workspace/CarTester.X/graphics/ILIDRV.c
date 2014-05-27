/* ILI9341 for MIKROE PIC32MX board with ILI9341 TFT controller */

#include <plib.h>
#include "ILIDRV.h"

// Clipping region control
SHORT       _clipRgn;

// Clipping region borders
SHORT       _clipLeft;
SHORT       _clipTop;
SHORT       _clipRight;
SHORT       _clipBottom; 

// Color
GFX_COLOR   _color;

#define USE_PRIMITIVE_PUTIMAGE
#ifndef USE_PRIMITIVE_PUTIMAGE
    #warning "This driver does not support partial putImage feature. To enable partial putimage feature, uncomment the macro USE_PRIMITIVE_PUTIMAGE in this file. This will enable the PutImageXBPPYYY() in the Primitive.c implementation."
#endif

/////////////////////// LOCAL FUNCTIONS PROTOTYPES ////////////////////////////
//void    SetReg(BYTE index, BYTE value);

#ifndef USE_PRIMITIVE_PUTIMAGE
void    PutImage1BPP(SHORT left, SHORT top, FLASH_BYTE *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData);
void    PutImage4BPP(SHORT left, SHORT top, FLASH_BYTE *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData);
void    PutImage8BPP(SHORT left, SHORT top, FLASH_BYTE *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData);
void    PutImage16BPP(SHORT left, SHORT top, FLASH_BYTE *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData);

void    PutImage1BPPExt(SHORT left, SHORT top, void *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData);
void    PutImage4BPPExt(SHORT left, SHORT top, void *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData);
void    PutImage8BPPExt(SHORT left, SHORT top, void *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData);
void    PutImage16BPPExt(SHORT left, SHORT top, void *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData);
#endif

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


#ifdef USE_TRANSPARENT_COLOR
/*********************************************************************
* Function:  void TransparentColorEnable(GFX_COLOR color)
* Overview: Sets current transparent color.
* PreCondition: none
* Input: color - Color value chosen.
* Output: none
* Side Effects: none
********************************************************************/
void TransparentColorEnable(GFX_COLOR color)
{
    _colorTransparent = color;    
    _colorTransparentEnable = TRANSPARENT_COLOR_ENABLE;
}
#endif

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
* Function: void PutPixel(SHORT x, SHORT y)
* PreCondition: none
* Input: x,y - pixel coordinates
* Output: none
* Side Effects: none
* Overview: puts pixel
* Note: none
********************************************************************/
void PutPixel(SHORT x, SHORT y)
{
    if(_clipRgn)
    {
        if(x < _clipLeft)
            return;
        if(x > _clipRight)
            return;
        if(y < _clipTop)
            return;
        if(y > _clipBottom)
            return;
    }

    DisplayEnable();
    SetAddress(x, y);
    DisplaySetCommand();
    DeviceWrite(MemoryWrite);
    DisplaySetData();
#if defined (_256K_COLOR_MODE)
    RGBPIXEL p = ColorToPixel(_color);
    DeviceWrite(p.L16);
    DeviceWrite(p.H16);
#else
    DeviceWrite(ColorToPixel(_color).D16);
#endif
    DisplayDisable();
}

/*********************************************************************
* Function: GFX_COLOR GetPixel(SHORT x, SHORT y)
* PreCondition: none
* Input: x,y - pixel coordinates 
* Output: pixel color
* Side Effects: none
* Overview: return pixel color at x,y position
* Note: This implementation assumes an 8bit Data interface. 
*       For other data interface, this function should be modified.
********************************************************************/
GFX_COLOR GetPixel(SHORT x, SHORT y)
{ GFX_COLOR result;
    BYTE red = 0, green = 0, blue = 0;
    
    DisplayEnable();
    SetAddress(x, y);
    DisplaySetCommand();
    DeviceWrite(READMEMCONTINUE_REG);
    DisplaySetData(); 
    SingleDeviceRead();
    // read RED
	result = SingleDeviceRead();
/*    // read GREEN
	green = SingleDeviceRead();
    // read BLUE
	blue = SingleDeviceRead();*/

    DisplayDisable();
    return result;
//    return ((WORD) (((((GFX_COLOR)(red) & 0xF8) >> 3) << 11) | ((((GFX_COLOR)(green) & 0xFC) >> 2) << 5) | (((GFX_COLOR)(blue) & 0xF8) >> 3)));
}

/*********************************************************************
* Function: WORD Bar(SHORT left, SHORT top, SHORT right, SHORT bottom)
* PreCondition: none
* Input: left,top - top left corner coordinates,
*        right,bottom - bottom right corner coordinates
* Output: none
* Side Effects: none
* Overview: draws rectangle filled with current color
* Note: none
********************************************************************/
WORD Bar(SHORT left, SHORT top, SHORT right, SHORT bottom)
{
    register SHORT  x, y;

    if(_clipRgn)
    {
        if(left < _clipLeft)
            left = _clipLeft;
        if(right > _clipRight)
            right = _clipRight;
        if(top < _clipTop)
            top = _clipTop;
        if(bottom > _clipBottom)
            bottom = _clipBottom;
    }

    RGBPIXEL p = ColorToPixel(_color);
    DisplayEnable();
    
    SetRegion(left, right, top, bottom);
    DisplaySetCommand();
    DeviceWrite(MemoryWrite);
    DisplaySetData();
    for(y = top; y < bottom + 1; y++)
    {
      for(x = left; x < right + 1; x++)
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
    return (1);
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

#ifndef USE_PRIMITIVE_PUTIMAGE

    #ifdef USE_BITMAP_FLASH

/*********************************************************************
* Function: void PutImage1BPP(SHORT left, SHORT top, FLASH_BYTE* image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
* PreCondition: none
* Input: left,top - left top image corner,
*        image - image pointer,
*        stretch - image stretch factor
*        pPartialImageData - (currently not implemented in this driver)
* Output: none
* Side Effects: none
* Overview: outputs monochrome image starting from left,top coordinates
* Note: image must be located in flash
********************************************************************/
void PutImage1BPP(SHORT left, SHORT top, FLASH_BYTE *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
{
    register FLASH_BYTE *flashAddress;
    register FLASH_BYTE *tempFlashAddress;
    BYTE                temp = 0;
    WORD                sizeX, sizeY;
    WORD                x, y, currentXLocation;
    BYTE                stretchX, stretchY;
    WORD                pallete[2];
    BYTE                mask;

    // Move pointer to size information
    flashAddress = image + 2;

    // Read image size
    sizeY = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;
    sizeX = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;
    pallete[0] = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;
    pallete[1] = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;

    DisplayEnable();
    for(y = 0; y < sizeY; y++)
    {
        tempFlashAddress = flashAddress;
        for(stretchY = 0; stretchY < stretch; stretchY++)
        {
            flashAddress = tempFlashAddress;
            SetAddress((WORD) left, (WORD) top);
            mask = 0;
            for(x = 0, currentXLocation = 0; x < sizeX; x++)
            {

                // Read 8 pixels from flash
                if(mask == 0)
                {
                    temp = *flashAddress;
                    flashAddress++;
                    mask = 0x01;
                }

                // Set color
                if(mask & temp)
                {
                    SetColor(pallete[1]);
                }
                else
                {
                    SetColor(pallete[0]);
                }

                // Write pixel to screen
                for(stretchX = 0; stretchX < stretch; stretchX++)
                {
#ifdef USE_TRANSPARENT_COLOR
                    if (((GetTransparentColor() == GetColor()) && (GetTransparentColorStatus() == TRANSPARENT_COLOR_ENABLE)))
                    {
                        currentXLocation++;
                        SetAddress(left + currentXLocation , top);
                    }
                    else
#endif              
                    {
                        currentXLocation++;
                        WritePixel(_color);
                    }
                }

                // Shift to the next pixel
                mask <<= 1;
            }

            top++;
        }
    }

    DisplayDisable();
}

/*********************************************************************
* Function: void PutImage4BPP(SHORT left, SHORT top, FLASH_BYTE* image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
* PreCondition: none
* Input: left,top - left top image corner,
*        image - image pointer,
*        stretch - image stretch factor
*        pPartialImageData - (currently not implemented in this driver)
* Output: none
* Side Effects: none
* Overview: outputs 16 color image starting from left,top coordinates
* Note: image must be located in flash
********************************************************************/
void PutImage4BPP(SHORT left, SHORT top, FLASH_BYTE *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
{
    register FLASH_BYTE *flashAddress;
    register FLASH_BYTE *tempFlashAddress;
    WORD                sizeX, sizeY;
    register WORD       x, y, currentXLocation;
    BYTE                temp = 0;
    register BYTE       stretchX, stretchY;
    WORD                pallete[16];
    WORD                counter;

    // Move pointer to size information
    flashAddress = image + 2;

    // Read image size
    sizeY = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;
    sizeX = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;

    // Read pallete
    for(counter = 0; counter < 16; counter++)
    {
        pallete[counter] = *((FLASH_WORD *)flashAddress);
        flashAddress += 2;
    }

    DisplayEnable();
    for(y = 0; y < sizeY; y++)
    {
        tempFlashAddress = flashAddress;
        for(stretchY = 0; stretchY < stretch; stretchY++)
        {
            flashAddress = tempFlashAddress;
            SetAddress(left, top);
            for(x = 0, currentXLocation = 0; x < sizeX; x++)
            {

                // Read 2 pixels from flash
                if(x & 0x0001)
                {

                    // second pixel in byte
                    SetColor(pallete[temp >> 4]);
                }
                else
                {
                    temp = *flashAddress;
                    flashAddress++;

                    // first pixel in byte
                    SetColor(pallete[temp & 0x0f]);
                }

                // Write pixel to screen
                for(stretchX = 0; stretchX < stretch; stretchX++)
                {
#ifdef USE_TRANSPARENT_COLOR
                    if (((GetTransparentColor() == GetColor()) && (GetTransparentColorStatus() == TRANSPARENT_COLOR_ENABLE)))
                    {
                        currentXLocation++;
                        SetAddress(left + currentXLocation, top);
                    }
                    else
#endif
                    {
                        WritePixel(_color);
                        currentXLocation++;
                    }
                }
            }

            top++;
        }
    }

    DisplayDisable();

}

/*********************************************************************
* Function: void PutImage8BPP(SHORT left, SHORT top, FLASH_BYTE* image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
*
* PreCondition: none
*
* Input: left,top - left top image corner,
*        image - image pointer,
*        stretch - image stretch factor
*        pPartialImageData - (currently not implemented in this driver)
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs 256 color image starting from left,top coordinates
*
* Note: image must be located in flash
*
********************************************************************/
void PutImage8BPP(SHORT left, SHORT top, FLASH_BYTE *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
{
    register FLASH_BYTE *flashAddress;
    register FLASH_BYTE *tempFlashAddress;
    WORD                sizeX, sizeY;
    WORD                x, y, currentXLocation;
    BYTE                temp;
    BYTE                stretchX, stretchY;
    WORD                pallete[256];
    WORD                counter;

    // Move pointer to size information
    flashAddress = image + 2;

    // Read image size
    sizeY = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;
    sizeX = *((FLASH_WORD *)flashAddress);
    flashAddress += 2;

    // Read pallete
    for(counter = 0; counter < 256; counter++)
    {
        pallete[counter] = *((FLASH_WORD *)flashAddress);
        flashAddress += 2;
    }

    DisplayEnable();
    for(y = 0; y < sizeY; y++)
    {
        tempFlashAddress = flashAddress;
        for(stretchY = 0; stretchY < stretch; stretchY++)
        {
            flashAddress = tempFlashAddress;
            SetAddress(left, top);
            for(x = 0, currentXLocation = 0; x < sizeX; x++)
            {

                // Read pixels from flash
                temp = *flashAddress;
                flashAddress++;

                // Set color
                SetColor(pallete[temp]);

                // Write pixel to screen
                for(stretchX = 0; stretchX < stretch; stretchX++)
                {
#ifdef USE_TRANSPARENT_COLOR
                    if (((GetTransparentColor() == GetColor()) && (GetTransparentColorStatus() == TRANSPARENT_COLOR_ENABLE)))
                    {
                        currentXLocation++;
                        SetAddress(left + currentXLocation, top);
                    }
                    else
#endif
                    {
                        WritePixel(_color);
                        currentXLocation++;
                    }
                }
            }

            top++;
        }
    }

    DisplayDisable();
}

/*********************************************************************
* Function: void PutImage16BPP(SHORT left, SHORT top, FLASH_BYTE* image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
*
* PreCondition: none
*
* Input: left,top - left top image corner,
*        image - image pointer,
*        stretch - image stretch factor
*        pPartialImageData - (currently not implemented in this driver)
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs hicolor image starting from left,top coordinates
*
* Note: image must be located in flash
*
********************************************************************/
void PutImage16BPP(SHORT left, SHORT top, FLASH_BYTE *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
{
    register FLASH_WORD *flashAddress;
    register FLASH_WORD *tempFlashAddress;
    WORD                sizeX, sizeY;
    register WORD       x, y, currentXLocation;
    WORD                temp;
    register BYTE       stretchX, stretchY;

    // Move pointer to size information
    flashAddress = (FLASH_WORD *)image + 1;

    // Read image size
    sizeY = *flashAddress;
    flashAddress++;
    sizeX = *flashAddress;
    flashAddress++;

    DisplayEnable();
    for(y = 0; y < sizeY; y++)
    {
        tempFlashAddress = flashAddress;
        for(stretchY = 0; stretchY < stretch; stretchY++)
        {
            flashAddress = tempFlashAddress;
            SetAddress(left, top);
            for(x = 0, currentXLocation = 0; x < sizeX; x++)
            {

                // Read pixels from flash
                temp = *flashAddress;
                flashAddress++;

                // Set color
                SetColor(temp);

                // Write pixel to screen
                for(stretchX = 0; stretchX < stretch; stretchX++)
                {
#ifdef USE_TRANSPARENT_COLOR
                    if (((GetTransparentColor() == GetColor()) && (GetTransparentColorStatus() == TRANSPARENT_COLOR_ENABLE)))
                    {
                        currentXLocation++;
                        SetAddress(left + currentXLocation, top);
                    }
                    else
#endif
                    {
                        WritePixel(_color);
                        currentXLocation++;
                    }
                }
            }

            top++;
        }
    }

    DisplayDisable();
}

    #endif // USE_BITMAP_FLASH
    #ifdef USE_BITMAP_EXTERNAL


/*********************************************************************
* Function: void PutImage1BPPExt(SHORT left, SHORT top, void* image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
*
* PreCondition: none
*
* Input: left,top - left top image corner,
*        image - image pointer,
*        stretch - image stretch factor
*        pPartialImageData - (currently not implemented in this driver)
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs monochrome image starting from left,top coordinates
*
* Note: image must be located in external memory
*
********************************************************************/
void PutImage1BPPExt(SHORT left, SHORT top, void *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
{
    register DWORD  memOffset;
    BITMAP_HEADER   bmp;
    WORD            pallete[2];
    BYTE            lineBuffer[((GetMaxX() + 1) / 8) + 1];
    BYTE            *pData;
    SHORT           byteWidth;

    BYTE            temp = 0;
    BYTE            mask;
    WORD            sizeX, sizeY;
    WORD            x, y, currentXLocation;
    BYTE            stretchX, stretchY;

    // Get image header
    ExternalMemoryCallback(image, 0, sizeof(BITMAP_HEADER), &bmp);

    // Get pallete (2 entries)
    ExternalMemoryCallback(image, sizeof(BITMAP_HEADER), 2 * sizeof(WORD), pallete);

    // Set offset to the image data
    memOffset = sizeof(BITMAP_HEADER) + 2 * sizeof(WORD);

    // Line width in bytes
    byteWidth = bmp.width >> 3;
    if(bmp.width & 0x0007)
        byteWidth++;

    // Get size
    sizeX = bmp.width;
    sizeY = bmp.height;

    for(y = 0; y < sizeY; y++)
    {

        // Get line
        ExternalMemoryCallback(image, memOffset, byteWidth, lineBuffer);
        memOffset += byteWidth;
        DisplayEnable();
        for(stretchY = 0; stretchY < stretch; stretchY++)
        {
            pData = lineBuffer;
            SetAddress(left, top);
            mask = 0;
            for(x = 0, currentXLocation = 0; x < sizeX; x++)
            {

                // Read 8 pixels from flash
                if(mask == 0)
                {
                    temp = *pData++;
                    mask = 0x01;
                }

                // Set color
                if(mask & temp)
                {
                    SetColor(pallete[1]);
                }
                else
                {
                    SetColor(pallete[0]);
                }

                // Write pixel to screen
                for(stretchX = 0; stretchX < stretch; stretchX++)
                {
#ifdef USE_TRANSPARENT_COLOR
                    if (((GetTransparentColor() == GetColor()) && (GetTransparentColorStatus() == TRANSPARENT_COLOR_ENABLE)))
                    {
                        currentXLocation++;
                        SetAddress(left + currentXLocation, top);
                    }
                    else
#endif
                    {
                        WritePixel(_color);
                        currentXLocation++;
                    }
                }

                // Shift to the next pixel
                mask <<= 1;
            }

            top++;
        }

        DisplayDisable();
    }
}

/*********************************************************************
* Function: void PutImage4BPPExt(SHORT left, SHORT top, void* image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
*
* PreCondition: none
*
* Input: left,top - left top image corner,
*        image - image pointer,
*        stretch - image stretch factor
*        pPartialImageData - (currently not implemented in this driver)
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs monochrome image starting from left,top coordinates
*
* Note: image must be located in external memory
*
********************************************************************/
void PutImage4BPPExt(SHORT left, SHORT top, void *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
{
    register DWORD  memOffset;
    BITMAP_HEADER   bmp;
    WORD            pallete[16];
    BYTE            lineBuffer[((GetMaxX() + 1) / 2) + 1];
    BYTE            *pData;
    SHORT           byteWidth;

    BYTE            temp = 0;
    WORD            sizeX, sizeY;
    WORD            x, y, currentXLocation;
    BYTE            stretchX, stretchY;

    // Get image header
    ExternalMemoryCallback(image, 0, sizeof(BITMAP_HEADER), &bmp);

    // Get pallete (16 entries)
    ExternalMemoryCallback(image, sizeof(BITMAP_HEADER), 16 * sizeof(WORD), pallete);

    // Set offset to the image data
    memOffset = sizeof(BITMAP_HEADER) + 16 * sizeof(WORD);

    // Line width in bytes
    byteWidth = bmp.width >> 1;
    if(bmp.width & 0x0001)
        byteWidth++;

    // Get size
    sizeX = bmp.width;
    sizeY = bmp.height;

    for(y = 0; y < sizeY; y++)
    {

        // Get line
        ExternalMemoryCallback(image, memOffset, byteWidth, lineBuffer);
        memOffset += byteWidth;
        DisplayEnable();
        for(stretchY = 0; stretchY < stretch; stretchY++)
        {
            pData = lineBuffer;
            SetAddress(left, top);

            for(x = 0, currentXLocation = 0; x < sizeX; x++)
            {

                // Read 2 pixels from flash
                if(x & 0x0001)
                {

                    // second pixel in byte
                    SetColor(pallete[temp >> 4]);
                }
                else
                {
                    temp = *pData++;

                    // first pixel in byte
                    SetColor(pallete[temp & 0x0f]);
                }

                // Write pixel to screen
                for(stretchX = 0; stretchX < stretch; stretchX++)
                {
#ifdef USE_TRANSPARENT_COLOR
                    if (((GetTransparentColor() == GetColor()) && (GetTransparentColorStatus() == TRANSPARENT_COLOR_ENABLE)))
                    {
                        currentXLocation++;
                        SetAddress(left + currentXLocation, top);
                    }
                    else
#endif
                    {
                        WritePixel(_color);
                        currentXLocation++;
                    }
                }
            }

            top++;
        }

        DisplayDisable();
    }
}

/*********************************************************************
* Function: void PutImage8BPPExt(SHORT left, SHORT top, void* image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
*
* PreCondition: none
*
* Input: left,top - left top image corner,
*        image - image pointer,
*        stretch - image stretch factor
*        pPartialImageData - (currently not implemented in this driver)
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs monochrome image starting from left,top coordinates
*
* Note: image must be located in external memory
*
********************************************************************/
void PutImage8BPPExt(SHORT left, SHORT top, void *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
{
    register DWORD  memOffset;
    BITMAP_HEADER   bmp;
    WORD            pallete[256];
    BYTE            lineBuffer[(GetMaxX() + 1)];
    BYTE            *pData;

    BYTE            temp;
    WORD            sizeX, sizeY;
    WORD            x, y, currentXLocation;
    BYTE            stretchX, stretchY;

    // Get image header
    ExternalMemoryCallback(image, 0, sizeof(BITMAP_HEADER), &bmp);

    // Get pallete (256 entries)
    ExternalMemoryCallback(image, sizeof(BITMAP_HEADER), 256 * sizeof(WORD), pallete);

    // Set offset to the image data
    memOffset = sizeof(BITMAP_HEADER) + 256 * sizeof(WORD);

    // Get size
    sizeX = bmp.width;
    sizeY = bmp.height;

    for(y = 0; y < sizeY; y++)
    {

        // Get line
        ExternalMemoryCallback(image, memOffset, sizeX, lineBuffer);
        memOffset += sizeX;
        DisplayEnable();
        for(stretchY = 0; stretchY < stretch; stretchY++)
        {
            pData = lineBuffer;
            SetAddress(left, top);

            for(x = 0, currentXLocation = 0; x < sizeX; x++)
            {
                temp = *pData++;
                SetColor(pallete[temp]);

                // Write pixel to screen
                for(stretchX = 0; stretchX < stretch; stretchX++)
                {
#ifdef USE_TRANSPARENT_COLOR
                    if (((GetTransparentColor() == GetColor()) && (GetTransparentColorStatus() == TRANSPARENT_COLOR_ENABLE)))
                    {
                        currentXLocation++;
                        SetAddress(left + currentXLocation, top);
                    }
                    else
#endif
                    {
                        WritePixel(_color);
                        currentXLocation++;
                    }
                }
            }

            top++;
        }

        DisplayDisable();
    }
}

/*********************************************************************
* Function: void PutImage16BPPExt(SHORT left, SHORT top, void* image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
*
* PreCondition: none
*
* Input: left,top - left top image corner,
*        image - image pointer,
*        stretch - image stretch factor
*        pPartialImageData - (currently not implemented in this driver)
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs monochrome image starting from left,top coordinates
*
* Note: image must be located in external memory
*
********************************************************************/
void PutImage16BPPExt(SHORT left, SHORT top, void *image, BYTE stretch, PUTIMAGE_PARAM *pPartialImageData)
{
    register DWORD  memOffset;
    BITMAP_HEADER   bmp;
    WORD            lineBuffer[(GetMaxX() + 1)];
    WORD            *pData;
    WORD            byteWidth;

    WORD            temp;
    WORD            sizeX, sizeY;
    WORD            x, y, currentXLocation;
    BYTE            stretchX, stretchY;

    // Get image header
    ExternalMemoryCallback(image, 0, sizeof(BITMAP_HEADER), &bmp);

    // Set offset to the image data
    memOffset = sizeof(BITMAP_HEADER);

    // Get size
    sizeX = bmp.width;
    sizeY = bmp.height;

    byteWidth = sizeX << 1;

    for(y = 0; y < sizeY; y++)
    {

        // Get line
        ExternalMemoryCallback(image, memOffset, byteWidth, lineBuffer);
        memOffset += byteWidth;
        DisplayEnable();
        for(stretchY = 0; stretchY < stretch; stretchY++)
        {
            pData = lineBuffer;
            SetAddress(left, top);

            for(x = 0, currentXLocation = 0; x < sizeX; x++)
            {
                temp = *pData++;
                SetColor(temp);

                // Write pixel to screen
                for(stretchX = 0; stretchX < stretch; stretchX++)
                {
#ifdef USE_TRANSPARENT_COLOR
                    if (((GetTransparentColor() == GetColor()) && (GetTransparentColorStatus() == TRANSPARENT_COLOR_ENABLE)))
                    {
                        currentXLocation++;
                        SetAddress(left + currentXLocation, top);
                    }
                    else
#endif
                    {
                        WritePixel(_color);
                        currentXLocation++;
                    }
                }
            }

            top++;
        }

        DisplayDisable();
    }
}

    #endif //USE_BITMAP_EXTERNAL
#endif //#ifndef USE_PRIMITIVE_PUTIMAGE

//#endif // #if defined (GFX_USE_DISPLAY_CONTROLLER_ILI9341)

