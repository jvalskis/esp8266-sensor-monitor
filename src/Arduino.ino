#include <Arduino.h>

#include <SimpleTimer.h>
#include <Wire.h>
#include "BMP180SensorReader.h"
#include "DHT11SensorReader.h"
#include "MQTTConnector.h"
#include "Properties.h"
#include "TSL2561SensorReader.h"
#include "WifiConnector.h"

#define PIN_DHT 12
#define PIN_SDA 4
#define PIN_SCL 5

ADC_MODE(ADC_VCC);

WiFiClient client;
MQTTConnector mqttConnector(client, SOURCE_ID, MQTT_SERVER, MQTT_SERVER_PORT,
                            MQTT_USERNAME, MQTT_PASSWORD);

SimpleTimer timer;
DHT11SensorReader dht11SensorReader(PIN_DHT);
BMP180SensorReader bmp180SensorReader;
TSL2561SensorReader tsl2561SensorReader;

void printFreeHeap();
void mqttRunnerCallback();
void readSensorData();
void publishAttributes();
void scanI2C();

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	Wire.begin(PIN_SDA, PIN_SCL);
	Serial.begin(115200);
	delay(2000);
	Serial.println(F("Starting..."));

	scanI2C();

	tsl2561SensorReader.initialize();
	bmp180SensorReader.initialize();

	WifiConnector connector;
	if (!connector.connect(WIFI_SSID, WIFI_PASSWORD)) {
		return;
	}

	mqttConnector.onConnect(publishAttributes);

	timer.setInterval(1000, &mqttRunnerCallback);
	timer.setInterval(60000, &readSensorData);
}

void loop() { timer.run(); }

void publishAttributes() {
	StaticJsonBuffer<100> jsonBuffer;
	JsonObject &root = jsonBuffer.createObject();
	root["firmware_version"] = FIRMWARE_VERSION;
	root["serial_number"] = ESP.getChipId();
	root["name"] = SOURCE_ID;
	char buffer[root.measureLength() + 1];
	root.printTo(buffer, root.measureLength() + 1);
	mqttConnector.publish(TOPIC_ATTRIBUTES, buffer);
}

void readSensorData() {
	digitalWrite(LED_BUILTIN, LOW);
	Serial.print(F("Reading sensor data... "));
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject &root = jsonBuffer.createObject();
	tsl2561SensorReader.read(root);
	bmp180SensorReader.read(root);
	dht11SensorReader.read(root);
	Serial.println(F("DONE"));

	root["free_heap"] = ESP.getFreeHeap();
	root["vcc"] = ESP.getVcc() / 1000.0;
	char buffer[root.measureLength() + 1];
	root.printTo(buffer, root.measureLength() + 1);

	Serial.print(F("Publishing sensor data... "));
	mqttConnector.publish(TOPIC_TELEMETRY, buffer);
	Serial.println(F("DONE"));
	digitalWrite(LED_BUILTIN, HIGH);
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
