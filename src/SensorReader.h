#ifndef _SENSOR_READER_H
#define _SENSOR_READER_H

#include <ArduinoJson.h>

class SensorReader {
	protected:
	uint8_t pin;
	bool initialized;

	public:
	SensorReader(uint8_t pin = 0) : pin{pin} {}
	virtual void read(JsonObject &jsonObject) = 0;
};

#endif
