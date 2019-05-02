class gradientClass {

public:

	uint8_t red1 = 100;
	uint8_t red2 = 150;
	uint8_t red3 = 100;
	uint8_t red4 = 150;
	uint8_t green1 = 100;
	uint8_t green2 = 150;
	uint8_t green3 = 100;
	uint8_t green4 = 150;
	uint8_t blue1 = 100;
	uint8_t blue2 = 150;
	uint8_t blue3 = 100;
	uint8_t blue4 = 150;

	void doubleRGB() {
		fill_gradient_RGB(dled.leds, dled.num_leds, CRGB(red1, green1, blue1),
									      CRGB(red2, green2, blue2));
	}
	void tripleRGB() {
		fill_gradient_RGB(dled.leds, dled.num_leds, CRGB(red1, green1, blue1),
										  CRGB(red2, green2, blue2),
										  CRGB(red3, green3, blue3));
	}
	void quadRGB() {
		fill_gradient_RGB(dled.leds, dled.num_leds, CRGB(red1, green1, blue1),
									      CRGB(red2, green2, blue2),
									      CRGB(red3, green3, blue3),
										  CRGB(red4, green4, blue4));
	}

	uint8_t bpm = 20;
	uint8_t fromHue = 0;
	uint8_t toHue = 255;
	uint8_t direction = 0; 

	void fadeBPM() {
		uint8_t gradientHue = beatsin8(bpm, fromHue, toHue);

		if (direction == 0)
		{
			fill_gradient(dled.leds, dled.num_leds, CHSV(gradientHue, 255, 255), CHSV(gradientHue, 255, 255), FORWARD_HUES);
		}
		else if (direction == 1)
		{
			fill_gradient(dled.leds, dled.num_leds, CHSV(gradientHue, 255, 255), CHSV(gradientHue, 255, 255), BACKWARD_HUES);
		}
	}

};

gradientClass gradient;