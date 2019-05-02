/***************************************************************
* FILE NAME: status_led.h
*
* MIT License
*
* Copyright (c) 2019 Dylan Meng
*
***************************************************************/

class statusLedClass {

protected:
	unsigned long status_led_previous_millis = 0;
	int state_status_led = LOW;

public:

	void init() {
		pinMode(STATUS_LED_PIN, OUTPUT);
	}

	void blink(uint8 tDelay, uint8 numBlink)
	{
		for (int i = 0; i < numBlink; i++) { // Blink status led for feedback
			digitalWrite(STATUS_LED_PIN, HIGH);
			delay(tDelay);
			digitalWrite(STATUS_LED_PIN, LOW);
			delay(tDelay);
		}
	}

	void blinkMillis(unsigned long status_led_interval)
	{
		unsigned long currentMillis = millis();
		if (currentMillis - status_led_previous_millis > status_led_interval)
		{
			status_led_previous_millis = currentMillis;

			if (state_status_led == LOW)
				state_status_led = HIGH;
			else
				state_status_led = LOW;

			digitalWrite(STATUS_LED_PIN, state_status_led);
		}
	}

	void state(bool state) {
		if (state == false)
			digitalWrite(STATUS_LED_PIN, LOW);
		else if (state == true)
			digitalWrite(STATUS_LED_PIN, HIGH);
	}

};

statusLedClass statusLed;
