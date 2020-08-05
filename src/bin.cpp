#include "bin.hpp"

Bin::Bin(uint32_t servoPin, uint32_t leftSensePin, uint32_t rightSensePin, uint8_t active)
	: servoPin(servoPin), leftSensePin(leftSensePin), rightSensePin(rightSensePin), active(active) {
		int inputType = (active == HIGH) ? INPUT_PULLDOWN : INPUT_PULLUP;

		pinMode(leftSensePin, inputType);
		pinMode(rightSensePin, inputType);
}

void Bin::setAngle(int angle) {
	if (!attached) {
		binServo.attach(servoPin);
		attached = true;
	}

	binServo.write(angle);
}

bool Bin::onLeft() {
	// Something fishy is going on here - digitalRead 
	//	might want to use a pin number, not a pin name?
	return digitalRead(leftSensePin) == active;
}

bool Bin::onRight() {
	return digitalRead(rightSensePin) == active;
}
