#ifndef _BME280_SEED_SENSOR_READER_H
#define _BME280_SEED_SENSOR_READER_H

#include <Seeed_BME280.h>
#include "SensorReader.h"

class BME280SeedSensorReader : public SensorReader {
	private:
	BME280 bme;

	public:
	BME280SeedSensorReader(String name);
	
	protected:
	bool initializeSensor();
	void readSensor(JsonObject &jsonObject);
};

#endif
