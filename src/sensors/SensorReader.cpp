#include "SensorReader.h"
#include <Arduino.h>

SensorReader::SensorReader(String name) : name{name} {}

void SensorReader::read(JsonObject &jsonObject) {
	if (!initialized && !init()) {
		return;
	}
	readSensor(jsonObject);
}

bool SensorReader::init() {
	initialized = initializeSensor();
	if (!initialized) {
		Serial.print(F("Could not find a valid "));
		Serial.print(name);
		Serial.println(F(" sensor."));
	}
	return initialized;
}
