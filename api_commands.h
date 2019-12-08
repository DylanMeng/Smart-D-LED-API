/***************************************************************
* FILE NAME: api_commands.h
*
* MIT License
*
* Copyright (c) 2019 Dylan Meng
*
* Note: 1. Some commands are in development and not tested yet.
*       2. More documentation will be added later.
***************************************************************/

#define mFactoryReset  0x0100  
/*
	1. Reset default parameters
	2. Reply: mFactoryReset
	3. Reset the device to apply change	
*/

#define mSetKey  0x0101   
/*
	TO-DO
*/

#define mReset  0x0103   
/*
	1. Reply: mReset
	2. Reset the device
*/

/*============================================================*/
/* Serial flash control for OTA update                        */
/*============================================================*/

#define mEraseSpiFlash  0x0104
/*
	1. Erase all DATA on SPI flash
	2. Erase complete, Reply: mEraseSpiFlash (long reply delay)
*/

#define mUpdateFileChecksum  0x0105 
/*
	1. Data: CRC32 checksum of the file that will be transferred later
	2. Create KNOW_CHECKSUM_FILE
	2. Reply: mUpdateFileChecksum + saved CRC32 checksum
*/

#define mListFile  0x0106 
/*
	USED FOR DEBUGGING
*/

#define mCRC32File  0x0107 
/*
	1. Read UPDATE_FILE
	2. Calculate CRC32 checksum of UPDATE_FILE
	2. Read KNOW_CHECKSUM_FILE
	3. Compare KNOW_CRC32 with CALCULATED_CRC32
	4. CRC32 MATCH: Reply mCRC32File + 0xAA
	         ERROR: Reply mCRC32File + 0xEE
*/


/*============================================================*/
/* Digital LED strip chipset selection                        */
/*============================================================*/

#define mSetLedType  0x9000  
/*
	1. Save LED type in flash
	2. Reply: mSetLedType
    
	*Change will only take effect after reset
*/

#define mGetLedType  0x9001
/*
	1. Reply: mGetLedType + selected chipset
*/


/*============================================================*/
/* Number of LEDs selection                                   */
/*============================================================*/

#define mSetNumLedsFlash  0x9004
/*
	1. Turn off pattern and effect
	2. Blackout
	3. Save number of leds in flash
	4. Reply: mSetNumLedsFlash

	*Change will only take effect after reset
*/
#define mGetNumLedsFlash  0x9005
/*
	1. Reply: mGetNumLedsFlash + number of leds
*/


/*============================================================*/
/* Power limitation                                           */
/*============================================================*/

#define mSetPowerLimitation  0x9020
/*

	NOT TESTED!
	TO-DO: Test behavior
	
	1. Save limitpower   (OFF: 0x00, ON: 0x01)
	2. Save maxMilliamps (0x0000 -> 0xFFFF)
	2. Reply: mSetPowerLimitation

	*Change will only take effect after reset

	Example:

	NO LIMIT: |00|FFFF|
	5A LIMIT: |01|1388|

	- Default setting is 5A LIMIT. 
	- Only change this setting if the LED strips are powered externally
*/

#define mGetPowerLimitation  0x9021
/*
	1. Reply: mGetPowerLimitation + limitpower + maxMilliamps
*/


/*============================================================*/
/* Resource Monitor (Get only)                                */
/*============================================================*/
#define mRequestHello        0xA000  // Reply: mRequestHello
#define mGetFreeRam          0xA001  // Reply: available ram
#define mGetCurrentFps	     0xA002  // Reply: led strip animation framerate
#define mGetLedPerformance   0xA003  // Reply: Fastled.show() performance in uS
#define mGetfirmwareVersion  0xA004	 // Reply: firware version in ASCII
#define mGetRssi		     0xA005  // Reply: RSSI (signed 32bit)

/*============================================================*/
/* Wifi Control OUTDATED WILL BE UPDATED SOON                 */
/*============================================================*/
#define mAccessPoint    0xF000
#define mSetLocalPort   0xF001
#define mStopUdp		0xF004
#define mDirectWifiOn   0xF005
#define mDirectWifiOff  0xF006
#define mGetIpAddress   0xF007

/*============================================================*/
/* LED control    0x1000 -> 0x5000                            */
/*============================================================*/

// Led State    
#define mSetLedState  0x1000
#define mGetLedState  0x1001

// Brightness 
#define mSetBrightness  0x1002
#define mGetBrightness  0x1003

// Pattern
#define mSetPattern  0x2071
#define mGetPattern  0x2072

// Effect
#define mSetEffect   0x2073
#define mGetEffect   0x2074

// Color
#define mGetHsvState  0x1010
#define mSetHsvState  0x1011

// Color
#define mGetRgbState  0x1012
#define mSetRgbState  0x1013

// Vu Meter
#define mSetVuMeter  0x1100
#define mGetVuMeter  0x1101

// Gradient Fill 
#define mSetGradientFill  0x2001
#define mGetGradientFill  0x2002

// Double Gradient
#define mSetDoubleGradient  0x2003
#define mGetDoubleGradient  0x2004

// Triple Gradient
#define mSetTripleGradient  0x2005
#define mGetTripleGradient  0x2006

// Quad Gradient
#define mSetQuadGradient    0x2007
#define mGetQuadGradient    0x2008

// Double Gradient
#define mSetDoubleGradientRGB  0x2009
#define mGetDoubleGradientRGB  0x2010

// Triple Gradient
#define mSetTripleGradientRGB  0x2011
#define mGetTripleGradientRGB  0x2012

// Quad Gradient
#define mSetQuadGradientRGB  0x2013
#define mGetQuadGradientRGB  0x2014

// Fire   
#define mGetFire  0x2020
#define mSetFire  0x2021

// Smart Rainbow                                             
#define mGetRainbowState   0x2030
#define mSetRainbowState   0x2031

// Breathing effect
#define mSetBreathing  0x2080
#define mGetBreathing  0x2081

// Confetti
#define mSetConfetti  0x2090
#define mGetConfetti  0x2091

// Sinelon 
#define mSetSinelon 0x20A0
#define mGetSinelon  0x20A1

// Pulse
#define mSetPulse  0x20B0
#define mGetPulse  0x20B1

// Color order calibration
#define mSetColorOrderCalibrate  0x20C0

// Palette fill
#define mSetPaletteFill 0x20D0

#define mSetJuggle 0x20C1
#define mGetJuggle 0x20C2

/*============================================================*/
/* Predefine color palettes                                   */
/*============================================================*/
#define cpPartyColors			0x0000
#define cpCloudColors			0x0001
#define cpLavaColors			0x0002
#define cpOceanColors			0x0003
#define cpForestColors			0x0004
#define cpRainbowColors			0x0005
#define cpRainbowStripeColors   0x0006
#define cpHeatColors		    0x0007

// Blend type
#define cpNoBlend	  0x0000
#define cpLinearBlend 0x0001

/*============================================================*/
/* API Error Code                                             */
/*============================================================*/
#define ercInvalidCmd  0xEEE1
#define ercOffLimits   0xEEE2
#define ercRestricted  0xEEE3



