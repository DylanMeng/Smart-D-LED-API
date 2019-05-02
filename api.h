/***************************************************************
* FILE NAME: api.h
*
* MIT License
*
* Copyright (c) 2019 Dylan Meng
*
***************************************************************/

class apiClass {

protected:

	uint8_t replyBuffer[15] = { 0xCC, 0xCC, 0x00, 0x00 , 0x00, 0x00 , 0x00, 0x00 , 0x00 , 0x00, 0x00 , 0x00, 0x00 , 0x00 , 0x00 }; // 0 and 1 reserve for command 
	uint8_t receivedCommand[2] = { 0xEE, 0xEE };
	uint16_t command;
	uint16_t num_leds_tmp;
	uint32_t ipLocal;

	void decode(uint16_t aCommand) {
		switch (aCommand) {

			/*============================================================*/
			/* LED critical configuration                                 */
			/*============================================================*/
		case mSetLedType:
			led_type_flash.write(wifi.packetBuffer[4]);
			replyHex(mSetLedType, NULL, NULL);
			break;

		case mGetLedType:
			replyBuffer[2] = led_type_flash.read();
			replyHex(mGetLedType, 1, NULL);
			break;

		case mSetNumLedsFlash:
			pattern.select = pNoPattern;
			effect.select  = eNoEffect;
			dled.blackout();
		    num_leds_tmp = (uint16_t)wifi.packetBuffer[4] << 8 | wifi.packetBuffer[5];
			if (num_leds_tmp <= MAX_NUM_LEDS) {
				num_leds_flash.write(num_leds_tmp);
				replyHex(mSetNumLedsFlash, NULL, NULL);
			}
			else {
				replyHex(mSetNumLedsFlash, NULL, ercOffLimits);
			}
			break;

		case mGetNumLedsFlash:
			if (dled.num_leds == num_leds_flash.read())
			{
				replyBuffer[3] = (uint8_t)num_leds_tmp;
				replyBuffer[2] = (uint8_t)(num_leds_tmp >> 8);
				replyHex(mGetNumLedsFlash, 2, NULL);
			}
			else
			{
				replyHex(mGetNumLedsFlash, NULL, ercOffLimits);
			}
			break;

		case mSetPowerLimitation:
			dled.limitPower = wifi.packetBuffer[4];
			dled.milliamps = (uint16_t)wifi.packetBuffer[5] << 8 | wifi.packetBuffer[6];
			power_limit_state_flash.write(dled.limitPower);
			power_max_milliamps_flash.write(dled.milliamps);
			replyHex(mSetPowerLimitation, NULL, NULL);
			break;

		case mGetPowerLimitation:
			replyBuffer[4] = dled.limitPower;
			replyBuffer[6] = (uint8_t)dled.milliamps;
			replyBuffer[5] = (uint8_t)(dled.milliamps >> 8);
			replyHex(mGetPowerLimitation, 2, NULL);
			break;

		case mEraseSpiFlash:
			SerialFlash.eraseAll();
			while (SerialFlash.ready() == false) {
				// TO DO: add feedback when erasing or timeout
			}
			replyHex(mEraseSpiFlash, NULL, NULL);
			break;

		case mListFile:
			SerialFlash.opendir();
			while (1) {
				char filename[64];
				uint32_t filesize;

				if (SerialFlash.readdir(filename, sizeof(filename), filesize)) {
					DEBUG_PRINT("  ");
					DEBUG_PRINT(filename);
					DEBUG_PRINT("  ");
					DEBUG_PRINT(filesize);
					DEBUG_PRINT(" bytes");
					DEBUG_PRINT_LN();
				}
				else {
					break; // no more files
				}
			}
			break;

		case mUpdateFileChecksum:
			ota.addChecksumToFlash(wifi.packetBuffer[4], wifi.packetBuffer[5],
				wifi.packetBuffer[6], wifi.packetBuffer[7]);
			replyHex(mUpdateFileChecksum, 0, NULL);
			break;

		case mCRC32File:

			if (ota.verifyFile()) {
				replyBuffer[2] = 0xAA;		
			}
			else {
				replyBuffer[2] = 0xEE;
			}

			replyHex(mCRC32File, 1, NULL);

			break;

		/*============================================================*/
		/* WiFi Control                                               */
		/*============================================================*/
		case mAccessPoint: // Start access point 
			//replyHex(mSetConfetti, replyBuffer, 0);
			wifi.startProvisionning();
			break;

		/*============================================================*/
		/* Color calibration helper                                   */
		/*============================================================*/
		case mSetColorOrderCalibrate:
			dled.blackout();
			pattern.select = pColorOrderCalibrate;
			break;

		/*============================================================*/
		/* LED State                                                  */
		/*============================================================*/
		case mSetLedState:
			//lampON = wifi.packetBuffer[4];
			replyHex(mSetLedState, NULL, NULL);
			break;

		case mGetLedState:
			//replyBuffer[2] = lampON;
			replyHex(mGetLedState, 1, NULL);
			break;

		/*============================================================*/
		/* Brigthness Control                                         */
		/*============================================================*/
		case mSetBrightness:
			dled.setBrightness(wifi.packetBuffer[4]);
			//replyHex(mBrightness, NULL, NULL);
			break;

		case mGetBrightness:
			replyBuffer[2] = dled.brightness;
			replyHex(mGetBrightness, 1, NULL);
			break;

		/*============================================================*/
		/* Pattern                                                    */
		/*============================================================*/
		case mSetPattern:
			pattern.select = wifi.packetBuffer[4];
			replyHex(mSetPattern, NULL, NULL);
			break;
		case mGetPattern:
			replyBuffer[2] = pattern.select;
			replyHex(mGetPattern, 1, NULL);
			break;

		/*============================================================*/
		/* Effect                                                     */
		/*============================================================*/
		case mSetEffect:
			effect.select = wifi.packetBuffer[4];
			replyHex(mSetEffect, NULL, NULL);
			break;

		case mGetEffect:
			replyBuffer[2] = effect.select;
			replyHex(mGetEffect, 1, NULL);
			break;

		case mSetBreathing:
		/*	breathingSpeed = ((uint16_t)wifi.packetBuffer[5] << 8) | wifi.packetBuffer[4]; // From 250 to 5000
			breathingSpeedCalc = (float)breathingSpeed;
			pattern.select = eBreathing;
			replyHex(mSetBreathing, NULL, NULL);*/
			break;

		case mGetBreathing:
			/*breathingSpeed = (uint16_t)breathingSpeedCalc;
			replyBuffer[3] = (uint8_t)breathingSpeed;
			replyBuffer[2] = (uint8_t)(breathingSpeed >> 8);
			replyHex(mGetBreathing, 2, NULL);*/
			break;

		/*============================================================*/
		/* Confetti                                                   */
		/*============================================================*/
		case mSetConfetti:
			confetti.fade = wifi.packetBuffer[4];
			confetti.rotateEnable = wifi.packetBuffer[5];
			confetti.hue = wifi.packetBuffer[6];
			confetti.saturation = wifi.packetBuffer[7];
			confetti.random = wifi.packetBuffer[8];
			pattern.select = pConfetti;
			break;

		case mGetConfetti:
			/*replyBuffer[2] = confetti.fade;
			replyBuffer[3] = confetti.hue;
			replyBuffer[4] = confetti.saturation;
			replyBuffer[5] = confetti.random;*/
			replyHex(mGetConfetti, 4, NULL);
			break;

		/*============================================================*/
		/* Sinelon                                                    */
		/*============================================================*/
		case mSetSinelon:
			sinelon.rotateEnable = wifi.packetBuffer[4];
			sinelon.fade = wifi.packetBuffer[5];
			sinelon.bpm = wifi.packetBuffer[6];
			sinelon.hue = wifi.packetBuffer[7];
			sinelon.saturation = wifi.packetBuffer[8];
			pattern.select = pSinelon;
			break;

		case mGetSinelon:
			/*replyBuffer[2] = sinelon.fade;
			replyBuffer[3] = sinelon.bpm; 
			replyBuffer[4] = sinelon.rotateEnable;
			replyBuffer[5] = sinelon.hue;
			replyBuffer[6] = sinelon.saturation;
			replyBuffer[7] = sinelon.hueRotation;
			replyBuffer[8] = sinelon.hueSpeed;
			replyBuffer[9] = sinelon.speed;*/
			replyHex(mGetSinelon, 8, NULL);
			break;

		/*============================================================*/
		/* Pulse                                                      */
		/*============================================================*/
		case mSetPulse:
			pulse.rotateEnable = wifi.packetBuffer[4];
			pulse.bpm = wifi.packetBuffer[5];
			pulse.hue = wifi.packetBuffer[6];
			pulse.setPalette(wifi.packetBuffer[7]);
			pattern.select = pPulse;
			break;

		case mGetPulse:
			/*replyBuffer[2] = spBPM;
			replyBuffer[3] = spRotatingHues;
			replyBuffer[4] = spSpeed;
			replyBuffer[5] = spHue;
			replyBuffer[6] = spRotationToggle;
			replyHex(mGetPulse, 5, NULL);*/
			break;
		
		case mSetJuggle:
			juggle.fade = wifi.packetBuffer[4];
			juggle.hueRotation = wifi.packetBuffer[5];
			juggle.saturation = wifi.packetBuffer[6];
			pattern.select = pJuggle;
			break;
		
		case mGetJuggle:
			break;


			/*============================================================*/
			/* Vu Meter                                                   */
			/*============================================================*/
		case mSetVuMeter:
			/*vumeter.inputFloor = wifi.packetBuffer[4];
			vumeter.inputCeiling = wifi.packetBuffer[5];
			vumeter.fallingDotEnable = wifi.packetBuffer[6];
			vumeter.fallingDotHang = wifi.packetBuffer[7];
			vumeter.fallingDotFall = wifi.packetBuffer[8];
			vumeter.fallingDotHue = wifi.packetBuffer[9];
			vumeter.fallingDotSat = wifi.packetBuffer[10];*/
			effect.select = eVuMeter;
			break;

		case mGetVuMeter:
			replyBuffer[2] = vumeter.inputFloor;
			replyBuffer[3] = vumeter.inputCeiling;
			replyBuffer[4] = vumeter.fallingDotEnable;
			replyBuffer[5] = vumeter.fallingDotHang;
			replyBuffer[6] = vumeter.fallingDotFall;
			replyBuffer[7] = vumeter.fallingDotHue;
			replyBuffer[8] = vumeter.fallingDotSat;
			replyHex(mGetVuMeter, 8, NULL);
			break;

	
		/*============================================================*/
		/* HSV Color Picker                                           */
		/*============================================================*/
		case mSetHsvState:
			color.hue = wifi.packetBuffer[4];
			color.saturation = wifi.packetBuffer[5];
			color.value = wifi.packetBuffer[6];
			pattern.select = pStaticColorHSV;
			break;

		case mGetHsvState:
			replyBuffer[2] = color.hue;
			replyBuffer[3] = color.saturation;
			replyBuffer[4] = color.value;
			replyHex(mGetRgbState, 3, NULL);
			break;

		/*============================================================*/
		/* RGB Color Picker                                           */
		/*============================================================*/
		case mSetRgbState:
			color.red = wifi.packetBuffer[4];
			color.green = wifi.packetBuffer[5];
			color.blue= wifi.packetBuffer[6];
			pattern.select = pStaticColorRGB;
			break;

		case mGetRgbState:
			replyBuffer[2] = color.red;
			replyBuffer[3] = color.green;
			replyBuffer[4] = color.blue;
			replyHex(mGetRgbState, 3, NULL);
			break;

		/*============================================================*/
		/* Rainbow		                                              */
		/*============================================================*/
		case mSetRainbowState:
			rainbow.direction   = wifi.packetBuffer[4];
			rainbow.deltaHue	= wifi.packetBuffer[5];
			rainbow.hueRotation = wifi.packetBuffer[6];
			pattern.select = pRainbowSmart;
			break;

		case mGetRainbowState:
			replyBuffer[2] = rainbow.direction;
			replyBuffer[3] = rainbow.deltaHue;
			replyBuffer[4] = rainbow.hueRotation;
			replyHex(mGetRainbowState, 3, NULL);
			break;

		/*============================================================*/
		/* Fire                                                       */
		/*============================================================*/
		case mSetFire:
			fire.direction = wifi.packetBuffer[4];
			fire.sparking  = wifi.packetBuffer[5];
			fire.cooling   = wifi.packetBuffer[6];
			fire.palette   = wifi.packetBuffer[7];
			pattern.select = pFire;
			break;

		case mGetFire:
			replyBuffer[2] = fire.direction;
			replyBuffer[3] = fire.sparking;
			replyBuffer[4] = fire.cooling;
			replyBuffer[5] = fire.palette;
			replyHex(mGetFire, 4, NULL);
			break;

		/*============================================================*/
		/* Gradient (SET)                                             */
		/*============================================================*/
		case mSetGradientFill:
			gradient.bpm = wifi.packetBuffer[4];
			gradient.fromHue = wifi.packetBuffer[5];
			gradient.toHue = wifi.packetBuffer[6];
			gradient.direction = wifi.packetBuffer[7];
			pattern.select = pGradientBPM;
			//replyHex(mSetGradientFill, NULL, NULL);
			break;

		case mSetDoubleGradientRGB:
			gradient.red1 = wifi.packetBuffer[4];
			gradient.green1 = wifi.packetBuffer[5];
			gradient.blue1 = wifi.packetBuffer[6];

			gradient.red2 = wifi.packetBuffer[7];
			gradient.green2 = wifi.packetBuffer[8];
			gradient.blue2 = wifi.packetBuffer[9];

			pattern.select = pDoubleGradient;
			break;

		case mSetTripleGradientRGB:
			gradient.red1 = wifi.packetBuffer[4];
			gradient.green1 = wifi.packetBuffer[5];
			gradient.blue1 = wifi.packetBuffer[6];

			gradient.red2 = wifi.packetBuffer[7];
			gradient.green2 = wifi.packetBuffer[8];
			gradient.blue2 = wifi.packetBuffer[9];

			gradient.red3 = wifi.packetBuffer[10];
			gradient.green3 = wifi.packetBuffer[11];
			gradient.blue3 = wifi.packetBuffer[12];

			pattern.select = pTripleGradient;
			break;

		case mSetQuadGradientRGB:
			gradient.red1 = wifi.packetBuffer[4];
			gradient.green1 = wifi.packetBuffer[5];
			gradient.blue1 = wifi.packetBuffer[6];

			gradient.red2 = wifi.packetBuffer[7];
			gradient.green2 = wifi.packetBuffer[8];
			gradient.blue2 = wifi.packetBuffer[9];

			gradient.red3 = wifi.packetBuffer[10];
			gradient.green3 = wifi.packetBuffer[11];
			gradient.blue3 = wifi.packetBuffer[12];


			gradient.red4 = wifi.packetBuffer[13];
			gradient.green4 = wifi.packetBuffer[14];
			gradient.blue4 = wifi.packetBuffer[15];

			pattern.select = pQuadGradient;
			break;

		/*============================================================*/
		/* Gradient GET TO-DO                                         */
		/*============================================================*/

		/*============================================================*/
		/* Palette Fill                                               */
		/*============================================================*/
		case mSetPaletteFill:
			palette.speed = wifi.packetBuffer[4];
			palette.movingSpeed = wifi.packetBuffer[5];
			palette.setPalette(wifi.packetBuffer[7], wifi.packetBuffer[8]);
			pattern.select = pPaletteFill;
			break;


		case mRequestHello:
			replyHex(mRequestHello, NULL, NULL);
			break;

		case mReset:
			replyHex(mReset, NULL, NULL);
			NVIC_SystemReset();
			break;

		case mGetfirmwareVersion:
			replyString(firmwareVersion);
			break;

		case mStopUdp:
			replyHex(mStopUdp, NULL, NULL);
			wifi.Udp.stop();
			break;

		case mDirectWifiOn:
			replyHex(mDirectWifiOn, NULL, NULL);
			direct_wifi_flash.write(true); 
			NVIC_SystemReset();
			break;

		case mDirectWifiOff:
			replyHex(mDirectWifiOff, NULL, NULL);
			direct_wifi_flash.write(false);
			NVIC_SystemReset();
			break;

		case mGetIpAddress:
			ipLocal = ip_address_flash.read();
			replyBuffer[2] = ipLocal;
			replyBuffer[3] = ipLocal >> 8;
			replyBuffer[4] = ipLocal >> 16;
			replyBuffer[5] = ipLocal >> 24;
			replyHex(mGetIpAddress, 4, NULL);
			break;

		case mSetLocalPort:
			wifi.localPort = ((uint16_t)wifi.packetBuffer[4] << 8) | wifi.packetBuffer[5];
			local_port_flash.write(wifi.localPort);
			replyHex(mSetLocalPort, NULL, NULL);
			NVIC_SystemReset();
			break;

		case mFactoryReset:
			first_time_prog_flash.write(true);
			replyHex(mFactoryReset, NULL, NULL);
			NVIC_SystemReset();
			break;

		case mGetFreeRam:
			replyBuffer[3] = (uint8_t)freeRam();
			replyBuffer[2] = (uint8_t)(freeRam() >> 8);
			replyHex(mGetFreeRam, 2, NULL);
			break;

		case mGetRssi:
			wifi.rssi = WiFi.RSSI();
			replyBuffer[5] = wifi.rssi;
			replyBuffer[4] = wifi.rssi >> 8;
			replyBuffer[3] = wifi.rssi >> 16;
			replyBuffer[2] = wifi.rssi >> 24;
			replyHex(mGetRssi, 4, NULL);
			break;

		case mGetLedPerformance:
			replyBuffer[5] = dled.ledPerformance;
			replyBuffer[4] = dled.ledPerformance >> 8;
			replyBuffer[3] = dled.ledPerformance >> 16;
			replyBuffer[2] = dled.ledPerformance >> 24;
			replyHex(mGetLedPerformance, 4, NULL);
			break;

		/*case mSetKey:
			key[0] = wifi.packetBuffer[4];
			key[1] = wifi.packetBuffer[5];
			keyTmp = ((uint16_t)key[0] << 8) | key[1];
			key_flash.write(keyTmp);
			NVIC_SystemReset();
			break;

			case mRetrieveKey:
				if(wifi.packetBuffer[4] == 0x10 && wifi.packetBuffer[5] == 0x15 && wifi.packetBuffer[6] == 0x10 && wifi.packetBuffer[7] == 0x10)
				{
					replyBuffer[1] = key[0];
					replyBuffer[0] = key[1];
					replyHex(mSetConfetti, NULL, NULL);
				}
				break;*/

		default:
			replyHex(NULL, NULL, ercInvalidCmd);
			break;
		}

	}

	void replyHex(uint16 aCmd, uint8 aSize, uint16 aErrorCode)
	{
		if (aErrorCode == ercInvalidCmd)
		{
			replyBuffer[1] = (uint8_t)ercInvalidCmd;
			replyBuffer[0] = (uint8_t)(ercInvalidCmd >> 8);
		}
		else if (aErrorCode == ercOffLimits)
		{
			replyBuffer[1] = (uint8_t)ercOffLimits;
			replyBuffer[0] = (uint8_t)(ercOffLimits >> 8);
		}
		else
		{
			replyBuffer[1] = (uint8_t)aCmd;
			replyBuffer[0] = (uint8_t)(aCmd >> 8);
		}
		wifi.Udp.beginPacket(wifi.Udp.remoteIP(), wifi.Udp.remotePort());
		wifi.Udp.write(replyBuffer, aSize + 2);
		wifi.Udp.endPacket();
	}

	void replyString(char aReplyBuffer[]) {
		wifi.Udp.beginPacket(wifi.Udp.remoteIP(), wifi.Udp.remotePort());
		wifi.Udp.write(aReplyBuffer);
		wifi.Udp.endPacket();
	}



public:
	
	uint8_t key[2] = { 0x00, 0x00 };
	
	void setKey(uint16_t aKey) {
		key[0] = aKey;
		key[1] = aKey >> 8;
	}

	void status() {

	}

	void poll() {
		int packetSize = wifi.Udp.parsePacket();
		if (packetSize) // If there's data available, read a packet
		{
			wifi.Udp.read(wifi.packetBuffer, 25);
			DEBUG_PRINT("Received packet of size ");
			DEBUG_PRINT(packetSize);
			DEBUG_PRINT("From ");
			IPAddress remoteIp = wifi.Udp.remoteIP();
			DEBUG_PRINT(remoteIp);
			DEBUG_PRINT(", port ");
			DEBUG_PRINT_LN(wifi.Udp.remotePort());

			DEBUG_PRINT("Contents: ");
			DEBUG_PRINT_HEX(wifi.packetBuffer[0]);
			DEBUG_PRINT_HEX(wifi.packetBuffer[1]);
			DEBUG_PRINT_HEX(wifi.packetBuffer[2]);
			DEBUG_PRINT_HEX(wifi.packetBuffer[3]);
			DEBUG_PRINT_HEX(wifi.packetBuffer[4]);
			DEBUG_PRINT_LN();

			/*============================================================*/
			/* Smart D-LED Key (Default key is 0x12FF)                    */
			/*============================================================*/
			if (wifi.packetBuffer[0] == key[1] && wifi.packetBuffer[1] == key[0])
			{
				command = ((uint16_t)wifi.packetBuffer[2] << 8) | wifi.packetBuffer[3];

				decode(command);

			}

			DEBUG_PRINT_LN("Client disonnected");
		}
	
	}

	
	
};

apiClass api;