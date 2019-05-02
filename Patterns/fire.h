/***************************************************************
* FILE NAME: fire.h
*
* Fire2012 by Mark Kriegsman, July 2012
*
* Modified/Ajusted for Smart D-LED by Dylan Meng, April 2019
*
***************************************************************/

class fireClass {

protected:

	byte heat[MAX_NUM_LEDS];
	CRGBPalette16 gPal;


public:
	
	uint8_t cooling = 100;
	uint8_t sparking = 200;
	uint8_t direction = 0;
	uint8_t palette = 0;

	void noPalette()
	{
		// Step 1.  Cool down every cell a little
		for (int i = 0; i < dled.num_leds; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / dled.num_leds) + 2));
		}

		// Step 2.  Heat from each cell drifts 'up' and diffuses a little
		for (int k = dled.num_leds - 1; k >= 2; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}

		// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
		if (random8() < sparking) {

			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}

		// Step 4.  Map from heat cells to LED colors
		for (int j = 0; j < dled.num_leds; j++) {
			CRGB color = HeatColor(heat[j]);
			int pixelnumber;
			if (direction) {
				pixelnumber = (dled.num_leds - 1) - j;
			}
			else {
				pixelnumber = j;
			}
			dled.leds[pixelnumber] = color;
		}
	}

	void withPalette() {
		// Step 1.  Cool down every cell a little
		for (int i = 0; i < dled.num_leds; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / dled.num_leds) + 2));
		}

		// Step 2.  Heat from each cell drifts 'up' and diffuses a little
		for (int k = dled.num_leds - 1; k >= 2; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}

		// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
		if (random8() < sparking) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}

		// Step 4.  Map from heat cells to LED colors
		for (int j = 0; j < dled.num_leds; j++) {
			// Scale the heat value from 0-255 down to 0-240
			// for best results with color palettes.
			byte colorindex = scale8(heat[j], 240);

			switch (palette)
			{
			case cpPartyColors:
				gPal = PartyColors_p;
				break;
			case cpCloudColors:
				gPal = CloudColors_p;
				break;
			case cpLavaColors:
				gPal = LavaColors_p;
				break;
			case cpOceanColors:
				gPal = OceanColors_p;
				break;
			case cpForestColors:
				gPal = ForestColors_p;
				break;
			case cpRainbowColors:
				gPal = RainbowColors_p;
				break;
			case cpRainbowStripeColors:
				gPal = RainbowStripeColors_p;
				break;
			case cpHeatColors:
				gPal = HeatColors_p;
				break;
			default:
				gPal = HeatColors_p;
				break;
			}
			CRGB color = ColorFromPalette(gPal, colorindex);
			
			int pixelnumber;
			if (direction) {
				pixelnumber = (dled.num_leds - 1) - j;
			}
			else {
				pixelnumber = j;
			}
			dled.leds[pixelnumber] = color;
		}
	}

};

fireClass fire;





















void fireWithPalette()
{
	/*// Step 1.  Cool down every cell a little
	for (int i = 0; i < num_leds; i++) {
		heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / num_leds) + 2));
	}

	// Step 2.  Heat from each cell drifts 'up' and diffuses a little
	for (int k = num_leds - 1; k >= 2; k--) {
		heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
	}

	// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
	if (random8() < sparking) {
		int y = random8(7);
		heat[y] = qadd8(heat[y], random8(160, 255));
	}

	// Step 4.  Map from heat cells to LED colors
	for (int j = 0; j < num_leds; j++) {
		// Scale the heat value from 0-255 down to 0-240
		// for best results with color palettes.
		byte colorindex = scale8(heat[j], 240);
		CRGB color = ColorFromPalette(firePalette, colorindex);
		int pixelnumber;
		if (fireDirection) {
			pixelnumber = (num_leds - 1) - j;
		}
		else {
			pixelnumber = j;
		}
		leds[pixelnumber] = color;
	}*/
}

