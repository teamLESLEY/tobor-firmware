#ifndef BIN_H
#define BIN_H

#include <Servo.h>
#include <Wire.h>

class Bin {
  Servo binServo;
  PinName servoPin;
  PinName leftSensePin;
  PinName rightSensePin;
  const uint8_t active;
  bool attached = false;

  void setup(PinName servoPin);

  public:
    Bin(PinName servoPin, PinName leftSensePin, PinName rightSensePin, uint8_t active);
    Bin(uint32_t servoPin, uint32_t leftSensePin, uint32_t rightSensePin, uint8_t active);

    void setAngle(int angle);
    bool onLeft();
    bool onRight();
};

#endif
