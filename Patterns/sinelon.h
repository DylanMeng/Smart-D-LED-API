/***************************************************************
* FILE NAME: sinelon.h
*
* Mark Kriegsman, December 2014
*
* Modified/Ajusted for Smart D-LED by Dylan Meng, April 2019
*
***************************************************************/

class sinelonClass {

public:

	uint8_t rotateEnable = 0x00;
	uint8_t fade		 = 0x10;
	uint8_t bpm			 = 0x10;
	uint8_t hue		     = 0x00;
	uint8_t saturation   = 0x00;
	
	void refresh()
	{
		fadeToBlackBy(dled.leds, dled.num_leds, fade);
		int pos = beatsin16(bpm, 0, dled.num_leds - 1);
		dled.leds[pos] += CHSV(hue, saturation, 255);

		EVERY_N_MILLISECONDS(20) {
			if (rotateEnable) hue++;
		}
	}
};

sinelonClass sinelon;