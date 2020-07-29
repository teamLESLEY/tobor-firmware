// Contains pin definitions

#ifndef PINS_H
#define PINS_H

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define DEBUG_POT PA4
#define DEBUG_UP PB12
#define DEBUG_DOWN PB13

#define WINDMILL PA3

#define BIN_SERVO PB7
#define BIN_DETECT_L PB4
#define BIN_DETECT_R PA8
#define BIN_MIN 20
#define BIN_MAX 130

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
#define MOTOR_R_FORWARD PB1
#define MOTOR_R_REVERSE PB0
#define MIN_PWM_LEFT 500
#define MIN_PWM_RIGHT 500

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#endif
