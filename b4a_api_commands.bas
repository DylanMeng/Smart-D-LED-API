'/***************************************************************
'* FILE NAME: api_commands.h
'*
'* MIT License
'*
'* Copyright (c) 2019 Dylan Meng
'*
'* Note: 1. Some commands are in development and not tested yet.
'*       2. More documentation will be added later.
'***************************************************************/

Dim const mFactoryReset  As String = "0100"  
'/*
'	1. Reset default parameters
'	2. Reply: mFactoryReset
'	3. Reset the device to apply change	
'*/

Dim const mSetKey  As String = "0101"   
'/*
'	TO-DO
'*/

Dim const mReset  As String = "0103"   
'/*
'	1. Reply: mReset
'	2. Reset the device
'*/

'/*============================================================*/
'/* Serial flash control for OTA update                        */
'/*============================================================*/

Dim const mEraseSpiFlash  As String = "0104"
'/*
'	1. Erase all DATA on SPI flash
'	2. Erase complete, Reply: mEraseSpiFlash (long reply delay)
'*/

Dim const mUpdateFileChecksum  As String = "0105" 
'/*
'	1. Data: CRC32 checksum of the file that will be transferred later
'	2. Create KNOW_CHECKSUM_FILE
'	2. Reply: mUpdateFileChecksum + saved CRC32 checksum
'*/

Dim const mListFile  As String = "0106" 
'/*
'	USED FOR DEBUGGING
'*/

Dim const mCRC32File  As String = "0107" 
'/*
'	1. Read UPDATE_FILE
'	2. Calculate CRC32 checksum of UPDATE_FILE
'	2. Read KNOW_CHECKSUM_FILE
'	3. Compare KNOW_CRC32 with CALCULATED_CRC32
'	4. CRC32 MATCH: Reply mCRC32File + 0xAA
'	         ERROR: Reply mCRC32File + 0xEE
'*/


'/*============================================================*/
'/* Digital LED strip chipset selection                        */
'/*============================================================*/

Dim const mSetLedType  As String = "9000"  
'/*
'	1. Save LED type in flash
'	2. Reply: mSetLedType
'    
'	*Change will only take effect after reset
'*/

Dim const mGetLedType  As String = "9001"
'/*
'	1. Reply: mGetLedType + selected chipset
'*/


'/*============================================================*/
'/* Number of LEDs selection                                   */
'/*============================================================*/

Dim const mSetNumLedsFlash  As String = "9004"
'/*
'	1. Turn off pattern and effect
'	2. Blackout
'	3. Save number of leds in flash
'	4. Reply: mSetNumLedsFlash

'	*Change will only take effect after reset
'*/
Dim const mGetNumLedsFlash  As String = "9005"
'/*
'	1. Reply: mGetNumLedsFlash + number of leds
'*/


'/*============================================================*/
'/* Power limitation                                           */
'/*============================================================*/

Dim const mSetPowerLimitation  As String = "9020"
'/*

'	NOT TESTED!
'	TO-DO: Test behavior
'	
'	1. Save limitpower   (OFF: 0x00, ON: 0x01)
'	2. Save maxMilliamps (0x0000 -> 0xFFFF)
'	2. Reply: mSetPowerLimitation

'	*Change will only take effect after reset

'	Example:

'	NO LIMIT: |00|FFFF|
'	5A LIMIT: |01|1388|

'	- Default setting is 5A LIMIT. 
'	- Only change this setting if the LED strips are powered externally
'*/

Dim const mGetPowerLimitation  As String = "9021"
'/*
'	1. Reply: mGetPowerLimitation + limitpower + maxMilliamps
'*/


'/*============================================================*/
'/* Resource Monitor (Get only)                                */
'/*============================================================*/
Dim const mRequestHello        As String = "A000"  ' Reply: mRequestHello
Dim const mGetFreeRam          As String = "A001"  ' Reply: available ram
Dim const mGetCurrentFps	     As String = "A002"  ' Reply: led strip animation framerate
Dim const mGetLedPerformance   As String = "A003"  ' Reply: Fastled.show() performance in uS
Dim const mGetfirmwareVersion  As String = "A004"	 ' Reply: firware version in ASCII
Dim const mGetRssi		     As String = "A005"  ' Reply: RSSI (signed 32bit)

'/*============================================================*/
'/* Wifi Control OUTDATED WILL BE UPDATED SOON                 */
'/*============================================================*/
Dim const mAccessPoint    As String = "F000"
Dim const mSetLocalPort   As String = "F001"
Dim const mStopUdp		As String = "F004"
Dim const mDirectWifiOn   As String = "F005"
Dim const mDirectWifiOff  As String = "F006"
Dim const mGetIpAddress   As String = "F007"

'/*============================================================*/
'/* LED control    0x1000 -> 0x5000                            */
'/*============================================================*/

'// Led State    
Dim const mSetLedState  As String = "1000"
Dim const mGetLedState  As String = "1001"

'// Brightness 
Dim const mSetBrightness  As String = "1002"
Dim const mGetBrightness  As String = "1003"

'// Pattern
Dim const mSetPattern  As String = "2071"
Dim const mGetPattern  As String = "2072"

'// Effect
Dim const mSetEffect   As String = "2073"
Dim const mGetEffect   As String = "2074"

'// Color
Dim const mGetHsvState  As String = "1010"
Dim const mSetHsvState  As String = "1011"

'// Color
Dim const mGetRgbState  As String = "1012"
Dim const mSetRgbState  As String = "1013"

'// Vu Meter
Dim const mSetVuMeter  As String = "1100"
Dim const mGetVuMeter  As String = "1101"

'// Gradient Fill 
Dim const mSetGradientFill  As String = "2001"
Dim const mGetGradientFill  As String = "2002"

'// Double Gradient
Dim const mSetDoubleGradient  As String = "2003"
Dim const mGetDoubleGradient  As String = "2004"

'// Triple Gradient
Dim const mSetTripleGradient  As String = "2005"
Dim const mGetTripleGradient  As String = "2006"

'// Quad Gradient
Dim const mSetQuadGradient    As String = "2007"
Dim const mGetQuadGradient    As String = "2008"

'// Double Gradient
Dim const mSetDoubleGradientRGB  As String = "2009"
Dim const mGetDoubleGradientRGB  As String = "2010"

'// Triple Gradient
Dim const mSetTripleGradientRGB  As String = "2011"
Dim const mGetTripleGradientRGB  As String = "2012"

'// Quad Gradient
Dim const mSetQuadGradientRGB  As String = "2013"
Dim const mGetQuadGradientRGB  As String = "2014"

'// Fire   
Dim const mGetFire  As String = "2020"
Dim const mSetFire  As String = "2021"

'// Smart Rainbow                                             
Dim const mGetRainbowState   As String = "2030"
Dim const mSetRainbowState   As String = "2031"

'// Breathing effect
Dim const mSetBreathing  As String = "2080"
Dim const mGetBreathing  As String = "2081"

'// Confetti
Dim const mSetConfetti  As String = "2090"
Dim const mGetConfetti  As String = "2091"

'// Sinelon 
Dim const mSetSinelon As String = "20A0"
Dim const mGetSinelon  As String = "20A1"

'// Pulse
Dim const mSetPulse  As String = "20B0"
Dim const mGetPulse  As String = "20B1"

'// Color order calibration
Dim const mSetColorOrderCalibrate  As String = "20C0"

'// Palette fill
Dim const mSetPaletteFill As String = "20D0"

Dim const mSetJuggle As String = "20C1"
Dim const mGetJuggle As String = "20C2"

'/*============================================================*/
'/* Predefine color palettes                                   */
'/*============================================================*/
Dim const cpPartyColors			As String = "0000"
Dim const cpCloudColors			As String = "0001"
Dim const cpLavaColors			As String = "0002"
Dim const cpOceanColors			As String = "0003"
Dim const cpForestColors			As String = "0004"
Dim const cpRainbowColors			As String = "0005"
Dim const cpRainbowStripeColors   As String = "0006"
Dim const cpHeatColors		    As String = "0007"

'// Blend type
Dim const cpNoBlend	  As String = "0000"
Dim const cpLinearBlend As String = "0001"

'/*============================================================*/
'/* API Error Code                                             */
'/*============================================================*/
Dim const ercInvalidCmd  As String = "EEE1"
Dim const ercOffLimits   As String = "EEE2"
Dim const ercRestricted  As String = "EEE3"



