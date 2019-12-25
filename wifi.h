/***************************************************************
* FILE NAME: wifi.h
*
* Created 30 December 2012 by dlf (Metodo2 srl)
*
* Modified/Ajusted for Smart D-LED by Dylan Meng, April 2019
*
***************************************************************/

class wifiClass {

protected:

	uint8_t wifiStatus;

	const char apSsid[12] = "Smart-D-LED";

	boolean wifiReconnect(byte attempts) {
		byte nAttempts = 0;
		do {
			nAttempts++;
			DEBUG_PRINT("Reconnecting # of Attempts: ");
			DEBUG_PRINT(nAttempts);
			wifiStatus = WiFi.begin();
			unsigned long startTime = millis();
			do {
				delay(2000);
				wifiStatus = WiFi.status();
			} while (wifiStatus != WL_CONNECTED && millis() - startTime < 10000); // wait up to 10 seconds for connection
		} while (wifiStatus != WL_CONNECTED && nAttempts < attempts); // Try the # of attempt

		if (wifiStatus != WL_CONNECTED) {
			DEBUG_PRINT_LN("Fail to reconnect");
			return false;

		}
		DEBUG_PRINT_LN("Connected succesfully");
		wifiReconnected = true;
		return true;
	}
	
public:

	WiFiUDP Udp;
	uint16_t localPort = 2390; // Local port
	uint8_t packetBuffer[25];  // Incoming data buffer
	int32_t rssi; // WiFi Signal Strength
	bool wifiReconnected = false; // Reconnect flag to reset udp, bonjour, etc...

	void init() {
		WiFi.setPins(WINC_CS, WINC_IRQ, WINC_RST, WINC_EN); // ATWINC1500 pin config

		// Check if the wifi module is working correctly
		if (WiFi.status() == WL_NO_SHIELD) {
			while (1) // Critical error: blink of death
			{
				statusLed.blink(25, 1);
			}
			DEBUG_PRINT_LN("Critical ERROR: winc1500 unresponsive");
		}

	}
	
	void beginConnection()
	{
		if (!Udp.begin(local_port_flash.read())) {
			while (1) // Critical error: blink of death
			{
				statusLed.blink(25, 1);
			}
		}

		WiFiOTA.begin("SMART-D-LED", "ZTkNxAW3fv", SerialFlashStorage); // Start over the air update support with external flash storage and mdns request		
	}

	void verify() {
		EVERY_N_SECONDS(1) // Verify wifi integrity each second
		{
			switch (WiFi.status()) {

			case WL_NO_SHIELD:
				DEBUG_PRINT_LN("Fatal: winc1500 unresponsive");
				while (1) // Fatal error: blinks of death
				{
					statusLed.blink(25, 1);
				}
				break;

			case WL_IDLE_STATUS:
				DEBUG_PRINT_LN("Trying to connect");
				break;

			case WL_NO_SSID_AVAIL:
				DEBUG_PRINT_LN("No SSID are available");
				break;

			case WL_SCAN_COMPLETED:
				DEBUG_PRINT_LN("Scan completed");
				break;

			case WL_CONNECTED:
				DEBUG_PRINT_LN("Connected");
				if (wifiReconnected) {
					beginConnection();
					wifiReconnected = false;
				}
				break;

			case WL_CONNECT_FAILED:
				DEBUG_PRINT_LN("Fails to connect");
				break;

			case WL_CONNECTION_LOST:
				DEBUG_PRINT_LN("Connection lost");
				break;

			case WL_DISCONNECTED:
				DEBUG_PRINT_LN("Disconnected from local network");
				// Try to reconnect to last know local network - 3 attempts	
				if (wifiReconnect(3))
				{
					return;
				}
				else // Fail to reconnect start setup mode
				{
					startProvisionning();
					/*WiFi.beginProvision();

					while (WiFi.status() != WL_CONNECTED) {
						DEBUG_PRINT_LN("Waiting for setup");
						delay(1000);
					}*/

					wifiReconnected = true;
				}
				break;

			case WL_AP_LISTENING:
				DEBUG_PRINT_LN("AP listening");
				break;

			case WL_AP_CONNECTED:
				DEBUG_PRINT_LN("AP connected");
				break;

			case WL_AP_FAILED:
				while (1) // FAIL
				{
					statusLed.blink(100, 1);
				}
				DEBUG_PRINT_LN("AP failed");
				break;

			case WL_PROVISIONING:
				DEBUG_PRINT_LN("Provisioning mode");
				break;

			case WL_PROVISIONING_FAILED:
				DEBUG_PRINT_LN("Provisioning failed");
				break;
			}
		}
	}

	void direct(bool aState) {
		if (aState)
		{
			if (WiFi.beginAP(apSsid) != WL_AP_LISTENING) {
				DEBUG_PRINT_LN("Creating access point failed");
				// don't continue
				while (true);
			}
		}
		else
		{
			startProvisionning();
		}
	}

	void startProvisionning() {

		WiFi.beginProvision();

		while (WiFi.status() != WL_CONNECTED) {

			statusLed.blinkMillis(500);

		}

		statusLed.state(false); // Turn off status LED

	}

	void printStatus() {
		// print the SSID of the network you're attached to:
		DEBUG_PRINT("SSID: ");
		DEBUG_PRINT_LN(WiFi.SSID());

		// print your WiFi shield's IP address:
		IPAddress ip = WiFi.localIP();
		DEBUG_PRINT("IP Address: ");
		DEBUG_PRINT_LN(ip);

		// print the received signal strength:
		rssi = WiFi.RSSI();
		DEBUG_PRINT("signal strength (RSSI):");
		DEBUG_PRINT(rssi);
		DEBUG_PRINT_LN(" dBm");
	}
	
	
};

wifiClass wifi;

// TO-DO add ip save funciton (to find device ip addres without bonjour)
/*ipLocal = WiFi.localIP();  // Get local ip address
ipLocalTmp = ip_address_flash.read();
if (ipLocalTmp != ipLocal && directWifi == 0xAA)
{
	DEBUG_PRINT("IP IS DIF");
	ip_address_flash.write(ipLocal);
}*/