#ifndef _DHT11_SENSOR_READER_H
#define _DHT11_SENSOR_READER_H

#include <DHT.h>
#include "SensorReader.h"

class DHT11SensorReader : public SensorReader {
	private:
	DHT dht;

	public:
	DHT11SensorReader(String name, uint8_t pin);

	protected:
	bool initializeSensor();
	void readSensor(JsonObject &jsonObject);
};

#endif
