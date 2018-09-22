#include "BME280SeedSensorReader.h"
#include <Arduino.h>

BME280SeedSensorReader::BME280SeedSensorReader(String name) : SensorReader(name) {}

bool BME280SeedSensorReader::initializeSensor() {
	return bme.init();
}

void BME280SeedSensorReader::readSensor(JsonObject &jsonObject) {
	jsonObject[name + "T"] = bme.getTemperature();
	jsonObject[name + "P"] = bme.getPressure();
	jsonObject[name + "H"] = bme.getHumidity();
}
