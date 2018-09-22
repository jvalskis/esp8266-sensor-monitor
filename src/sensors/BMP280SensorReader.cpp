#include "BMP280SensorReader.h"
#include <Arduino.h>

BMP280SensorReader::BMP280SensorReader(String name) : SensorReader(name) {}

bool BMP280SensorReader::initializeSensor() {
	return bmp.begin();
}

void BMP280SensorReader::readSensor(JsonObject &jsonObject) {
	jsonObject[name + "T"] = bmp.readTemperature();
	jsonObject[name + "P"] = bmp.readPressure();
}
