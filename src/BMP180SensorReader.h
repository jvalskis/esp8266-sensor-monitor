#ifndef _BMP180_SENSOR_READER_H
#define _BMP180_SENSOR_READER_H

#include <Adafruit_BMP085.h>
#include "SensorReader.h"

class BMP180SensorReader : public SensorReader {
	private:
	Adafruit_BMP085 bmp;

	public:
	BMP180SensorReader();
	bool initialize();
	void read(JsonObject &jsonObject);
};

#endif
