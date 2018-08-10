#include "MessageHandler.h"

MessageHandler::MessageHandler(char* topic, MQTTHandler* mqttHandler)
    : topic{topic}, mqttHandler{mqttHandler} {}

bool MessageHandler::supports(char* topic) {
	return strcmp(this->topic, topic) == 0;
}

void MessageHandler::execute(byte* payload, unsigned int length) {
	this->mqttHandler->handle(topic);
}
