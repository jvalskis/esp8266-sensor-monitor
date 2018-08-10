#ifndef _MQTT_HANDLER_H
#define _MQTT_HANDLER_H

class MQTTHandler {
	public:
	virtual void handle(char *topic);
};

class MQTTControlHandler : public MQTTHandler {
	public:
	void handle(char *topic);
};

#endif
