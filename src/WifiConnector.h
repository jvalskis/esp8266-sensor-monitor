#ifndef _WIFI_CONNECTOR_H
#define _WIFI_CONNECTOR_H

#include <ESP8266WiFi.h>
#include "LedFeedback.h"

class WifiConnector {
	private:
	LedFeedback ledFeedback;

	public:
	WifiConnector(LedFeedback &ledFeedback);
	bool connect(const char *ssid, const char *password);

};

#endif
