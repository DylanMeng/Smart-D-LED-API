class pulseClass {

public:

	uint8_t rotateEnable = 0x00;
	uint8_t bpm = 0x10;
	uint8_t hue = 0x10;
	uint8_t paletteId = cpPartyColors;
	CRGBPalette16 gPal;

	void setPalette(uint8_t aPalette) {

		paletteId = aPalette;
		// Palette select
		switch (paletteId)
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
			gPal = PartyColors_p;
			break;
		}
	}

	void refresh() {

		uint8_t beat = beatsin8(bpm, 64, 255);
		for (int i = 0; i < dled.num_leds; i++)
		{
			dled.leds[i] = ColorFromPalette(gPal, hue + (i * 2), beat - hue + (i * 10));
		}

		EVERY_N_MILLISECONDS(20) {
			if (rotateEnable) hue++;
		}
	}
	
};

pulseClass pulse;