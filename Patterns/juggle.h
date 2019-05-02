/***************************************************************
* FILE NAME: juggle.h
*
* Mark Kriegsman, December 2014
*
* Modified/Ajusted for Smart D-LED by Dylan Meng, April 2019
*
***************************************************************/

class juggleClass {

public:

	uint8_t saturation = 200;
	uint8_t hueRotation = 32;
	uint8_t fade = 20;

	void refresh() {
		fadeToBlackBy(dled.leds, dled.num_leds, fade);
		byte dothue = 0;
		for (int i = 0; i < 8; i++) {
			dled.leds[beatsin16(i + 7, 0, dled.num_leds - 1)] |= CHSV(dothue, saturation, 255);
			dothue += hueRotation;
		}
	}
};

juggleClass juggle;