#include "TSL2561SensorReader.h"

TSL2561SensorReader::TSL2561SensorReader(tsl2561Gain_t gain,
                                         tsl2561IntegrationTime_t timing)
    : SensorReader(), gain{gain}, timing{timing}, tsl{TSL2561_ADDR_FLOAT} {}

boolean TSL2561SensorReader::initialize() {
	initialized = tsl.begin();
	if (initialized) {
		tsl.setGain(gain);
		tsl.setTiming(timing);
	} else {
		Serial.println(F("Could not find a valid TSL2561 sensor."));
	}
	return initialized;
}

void TSL2561SensorReader::read(JsonObject &jsonObject) {
	if (!initialized && !initialize()) {
		return;
	}

	uint32_t lum = tsl.getFullLuminosity();
	uint16_t ir = lum >> 16;
	uint16_t full = lum & 0xFFFF;

	jsonObject["MS4I"] = ir;
	jsonObject["MS4F"] = full;
	jsonObject["MS4L"] = tsl.calculateLux(full, ir);
}
