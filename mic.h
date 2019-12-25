/***************************************************************
* FILE NAME: mic.h
*
* Created 23 November 2016 by Sandeep Mistry
*
* Modified/Ajusted for Smart D-LED by Dylan Meng, April 2019
*
***************************************************************/

class micClass {

protected:
	//AmplitudeAnalyzer amplitudeAnalyzer;
	int lastAmplitude;

public:

	bool available = false;

	int init() {
		// setup the I2S audio input for 44.1 kHz with 32-bits per sample
		//if (!AudioInI2S.begin(44100, 32)) {
			DEBUG_PRINT_LN("Failed to initialize I2S input!");
			available = false;
			return NULL;
		//}
		// configure the I2S input as the input for the amplitude analyzer
		//if (!amplitudeAnalyzer.input(AudioInI2S)) {
			DEBUG_PRINT_LN("Failed to set amplitude analyzer input!");
			available = false;
			return NULL;
		//}
		DEBUG_PRINT_LN("MIC GOOD");
		return true;

	}
	
	int readAmplitudeRaw() {
		// check if a new analysis is available
		//if (amplitudeAnalyzer.available()) {
			// read the new amplitude
			//return amplitudeAnalyzer.read();
		//}
	}

	int readAmplitudeDelta() {
	
		int amplitude = readAmplitudeRaw();

		amplitude >>= 15;

		int delta = abs(amplitude - lastAmplitude);

		lastAmplitude = amplitude;

		return delta;
	}

};

micClass mic;