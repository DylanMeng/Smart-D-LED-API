class colorClass {

protected:

public:

	// RGB Color
	uint8_t red;
	uint8_t green;
	uint8_t blue;

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