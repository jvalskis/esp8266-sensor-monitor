#include "WifiConnector.h"

WifiConnector::WifiConnector(LedFeedback &ledFeedback): ledFeedback{ledFeedback} {}

bool WifiConnector::connect(const char *ssid, const char *password) {
	Serial.println(F("WIFI: Trying to connect. SSID: "));
	Serial.println(ssid);

	WiFi.persistent(false);
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);

	int attempts = 60;
	Serial.print(F("Connecting"));
	while (WiFi.status() != WL_CONNECTED) {
		ledFeedback.blinkFast(1);
		Serial.print(F("."));
		if (attempts-- < 0) {
			Serial.print(F("WIFI: could not connect. Status: "));
			Serial.println(WiFi.status());
			return false;
		}
	}

	ledFeedback.blinkFast(3);

	Serial.print(F("WIFI: connected. IP address: "));
	Serial.println(WiFi.localIP());
	return true;
}