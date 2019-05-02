/***************************************************************
* FILE NAME: Smart_D_LED.ino
* 
* MIT License
*
* Copyright (c) 2019 Dylan Meng
* 
* For any Bug report, Feature request, Pull request, 
*	Positive criticism, and Donation.
*
* Please visit: https://github.com/DylanMeng/Smart-D-LED-API
*				https://github.com/DylanMeng/Smart-D-LED-REMOTE
*				https://github.com/DylanMeng/Smart-D-LED-PCB
*				https://github.com/DylanMeng/Smart-D-LED-TOOLS
*				https://github.com/DylanMeng/Smart-D-LED-TOWER
*
***************************************************************/

/*============================================================*/
/* Import library                                             */
/*============================================================*/  
//#include <SFU.h>				   // Add support for serial flash update       (LGPL-2.1)  
#include <FastLED.h>		       // Add support to control digital LED strip  (MIT)
#include <SPI.h>				   // Add support for SPI device				(LGPL-2.1)
#include <WiFi101.h>		       // Add support for ATWINC1500				(LGPL-2.1)
#include <WiFi101OTA.h>		       // Add support for over the air update       (LGPL-2.1)
#include <WiFiUdp.h>		       // Add support for udp protocol			    (LGPL-2.1)
//#include <Smart_D_LED_Bonjour.h>   // Add support for Smart-D-LED Bonjour       (LGPL-2.1 - Modification of Wifi101OTA)
#include <FlashStorage.h>		   // Add support for internal flash			(LGPL-2.1)
#include <wiring_private.h>        // Add support for custom pin definition     (LGPL-2.1)
#include <SerialFlash.h>           // Add support for SPI flash				    (MIT)
#include <ArduinoSound.h>		   // Add support for I2S mic					(LGPL-2.1)
#include <CRC32.h>				   // Add support for CRC32					    (MIT)

#include "api_commands.h"		   // Add all API command

/*============================================================*/
/* Version control                                            */
/*============================================================*/
char firmwareVersion[] = "0.0.1";

/*============================================================*/
/* Hardware PIN for Smart-D-LED-PCB                           */
/*============================================================*/

// ATWINC1500 - Wireless Module
#define WINC_CS		8	
#define WINC_IRQ	7	
#define WINC_RST	5	
#define WINC_EN		2	

#define DATA_PIN    11    // LED strip data
#define CLOCK_PIN   13	  // LED strip clock

#define FLASH_CS_PIN  10  // External SPI flash chip select

#define LED_EN_PIN	6     // Bit level converter enable

#define STATUS_LED_PIN 4  // Red LED for some feedback

#define BTN_1_PIN   20    // Direct wifi state select
#define BTN_2_PIN   21    // Reconnect wifi 

/*============================================================*/
/* Reserve bytes in flash storage (data is keep after reset)  */
/*============================================================*/
FlashStorage(direct_wifi_flash, bool);
FlashStorage(ip_address_flash, uint32_t);
FlashStorage(led_type_flash, uint8_t);
FlashStorage(led_color_order_flash, uint8_t);
FlashStorage(first_time_prog_flash, uint8_t);
FlashStorage(local_port_flash, uint16_t)
FlashStorage(fps_flash, uint16_t);
FlashStorage(num_leds_flash, uint16_t);
FlashStorage(key_flash, uint16_t);
FlashStorage(power_limit_state_flash, uint8_t);
FlashStorage(power_max_milliamps_flash, uint16_t);

/*============================================================*/
/* Extra code to clean up the main                            */
/*============================================================*/
#include "status_led.h"

#include "debug.h"

#include "dled.h"
#include "mic.h"

#include "ota.h"

#include "Patterns/color.h"
#include "Patterns/gradient.h"
#include "Patterns/rainbow.h"
#include "Patterns/fire.h"
#include "Patterns/sinelon.h"
#include "Patterns/palette.h"
#include "Patterns/pulse.h"
#include "Patterns/juggle.h"
#include "Patterns/confetti.h"

#include "Effects/vumeter.h"
#include "Effects/glitter.h"

#include "Selectors/patterns.h"
#include "Selectors/effects.h"

#include "wifi.h"
#include "api.h"

#include "buttons.h"


/*============================================================*/
/* SETUP                                                      */
/*============================================================*/
void setup() {
	
	DEBUG_SERIAL_INIT(9600);

	button.init();
	button.factory_reset();	
	
	statusLed.blink(150, 2); // Blink to show boot up

	/*============================================================*/
	/* First time programming: DEFAULT setting                    */
	/*============================================================*/
	if (first_time_prog_flash.read() != 0xAA)
	{
		fps_flash.write(400);			       // Default framerate is 400Hz
		led_type_flash.write(sAPA102);		   // Default led strip is WS2812B
		led_color_order_flash.write(cRGB);     // Default color order is RGB - not implemented yet
		num_leds_flash.write(60);			   // Default number of leds is 60
		direct_wifi_flash.write(false);		   // Default wifi mode (false for router, true for direct wifi)
		ip_address_flash.write(0xC0A80101);    // Default IP adress is 192.168.1.1 (0xC0A80101)
		local_port_flash.write(2390);		   // Default local port is 2390
		key_flash.write(0x12FF);			   // Default device key is 0x12FF
		power_limit_state_flash.write(0x01);   // Default power state is limiting power
		power_max_milliamps_flash.write(5000); // Default max amps is 5A

		first_time_prog_flash.write(0xAA);     // No longer first time progamming
	} 
	
	// Mic setup
	mic.init();

	// Init SPI flash
	ota.initFlash();

	// Wifi setup	 
	wifi.init();
	wifi.direct(direct_wifi_flash.read());
	wifi.printStatus();  

	// API setup
	api.setKey(key_flash.read());

	// Dled setup
	dled.num_leds = num_leds_flash.read();
	dled.init(led_type_flash.read(), num_leds_flash.read());
	dled.setPower(power_limit_state_flash.read(), power_max_milliamps_flash.read());	
	
	// Default start-up pattern and effect
	pattern.select = pColorOrderCalibrate;
	effect.select = eNoEffect;
	
	// Start udp, bonjour, ota
	wifi.beginConnection(); 
  
	// Default start-up brightness
	dled.setBrightness(100);
}

/*============================================================*/
/* LOOP                                                       */
/*============================================================*/
void loop()
{
	button.directState();	 // Read button to switch from direct wifi to provisioning/routers
	button.routerConnect();  // Start provisioning mode (only work when direct wifi is off)

	//SmartdledBonjour.poll(); // Check for Bonjour question
	WiFiOTA.poll();			 // Check for OTA update

	wifi.verify();			 // Verify wifi integrity	
	api.poll();				 // Check for Smart-D-LED commands
	
	pattern.refresh();		 // Refresh selected pattern animation
	effect.refresh();		 // Refresh selected effect animation
	
	dled.refresh();			 // Refresh led strip data
}
