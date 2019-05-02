/***************************************************************
* FILE NAME: confetti.h
*
* Mark Kriegsman, December 2014
*
* Modified/Ajusted for Smart D-LED by Dylan Meng, April 2019
*
***************************************************************/

class rainbowClass {

protected:

	uint8_t currentHue = 0;


public:

	uint8_t speed = 1;
	uint8_t direction = 0;
	uint8_t deltaHue = 200;
	uint8_t hueRotation = 5;
	uint8_t bpmA = 17;
	uint8_t bpmB = 13;

	void beat()
	{
		uint8_t beatA = beatsin8(17, 0, 255);
		uint8_t beatB = beatsin8(13, 0, 255);
		fill_rainbow(dled.leds, dled.num_leds, (beatA + beatB) / 2, 8);       
	}

	void smart()
	{
		EVERY_N_MILLIS_I(srSpeedTmp, 1)
		{
			if (direction == 1) currentHue += hueRotation; else currentHue -= hueRotation;
			fill_rainbow(dled.leds, dled.num_leds, currentHue, deltaHue);
			srSpeedTmp.setPeriod(speed);
		} 
	}
};

rainbowClass rainbow;








