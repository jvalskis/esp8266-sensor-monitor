#ifndef _WIFI_CONNECTOR_H
#define _WIFI_CONNECTOR_H

#include <ESP8266WiFi.h>

class WifiConnector {
	public:
	WifiConnector();
	boolean connect(const char *ssid, const char *password);

	private:
	void blink(int timeout);
};

#endif
