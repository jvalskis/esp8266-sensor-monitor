#ifndef _SENSOR_READER_H
#define _SENSOR_READER_H

#include <ArduinoJson.h>

class SensorReader {
	protected:
	bool initialized;
	String name;

	public:
	SensorReader(String name);
	void read(JsonObject &jsonObject);
	bool init();

	protected:
	virtual bool initializeSensor() = 0;
	virtual void readSensor(JsonObject &jsonObject) = 0;
};

#endif
