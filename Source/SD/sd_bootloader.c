/********************************************************************
 FileName:     SD Bootloader.c
 Dependencies: See INCLUDES section
 Processor:		PIC32 USB Microcontrollers
 Hardware:		
 Complier:  	Microchip C18 (for PIC18), C30 (for PIC24), C32 (for PIC32)
 Company:		Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the “Company”) for its PIC® Microcontroller is intended and
 supplied to you, the Company’s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Description
  1.0   Initial release
  2.1   Updated for simplicity and to use common
                     coding style
********************************************************************/
#include "FSIO.h"
#include "NVMem.h"
#include "sd_bootloader.h"
#include "Bootloader.h"
#include <plib.h>
#include <string.h>
#include "HardwareProfile.h"

// *****************************************************************************
// *****************************************************************************
// Device Configuration Bits (Runs from Aux Flash)
// *****************************************************************************
// *****************************************************************************
// Configuring the Device Configuration Registers
// 80Mhz Core/Periph, Pri Osc w/PLL, Write protect Boot Flash
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
#pragma config ICESEL = ICS_PGx2, BWP = OFF
#if defined(TRANSPORT_LAYER_ETH)
	#pragma config FMIIEN = OFF, FETHIO = OFF	// external PHY in RMII/alternate configuration
#endif

#define SWITCH_PRESSED 0




/******************************************************************************
Macros used in this file
*******************************************************************************/
#define SWITCH_PRESSED 0
#define AUX_FLASH_BASE_ADRS				(0x7FC000)
#define AUX_FLASH_END_ADRS				(0x7FFFFF)
#define DEV_CONFIG_REG_BASE_ADDRESS 	(0xF80000)
#define DEV_CONFIG_REG_END_ADDRESS   	(0xF80012)

/******************************************************************************
Global Variables
*******************************************************************************/
FSFILE * myFile;
BYTE myData[512];
size_t numBytes;
UINT pointer = 0;
UINT readBytes;

UINT8 asciiBuffer[1024];
UINT8 asciiRec[200];
UINT8 hexRec[100];

T_REC record;

/****************************************************************************
Function prototypes
*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
void ConvertAsciiToHex(UINT8* asciiRec, UINT8* hexRec);
void InitializeBoard(void);
BOOL CheckTrigger(void);
void JumpToApp(void);
BOOL ValidAppPresent(void);
#ifdef __cplusplus
}
#endif

/********************************************************************
* Function: 	main()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview: 	Main entry function. If there is a trigger or 
*				if there is no valid application, the device 
*				stays in firmware upgrade mode.
*
*			
* Note:		 	None.
********************************************************************/
int main(void)
{
    volatile UINT i;
    volatile BYTE led = 0;
        
    // Setup configuration
    (void)SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
	
	InitLED();   
    
    if(!CheckTrigger() && ValidAppPresent())
	{
        // This means the switch is not pressed. Jump
        // directly to the application
        
        JumpToApp();        
    }

#if   (((__PIC32_FEATURE_SET__ >= 100) && (__PIC32_FEATURE_SET__ <= 299)))
		#error("TODO: For PIC32MX1xx/PIC32MX2xx devices, user must map the SPI ports to required I/Os using PPS");
		/* Example Code
		PPSInput(3,SDI2,RPn); // SDI2 mapping, where RPn = RPA2, RPB6....
    	
    	PPSOutput(2,RPn,SDO2);// SDO2 on RPA8
    
    	//Do not forget to switch-off corrresponding "analog selection".
    	ANSELx = 0;
    	*/
#endif

    //Initialize the media
    while (!MDD_MediaDetect())
    {
	    // Waiting for media to be inserted.
	    BlinkLED();
	} 
    
    // Initialize the File System
   	if(!FSInit())
   	{
	   	//Indicate error and stay in while loop.
         Error();
         while(1);
    }         
	   	

	myFile = FSfopen("image.hex","r");
			
    if(myFile == NULL)// Make sure the file is present.
    {
	    //Indicate error and stay in while loop.
         Error();
         while(1);
    }     
    
    // Erase Flash (Block Erase the program Flash)
    EraseFlash();
    // Initialize the state-machine to read the records.
    record.status = REC_NOT_FOUND;
	 
     while(1)
     {
	     
         // For a faster read, read 512 bytes at a time and buffer it.
         readBytes = FSfread((void *)&asciiBuffer[pointer],1,512,myFile);
         
         if(readBytes == 0)
         {
             // Nothing to read. Come out of this loop
             // break;
             FSfclose(myFile);
             // Something fishy. The hex file has ended abruptly, looks like there was no "end of hex record".
             //Indicate error and stay in while loop.
             Error();
             while(1);             
         }

         for(i = 0; i < (readBytes + pointer); i ++)
         {
	         
          // This state machine seperates-out the valid hex records from the read 512 bytes.
             switch(record.status)
             {
                 case REC_FLASHED:
                 case REC_NOT_FOUND:
                     if(asciiBuffer[i] == ':')
                     {
                      // We have a record found in the 512 bytes of data in the buffer.
                         record.start = &asciiBuffer[i];
                         record.len = 0;
                         record.status = REC_FOUND_BUT_NOT_FLASHED;
                     }
                     break;
                 case REC_FOUND_BUT_NOT_FLASHED:
                     if((asciiBuffer[i] == 0x0A) || (asciiBuffer[i] == 0xFF))
                     {
                      // We have got a complete record. (0x0A is new line feed and 0xFF is End of file)
                         // Start the hex conversion from element
                         // 1. This will discard the ':' which is
                         // the start of the hex record.
                         ConvertAsciiToHex(&record.start[1],hexRec);
                         WriteHexRecord2Flash(hexRec);
                         record.status = REC_FLASHED;
                     }
                     break;
             }
             // Move to next byte in the buffer.
             record.len ++;
         }

         if(record.status == REC_FOUND_BUT_NOT_FLASHED)
         {
          // We still have a half read record in the buffer. The next half part of the record is read 
          // when we read 512 bytes of data from the next file read. 
             memcpy(asciiBuffer, record.start, record.len);
             pointer = record.len;
             record.status = REC_NOT_FOUND;
         }
         else
         {
             pointer = 0;
         }
         // Blink LED at Faster rate to indicate programming is in progress.
         led += 3;
	     mLED = ((led & 0x80) == 0);
        	 
     }//while(1)
  
  
    return 0;
}


/********************************************************************
* Function: 	CheckTrigger()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		TRUE: If triggered
				FALSE: No trigger
*
* Side Effects:	None.
*
* Overview: 	Checks if there is a trigger to enter 
				firmware upgrade mode.
*
*			
* Note:		 	None.
********************************************************************/
BOOL CheckTrigger(void)
{
	UINT SwitchStatus;
	SwitchStatus = ReadSwitchStatus();
	if(SwitchStatus == SWITCH_PRESSED)
	{
		// Switch is pressed
		return TRUE;		
	}	
	else
	{
		// Switch is not pressed.
		return FALSE;	
	}	
}	


/********************************************************************
* Function: 	JumpToApp()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		
*
* Side Effects:	No return from here.
*
* Overview: 	Jumps to application.
*
*			
* Note:		 	None.
********************************************************************/
void JumpToApp(void)
{	
	void (*fptr)(void);
	fptr = (void (*)(void))USER_APP_RESET_ADDRESS;
	fptr();
}	



/********************************************************************
* Function: 	ConvertAsciiToHex()
*
* Precondition: 
*
* Input: 		Ascii buffer and hex buffer.
*
* Output:		
*
* Side Effects:	No return from here.
*
* Overview: 	Converts ASCII to Hex.
*
*			
* Note:		 	None.
********************************************************************/
void ConvertAsciiToHex(UINT8* asciiRec, UINT8* hexRec)
{
	UINT8 i = 0;
	UINT8 k = 0;
	UINT8 hex;
	
	
	while((asciiRec[i] >= 0x30) && (asciiRec[i] <= 0x66))
	{
		// Check if the ascci values are in alpha numeric range.
		
		if(asciiRec[i] < 0x3A)
		{
			// Numerical reperesentation in ASCII found.
			hex = asciiRec[i] & 0x0F;
		}
		else
		{
			// Alphabetical value.
			hex = 0x09 + (asciiRec[i] & 0x0F);						
		}
	
		// Following logic converts 2 bytes of ASCII to 1 byte of hex.
		k = i%2;
		
		if(k)
		{
			hexRec[i/2] |= hex;
			
		}
		else
		{
			hexRec[i/2] = (hex << 4) & 0xF0;
		}	
		i++;		
	}		
	
}
// Do not change this
#define FLASH_PAGE_SIZE 0x1000
/********************************************************************
* Function: 	EraseFlash()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		
*
* Side Effects:	No return from here.
*
* Overview: 	Erases Flash (Block Erase).
*
*			
* Note:		 	None.
********************************************************************/
void EraseFlash(void)
{
	void * pFlash;
    UINT result;
    INT i;

    pFlash = (void*)APP_FLASH_BASE_ADDRESS;									
    for( i = 0; i < ((APP_FLASH_END_ADDRESS - APP_FLASH_BASE_ADDRESS + 1)/FLASH_PAGE_SIZE); i++ )
    {
	     result = NVMemErasePage( pFlash + (i*FLASH_PAGE_SIZE) );
        // Assert on NV error. This must be caught during debug phase.

        if(result != 0)
        {
           // We have a problem. This must be caught during the debug phase.
            while(1);
        } 
        // Blink LED to indicate erase is in progress.
        mLED = mLED ^ 1;
    }			           	     
}



/********************************************************************
* Function: 	WriteHexRecord2Flash()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		
*
* Side Effects:	No return from here.
*
* Overview: 	Writes Hex Records to Flash.
*
*			
* Note:		 	None.
********************************************************************/
void WriteHexRecord2Flash(UINT8* HexRecord)
{
	static T_HEX_RECORD HexRecordSt;
	UINT8 Checksum = 0;
	UINT8 i;
	UINT WrData;
	UINT RdData;
	void* ProgAddress;
	UINT result;
		
	HexRecordSt.RecDataLen = HexRecord[0];
	HexRecordSt.RecType = HexRecord[3];	
	HexRecordSt.Data = &HexRecord[4];	
	
	// Hex Record checksum check.
	for(i = 0; i < HexRecordSt.RecDataLen + 5; i++)
	{
		Checksum += HexRecord[i];
	}	
	
    if(Checksum != 0)
    {
	    //Error. Hex record Checksum mismatch.
	    //Indicate Error by switching ON all LEDs.
	    Error();
	    // Do not proceed further.
	    while(1);
	} 
	else
	{
		// Hex record checksum OK.
		switch(HexRecordSt.RecType)
		{
			case DATA_RECORD:  //Record Type 00, data record.
				HexRecordSt.Address.byte.MB = 0;
					HexRecordSt.Address.byte.UB = 0;
					HexRecordSt.Address.byte.HB = HexRecord[1];
					HexRecordSt.Address.byte.LB = HexRecord[2];
					
					// Derive the address.
					HexRecordSt.Address.Val = HexRecordSt.Address.Val + HexRecordSt.ExtLinAddress.Val + HexRecordSt.ExtSegAddress.Val;
							
					while(HexRecordSt.RecDataLen) // Loop till all bytes are done.
					{
											
						// Convert the Physical address to Virtual address. 
						ProgAddress = (void *)PA_TO_KVA0(HexRecordSt.Address.Val);
						
						// Make sure we are not writing boot area and device configuration bits.
						if(((ProgAddress >= (void *)APP_FLASH_BASE_ADDRESS) && (ProgAddress <= (void *)APP_FLASH_END_ADDRESS))
						   && ((ProgAddress < (void*)DEV_CONFIG_REG_BASE_ADDRESS) || (ProgAddress > (void*)DEV_CONFIG_REG_END_ADDRESS)))
						{
							if(HexRecordSt.RecDataLen < 4)
							{
								
								// Sometimes record data length will not be in multiples of 4. Appending 0xFF will make sure that..
								// we don't write junk data in such cases.
								WrData = 0xFFFFFFFF;
								memcpy(&WrData, HexRecordSt.Data, HexRecordSt.RecDataLen);	
							}
							else
							{	
								memcpy(&WrData, HexRecordSt.Data, 4);
							}		
							// Write the data into flash.	
							result = NVMemWriteWord(ProgAddress, WrData);	
							// Assert on error. This must be caught during debug phase.		
							if(result != 0)
							{
    							while(1);
    						}									
						}	
						
						// Increment the address.
						HexRecordSt.Address.Val += 4;
						// Increment the data pointer.
						HexRecordSt.Data += 4;
						// Decrement data len.
						if(HexRecordSt.RecDataLen > 3)
						{
							HexRecordSt.RecDataLen -= 4;
						}	
						else
						{
							HexRecordSt.RecDataLen = 0;
						}	
					}
					break;
			
			case EXT_SEG_ADRS_RECORD:  // Record Type 02, defines 4th to 19th bits of the data address.
			    HexRecordSt.ExtSegAddress.byte.MB = 0;
				HexRecordSt.ExtSegAddress.byte.UB = HexRecordSt.Data[0];
				HexRecordSt.ExtSegAddress.byte.HB = HexRecordSt.Data[1];
				HexRecordSt.ExtSegAddress.byte.LB = 0;
				// Reset linear address.
				HexRecordSt.ExtLinAddress.Val = 0;
				break;
				
			case EXT_LIN_ADRS_RECORD:   // Record Type 04, defines 16th to 31st bits of the data address. 
				HexRecordSt.ExtLinAddress.byte.MB = HexRecordSt.Data[0];
				HexRecordSt.ExtLinAddress.byte.UB = HexRecordSt.Data[1];
				HexRecordSt.ExtLinAddress.byte.HB = 0;
				HexRecordSt.ExtLinAddress.byte.LB = 0;
				// Reset segment address.
				HexRecordSt.ExtSegAddress.Val = 0;
				break;
				
			case END_OF_FILE_RECORD:  //Record Type 01, defines the end of file record.
				HexRecordSt.ExtSegAddress.Val = 0;
				HexRecordSt.ExtLinAddress.Val = 0;
				// Disable any interrupts here before jumping to the application.
				JumpToApp();
				break;
				
			default: 
				HexRecordSt.ExtSegAddress.Val = 0;
				HexRecordSt.ExtLinAddress.Val = 0;
				break;
		}		
	}	
		
}	

/********************************************************************
* Function: 	ValidAppPresent()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		TRUE: If application is valid.
*
* Side Effects:	None.
*
* Overview: 	Logic: Check application vector has 
				some value other than "0xFFFFFF"
*
*			
* Note:		 	None.
********************************************************************/
BOOL ValidAppPresent(void)
{
	volatile UINT32 *AppPtr;
	
	AppPtr = (UINT32*)USER_APP_RESET_ADDRESS;

	if(*AppPtr == 0xFFFFFFFF)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}			

/*********************End of File************************************/
