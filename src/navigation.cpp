#include <motor.hpp>
#include <navigation.hpp>
#include <Arduino.h>

using namespace Motor;

    Navigator::Navigator(Motor::DCMotor leftMotor, Motor::DCMotor rightMotor, TapeSensor tapeSensor, int nemo) 
        :motorL(leftMotor), motorR(rightMotor), tapeSensor(tapeSensor), nemo(nemo){
            pinMode(nemo, INPUT_PULLUP);
            attachInterrupt(nemo, nemoDetect, FALLING);
            nemoTriggered = false;
    }

    // follows tape, if put in a while loop
    void Navigator::correctToTape(double motorL_base_speed, double motorR_base_speed, double kp, double kd){
        unsigned long now = millis();
        int error = tapeSensorError();

        double derivative = 0; // This is zero until we detect a change
        
        // See if a change has occured
        if (error != previousError) {
            // Set the derivative to reflect the change
            double dError = error - previousError;
            double dt = now - previousErrorStartTime;
            derivative = dError / dt;

            // Update the time tracker
            previousErrorStartTime = now;
            previousError = error;
        }
        
        double correction = kp * error + kd * derivative;

        // if (random(1, 100) > 90) {
        //     Serial.printf("err=%d, kp=%d, corr=%d\n", error, (int)kp, (int)correction);
        // }

        start(motorL_base_speed - correction, motorR_base_speed + correction);
    }

    bool Navigator::consumeNemoTrigger(){
        if (!nemoTriggered){
            return false;
        }
        nemoTriggered = false;
        return true;
    }

    void Navigator::tapeFollowUntilNemo(double lSpeed, double rSpeed, double kp, double kd,
        int startSide, int bufferTime){
        consumeNemoTrigger();
        while(!consumeNemoTrigger()){
            correctToTape(lSpeed,rSpeed,kp,kd);
        }
        stop();
    }

    int Navigator::tapeSensorError() {
        bool tapeLeftOn = tapeSensor.isLeftOn();
        bool tapeRightOn = tapeSensor.isRightOn();

        if (tapeLeftOn && tapeRightOn) {
            return 0;
        } else if (!tapeLeftOn && tapeRightOn) {
            return -ERROR_ONE_OFF;
        } else if (tapeLeftOn && !tapeRightOn) {
            return ERROR_ONE_OFF;
        } else {
            // In the fully off the tape case, assume it's off on the same
            // side as the last error. Implementation detail: if the robot
            // goes from on tape to fully off tape in one iteration, assume it
            // is on the right side of the tape.
            if (previousError < 0) {
                return -ERROR_BOTH_OFF;
            } else {
                return ERROR_BOTH_OFF;
            }
        }
    }

    void Navigator::nemoDetect(){
        nemoTriggered = true;
    }
    
    void Navigator::start(double lSpeed, double rSpeed){
        motorL.setSpeed(constrain(lSpeed, -1, 1));
        motorR.setSpeed(constrain(rSpeed, -1, 1));
    }
    void Navigator::stop(){
        motorL.stop();
        motorR.stop();
    }
    void Navigator::drive(double lSpeed, double rSpeed, unsigned int millis){
        start(lSpeed, rSpeed);
        delay(millis);
        stop();
    }

    void Navigator::driveUntilNemo(double lSpeed, double rSpeed, int bufferTime){
        start(lSpeed, rSpeed);
        delay(bufferTime);
        consumeNemoTrigger();
        while(!consumeNemoTrigger())
            ;
        stop();
    }

    void Navigator::driveUntilDory(double lSpeed, double rSpeed, int bufferTime){
        start(lSpeed, rSpeed);
        delay(bufferTime);
        while(!tapeSensor.isLeftOn() && !tapeSensor.isRightOn())
            ;
        stop();
    }

    
