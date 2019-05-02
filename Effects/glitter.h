/***************************************************************
* FILE NAME: sinelon.h
*
* Mark Kriegsman, December 2014
*
* Modified/Ajusted for Smart D-LED by Dylan Meng, April 2019
*
***************************************************************/

class glitterClass {

public:

	fract8 chance = 80;
	uint8_t red = 255;
	uint8_t green = 255;
	uint8_t blue = 255;

	void add() {
		if (random8() < chance) {
			dled.leds[random16(dled.num_leds)] += CRGB(red, green, blue);
		}
	}

	void soundReactive() {

		fract8 chanceBySound = mic.readAmplitudeDelta();
		chanceBySound = map(chanceBySound, 0, 1023, 0, 255);

		if (random8() < chanceBySound) {
			dled.leds[random16(dled.num_leds)] += CRGB(red, green, blue);
		}

	}

};

glitterClass glitter;