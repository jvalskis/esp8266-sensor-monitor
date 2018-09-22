#ifndef _LED_FEEDBACK_H
#define _LED_FEEDBACK_H

#include <Arduino.h>

class LedFeedback {
	private:
	uint8_t ledPin;
	bool ledStatus;

	public:
	LedFeedback(uint8_t ledPin);
	bool ledOn();
	bool ledOff();
	bool ledToggle();
	bool blinkFast(int times);
};

#endif
