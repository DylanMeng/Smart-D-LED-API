/***************************************************************
* FILE NAME: buttons.h
*
* Created 21 Nov 2006 by David A. Mellis
*
* Modified/Ajusted for Smart D-LED by Dylan Meng, April 2019
*
***************************************************************/

class buttonClass {

protected:

    // Button #1 with debouce                                   
	uint8_t btn_1_state;
	uint8_t btn_1_last_state = LOW;
	unsigned long btn_1_last_debounce_time = 0;  // the last time the output pin was toggled
	unsigned long btn_1_debounce_delay = 300;    // the debounce time

	// Button #2 with debouce    
	uint8_t btn_2_state;
	uint8_t btn_2_last_state = LOW;
	unsigned long btn_2_last_debounce_time = 0;  // the last time the output pin was toggled
	unsigned long btn_2_debounce_delay = 500;    // the debounce time

public:

	void init() {
		// Button #1: Re-Connect
		pinMode(BTN_1_PIN, INPUT);

		// Button #2: Factory Reset
		pinMode(BTN_2_PIN, INPUT);
	}

	// Button #1 Direct wifi ON/OFF
	void directState() {

		int btn_1_reading = digitalRead(BTN_1_PIN);

		if (btn_1_reading != btn_1_last_state) {
			btn_1_last_debounce_time = millis();  // reset the debouncing timer
		}
		if ((millis() - btn_1_last_debounce_time) > btn_1_debounce_delay) {

			if (btn_1_reading != btn_1_state) {
				btn_1_state = btn_1_reading;

				if (btn_1_state == HIGH) {
				
					if (direct_wifi_flash.read() == true)
					{
						direct_wifi_flash.write(false);  // Turn off direct wifi
						statusLed.blink(35, 10);
						NVIC_SystemReset();
					}

					if (direct_wifi_flash.read() == false)
					{
						direct_wifi_flash.write(true);  // Turn on direct wifi
						statusLed.blink(35, 10);
						NVIC_SystemReset();
					}


					btn_1_last_state = btn_1_reading;

					
				}
			}
		}

		btn_1_last_state = btn_1_reading;
	}

	void routerConnect() {

		int btn_2_reading = digitalRead(BTN_2_PIN);

		if (btn_2_reading != btn_2_last_state) {
			btn_2_last_debounce_time = millis();  // reset the debouncing timer
		}
		if ((millis() - btn_2_last_debounce_time) > btn_2_debounce_delay) {

			if (btn_2_reading != btn_2_state) {
				btn_2_state = btn_2_reading;

				if (btn_2_state == HIGH) {

					if (direct_wifi_flash.read() == false)
					{
						dled.blackout();

						wifi.startProvisionning();
					}
					}
			}
		}

		btn_2_last_state = btn_2_reading;
	}
	

	void factory_reset() {
		// TO-DO
	}

};

buttonClass button;