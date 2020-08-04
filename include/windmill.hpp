#ifndef WINDMILL_HPP
#define WINDMILL_HPP

#include <Arduino.h>

struct Windmill {
  int currentSpeed;
  int targetSpeed;
  int period; // milliseconds
  int dutycycle;
  int timerPin;
  HardwareTimer timer;
};

void windmillPulseHigh(uint32_t pin, unsigned int speed);
void windmillPulseLow(uint32_t pin);

#endif
