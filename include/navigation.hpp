#ifndef NAVIGATOR_HPP
#define NAVIGATOR_HPP

#include <motor.hpp>
#include <tape.hpp>

namespace Motor{

    class Navigator {

        const int ERROR_ONE_OFF = 2;
        const int ERROR_BOTH_OFF = 10;

        DCMotor motorL;
        DCMotor motorR;
        TapeSensor tapeSensor;

        int previousError = 0;
        int lastIterationError = 0;
        unsigned long previousErrorStartTime = 0;
        unsigned long currentErrorStartTime = 0;

    public:
        Navigator(Motor::DCMotor motorL, Motor::DCMotor motorR, TapeSensor ts);

        int tapeSensorError();
        void correctToTape(double motorL_base_speed, double motorR_base_speed, double kp, double kd);
        
        void drive(double motorL_speed, double motorR_speed, unsigned int millis);
        void start(double motorL_speed, double motorR_speed);
        void stop();
    };
}

#endif

