/* 
 * File:   HardwareProfile_MIKROMEDIAPIC32MX.h
 * Author: Tulajdonos
 *
 * Created on 2014. május 28., 14:46
 */

#ifndef HARDWAREPROFILE_MIKROMEDIAPIC32MX_H
#define	HARDWAREPROFILE_MIKROMEDIAPIC32MX_H

#ifdef	__cplusplus
extern "C" {
#endif

/*********************************************************************
* Hardwareprofile for Mikroelectronika PIC32MX
 * Compact development system rich with on-board peripherals for all-round
 * multimedia development on PIC32MX460F512L device.
 * WARNING the device contains
 * newest LCD driver that called ILI9341 LCD driver !!!
*********************************************************************/
    #include "../Compiler.h"

/*********************************************************************
* GetSystemClock() returns system clock frequency.
* GetPeripheralClock() returns peripheral clock frequency.
* GetInstructionClock() returns instruction clock frequency.
********************************************************************/

/*********************************************************************
* START OF GRAPHICS RELATED MACROS
********************************************************************/

/*********************************************************************
* PARALLEL MASTER PORT INTERFACE TIMING FOR TFT MODULE
*********************************************************************
 *WAITB<1:0>: Data Setup to Read/Write Strobe Wait States bits(1)
11 = Data wait of 4 TPB; multiplexed address phase of 4 TPB
10 = Data wait of 3 TPB; multiplexed address phase of 3 TPB
01 = Data wait of 2 TPB; multiplexed address phase of 2 TPB
00 = Data wait of 1 TPB; multiplexed address phase of 1 TPB (default)*/

  #define PMP_Data_Setup_Wait_States                0b11

/*WAITM<3:0>: Data Read/Write Strobe Wait States bits(1)
1111 = Wait of 16 TPB
?
?
?
0001 = Wait of 2 TPB
0000 = Wait of 1 TPB (default)*/
  #define PMP_Data_Strobe_Wait_States               0b1111

/*WAITE<1:0>: Data Hold After Read/Write Strobe Wait States bits(1)
11 = Wait of 4 TPB
10 = Wait of 3 TPB
01 = Wait of 2 TPB
00 = Wait of 1 TPB (default)
For read operations:
11 = Wait of 3 TPB
10 = Wait of 2 TPB
01 = Wait of 1 TPB
00 = Wait of 0 TPB (default)*/
  #define PMP_Data_Hold_After_Write_Strobe_Wait_States        0b11

/*********************************************************************
* External Memory Programmer Settings
*********************************************************************/
/*
    USE_COMM_PKT_MEDIA_SERIAL_PORT - to use UART port as the flash programming port
    USE_COMM_PKT_MEDIA_USB - to use USB port as the flash programming port

    When non of the two are defined prior to this check, the default
    programming port is used.
    EXPLORER_16 - uses UART as default port
    PIC24FJ256DA210_DEV_BOARD - use USB as the default port
    PIC_SK, MEB_BOARD - use USB as the default port

*/
// error checks
#if defined (USE_COMM_PKT_MEDIA_SERIAL_PORT) && defined (USE_COMM_PKT_MEDIA_USB)
    #error "Cannot have two programming ports"
#endif

#if !defined (USE_COMM_PKT_MEDIA_SERIAL_PORT)
    // assign the default external flash programming port
    #if defined (EXPLORER_16)
        #define USE_COMM_PKT_MEDIA_SERIAL_PORT
        #define BAUDRATE2               115200UL
        #define BRG_DIV2                4
        #define BRGH2                   1
    #endif
#else
        #define BAUDRATE2               115200UL
        #define BRG_DIV2                4
        #define BRGH2                   1
#endif

#if !defined (USE_COMM_PKT_MEDIA_USB)
	// assign the default external flash programming port
    #if defined (PIC24FJ256DA210_DEV_BOARD)      || \
        (defined (MEB_BOARD) && defined (_USB))  || \
        (defined (PIC_SK) && defined (_USB))   || \
        (defined (PIC_SK) && defined (__dsPIC33EP512MU810__)) || \
        (defined (PIC_SK) && defined (__PIC24EP512GU810__))

        #define USE_COMM_PKT_MEDIA_USB
        //#define USE_SELF_POWER_SENSE_IO
        #define tris_self_power     TRISAbits.TRISA2    // Input
        #define self_power          1

        //#define USE_USB_BUS_SENSE_IO
        #define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
        #define USB_BUS_SENSE       U1OTGSTATbits.SESVD // Special considerations required if using SESVD for this purpose.  See documentation.
    #endif
#else
        //#define USE_SELF_POWER_SENSE_IO
        #define tris_self_power     TRISAbits.TRISA2    // Input
        #define self_power          1

        //#define USE_USB_BUS_SENSE_IO
        #define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
        #define USB_BUS_SENSE       U1OTGSTATbits.SESVD // Special considerations required if using SESVD for this purpose.  See documentation.
#endif

// set the default packet size
#if defined (USE_COMM_PKT_MEDIA_USB) || defined (USE_COMM_PKT_MEDIA_SERIAL_PORT)
    #if !defined (COMM_PKT_RX_MAX_SIZE)
        #define COMM_PKT_RX_MAX_SIZE    (1024)
    #endif
#endif

/*********************************************************************
* HARDWARE DEVICES SELECTION
*********************************************************************/
/*
    This portion selects the different components available to
    the application depending on the hardware platform selected.
    * EXPLORER_16 - Explorer 16 Development Board (DM240001)
    * PIC24FJ256DA210_DEV_BOARD - PIC24FJ256DA210 Development Board (DM240312)
    * GFX_PICTAIL_V3 - Graphics LCD Controller PICtail Plus SSD1926 Board (AC164127-5)
    * GFX_PICTAIL_V3E - Graphics LCD Controller PICtail Plus Epson S1D13517 Board (AC164127-7)
    * MEB_BOARD - MultiMedia Expansion Board (DM320005)
*/
       #define      USE_M25P80                        // use the 16 Mbit SPI Serial Flash
       #define      USE_TOUCHSCREEN_RESISTIVE         // use 4-wire resistive touch screen driver
/* Touchscreen debug enabled define. */
//       #define      ENABLE_DEBUG_TOUCHSCREEN
//       #define      TOUCH_MUST_CALIBRATION

/*********************************************************************
* DISPLAY PARAMETERS
*********************************************************************/
/*
    The following are the parameters required for the
    different display drivers that is supported.
    When adding support to a new display controller or display panel,
    follow the parameterization of the driver for reusability of the
    driver.

    Display Parameter Macros Descriptions:

    1. DISP_ORIENTATION - defines the display rotation with
            respect to its native orientation. For example, if the display
            has a resolution specifications that says 240x320 (QVGA), the
            display is natively in portrait mode. If the application
            uses the display in landscape mode (320x240), then the
            orientation musts be defined as 90 or 180 degree rotation.
            The Graphics Library will calculate the actual pixel location
            to rotate the contents of the screen. So when users view the
            display, the image on the screen will come out in the correct
            orientation.

            Valid values: 0, 90, 180 and 270
            Example: #define DISP_ORIENTATION 90

    2. DISP_HOR_RESOLUTION - defines the horizontal dimension in pixels. This
            is the native horizontal dimension of the screen. In the example
            given in DISP_ORIENTATION, a 320x240 display will have DISP_HOR_RESOLUTION
            of 320.

            Valid Values: dependent on the display glass resolution used.
            Example: #define DISP_HOR_RESOLUTION 320

    3. DISP_VER_RESOLUTION - defines the vertical dimension in pixels. This
            is the native vertical dimension of the screen. In the example
            given in DISP_ORIENTATION, a 320x240 display will have DISP_VER_RESOLUTION
            of 240.

            Valid Values: dependent on the display glass resolution used.
            Example: #define DISP_VER_RESOLUTION 240

    4. COLOR_DEPTH - (NOTE: Define this macro in the GraphicsConfig.h
             This defines the vertical dimension in pixels.

            Valid Values: 1, 4, 8, 16, 24 (note 24 bpp is only used if you are
                          using a Display Driver that supports 24 bpp color depth.
            Example: #define COLOR_DEPTH 16

    5. DISP_DATA_WIDTH - this defines the display controller physical interface
            to the display panel.

            Valid Values: 1, 4, 8, 16, 18, 24
                          1, 4, 8 are usually used in MSTN and CSTN displays
                          16, 18 and 24 are usually used in TFT displays.
            Example: #define DISP_DATA_WIDTH 18

    6. DISP_INV_LSHIFT - this indicates that the color data is sampled in the
            falling edge of the pixel clock.

            Example: #define DISP_INV_LSHIFT - define this to sample the
                          color data in the falling edge of the pixel clock.

    7. DISP_HOR_PULSE_WIDTH - this defines the horizontal sync signal pulse width.

            Valid Values: See display panel data sheet
            Example: #define DISP_HOR_PULSE_WIDTH 25

    8. DISP_VER_PULSE_WIDTH - this defines the vertical sync signal pulse width.

            Valid Values: See display panel data sheet
            Example: #define DISP_VER_PULSE_WIDTH 4

    9. DISP_HOR_BACK_PORCH - this defines the horizontal back porch.
            DISP_HOR_BACK_PORCH + DISP_HOR_FRONT_PORCH + DISP_HOR_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet
            Example: #define DISP_HOR_BACK_PORCH 5

    10. DISP_HOR_FRONT_PORCH - this defines the horizontal front porch.
            DISP_HOR_BACK_PORCH + DISP_HOR_FRONT_PORCH + DISP_HOR_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet
            Example: #define DISP_HOR_FRONT_PORCH 10

    11. DISP_VER_BACK_PORCH - this defines the vertical back porch.
            DISP_VER_BACK_PORCH + DISP_VER_FRONT_PORCH + DISP_VER_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet
            Example: #define DISP_VER_BACK_PORCH 0

    12. DISP_VER_FRONT_PORCH - this defines the horizontal front porch.
            DISP_VER_BACK_PORCH + DISP_VER_FRONT_PORCH + DISP_VER_PULSE_WIDTH
            makes up the horizontal blanking period.

            Valid Values: See display panel data sheet
            Example: #define DISP_VER_FRONT_PORCH 2

    13. GFX_LCD_TYPE - this defines the type of display glass used.

            Valid Values: Dependent on the display controller supported LCD types.
                          GFX_LCD_TFT  // Type TFT Display
                          GFX_LCD_CSTN // Type Color STN Display
                          GFX_LCD_MSTN // Type Mono STN Display
                          GFX_LCD_OLED // Type OLED Display

            Example: #define GFX_LCD_TYPE GFX_LCD_TFT

    14. GFX_DISPLAYENABLE_ENABLE - this enables the use of the Display Enable Port
            (GEN) when using the Microchip Graphics Module. The signal required when
            using a display panel that supports DATA ENABLE Mode. DATA ENABLE Mode
            is used when the display panel do not have sync (HSYNC and VSYNC) signals.

            Example: #define GFX_DISPLAYENABLE_ENABLE

    15. GFX_DISPLAYENABLE_POLARITY - this sets the polarity of the Display Enable Port
            (GEN) when using the Microchip Graphics Module.

            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_DISPLAYENABLE_POLARITY GFX_ACTIVE_HIGH

    16. GFX_HSYNC_ENABLE - this enables the use of the Display Horizontal Synchronization
            Port (HSYNC) when using the Microchip Graphics Module. The signal required when
            using a display panel that supports SYNC Mode. SYNC Mode
            is used when the display panel has sync (HSYNC and VSYNC) signals.

            Example: #define GFX_HSYNC_ENABLE

    17. GFX_HSYNC_POLARITY - this sets the polarity of the Display Horizontal Synchronization
            Port (HSYNC)when using the Microchip Graphics Module.

            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_HSYNC_POLARITY GFX_ACTIVE_LOW

    18. GFX_VSYNC_ENABLE - this enables the use of the Display Vertical Synchronization
            Port (VSYNC) when using the Microchip Graphics Module. The signal required when
            using a display panel that supports SYNC Mode. SYNC Mode
            is used when the display panel has sync (HSYNC and VSYNC) signals.

            Example: #define GFX_VSYNC_ENABLE

    19. GFX_VSYNC_POLARITY - this sets the polarity of the Display Vertical Synchronization
            Port (VSYNC)when using the Microchip Graphics Module.

            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_VSYNC_POLARITY GFX_ACTIVE_LOW

    20. GFX_DISPLAYPOWER_ENABLE - this enables the use of the Display Power Sequencer
            Control Port (GPWR) when using the Microchip Graphics Module. The signal
            can be used to control the display power circuitry. The Graphics Module
            can manage the powering up and powering down of the display since
            power up and power down sequence in display panels is essential to
            extend display life cycle.

            Example: #define GFX_DISPLAYPOWER_ENABLE

    21. GFX_DISPLAYPOWER_POLARITY - this sets the polarity of the Display Power Sequencer
            Control Port (GPWR) when using the Microchip Graphics Module.

            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_DISPLAYPOWER_POLARITY GFX_ACTIVE_HIGH

    22. GFX_CLOCK_POLARITY - this sets the polarity of the Display Glass Clock Port (GCLK)
            when using the Microchip Graphics Module.

            Valid Values: GFX_ACTIVE_HIGH, GFX_ACTIVE_LOW
            Example: #define GFX_CLOCK_POLARITY GFX_ACTIVE_HIGH


    There are two major types of controllers enumerated here:
    1. Controllers in Smart Displays - these are display modules that have
       built in display controller. Interface to the PIC device(s)
       are usually through parallel interface or serial interface.

       Required parameters:
       #define DISP_ORIENTATION
       #define DISP_HOR_RESOLUTION
       #define DISP_VER_RESOLUTION

    2. Controller that drives the RGB Glass directly - these are display
       controllers that comes in a separate package or built into the
       microcontrollers.

       Required parameters:
       #define DISP_ORIENTATION
       #define DISP_HOR_RESOLUTION
       #define DISP_VER_RESOLUTION
       #define DISP_DATA_WIDTH
       #define DISP_HOR_PULSE_WIDTH
       #define DISP_HOR_BACK_PORCH
       #define DISP_HOR_FRONT_PORCH
       #define DISP_VER_PULSE_WIDTH
       #define DISP_VER_BACK_PORCH
       #define DISP_VER_FRONT_PORCH

       Optional parameters:
       #define DISP_INV_LSHIFT

       When using Microchip Graphics Module (mchpGfxDrv) required parameters:
       #define GFX_DISPLAYENABLE_ENABLE
       #define GFX_DISPLAYENABLE_POLARITY

       or

       #define GFX_HSYNC_ENABLE
       #define GFX_VSYNC_ENABLE
       #define GFX_HSYNC_POLARITY
       #define GFX_VSYNC_POLARITY

       #define GFX_CLOCK_POLARITY

       When using Microchip Graphics Module (mchpGfxDrv) Optional parameters:
       #define GFX_DISPLAYPOWER_ENABLE
       #define GFX_DISPLAYPOWER_POLARITY


*/
  #define DISP_ORIENTATION    90
  #define DISP_HOR_RESOLUTION 240
  #define DISP_VER_RESOLUTION 320

  #define GFX_USE_TCON_CUSTOM

  #define DISP_DATA_WIDTH 16
  #define DISPLAY_COLOR_DEPTH DISP_DATA_WIDTH

//  #define TFT_NO_WAIT_BUSY

/*********************************************************************
* DISPLAY PARALLEL INTERFACE
*********************************************************************/
/*
   Select the correct Parallel Master Port Interface Driver.
   This selection is valid only for parallel interface. When using
   display drivers that uses serial interface, this portion should be
   commented out or removed.
*/
  #define USE_GFX_PMP

  #define BACKLIGHT_ENABLE_LEVEL      0
  #define BACKLIGHT_DISABLE_LEVEL     1

typedef enum
{
    ANSEL_DIGITAL = 0,
    ANSEL_ANALOG = 1
}ANSEL_BIT_STATE;


    // Definitions for reset pin
  #define DisplayResetConfig()        TRISCbits.TRISC1 = 0
  #define DisplayResetEnable()        LATCbits.LATC1 = 0
  #define DisplayResetDisable()       LATCbits.LATC1 = 1

  // Definitions for RS pin
  #define DisplayCmdDataConfig()      TRISBbits.TRISB15 = 0
  #define DisplaySetCommand()         LATBbits.LATB15 = 0
  #define DisplaySetData()            LATBbits.LATB15 = 1

  // Definitions for CS pin
  #define DisplayConfig()             TRISFbits.TRISF12 = 0
  #define DisplayEnable()             LATFbits.LATF12 = 0
  #define DisplayDisable()            LATFbits.LATF12 = 1

  #define DisplayBacklightConfig()      TRISAbits.TRISA9  = 0
  #define DisplayBacklightOn()          LATAbits.LATA9    = 1
  #define DisplayBacklightOff()         LATAbits.LATA9    = 0

  #define LED_0_Config    TRISDbits.TRISD0 = 0;   // Red LED output.
  #define LED_1_Config    TRISDbits.TRISD1 = 0;   // Yellow LED output.
  #define LED_2_Config    TRISDbits.TRISD2 = 0;   // Red LED output.
  #define LED_3_Config    TRISDbits.TRISD3 = 0;   // Yellow LED output.
  #define AllLEDConfig()    TRISD   &= 0b1111111111110000
  #define AllLEDOff()       LATD    &= 0b1111111111110000

  #define LED_0_LAT   LATDbits.LATD0    //
  #define LED_1_LAT   LATDbits.LATD1    //
  #define LED_2_LAT   LATDbits.LATD2    //
  #define LED_3_LAT   LATDbits.LATD3    //


/*********************************************************************
* HARDWARE PROFILE FOR THE RESISTIVE TOUCHSCREEN
*********************************************************************/
/*
	These are the hardware settings for the 4-wire resistive
	touch screen. There are two analog inputs and two digital I/Os
	needed.

	This portion is divided into 3 components
	1. IO and ADC channels settings - sets up the IO pins used and the
	   ADC channel selected to evaluate the screen touch.
	2. Touch Screen X and Y orientation settings - sets up the
	   x and y directions. This is dependent on how the resistive
	   touch signals (X-, Y-, X+, and Y+) are wired up to the
	   IOs and ADC signals with respect to the orientation of the
	   screen. Based on these factors, we can control the calculation
	   of the touch by swapping x and/or y and flipping the x and/or y
	   directions.
	3. Touch Screen Non-Volatile Memory Storage Macros - this defines
	   the non-volatile memory read, write and sector erase functions
	   to be used when reading or storing calibration values.

	The resistive touch screen driver assumes the following:
	1. X+ and Y+ are mapped to the A/D inputs
	2. X- and Y- are mapped to the pure digital I/Os
*/

#if defined (USE_TOUCHSCREEN_RESISTIVE)

	/*********************************************************************
	* Resistive Touch Screen A/D and I/O Specific Macros
	*********************************************************************/
	// ADC Input Channel Selector
  #define TOUCH_ADC_INPUT_SEL_DEF   AD1CHS

	// ADC Sample Start
	#define TOUCH_ADC_START   AD1CON1bits.SAMP

	// ADC Status
	#define TOUCH_ADC_DONE   AD1CON1bits.DONE

  #define ADC_CH0_POS_SAMPLEA_AN11  (0xB << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN11 */
  #define ADC_CH0_POS_SAMPLEA_AN10  (0xA << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN10 */

  #define ADC_XPOS    ADC_CH0_POS_SAMPLEA_AN11 // 0x0D00 // 13
  #define ADC_YPOS    ADC_CH0_POS_SAMPLEA_AN10 // ADC_CH0_POS_SAMPLEA_AN10 // 0x0C00 // 12

  #define ADPCFG_XPOS AD1PCFGbits.PCFG11 // AD1PCFGbits.PCFG13
  #define ADPCFG_YPOS AD1PCFGbits.PCFG10 // AD1PCFGbits.PCFG12

  #define RESISTIVETOUCH_ANALOG  0
  #define RESISTIVETOUCH_DIGITAL 1

	// X port definitions
  #define ResistiveTouchScreen_XPlus_Drive_High()         LATBbits.LATB13   = 1
  #define ResistiveTouchScreen_XPlus_Drive_Low()          LATBbits.LATB13   = 0
  #define ResistiveTouchScreen_XPlus_Config_As_Input()    TRISBbits.TRISB13 = 1
  #define ResistiveTouchScreen_XPlus_Config_As_Output()   TRISBbits.TRISB13 = 0

  #define ResistiveTouchScreen_XMinus_Drive_High()        LATBbits.LATB11   = 1
  #define ResistiveTouchScreen_XMinus_Drive_Low()         LATBbits.LATB11   = 0
  #define ResistiveTouchScreen_XMinus_Config_As_Input()   TRISBbits.TRISB11 = 1
  #define ResistiveTouchScreen_XMinus_Config_As_Output()  TRISBbits.TRISB11 = 0

  // Y port definitions
  #define ResistiveTouchScreen_YPlus_Drive_High()         LATBbits.LATB12   = 1
  #define ResistiveTouchScreen_YPlus_Drive_Low()          LATBbits.LATB12   = 0
  #define ResistiveTouchScreen_YPlus_Config_As_Input()    TRISBbits.TRISB12 = 1
  #define ResistiveTouchScreen_YPlus_Config_As_Output()   TRISBbits.TRISB12 = 0

  #define ResistiveTouchScreen_YMinus_Drive_High()        LATBbits.LATB10   = 1
  #define ResistiveTouchScreen_YMinus_Drive_Low()         LATBbits.LATB10   = 0
  #define ResistiveTouchScreen_YMinus_Config_As_Input()   TRISBbits.TRISB10 = 1
  #define ResistiveTouchScreen_YMinus_Config_As_Output()  TRISBbits.TRISB10 = 0

	/*********************************************************************
	* Touch Screen X and Y orientation
	*********************************************************************/
	/*********************************************************************
	Description:
		The usage of the resistive touch screen will be affected
		by the way the hardware is mapped to the A/D channels that
		samples the touch. Since resistive touch is basically a
		measurement of X and Y coordinates the following are macros
		that can modify the touch algorithm when sampling the
		touch.
		TOUCHSCREEN_RESISTIVE_FLIP_X - will flip the x direction.
		TOUCHSCREEN_RESISTIVE_FLIP_Y - will flip the y direction.
		TOUCHSCREEN_RESISTIVE_SWAP_XY - will swap the x and y sampling.

		As long as the (X-,Y-) and (X+,Y+) are used consistently,
		and connected properly in hardware, the macros above
		can provide options to the user to align the touch screen
		to the screen orientation.

        Another macro that may affect the way the x and y measurement
        are the following:
        TOUCHSCREEN_RESISTIVE_PRESS_THRESHOLD - determines how light the
            touch on the screen. The smaller the  value the lighter the
            touch. Valid range of values: 0-0x03ff
        TOUCHSCREEN_RESISTIVE_CALIBRATION_SCALE_FACTOR - this is the scale
            factor used to calculate the touch coefficients. The equation
            to calculate the scale factor is:
               (1 << TOUCHSCREEN_RESISTIVE_CALIBRATION_SCALE_FACTOR).
            Valid values: 0 - 15 (most resistive touch screens will work
                                  in the range of 5 - 7)

	*********************************************************************/

  #define TOUCHSCREEN_RESISTIVE_PRESS_THRESHOLD           0x200
  #define TOUCHSCREEN_RESISTIVE_CALIBRATION_SCALE_FACTOR  6

	/*********************************************************************
	* Touch Screen Non-Volatile Memory Storage Macros
	*********************************************************************/
	// Addresses for calibration and version values in SPI Flash on Graphics PICtail 3 & PIC24FJ256DA210 Development Board.
	// Or Addresses for calibration and version values in Parallel Flash on PIC24FJ256DA210 Development Board.

  #define ADDRESS_RESISTIVE_TOUCH_VERSION	(unsigned long)0xFFFFFFFE
  #define ADDRESS_RESISTIVE_TOUCH_ULX   (unsigned long)0xFFFFFFFC
  #define ADDRESS_RESISTIVE_TOUCH_ULY   (unsigned long)0xFFFFFFFA
  #define ADDRESS_RESISTIVE_TOUCH_URX   (unsigned long)0xFFFFFFF8
  #define ADDRESS_RESISTIVE_TOUCH_URY   (unsigned long)0xFFFFFFF6

  #define ADDRESS_RESISTIVE_TOUCH_LLX   (unsigned long)0xFFFFFFF4
  #define ADDRESS_RESISTIVE_TOUCH_LLY   (unsigned long)0xFFFFFFF2
  #define ADDRESS_RESISTIVE_TOUCH_LRX   (unsigned long)0xFFFFFFF0
  #define ADDRESS_RESISTIVE_TOUCH_LRY   (unsigned long)0xFFFFFFEE

  // define the functions to call for the non-volatile memory
  // check out touch screen module for definitions of the following function pointers
  // used: NVM_READ_FUNC, NVM_WRITE_FUNC & NVM_SECTORERASE_FUNC
  #define NVMSectorErase        ((NVM_SECTORERASE_FUNC)&SST25SectorErase)
  #define NVMWrite              ((NVM_WRITE_FUNC)&SST25WriteWord)
  #define NVMRead               ((NVM_READ_FUNC)&SST25ReadWord)

/*********************************************************************
* HARDWARE PROFILE FOR THE SPI FLASH MEMORY
*********************************************************************/
/*
	These are the hardware settings for the SPI peripherals used.
*/

  #define MCHP25LC256_CS_TRIS  TRISDbits.TRISD12
  #define MCHP25LC256_CS_LAT   LATDbits.LATD12

	/*********************************************************************
	* SPI Flash Memory on GFX_PICTIAL_V3, GFX_PICTAIL_V3e,
	* PIC24FJ256DA210 Development Board and MEB_BOARD
	*********************************************************************/
	// Set up the signals used to communicate to the SPI Flash device

  #define SPIFlashConfigurePins() {                           \
                                            SST25_SDO_ANS  = ANSEL_DIGITAL; \
                                            SST25_SDI_ANS  = ANSEL_DIGITAL; \
                                            SST25_CS_LAT   = 1; \
                                            SST25_CS_TRIS  = 0; \
                                            SST25_SCK_TRIS = 0; \
                                            SST25_SDO_TRIS = 0; \
                                            SST25_SDI_TRIS = 1; \
                                    }

	/*********************************************************************
	* SPI Flash Memory on MIKRO_BOARD
	*********************************************************************/
	// Set up the signals used to communicate to the SPI Flash device

    // define the SPI channel to be used
#define SST25_SPI_CHANNEL 2

    /* Define all the SPI channels that will be used here.
       These will be used to determine how the SPI Driver (drv_spi)
       will be compiled.
    */
    #if (SST25_SPI_CHANNEL == 1)
        #define SPI_CHANNEL_1_ENABLE
    #elif (SST25_SPI_CHANNEL == 2)
        #define SPI_CHANNEL_2_ENABLE
    #elif (SST25_SPI_CHANNEL == 3)
        #define SPI_CHANNEL_3_ENABLE
    #elif (SST25_SPI_CHANNEL == 4)
        #define SPI_CHANNEL_4_ENABLE
    #endif

  #define SST25_CS_TRIS   TRISCbits.TRISC2
  #define SST25_CS_LAT    LATCbits.LATC2
  #define SST25_SCK_TRIS  TRISGbits.TRISG6
  #define SST25_SDO_TRIS  TRISGbits.TRISG8
  #define SST25_SDI_TRIS  TRISGbits.TRISG7

/*********************************************************************
* IOS FOR THE SWITCHES (SIDE BUTTONS)
*********************************************************************/
/*typedef enum
{
    HW_BUTTON_PRESS = 0,
    HW_BUTTON_RELEASE = 1
}HW_BUTTON_STATE;*/

/*********************************************************************
* IOS FOR THE UART
*********************************************************************/
  #define TX_TRIS TRISFbits.TRISF5
  #define RX_TRIS TRISFbits.TRISF4

/*********************************************************************
* RTCC DEFAULT INITIALIZATION (these are values to initialize the RTCC
*********************************************************************/
#define RTCC_DEFAULT_DAY        8       // 13th
#define RTCC_DEFAULT_MONTH      12       // February
#define RTCC_DEFAULT_YEAR       13      // 2012
#define RTCC_DEFAULT_WEEKDAY    7       // Monday
#define RTCC_DEFAULT_HOUR       7      // 10:10:01
#define RTCC_DEFAULT_MINUTE     10
#define RTCC_DEFAULT_SECOND     1

#endif    

#ifdef	__cplusplus
}
#endif

#endif	/* HARDWAREPROFILE_MIKROMEDIAPIC32MX_H */

