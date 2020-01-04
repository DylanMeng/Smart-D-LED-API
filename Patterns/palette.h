class paletteClass {

protected:
	CRGBPalette16 gPal;
	TBlendType blendType = LINEARBLEND;
	uint8_t colorIndex = 0;

public:

	uint8_t speed = 100;

	void setPalette(uint8_t aPalette, uint8_t aBlendtype) {
		
		// Palette select
		switch (aPalette)
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

		// Blend type select
		switch (aBlendtype)
		{
		case cpNoBlend:
			blendType = NOBLEND;
			break;
		case cpLinearBlend:
			blendType = LINEARBLEND;
			break;
		default:
			blendType = LINEARBLEND;
			break;
		}
	}

	void dynamic()
	{
		EVERY_N_MILLISECONDS(20) {
			colorIndex = colorIndex + speed;   //if it is 0, then it will all stay the same
			fill_palette(dled.leds, dled.num_leds, colorIndex, 128 / dled.num_leds, gPal, dled.brightness, blendType);
		}
	}

};

paletteClass palette;