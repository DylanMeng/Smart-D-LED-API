class colorClass {

public:

	// RGB Color
	uint8_t red	  = 0x2B;
	uint8_t green = 0x2D;
	uint8_t blue  = 0x5C;

	// HSV Color
	uint8_t hue = 215;
	uint8_t saturation = 255;
	uint8_t value = 255;

	void setHSV()
	{
		for (int i = 0; i <= dled.num_leds; i++) {
			for (int i = 0; i <= dled.num_leds; i++) {
				dled.leds[i] = CHSV(hue, saturation, value);
			}
		}
	}

	void setRGB()
	{
		for (int i = 0; i <= dled.num_leds; i++) {
			dled.leds[i] = CRGB(red, green, blue);
		}
	}

};

colorClass color;