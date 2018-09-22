#include "MQTTConnector.h"
#include <ArduinoJson.h>

MQTTConnector::MQTTConnector(Client &client, const char *id, const char *server,
                             uint16_t port, const char *user, const char *pass)
    : mqttClient{client}, id{id}, user{user}, pass{pass} {
	mqttClient.setServer(server, port);

	std::function<void(char *, uint8_t *, unsigned int)> callback =
	    std::bind(&MQTTConnector::callback, this, std::placeholders::_1,
	              std::placeholders::_2, std::placeholders::_3);
	mqttClient.setCallback(callback);
}

bool MQTTConnector::publish(const char *topic, const char *data) {
	Serial.print(F("Publishing. Topic: "));
	Serial.print(topic);
	Serial.print(F(", content: "));
	Serial.println(data);
	return mqttClient.publish(topic, data);
}

bool MQTTConnector::publish(const char *topic, std::function<void(JsonObject&)> jsonProvider) {
	StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;
	JsonObject &root = jsonBuffer.createObject();
	jsonProvider(root);
	char buffer[root.measureLength() + 1];
	root.printTo(buffer, root.measureLength() + 1);
	return publish(topic, buffer);
}

void MQTTConnector::subscribe(const char *topic, MQTTHandler *handler) {}

void MQTTConnector::loop() { keepAlive(); }

void MQTTConnector::onConnect(std::function<void()> handler) {
	onConnectHandler = handler;
}

void MQTTConnector::callback(char *topic, byte *payload, unsigned int length) {
	Serial.print(F("Message arrived ["));
	Serial.print(topic);
	Serial.print(F("] "));
	for (unsigned int i = 0; i < length; i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println();

	for (int i = 0; i < messageHandlers.size(); i++) {
		MessageHandler *handler = messageHandlers.get(i);

		if (handler->supports(topic)) {
			handler->execute(payload, length);
		}
	}
}

void MQTTConnector::keepAlive() {
	if (!mqttClient.connected()) {
		reconnect();
	}
	mqttClient.loop();
}

void MQTTConnector::reconnect() {
	while (!mqttClient.connected()) {
		Serial.print(F("Attempting MQTT connection..."));
		if (mqttClient.connect(id, user, pass)) {
			Serial.println(F("connected"));

			onConnectHandler();
		} else {
			Serial.print(F("failed, rc="));
			Serial.print(mqttClient.state());
			Serial.println(F(" try again in 5 seconds"));
			delay(5000);
		}
	}
}
