#ifndef _MESSAGE_HANDLER_H
#define _MESSAGE_HANDLER_H

#include <ESP8266WiFi.h>
#include "LinkedList.h"
#include "MQTTHandler.h"

class MessageHandler {
	private:
	char* topic;
	MQTTHandler* mqttHandler;

	public:
	MessageHandler(char* topic, MQTTHandler* mqttHandler);
	bool supports(char* topic);
	void execute(byte* payload, unsigned int length);
};

#endif
