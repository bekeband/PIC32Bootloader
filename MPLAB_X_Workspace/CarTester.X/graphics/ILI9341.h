#ifndef _ILI9341_H
    #define _ILI9341_H

/*262K color: 18-bit/pixel (RGB 6-6-6 bits input)
 * Send datas R6:2G6:2, B6:2R6:2, G6:2B6:2,... 2 pixels (6 subpixels)
*/
//#define _MDT00

/*262K color: 18-bit/pixel (RGB 6-6-6 bits input)
 * Send datas: R6:2G6:2, B6:2:8, ... 1 pixel (3 subpixels)
*/

#define _MDT01

/*262K color: 18-bit/pixel (RGB 6-6-6 bits input)
 * One pixel (3 sub-pixels) display data is sent by 2 transfers when DBI [2:0]
 * bits of 3Ah register are set to ?110?.*/

//#define _256K_COLOR_MODE

/*65K color: 16-bit/pixel (RGB 5-6-5 bits input)
 * One pixel (3 sub-pixels) display data is sent by 1 transfer when DBI [2:0] bits
 * of 3Ah register are set to ?101?.*/

#define _64K_COLOR_MODE

/* ------------------- Define ILI9341 controller commands. -------------------*/
/*Power control B (CFh)*/
#define PowerControlB  0x0CF
/*  1stParameter 1 1 M XX 0 0 0 0 0 0 0 0 00
 *  2ndParameter 1 1 M XX 1 0 0 Power control[1:0] 0 0 1 81
 *  3rdParameter 1 1 M XX 0 0 1 DC_ena 0 0 0 0 30
*/
/*Power on sequence control (EDh)*/
#define PowerOnSequenceControl 0xED
/*
 *  1stParameter 1 1 M XX X 1 CP1 soft start X 1 CP23 soft start 55
 *  2ndParameter 1 1 M XX X 0 En_vcl X 0 En_ddvdh 01
 *  3rdParameter 1 1 M XX X 0 En_vgh X 0 En_vgl 23
 *  4thParameter 1 1 M XX DDVDH_ENH 0 0 0 0 0 0 1 1
 */

/*Driver timing control A (E8h)*/
#define DriverTimingControlA  0xE8
  /*
  1stParameter 1 1 M XX 1 0 0 0 0 1 0 NOW 84
  2ndParameter 1 1 M XX 0 0 0 EQ 0 0 0 CR 11
  3rdParameter 1 1 M XX 0 1 1 1 1 0 PC[1:0] 7A
   */

  /*Power control A (CBh)*/
  #define PowerControlA  0x0CB
/*  1stParameter 1 1 M XX 0 0 1 1 1 0 0 1 39
    2ndParameter 1 1 M XX 0 0 1 0 1 1 0 0 2C
    3rdParameter 1 1 M XX 0 0 0 0 0 0 0 0 00
    4rdParameter 1 1 M XX 0 0 1 1 0 REG_VD[2:0] 34
    5rdParameter 1 1 M XX 0 0 0 0 0 VBC[2:0] 02
 */
  /*Pump ratio control (F7h)*/

#define PumpRatioControl 0xF7
  /*1 1 M XX X X Ratio[1:0] 0 0 0 0 10*/
/*Driver timing control B (EAh)*/

#define DriverTimingControlB 0xEA

  /*1stParameter 1 1 M XX VG_SW_T4 VG_SW_T3 VG_SW_T2 VG_SW_T1 66
    2ndParameter 1 1 M XX X X X X X X 0 0 00  */

/*Frame Rate Control (In Normal Mode/Full Colors) (B1h)*/
#define FrameRateControlInNormalModeFullColors  0xB1
/*1st Parameter 1 1 M XX 0 0 0 0 0 0 DIVA [1:0] 00
2nd Parameter 1 1 M XX 0 0 0 RTNA [4:0] 1B*/


  /*Display Function Control (B6h)*/
#define DisplayFunctionControl 0xB6
  /*1st Parameter 1 1 M XX 0 0 0 0 PTG [1:0] PT [1:0] 0A
2nd Parameter 1 1 M XX REV GS SS SM ISC [3:0] 82
3rd Parameter 1 1 M XX 0 0 NL [5:0] 27
4th Parameter 1 1 M XX 0 0 PCDIV [5:0] XX*/

  /*Power Control 1 (C0h)*/
#define PowerControl1 0xC0
  /*1stParameter 1 1 M XX 0 0 VRH [5:0] 21*/

  /*Power Control 2 (C1h)*/
#define PowerControl2 0xC1
  /*Parameter 1 1 M XX 0 0 0 0 0 BT [2:0] 10*/

  /*VCOM Control 1(C5h)*/
#define VCOMControl1 0xC5
  /*1st Parameter 1 1 M XX 0 VMH [6:0] 31
2ndParameter 1 1 M XX 0 VML [6:0] 3C*/

  /*VCOM Control 2(C7h)*/
#define VCOMControl2 0xC7
  /*Parameter 1 1 M XX nVM VMF [6:0] C0*/

/*Memory Access Control (36h)*/
#define MemoryAccessControl 0x36
  /*Parameter 1 1 M XX MY MX MV ML BGR MH 0 0 00*/
/*This command makes no change on the other driver status.
Bit Name Description
MY Row Address Order
MX Column Address Order
MV Row / Column Exchange
These 3 bits control MCU to memory write/read direction.
ML Vertical Refresh Order LCD vertical refresh direction control.
BGR RGB-BGR Order
Color selector switch control
(0=RGB color filter panel, 1=BGR color filter panel)
MH Horizontal Refresh ORDER LCD horizontal refreshing direction control.
Note: When BGR bit is changed, the new setting is active immediately without update the content in Frame Memory again.*/

#define MHSET   0b00000100  // Horizontal Refresh ORDER LCD horizontal refreshing direction control.
#define RGBSET  0b00001000  // Color selector switch control (0=RGB color filter panel, 1=BGR color filter panel)
#define MLSET   0b00010000  // Vertical Refresh Order LCD vertical refresh direction control.
#define MVSET   0b00100000  // Row / Column Exchange
#define MXSET   0b01000000  // Column Address Order
#define MYSET   0b10000000  // Row Address Order

#define NORMAL  0b00000000  //
#define YMIRROR 0b10000000
#define XMIRROR 0b01000000
#define XYMIRROR 0b11000000
#define XYCHANGE 0b00100000

/* Display Inversion ON (21h) */
#define DisplayInversionOn 0x21

#define DisplayInversionOff 0x20

/*Enable 3G (F2h)*/
#define Enable3G 0xF2
  /*1stParameter 1 1 M XX 0 0 0 0 0 0 1 3G_enb 02*/
/*Gamma Set (26h)*/
#define GammaSet 0x26
  /*Parameter 1 1 M XX GC [7:0] 01*/

  /*Positive Gamma Correction (E0h)*/

#define PositiveGammaCorrection 0xE0
  /*1st Parameter 1 1 M XX 0 0 0 0 VP63 [3:0] 08
2ndParameter 1 1 M XX 0 0 VP62 [5:0]
3rdParameter 1 1 M XX 0 0 VP61 [5:0]
4th Parameter 1 1 M X 0 0 0 0 VP59 [3:0] 05
5th Parameter 1 1 M XX 0 0 0 VP57 [4:0]
6th Parameter 1 1 M XX 0 0 0 0 VP50 [3:0] 09
7th Parameter 1 1 M XX 0 VP43 [6:0]
8th Parameter 1 1 M XX VP27 [3:0] VP36 [3:0]
9th Parameter 1 1 M XX 0 VP20 [6:0]
10thParameter 1 1 M XX 0 0 0 0 VP13 [3:0] 0B
11thParameter 1 1 M XX 0 0 0 VP6 [4:0]
12thParameter 1 1 M XX 0 0 0 0 VP4 [3:0] 00
13thParameter 1 1 M XX 0 0 VP2 [5:0]
14thParameter 1 1 M XX 0 0 VP1 [5:0]
15thParameter 1 1 M XX 0 0 0 0 VP0 [3:0] 00*/

  /*Negative Gamma Correction (E1h)*/
#define NegativeGammaCorrection 0xE1

  /*1st Parameter 1 1 M XX 0 0 0 0 VN63 [3:0] 08
2ndParameter 1 1 M XX 0 0 VN62 [5:0]
3rdParameter 1 1 M XX 0 0 VN61 [5:0]
4th Parameter 1 1 M XX 0 0 0 0 VN59 [3:0] 07
5th Parameter 1 1 M XX 0 0 0 VN57 [4:0]
6th Parameter 1 1 M XX 0 0 0 0 VN50 [3:0] 05
7th Parameter 1 1 M XX 0 VN43 [6:0]
8th Parameter 1 1 M XX VN36 [3:0] VN27 [3:0]
9th Parameter 1 1 M XX 0 VN20 [6:0]
10thParameter 1 1 M XX 0 0 0 0 VN13 [3:0] 04
11thParameter 1 1 M XX 0 0 0 VN6 [4:0]
12thParameter 1 1 M XX 0 0 0 0 VN4 [3:0] 0F
13thParameter 1 1 M XX 0 0 VN2 [5:0]
14thParameter 1 1 M XX 0 0 VN1 [5:0]
15thParameter 1 1 M XX 0 0 0 0 VN0 [3:0] 0F*/

/* Sleep Out (11h)*/
#define SleepOut 0x11

  /*Display ON (29h)*/
#define DisplayOn   0x29

  /*Display OFF (28h)*/
#define DisplayOff  0x28

  /*Enter Sleep Mode (10h)*/
#define EnterSleepMode 0x10

  /*Page Address Set (2Bh)*/
#define PageAddressSet 0x2B
/*1st Parameter 1 1 M XX SP15 SP14 SP13 SP12 SP11 SP10 SP9 SP8
2ndParameter 1 1 M XX SP7 SP6 SP5 SP4 SP3 SP2 SP1 SP0
Note1
3rdParameter 1 1 M XX EP15 EP14 EP13 EP12 EP11 EP10 EP9 EP8
4th Parameter 1 1 M XX EP7 EP6 EP5 EP4 EP3 EP2 EP1 EP0
Note1*/

  /*Column Address Set (2Ah)*/
#define ColumnAddressSet    0x2a
  /*1st Parameter 1 1 M XX SC15 SC14 SC13 SC12 SC11 SC10 SC9 SC8
2ndParameter 1 1 M XX SC7 SC6 SC5 SC4 SC3 SC2 SC1 SC0
Note1
3rd Parameter 1 1 M XX EC15 EC14 EC13 EC12 EC11 EC10 EC9 EC8
4th Parameter 1 1 M XX EC7 EC6 EC5 EC4 EC3 EC2 EC1 EC0
Note1*/
  /*Memory Write (2Ch)*/
#define MemoryWrite         0x2c
  /*1st Parameter 1 1 M D1 [17:0] XX
: 1 1 M Dx [17:0] XX
Nth Parameter 1 1 M Dn [17:0] XX*/

  /*Memory Access Control (36h)*/
#define MemoryAccessControl     0x36
  /*Parameter 1 1 M XX MY MX MV ML BGR MH 0 0 00*/

  /*Write Display Brightness (51h)*/
#define WriteDisplayBrightness  0x51
/*Parameter 1 1 M XX DBV[7] DBV[6] DBV[5] DBV[4] DBV[3] DBV[2] DBV[1] DBV[0] 00*/

  /*COLMOD: Pixel Format Set (3Ah)*/
#define PixelFormatSet 0x3A
/*Parameter 1 1 M XX 0 DPI [2:0] 0 DBI [2:0] 66*/
/*This command sets the pixel format for the RGB image data used by the interface.
 * DPI [2:0] is the pixel format select of RGB interface and DBI [2:0] is the
 * pixel format of MCU interface. If a particular interface, either RGB interface
 * or MCU interface, is not used then the corresponding bits in the parameter are
 * ignored. The pixel format is shown in the table below.
DPI [2:0] RGB Interface Format DBI [2:0] MCU Interface Format
0 0 0 Reserved 0 0 0 Reserved
0 0 1 Reserved 0 0 1 Reserved
0 1 0 Reserved 0 1 0 Reserved
0 1 1 Reserved 0 1 1 Reserved
1 0 0 Reserved 1 0 0 Reserved
1 0 1 16 bits / pixel 1 0 1 16 bits / pixel
1 1 0 18 bits / pixel 1 1 0 18 bits / pixel
1 1 1 Reserved 1 1 1 Reserved
If using RGB Interface must selection serial interface.*/

  /*Write Display Brightness (51h)*/
#define WriteDisplayBrightness  0x51
/*Parameter 1 1 M XX DBV[7] DBV[6] DBV[5] DBV[4] DBV[3] DBV[2] DBV[1] DBV[0] 00*/

  /*COLMOD: Pixel Format Set (3Ah)*/
#define PixelFormatSet 0x3A
/*Parameter 1 1 M XX 0 DPI [2:0] 0 DBI [2:0] 66*/
/*This command sets the pixel format for the RGB image data used by the interface.
 * DPI [2:0] is the pixel format select of RGB interface and DBI [2:0] is the
 * pixel format of MCU interface. If a particular interface, either RGB interface
 * or MCU interface, is not used then the corresponding bits in the parameter are
 * ignored. The pixel format is shown in the table below.
DPI [2:0] RGB Interface Format DBI [2:0] MCU Interface Format
0 0 0 Reserved 0 0 0 Reserved
0 0 1 Reserved 0 0 1 Reserved
0 1 0 Reserved 0 1 0 Reserved
0 1 1 Reserved 0 1 1 Reserved
1 0 0 Reserved 1 0 0 Reserved
1 0 1 16 bits / pixel 1 0 1 16 bits / pixel
1 1 0 18 bits / pixel 1 1 0 18 bits / pixel
1 1 1 Reserved 1 1 1 Reserved
If using RGB Interface must selection serial interface.*/

#define BITPERPIXEL16 0x55
#define BITPERPIXEL18 0x66

    /*Interface Control (F6h)*/
#define InterfaceControl  0xF6
#define MDT00 0b00
#define MDT01 0b01
#define MDT10 0b10
#define MDT11 0b11


#define DISP_HOR_RESOLUTION
/*    #include "HWP_MIKROE_PIC32_GP_SK_16PMP.h"
    #include "GraphicsConfig.h"
    #include "GenericTypeDefs.h"*/

    #ifndef DISP_HOR_RESOLUTION
        #error DISP_HOR_RESOLUTION must be defined in HardwareProfile.h
    #endif
    #ifndef DISP_VER_RESOLUTION
        #error DISP_VER_RESOLUTION must be defined in HardwareProfile.h
    #endif
    #ifndef COLOR_DEPTH
        #error COLOR_DEPTH must be defined in GraphicsConfig.h
    #endif
    #ifndef DISP_ORIENTATION
        #error DISP_ORIENTATION must be defined in HardwareProfile.h
    #endif

/*********************************************************************
* Overview: Horizontal and vertical screen size.
*********************************************************************/
    #if (DISP_HOR_RESOLUTION != 240)
        #error "This driver doesn't supports this resolution. Horizontal resolution must be 240 pixels."
    #endif
    #if (DISP_VER_RESOLUTION != 320)
        #error "This driver doesn't supports this resolution. Vertical resolution must be 320 pixels."
    #endif

/*********************************************************************
* Overview: Display orientation.
*********************************************************************/
    #if (DISP_ORIENTATION != 0) && (DISP_ORIENTATION != 90)
        #error "This driver doesn't support this orientation."
    #endif

/*********************************************************************
* Overview: Color depth.
*********************************************************************/
    #if (COLOR_DEPTH != 16)
//        #error "This driver doesn't support this color depth. It should be 16."
    #endif

/*********************************************************************
* Macros: SetPalette(colorNum, color)
*
* Overview:  Sets palette register.
*
* PreCondition: none
*
* Input: colorNum - Register number.
*        color - Color.
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
    #define SetPalette(colorNum, color)

/* ILI9341 independent features command codes. */
#define ColumnAddressSet    0x2a
#define MemoryWrite         0x2c
#define MemoryAccessControl     0x36
#define WriteDisplayBrightness  0x51

#define DEVICE_CODE_READ_REG    0x00
#define SOFT_RESET_REG  0x01
#define IDENTINFO_R_REG 0x04
#define STATUS_R_REG    0x09
#define POWERMODE_R_REG 0x0A
#define MADCTL_R_REG    0x0B
#define PIXFORMAT_R_REG 0x0C
#define IMGFORMAT_R_REG 0x0D
#define SIGMODE_R_REG   0x0E
#define SD_RESULT_R_REG 0x0F
#define SLEEP_ENTER_REG 0x10
#define SLEEP_OUT_REG   0x11
#define PARTIALMODE_REG 0x12
#define NORDISPMODE_REG 0x13
#define INVERSIONOFF_REG  0x20
#define INVERSIONON_REG 0x21
#define GAMMASET_REG    0x26
#define DISPLAYOFF_REG  0x28
#define DISPLAYON_REG   0x29
#define COLADDRSET_REG  0x2A
#define PAGEADDRSET_REG 0x2B
#define MEMORYWRITE_REG 0x2C
#define COLORSET_REG    0x2D
#define MEMORYREAD_REG  0x2E
#define PARTIALAREA_REG 0x30
#define VERTSCROLL_REG  0x33
#define TEAREFFECTLINEOFF_REG 0x34
#define TEAREFFECTLINEON_REG  0x35
//#define MEMACCESS_REG   0x36
#define VERSCRSRART_REG 0x37
#define IDLEMODEOFF_REG 0x38
#define IDLEMODEON_REG  0x39
#define PIXFORMATSET_REG  0x3A
#define WRITEMEMCONTINUE_REG  0x3C
#define READMEMCONTINUE_REG 0x3E
#define SETTEATSCAN_REG 0x44
#define GETSCANLINE_REG 0x45
#define WRITEBRIGHT_REG 0x51
#define READBRIGHT_REG  0x52
#define WRITECTRL_REG   0x53
#define READCTRL_REG    0x54
#define WRITECABC_REG   0x55
#define READCABC_REG    0x56
#define WRITECABCMB_REG 0x5E
#define READCABCMB_REG  0x5F
#define RGB_ISCTL_REG   0xB0
#define FRAMECTL_NOR_REG  0xB1
#define FRAMECTL_IDLE_REG 0xB2
#define FRAMECTL_PARTIAL_REG  0xB3
#define INVERCTL_REG    0xB4
#define BLANKPORCTL_REG 0xB5
#define FUNCTONCTL_REG  0xB6
#define ENTRYMODE_REG   0xB7
#define BLIGHTCTL1_REG  0xB8
#define BLIGHTCTL2_REG  0xB9
#define BLIGHTCTL3_REG  0xBA
#define BLIGHTCTL4_REG  0xBB
#define BLIGHTCTL5_REG  0xBC
#define BLIGHTCTL7_REG  0xBE
#define BLIGHTCTL8_REG  0xBF
#define POWERCTL1_REG   0xC0
#define POWERCTL2_REG   0xC1
#define VCOMCTL1_REG    0xC5
#define VCOMCTL2_REG    0xC7
#define POWERCTLA_REG   0xCB
#define POWERCTLB_REG   0xCF
#define NVMEMWRITE_REG  0xD0
#define NVMEMPROTECTKEY_REG 0xD1
#define NVMEMSTATUS_REG 0xD2
#define READID4_REG     0xD3
#define READID1_REG     0xDA
#define READID2_REG     0xDB
#define READID3_REG     0xDC
#define POSGAMMACORRECTION_REG  0xE0
#define NEGGAMMACORRECTION_REG  0xE1
#define DIGGAMCTL1_REG  0xE2
#define DIGGAMCTL2_REG  0xE3
#define DIVTIMCTL_A_REG 0xE8
#define DIVTIMCTL_B_REG 0xEA
#define POWONSEQCTL_REG 0xED
#define ENABLE_3G_REG   0xF2
#define INTERFCTL_REG   0xF6
#define PUMPRATIOCTL_REG  0xF7

typedef union {
  struct {
    unsigned B : 5; // 32
    unsigned G : 6; // 64
    unsigned R : 5; // 32
  };
  struct {
    unsigned D16 : 16;
  };
} C565;

/* Typedef of one pixel derivating of the ILI controller color mode.  */

typedef union {

#if defined (_256K_COLOR_MODE)
  struct {
    unsigned G : 8;
    unsigned R : 8;
    unsigned :8;
    unsigned B : 8;
  };
  struct {
    unsigned L16 : 16;
    unsigned H16 : 16;
  };
  struct {
    unsigned D32 : 32;
  };

#elif defined (_64K_COLOR_MODE)
  struct {
    unsigned B : 5; // 32
    unsigned G : 6; // 64
    unsigned R : 5; // 32
  };
  struct {
    unsigned D16 : 16;
  };
#else
#error "Must be defined color mode !"
#endif
} RGBPIXEL;

#if defined (_256K_COLOR_MODE)

  /* union to RGB pixel out in MODE00 state. */
    typedef union {
    struct {
      unsigned A16 : 16;
      unsigned B16 : 16;
      unsigned C16 : 16;
    };
    struct {
      unsigned AL8 : 8;
      unsigned AH8 : 8;
      unsigned BL8 : 8;
      unsigned BH8 : 8;
      unsigned CL8 : 8;
      unsigned CH8 : 8;
    };
  } MODE00_STRUCT;

  /* union to RGB pixel out in MODE01 state. */
    typedef union {
    struct {
      unsigned A16 : 16;
      unsigned B16 : 16;
    };
    struct {
      unsigned AL8 : 8;
      unsigned AH8 : 8;
      unsigned : 8;
      unsigned BH8 : 8;
    };
  } MODE01_STRUCT;

#endif


#endif // _HX8347_H
