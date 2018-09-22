#include "LedFeedback.h"

LedFeedback::LedFeedback(uint8_t ledPin): ledPin{ledPin}, ledStatus{false} {}

bool LedFeedback::ledOn() {
	ledStatus = true;
	digitalWrite(ledPin, LOW);
	return ledStatus;
}

bool LedFeedback::ledOff() {
	ledStatus = false;
	digitalWrite(ledPin, HIGH);
	return ledStatus;
}

bool LedFeedback::ledToggle() {
	return ledStatus ? ledOff() : ledOn();
}

bool LedFeedback::blinkFast(int times) {
	for (int i = 0; i < times * 2; i++) {
		ledToggle();
		delay(100);
	}
	return ledStatus;
}
