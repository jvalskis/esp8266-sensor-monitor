#ifndef _TSL2561_SENSOR_READER_H
#define _TSL2561_SENSOR_READER_H

#include <Arduino.h>
#include <TSL2561.h>
#include "SensorReader.h"

class TSL2561SensorReader : public SensorReader {
	private:
	bool initialized;
	// Gain setting, 0 = X1, 1 = X16;
	tsl2561Gain_t gain;
	// Integration ("shutter") time in milliseconds
	tsl2561IntegrationTime_t timing;
	TSL2561 tsl;

	public:
	TSL2561SensorReader(
	    tsl2561Gain_t gain = TSL2561_GAIN_0X,
	    tsl2561IntegrationTime_t timing = TSL2561_INTEGRATIONTIME_13MS);
	boolean initialize();
	void read(JsonObject &jsonObject);
};

#endif
