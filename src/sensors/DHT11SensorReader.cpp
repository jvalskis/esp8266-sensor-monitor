#include "DHT11SensorReader.h"
#include <Arduino.h>

DHT11SensorReader::DHT11SensorReader(String name, uint8_t pin)
    : SensorReader(name), dht{pin, DHT22} {}

bool DHT11SensorReader::initializeSensor() {
	return true;
}

void DHT11SensorReader::readSensor(JsonObject &jsonObject) {
	float h = dht.readHumidity();
	float t = dht.readTemperature();

	if (isnan(h) || isnan(t)) {
		Serial.println(F("Failed to read from DHT sensor!"));
	} else {
		jsonObject[name + "T"] = t;
		jsonObject[name + "H"] = h;
	}
}
