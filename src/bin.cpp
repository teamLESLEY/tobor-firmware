#include "bin.hpp"

Bin::Bin(uint32_t servoPin, uint32_t leftSensePin, uint32_t rightSensePin, uint8_t normal)
	: servoPin(servoPin), leftSensePin(leftSensePin), rightSensePin(rightSensePin),
	  pressed(normal == NO ? LOW : HIGH) {
		pinMode(leftSensePin, INPUT_PULLUP);
		pinMode(rightSensePin, INPUT_PULLUP);
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
	return digitalRead(leftSensePin) == pressed;
}

bool Bin::onRight() {
	return digitalRead(rightSensePin) == pressed;
}
