/***************************************************************
* FILE NAME: effects.h
*
* MIT License
*
* Copyright (c) 2019 Dylan Meng
*
***************************************************************/

// Effects
#define eNoEffect		0
#define eAddGlitter		1
#define eVuMeter		2
#define eBreathing		3
#define eSoundblink		4
#define eGlitterActive	5
#define eGlitter		6

class effectsClass {

protected:

	void noEffect()
	{
		return;
	}

public:

	uint8_t select;
	   
	void refresh() {
		switch (select)
		{
		case eNoEffect:
			noEffect();
			break;
		case eAddGlitter:
			glitter.add();
			break;
		case eVuMeter:
			vumeter.adjustable();
			break;
		case eSoundblink:
			// TO-DO
			break;
		case eGlitterActive:
			glitter.soundReactive();
			break;
		case eGlitter:
			glitter.add();
			break;
		default:
			noEffect();
			break;
		}

	}
};

effectsClass effect;