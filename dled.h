/***************************************************************
* FILE NAME: dled.h
*
* MIT License
*
* FastLED: https://github.com/FastLED/FastLED
*
* Modified/Ajusted for Smart D-LED by Dylan Meng, April 2019
*
***************************************************************/

// Max number of leds
#define MAX_NUM_LEDS	600 

// Chipsets Type
#define sWS2812B     0x00  
#define sWS2812      0x01  
#define sNEOPIXEL    0x02
#define sWS2811      0x03
#define sTM1803      0x04
#define sTM1804      0x05
#define sTM1809      0x06
#define sAPA104      0x07
#define sUCS1903	 0x08
#define sUCS1903B	 0x09
#define sGW6205      0x0A
#define sGW6205_400  0x0B
#define sWS2801      0x0C  
#define sSM16716	 0x0D
#define sLPD8806	 0x0E
#define sP9813		 0x0F
#define sAPA102		 0x10  
#define sDOTSTAR	 0x11

// Color order (not implemented yet) 
#define cRGB 1
#define cRBG 2
#define cGRB 3
#define cGBR 4
#define cBRG 5
#define cBGR 6

class dledClass {

protected:
	   
public:
	CRGB leds[MAX_NUM_LEDS];

	uint8_t chipsetType;
	uint16_t num_leds;

	bool state = false; // leds on/off

	uint8_t brightness = 200;  // Brightness control
	uint8_t minBrightness = 0; // Not all led react the same at low brightness


	// LEDs Power Limitation             
	uint8_t  limitPower = 0x00;  // 0x00 = no power limitations, 0x01 = limiting power
	uint16_t milliamps = 5000;   // Default max amps = 5A = 25 Watt
	
	unsigned long ledPerformance;

	void init(uint8_t aChipsetType, uint16_t aNumLeds) {
		
		pinMode(LED_EN_PIN, OUTPUT);     // Enable bit level converter control
		digitalWrite(LED_EN_PIN, LOW);   // Enable LED strip

		chipsetType = aChipsetType;
		num_leds = aNumLeds;

		switch (chipsetType) {
		case sWS2812B:
			FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, num_leds);
			break;
		case sWS2812:
			FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, num_leds);
			break;
		case sNEOPIXEL:
			FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, num_leds);
			break;
		case sWS2811:
			FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, num_leds);
			break;
		case sWS2801:
			FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, num_leds);
			break;
		case sTM1803:
			FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, num_leds);
			break;
		case sTM1804:
			FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, num_leds);
			break;
		case sTM1809:
			FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, num_leds);
			break;
		case sAPA104:
			FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, num_leds);
			break;
		case sUCS1903:
			FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, num_leds);
			break;
		case sUCS1903B:
			FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, num_leds);
			break;
		case sGW6205:
			FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, num_leds);
			break;
		case sGW6205_400:
			FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, num_leds);
			break;
		case sSM16716:
			FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, num_leds);
			break;
		case sLPD8806:
			FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, num_leds);
			break;
		case sP9813:
			FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, num_leds);
			break;
		case sAPA102:
			FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, num_leds);
			break;
		case sDOTSTAR:
			FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, num_leds);
			break;
		default:
			FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, num_leds); // Default support is WS2812B 
			break;
		}
	}

	void setPower(uint8_t aLimitState, uint16_t aMaxMilliamps) {
		limitPower = aLimitState;
		milliamps = aMaxMilliamps;

		if (limitPower) {
			FastLED.setMaxPowerInVoltsAndMilliamps(5, milliamps);
		}
	}

	void setBrightness(uint8_t aBrightness) {
		brightness = aBrightness;
		FastLED.setBrightness(brightness);
	}

	void refresh() {
		FastLED.delay(1000 / 120);
		unsigned long start = micros();
		FastLED.show();
		unsigned long end = micros();
		ledPerformance = end - start; // Compute Fastled.show() performance in uS (not very precise but it give a general idea of the performance)
	}

	void blackout()
	{
		for (int i = 0; i <= MAX_NUM_LEDS; i++) {
			leds[i] = CRGB::Black;
		}
	}

	void colorOrderCalibrate() {
		leds[0] = CRGB(255, 0, 0);
		leds[1] = CRGB(0, 255, 0);
		leds[2] = CRGB(0, 255, 0);
		leds[3] = CRGB(0, 0, 255);
		leds[4] = CRGB(0, 0, 255);
		leds[5] = CRGB(0, 0, 255);
	}

};

dledClass dled;