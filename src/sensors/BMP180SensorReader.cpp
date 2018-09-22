#include "BMP180SensorReader.h"
#include <Arduino.h>

BMP180SensorReader::BMP180SensorReader(String name) : SensorReader(name) {}

bool BMP180SensorReader::initializeSensor() {
	return bmp.begin();
}

void BMP180SensorReader::readSensor(JsonObject &jsonObject) {
	jsonObject[name + "T"] = bmp.readTemperature();
	jsonObject[name + "P"] = bmp.readPressure();
}
