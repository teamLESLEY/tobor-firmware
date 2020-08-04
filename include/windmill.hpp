#ifndef WINDMILL_HPP
#define WINDMILL_HPP

#include <Arduino.h>

struct Windmill {
  int speed;
  int period; // milliseconds
  int dutycycle;
  uint32_t outputPin;
  uint32_t timerPin;
  HardwareTimer timer;
};

void setupWindmill(Windmill& wm);
void startWindmill(Windmill& wm);
void stopWindmill(Windmill& wm);
void windmillPulseHigh(uint32_t pin, unsigned int speed);
void windmillPulseLow(uint32_t pin);

#endif
