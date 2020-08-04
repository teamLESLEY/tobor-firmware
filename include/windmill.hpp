#ifndef WINDMILL_HPP
#define WINDMILL_HPP

#include <Arduino.h>

class Windmill {
  void on();
  void off();

public:
  unsigned int speed;
  int period; // milliseconds
  int dutycycle;
  uint32_t outputPin;
  uint32_t timerPin;
  HardwareTimer timer;

  void start();
  void stop();

  void setSpeed(unsigned int speed);
};

#endif
