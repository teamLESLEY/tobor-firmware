#ifndef WINDMILL_HPP
#define WINDMILL_HPP

#include <Arduino.h>
#include "config.h"

inline unsigned int currentSpeed = 0;
void windmillPulseHigh();
void windmillPulseLow();

class Windmill {

public:
    int outputPin;
    int period; // milliseconds
    int dutycycle;
    int timerPin;
    HardwareTimer timer;

    Windmill(int outputPin, int period, int dutycycle, int timerPin, HardwareTimer);

    void setup();
    void start();
    void stop();
    void detach();
};

#endif
