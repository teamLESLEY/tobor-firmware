#ifndef NAVIGATOR_HPP
#define NAVIGATOR_HPP

#include "motor.hpp"
#include "tape.hpp"
#include "config.h"

enum TapeSide {LEFT, RIGHT};
namespace Motor {
    class Navigator {
        DCMotor motorL;
        DCMotor motorR;
        TapeSensor tapeSensor;
        int nemo;

        int previousError = 0;
        int lastIterationError = 0;
        unsigned long previousErrorStartTime = 0;
        unsigned long currentErrorStartTime = 0;

    public:
        inline static bool nemoTriggered = false;

        Navigator(Motor::DCMotor motorL, Motor::DCMotor motorR, TapeSensor ts, int nemo);

        int tapeSensorError();
        void resetPDOnSide(int side);
        void correctToTape(double motorL_base_speed, double motorR_base_speed, double kp, double kd);
        void tapeFollowUntilNemo(double lSpeed, double rSpeed, double kp, double kd,
            int startSide = TapeSide::RIGHT, int bufferTime = 0);

        static void nemoDetect();
        bool consumeNemoTrigger();

        void drive(double motorL_speed, double motorR_speed, unsigned int millis);
        void driveUntilNemo(double lspeed, double rspeed, int bufferTime = 10);
        void driveUntilDory(double lspeed, double rspeed, int bufferTime = 10);
        void start(double motorL_speed, double motorR_speed);
        void stop();
    };
}

#endif
