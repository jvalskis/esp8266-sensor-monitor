#include "DeviceInfoReader.h"
#include <Arduino.h>
#include "Properties.h"

ADC_MODE(ADC_VCC);

DeviceInfoReader::DeviceInfoReader(String name) : SensorReader(name) {}

void DeviceInfoReader::readSensor(JsonObject &jsonObject) {
	jsonObject["free_heap"] = ESP.getFreeHeap();
	jsonObject["vcc"] = ESP.getVcc() / 1000.0;
}

bool DeviceInfoReader::initializeSensor() {
	return true;
}

void DeviceInfoReader::readAttributes(JsonObject &jsonObject) {
	jsonObject["firmware_version"] = FIRMWARE_VERSION;
	jsonObject["serial_number"] = ESP.getChipId();
	jsonObject["name"] = SOURCE_ID;
}
