#ifndef BIN_H
#define BIN_H

#include <Servo.h>
#include <Wire.h>

#define NO 0
#define NC 1

class Bin {
  Servo binServo;
  uint32_t servoPin;
  uint32_t leftSensePin;
  uint32_t rightSensePin;
  const uint8_t pressed;
  bool attached = false;

  void setup(PinName servoPin);

  public:
    Bin(uint32_t servoPin, uint32_t leftSensePin, uint32_t rightSensePin, uint8_t active);

    void setAngle(int angle);
    bool onLeft();
    bool onRight();
};

#endif
