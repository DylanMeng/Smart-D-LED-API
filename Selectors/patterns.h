/***************************************************************
* FILE NAME: patterns.h
*
* MIT License
*
* Copyright (c) 2019 Dylan Meng
*
***************************************************************/

// Patterns
#define pNoPattern		0x00

#define pPaletteFill	0x01

#define pDoubleGradient	0x02
#define pTripleGradient	0x03
#define pQuadGradient	0x05

#define pStaticColorRGB 0x06
#define pStaticColorHSV 0x07

#define pRainbowBeat	0x08
#define pRainbowSmart	0x09

#define pSinelon		0x0A

#define pPulse			0x0B

#define pConfetti		0x0C

#define pFire			0x0D
#define pFirePalette    0x0E

#define pJuggle			0x0F

#define pGradientBPM	0xA0

#define pColorOrderCalibrate 0xF0

class patternsClass {

protected:

	void noPattern()
	{
		return;
	}

public:

	uint8_t select;

	void refresh() {
		switch (select)
		{
		case pNoPattern:
			noPattern();
			break;

		case pPaletteFill:
			palette.dynamic();
			break;

		case pDoubleGradient:
			gradient.doubleRGB();
			break;
		case pTripleGradient:
			gradient.tripleRGB();
			break;
		case pQuadGradient:
			gradient.quadRGB();
			break;

		case pStaticColorRGB:
			color.setRGB();
			break;
		case pStaticColorHSV:
			color.setHSV();
			break;

		case pPulse:
			pulse.refresh();
			break;

		case pRainbowBeat:
			rainbow.beat();
			break;

		case pRainbowSmart:
			rainbow.smart();
			break;

		case pConfetti:
			confetti.refresh();
			break;

		case pFire:
			fire.noPalette();
			break;

		case pFirePalette:
			fire.withPalette();
			break;
	
		case pJuggle:
			juggle.refresh();
			break;
	
		case pColorOrderCalibrate:
			dled.colorOrderCalibrate();
			break;

		case pSinelon:
			sinelon.refresh();
			break;

		case pGradientBPM:
			gradient.fadeBPM();
			break;

		default:
			noPattern();
			dled.blackout();
			break;
		}

	}
};

patternsClass pattern;