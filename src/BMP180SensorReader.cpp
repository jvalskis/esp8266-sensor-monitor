#include "BMP180SensorReader.h"
#include <Arduino.h>

BMP180SensorReader::BMP180SensorReader() : SensorReader() {}

bool BMP180SensorReader::initialize() {
	initialized = bmp.begin();
	if (!initialized) {
		Serial.println(F("Could not find a valid BMP085 sensor."));
	}
	return initialized;
}

void BMP180SensorReader::read(JsonObject &jsonObject) {
	if (!initialized && !initialize()) {
		return;
	}
	jsonObject["MS1T"] = bmp.readTemperature();
	jsonObject["MS1P"] = bmp.readPressure();
}
