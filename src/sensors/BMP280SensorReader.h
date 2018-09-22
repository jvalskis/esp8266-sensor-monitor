#ifndef _BMP280_SENSOR_READER_H
#define _BMP280_SENSOR_READER_H

#include <Adafruit_BMP280.h>
#include "SensorReader.h"

class BMP280SensorReader : public SensorReader {
	private:
	Adafruit_BMP280 bmp;

	public:
	BMP280SensorReader(String name);
	
	protected:
	bool initializeSensor();
	void readSensor(JsonObject &jsonObject);
};

#endif
