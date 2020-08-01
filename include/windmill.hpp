#ifndef WINDMILL_HPP
#define WINDMILL_HPP

#include "config.h"

HardwareTimer windmillTimer(TIM1);

void windmillPulseHigh();
void windmillPulseLow();

struct Windmill {
    int outputPin;
    int currentSpeed;
    int period; // milliseconds
    int targetSpeed;
    int dutycycle;
    int timerPin;
    HardwareTimer timer;

    void setup();
    void start();
    
    /*
    * Sets PWM duty cycle for "on" segments of windmill. speed: [0 ... 1023]
    */
    void setSpeed(int speed);
    void stop();
    void detach();
};

Windmill windmill{
    WINDMILL,
    0,
    WINDMILL_SPEED, 
    WINDMILL_PULSE_PERIOD, 
    WINDMILL_PULSE_DUTYCYCLE, 
    WINDMILL_TIMER_PIN, 
    HardwareTimer(TIM1)
};

#endif