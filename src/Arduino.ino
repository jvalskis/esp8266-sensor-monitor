#include <Arduino.h>

#include <SimpleTimer.h>
#include <Wire.h>
#include "sensors/BMP180SensorReader.h"
#include "sensors/BMP280SensorReader.h"
#include "sensors/BME280SeedSensorReader.h"
#include "sensors/DHT11SensorReader.h"
#include "sensors/TSL2561SensorReader.h"
#include "sensors/DeviceInfoReader.h"
#include "MQTTConnector.h"
#include "Properties.h"
#include "WifiConnector.h"
#include "LedFeedback.h"

WiFiClient client;
MQTTConnector mqttConnector(client, SOURCE_ID, MQTT_SERVER, MQTT_SERVER_PORT, MQTT_USERNAME, MQTT_PASSWORD);

SimpleTimer timer;
DeviceInfoReader deviceInfoReader(SOURCE_ID);
DHT11SensorReader dht11SensorReader("DHT", PIN_DHT);
BMP180SensorReader bmp180SensorReader("BMP1");
BMP280SensorReader bmp280SensorReader("BMP2");
BME280SeedSensorReader bme280SeedSensorReader("BME2");
TSL2561SensorReader tsl2561SensorReader("TSL");

LedFeedback feedback(LED_BUILTIN);

void mqttRunnerCallback();
void errorCallback();
void scanI2C();

void publishTelemetry();
void publishAttributes();

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	Wire.begin(PIN_SDA, PIN_SCL);
	Serial.begin(115200);
	delay(2000);
	Serial.println(F("Starting..."));

	scanI2C();

	feedback.ledOn();
	
	WifiConnector connector(feedback);
	if (!connector.connect(WIFI_SSID, WIFI_PASSWORD)) {
		timer.setInterval(500, []() { feedback.ledToggle(); });
		return;
	}

	mqttConnector.onConnect(publishAttributes);

	timer.setInterval(1000, mqttRunnerCallback);
	timer.setInterval(INTERVAL_PUBLISH_TELEMETRY, publishTelemetry);

	feedback.ledOff();
}

void loop() { timer.run(); }

void readAttributes(JsonObject &jsonObject) {
	deviceInfoReader.readAttributes(jsonObject);
}

void readTelemetry(JsonObject &jsonObject) {
	tsl2561SensorReader.read(jsonObject);
	bmp180SensorReader.read(jsonObject);
	bmp280SensorReader.read(jsonObject);
	bme280SeedSensorReader.read(jsonObject);
	dht11SensorReader.read(jsonObject);
	deviceInfoReader.read(jsonObject);
}

void publishAttributes() {
	mqttConnector.publish(TOPIC_ATTRIBUTES, readAttributes);
}

void publishTelemetry() {
	feedback.ledOn();
	bool result = mqttConnector.publish(TOPIC_TELEMETRY, readTelemetry);
	if (!result) {
		feedback.blinkFast(3);
	}
	feedback.ledOff();
}

void mqttRunnerCallback() { mqttConnector.loop(); }

void scanI2C() {
	byte error, address;
	int nDevices;

	Serial.println("Scanning...");

	nDevices = 0;
	for (address = 1; address < 127; address++) {
		// The i2c_scanner uses the return value of
		// the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		Wire.beginTransmission(address);
		error = Wire.endTransmission();

		if (error == 0) {
			Serial.print("I2C device found at address 0x");
			if (address < 16) {
				Serial.print("0");
			}
			Serial.print(address, HEX);
			Serial.println("  !");

			nDevices++;
		} else if (error == 4) {
			Serial.print("Unknown error at address 0x");
			if (address < 16) {
				Serial.print("0");
			}
			Serial.println(address, HEX);
		}
	}
	if (nDevices == 0) {
		Serial.println("No I2C devices found\n");
	} else {
		Serial.println("done\n");
	}
	delay(5000);
}
