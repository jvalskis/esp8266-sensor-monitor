#ifndef _MQTT_CONNECTOR_H
#define _MQTT_CONNECTOR_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "LinkedList.h"
#include "MessageHandler.h"
#include "Properties.h"
#include <ArduinoJson.h>

#define STATUS_CONNECTED "connected"
#define STATUS_DISCONNECTED "disconnected"

class MQTTConnector {
	private:
	PubSubClient mqttClient;
	LinkedList<MessageHandler *> messageHandlers;
	std::function<void()> onConnectHandler;

	const char *id, *user, *pass, *disconnectedStatusMessage;

	void keepAlive();
	void callback(char *topic, byte *payload, unsigned int length);

	public:
	MQTTConnector(Client &client, const char *id, const char *server,
	              uint16_t port, const char *user, const char *pass);
	bool publish(const char *topic, const char *data);
	bool publish(const char *topic, std::function<void(JsonObject&)> jsonProvider);
	void subscribe(const char *topic, MQTTHandler *handler);
	void onConnect(std::function<void()> handler);
	void loop();
	void reconnect();
};

#endif
