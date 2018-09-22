#include "TSL2561SensorReader.h"

TSL2561SensorReader::TSL2561SensorReader(String name, tsl2561Gain_t gain, tsl2561IntegrationTime_t timing)
    : SensorReader(name), gain{gain}, timing{timing}, tsl{TSL2561_ADDR_FLOAT} {}

bool TSL2561SensorReader::initializeSensor() {
	initialized = tsl.begin();
	if (initialized) {
		tsl.setGain(gain);
		tsl.setTiming(timing);
	}
	return initialized;
}

void TSL2561SensorReader::readSensor(JsonObject &jsonObject) {
	uint32_t lum = tsl.getFullLuminosity();
	uint16_t ir = lum >> 16;
	uint16_t full = lum & 0xFFFF;

	jsonObject[name + "I"] = ir;
	jsonObject[name + "F"] = full;
	jsonObject[name + "L"] = tsl.calculateLux(full, ir);
}
