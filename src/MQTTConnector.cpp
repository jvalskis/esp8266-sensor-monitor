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

void MQTTConnector::publish(const char *topic, const char *data) {
	Serial.print(F("Publishing stuff to topic "));
	Serial.println(topic);
	Serial.print(F("Stuff: "));
	Serial.println(data);
	mqttClient.publish(topic, data);
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
