/*********************************************************************
 *
 *                  PIC32 Boot Loader
 *
 *********************************************************************
 * FileName:        EthernetTasks.c
 * Dependencies:
 * Processor:       PIC32
 *
 * Compiler:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PIC32 Microcontroller is intended
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PIC32 Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * $Id:  $
 * $Name: $
 *
 **********************************************************************/
#include "Include\GenericTypeDefs.h"
#include "Include\HardwareProfile\HardwareProfile.h"
#include "Include\Bootloader.h"
#include "Include\FrameWork\Framework.h"
#include <stdlib.h>
#include <plib.h>
// Include all headers for any enabled TCPIP Stack functions
#include "Include\TCPIP Stack\TCPIP.h"


UDP_PORT         serverPort = UDP_BTL_PORT;    // server port
UDP_SOCKET       udpSkt;        // communication handle

APP_CONFIG AppConfig;

UINT8 txData[200];
UINT8 rxData[FRAMEWORK_BUFF_SIZE];


/********************************************************************
* Function: 	loadAppConfig()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview: 	Loads application configured IP address and MAC address.
*
*			
* Note:		 	None.
********************************************************************/
void loadAppConfig(void)
{

	// TODO: Load IP/MAC address here.
	// Initialize the IP, Subnet Mask
	AppConfig.MyIPAddr.Val = (MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2<<8ul | MY_DEFAULT_IP_ADDR_BYTE3<<16ul | MY_DEFAULT_IP_ADDR_BYTE4<<24ul);
	AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
	AppConfig.MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2<<8ul | MY_DEFAULT_MASK_BYTE3<<16ul | MY_DEFAULT_MASK_BYTE4<<24ul;
	AppConfig.DefaultMask.Val = AppConfig.MyMask.Val;
	
	// Initialize the MAC address.
	AppConfig.MyMACAddr.v[0] = MY_DEFAULT_MAC_BYTE1;
	AppConfig.MyMACAddr.v[1] = MY_DEFAULT_MAC_BYTE2;
	AppConfig.MyMACAddr.v[2] = MY_DEFAULT_MAC_BYTE3;
	AppConfig.MyMACAddr.v[3] = MY_DEFAULT_MAC_BYTE4;	
}

/********************************************************************
* Function: 	ethernetInit()
*
* Precondition: 
*
* Input: 		peripheral bus clock (Not used).
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview: 	Initializes the IP address, TCPIP stack, creates UDP socket.
*
*			
* Note:		 	None.
********************************************************************/
void ethernetInit(UINT pbClk)
{
#if   (((__PIC32_FEATURE_SET__ >= 100) && (__PIC32_FEATURE_SET__ <= 299)))
		#error("TODO: For PIC32MX1xx/PIC32MX2xx devices, user should take care of mapping the ports to required pins");
		/* Example Code (if SPI2 is the interface)
	    PPSInput(3,SDI2,RPn); // SDI2 mapping, where RPn = RPA2, RPB6....
    	
    	PPSOutput(2,RPn,SDO2);// SDO2 mapping, where RPn = RPA1, RPB5....
    
    	//Do not forget to switch-off corrresponding "analog selection".
    	ANSELx = 0;
    	*/
#endif
	// Enable multi-vectored interrupts
	INTEnableSystemMultiVectoredInt();
	
	loadAppConfig();
	
	// Initialize the tick.
	TickInit();
	
	// Initialize MAC, PHY and Stack.
	StackInit();
	
	// UDP open
	udpSkt = UDPOpen(serverPort, 0, 0);	 
} 

/********************************************************************
* Function: 	ethernetTasks()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview:     Receive packets from UDP and send packets on UDP.
*
*			
* Note:		 	None.
********************************************************************/
void ethernetTasks(void)
{
	
	INT nBytes = 0;
	UINT txLen = 0;
	INT avlBytes = 0;
	
	StackTask();
	// Check if bootloader has something to send out to PC. 
	txLen = FRAMEWORK_GetTransmitFrame(txData);
	
	if(txLen)
	{
	
		while(nBytes < txLen)
		{
			StackTask();
			nBytes = UDPIsPutReady(udpSkt);
		}	
		
	    nBytes = UDPPutArray( (UINT8*)&txData, txLen);
	    // Make sure all bytes are transmitted.
	    // This assert must be caught during debug phase.
	    ASSERT(nBytes==txLen);
	    
	    UDPFlush();	
	} 
	else   
	{	
		avlBytes = UDPIsGetReady(udpSkt);
		
		if(avlBytes >= sizeof(rxData))
		{
			// PC application is pumping more data than device can handle.
			while(1);
		}	
			      
	    if(avlBytes) 
		{
						
		 	nBytes = UDPGetArray((BYTE*)&rxData, avlBytes ); 		  		
	  		if(nBytes)
	  		{
		  		// Pass the bytes to frame work.
				FRAMEWORK_BuildRxFrame(rxData, nBytes);	
		  		
		  	}					 
		}
			
	}		   	
}


/********************************************************************
* Function: 	disableInterrupt()
*
* Precondition: 
*
* Input: 		None.
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview:     Disables all interrupts used by ethernet.
*
*			
* Note:		 	None.
********************************************************************/
void disableInterrupt(void)
{
	
	IEC0bits.T1IE = 0;	
	
}	
	
//-----------------------------------------------------------------------------------------
