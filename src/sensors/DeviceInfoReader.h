#ifndef _DEVICE_INFO_READER_H
#define _DEVICE_INFO_READER_H

#include "SensorReader.h"

class DeviceInfoReader : public SensorReader {
	public:
	DeviceInfoReader(String name);
	void readAttributes(JsonObject &jsonObject);
	
	protected:
	bool initializeSensor();
	void readSensor(JsonObject &jsonObject);
};

#endif
