#include "DHT11SensorReader.h"
#include <Arduino.h>

DHT11SensorReader::DHT11SensorReader(uint8_t pin)
    : SensorReader(pin), dht{pin, DHT22} {}

void DHT11SensorReader::read(JsonObject &jsonObject) {
	float h = dht.readHumidity();
	float t = dht.readTemperature();

	if (isnan(h) || isnan(t)) {
		Serial.println(F("Failed to read from DHT sensor!"));
	} else {
		jsonObject["MS2T"] = t;
		jsonObject["MS2H"] = h;
	}
}
