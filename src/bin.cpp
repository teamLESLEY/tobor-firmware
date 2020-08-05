#include "bin.hpp"

Bin::Bin(PinName servoPin, PinName leftSensePin, PinName rightSensePin, uint8_t active)
	: servoPin(servoPin), leftSensePin(leftSensePin), rightSensePin(rightSensePin), active(active) {
}

// delegated constructor
Bin::Bin(uint32_t servoPin, uint32_t leftSensePin, uint32_t rightSensePin, uint8_t active)
	: Bin(digitalPinToPinName(servoPin), digitalPinToPinName(leftSensePin),
			digitalPinToPinName(rightSensePin), active) {};

void Bin::setAngle(int angle) {
	if (!attached) {
		binServo.attach(servoPin);
		attached = true;
	}

	binServo.write(angle);
}

bool Bin::onLeft() {
	return digitalRead(leftSensePin) == active;
}

bool Bin::onRight() {
	return digitalRead(rightSensePin) == active;
}
