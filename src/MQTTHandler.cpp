#include "MQTTHandler.h"
#include <Arduino.h>

void MQTTControlHandler::handle(char *string) {
	Serial.print(F("Got: "));
	Serial.println(string);
}
