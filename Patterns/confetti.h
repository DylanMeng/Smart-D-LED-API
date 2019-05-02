/***************************************************************
* FILE NAME: confetti.h
*
* Mark Kriegsman, December 2014
*
* Modified/Ajusted for Smart D-LED by Dylan Meng, April 2019
*
***************************************************************/

class confettiClass {

public:

	uint8_t rotateEnable = 0x00;
	
	uint8_t hue = 100;
	uint8_t saturation = 200;

	uint8_t fade = 10;
		
	uint8_t random = 64;
	
	void refresh()
	{
		fadeToBlackBy(dled.leds, dled.num_leds, fade);
		int pos = random16(dled.num_leds);
		dled.leds[pos] += CHSV(hue + random8(random), saturation, 255);

		EVERY_N_MILLISECONDS(20) { 
			if (rotateEnable) hue++;
		}
	}
};

confettiClass confetti;