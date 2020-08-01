#ifndef WINDMILL_HPP
#define WINDMILL_HPP

#include <Arduino.h>
#include "config.h"

void windmillPulseHigh();
void windmillPulseLow();

class Windmill {

public:
    int outputPin;
    int currentSpeed = 0;
    int period; // milliseconds
    int targetSpeed;
    int dutycycle;
    int timerPin;
    HardwareTimer timer;

    Windmill(int, int, int, int, int, HardwareTimer);

    void setup();
    void start();
    
    /*
    * Sets PWM duty cycle for "on" segments of windmill. speed: [0 ... 1023]
    */
    void setSpeed(int speed);
    void stop();
    void detach();
};

inline Windmill windmill(    
    WINDMILL, 
    WINDMILL_PULSE_PERIOD, 
    WINDMILL_SPEED, 
    WINDMILL_PULSE_DUTYCYCLE, 
    WINDMILL_TIMER_PIN, 
    HardwareTimer(TIM1)
);

#endif