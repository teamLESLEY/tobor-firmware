#include <motor.hpp>
#include <navigation.hpp>

using namespace Motor;

    Navigator::Navigator(Motor::DCMotor leftMotor, Motor::DCMotor rightMotor, TapeSensor tapeSensor) 
        :motorL(leftMotor), motorR(rightMotor), tapeSensor(tapeSensor){
    }
    
    // follows tape, if put in a while loop
    void Navigator::correctToTape(double motorL_base_speed, double motorR_base_speed, double kp, double kd){
        unsigned long now = millis();

        int error = tapeSensorError();
        if (error != lastIterationError) {
            previousError = lastIterationError;
            previousErrorStartTime = currentErrorStartTime;
            currentErrorStartTime = now;
        }
        lastIterationError = error;
        
        double derivative = (double)(error - previousError) / (now - previousErrorStartTime);
        double correction = kp * error + kd * derivative;

        start(motorL_base_speed - correction, motorR_base_speed + correction);
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
    