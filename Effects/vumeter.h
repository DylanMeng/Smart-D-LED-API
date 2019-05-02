/*
	LED VU meter for Arduino More info: http://learn.adafruit.com/led-ampli-tie/

	Written by Adafruit Industries.  Distributed under the BSD license.
	This paragraph must be included in any redistribution.

	Source code: https://github.com/adafruit/Adafruit_Learning_System_Guides/tree/master/LED_Ampli_Tie

	Modified/Ajusted for Smart D-LED by Dylan Meng, April 2019
*/
class vumeterClass {

protected:
	uint8_t peak = 16;		  // Peak level of column; used for falling dots
	uint8_t dotCount = 0;     // Frame counter for peak dot
	uint8_t dotHangCount = 0; // Frame counter for holding peak dot

	/*============================================================*/
	/* fscale (not modified)                                      */
	/*============================================================*/
	float fscale(float originalMin, float originalMax, float newBegin, float
		newEnd, float inputValue, float curve) {

		float OriginalRange = 0;
		float NewRange = 0;
		float zeroRefCurVal = 0;
		float normalizedCurVal = 0;
		float rangedValue = 0;
		boolean invFlag = 0;


		// condition curve parameter
		// limit range

		if (curve > 10) curve = 10;
		if (curve < -10) curve = -10;

		curve = (curve * -.1); // - invert and scale - this seems more intuitive - postive numbers give more weight to high end on output 
		curve = pow(10, curve); // convert linear scale into lograthimic exponent for other pow function

								/*
								Serial.println(curve * 100, DEC);   // multply by 100 to preserve resolution
								Serial.println();
								*/

								// Check for out of range inputValues
		if (inputValue < originalMin) {
			inputValue = originalMin;
		}
		if (inputValue > originalMax) {
			inputValue = originalMax;
		}

		// Zero Refference the values
		OriginalRange = originalMax - originalMin;

		if (newEnd > newBegin) {
			NewRange = newEnd - newBegin;
		}
		else
		{
			NewRange = newBegin - newEnd;
			invFlag = 1;
		}

		zeroRefCurVal = inputValue - originalMin;
		normalizedCurVal = zeroRefCurVal / OriginalRange;   // normalize to 0 - 1 float

															// Check for originalMin > originalMax  - the math for all other cases i.e. negative numbers seems to work out fine 
		if (originalMin > originalMax) {
			return 0;
		}

		if (invFlag == 0) {
			rangedValue = (pow(normalizedCurVal, curve) * NewRange) + newBegin;

		}
		else     // invert the ranges
		{
			rangedValue = newBegin - (pow(normalizedCurVal, curve) * NewRange);
		}

		return rangedValue;
	}

	/*============================================================*/
	/* draw line (modified)                                       */
	/*============================================================*/
	void drawLine(uint16_t from, uint16_t to, uint32_t c) {
		uint16_t fromTemp;
		if (from > to) {
			fromTemp = from;
			from = to;
			to = fromTemp;
		}
		for (int i = from; i <= to; i++) {
			dled.leds[i].setColorCode(c);
		}
	}

public:
	
	// uint8_t sampleWindow = 10;      // Sample window for average level
	uint16_t inputFloor = 10;        // Lower range
	uint16_t inputCeiling = 1000;	 // Max range (1023 = max)

	uint8_t fallingDotEnable = 0x01; // Falling dot ON/OFF
	uint8_t fallingDotHang = 5;	     // Time of pause before peak dot falls
	uint8_t fallingDotFall = 2;	     // Rate of falling peak dot
	uint8_t fallingDotHue = 0xFF;    // Falling dot hue color
	uint8_t fallingDotSat = 0xFF;    // Falling dot color saturation
	uint8_t fallingDotVal = 0xFF;    // Falling dot color value

	   
	void adjustable(void) {
	
		unsigned int c, y;

		//Scale the input logarithmically instead of linearly
		c = fscale(inputFloor, inputCeiling, dled.num_leds, 0, mic.readAmplitudeDelta(), 2);

		if (c < peak) {
			peak = c;        // Keep dot on top
			dotHangCount = 0;    // make the dot hang before falling
		}
		if (c <= dled.num_leds) { // Fill partial column with off pixels
			drawLine(dled.num_leds, dled.num_leds - c, 0);
		}

		if (fallingDotEnable == true) {
			// Set the peak dot to match the rainbow gradient
			y = dled.num_leds - peak;
			y = y - 1;
			dled.leds[y].setHSV(fallingDotHue, fallingDotSat, fallingDotVal);
		}

		// Frame based peak dot animation
		if (dotHangCount > fallingDotHang) { //Peak pause length
			if (++dotCount >= fallingDotFall) { //Fall rate
				peak++;
				dotCount = 0;
			}
		}
		else {
			dotHangCount++;
		}
	}
	
	void dynamic() {
		// TO-DO
	}
	
};

vumeterClass vumeter;