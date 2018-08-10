#include "WifiConnector.h"

WifiConnector::WifiConnector() {}

boolean WifiConnector::connect(const char *ssid, const char *password) {
	WiFi.mode(WIFI_STA);
	WiFi.disconnect();
	delay(100);

	Serial.println(F("Trying Connect to Router"));
	Serial.print(F("SSID: "));
	Serial.println(ssid);
	Serial.print(F("Waiting"));

	WiFi.persistent(false);
	WiFi.mode(WIFI_OFF);  // this is a temporary line, to be removed after SDK
	                      // update to 1.5.4
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);

	int attempts = 60;
	while (WiFi.status() != WL_CONNECTED) {
		blink(250);
		Serial.print(F("."));
		if (attempts-- < 0) {
			Serial.print(F("Cannot connect to specified WiFi, status is "));
			Serial.println(WiFi.status());
			return false;
		}
	}

	blink(100);
	blink(100);
	blink(100);

	Serial.println(F(""));
	Serial.println(F("WiFi connected"));
	Serial.print(F("IP address: "));
	Serial.print(WiFi.localIP());
	Serial.println(F(""));
	return true;
}

void WifiConnector::blink(int length) {
	digitalWrite(LED_BUILTIN, LOW);
	delay(length);
	digitalWrite(LED_BUILTIN, HIGH);
	delay(length);
}