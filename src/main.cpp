#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <tape.hpp>
#include <motor.hpp>
#include <Servo.h>
#include <navigation.hpp>
#include <config.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
TwoWire Wire2(DISPLAY_SDA, DISPLAY_SCL);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire2, OLED_RESET);

TapeSensor tape(TAPE_L, TAPE_R, THRESHOLD);
Motor::DCMotor motorL(MOTOR_L_FORWARD, MOTOR_L_REVERSE, MIN_PWM_LEFT);
Motor::DCMotor motorR(MOTOR_R_FORWARD, MOTOR_R_REVERSE, MIN_PWM_RIGHT);
Motor::Navigator navi(motorL, motorR, tape);

Servo binServo; 