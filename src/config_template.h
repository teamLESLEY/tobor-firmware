// Contains pin definitions and other robot-specific constants

#ifndef PINS_H
#define PINS_H

#define DEBUG_POT PA4
#define DEBUG_UP PB12
#define DEBUG_DOWN PB13

#define WINDMILL PA3
#define WINDMILL_PULSE_PERIOD 1000 // ms
#define WINDMILL_PULSE_DUTYCYCLE 70 // %
#define WINDMILL_TIMER_PIN PA11
#define WINDMILL_SPEED 500 // [0 ... 1023]

#define BIN_SERVO PB7
#define BIN_DETECT_L PB4
#define BIN_DETECT_R PA8
#define BIN_DETECT_ACTIVE HIGH
#define BIN_MIN 60      // run "Set bin with pot" subroutine to determine min angle
#define BIN_MAX 130     // run "Set bin with pot" subroutine to determine max angle

#define DISPLAY_SDA PB11
#define DISPLAY_SCL PB10

#define TAPE_L PA5
#define TAPE_R PA6
#define THRESHOLD 50
#define ERROR_ONE_OFF 2 //mm
#define ERROR_BOTH_OFF 10 //mm

#define NEMO PA0

#define MOTOR_BASE_SPEED 0.9
#define MOTOR_L_FORWARD PB8
#define MOTOR_L_REVERSE PB9
#define MOTOR_R_FORWARD PB0
#define MOTOR_R_REVERSE PA7
#define MIN_PWM_LEFT 500
#define MIN_PWM_RIGHT 500
#define K_PROPORTIONAL 300
#define K_DERIVATIVE 0
#define DERIVATIVE_MAX_DT 200 // the maximum value of dt for computing dError/dt

#define TURN_DOMINANT 0.9
#define TURN_SECONDARY (-0.1);
#define R_TURN_L_MOTOR_SPEED 0.9
#define R_TURN_R_MOTOR_SPEED (-0.1)
#define L_TURN_L_MOTOR_SPEED (-0.3)
#define L_TURN_R_MOTOR_SPEED 0.9
#define PIVOT_SPEED (MOTOR_BASE_SPEED / 3)
#define PIVOT_CORRECTION_SPEED MOTOR_BASE_SPEED
#define PIVOT_CORRECTION_DURATION 300
#define RIGHT_TURN_CORRECTION_DURATION 0

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#endif
