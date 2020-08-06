#ifndef MAIN_HPP
#define MAIN_HPP

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include "tape.hpp"
#include "motor.hpp"
#include "navigation.hpp"
#include "config.h"
#include "menu.hpp"
#include "bin.hpp"

#define CONFIRM DEBUG_UP
#define CYCLE DEBUG_DOWN

#define MENU_WAIT_TIME 500
#define CYCLE_WAIT_TIME 200

TwoWire Wire2(DISPLAY_SDA, DISPLAY_SCL);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire2, OLED_RESET);
char buffer [147];

TapeSensor tape(TAPE_L, TAPE_R, THRESHOLD);
Motor::DCMotor motorL(MOTOR_L_FORWARD, MOTOR_L_REVERSE, MIN_PWM_LEFT);
Motor::DCMotor motorR(MOTOR_R_FORWARD, MOTOR_R_REVERSE, MIN_PWM_RIGHT);
Motor::Navigator navi(motorL, motorR, tape, NEMO);
Bin bin(BIN_SERVO, BIN_DETECT_L, BIN_DETECT_R, BIN_DETECT_NORMAL);

double kp;
double kd;

using std::vector;
using std::string;

void debugCompetition();
void runCompetition();
void runEntertainment();

void setWindmillWithPot();

void lowerBin();
void raiseBin();
void tiltBin();
void setBinWithPot();
void raiseBinOnDetect();

void rightTurn(int skipped = 0);
void straight();
void leftUntilNemo();
void rightUntilNemo();
void pivotUntilNemo();
void perimeter();
void innerSquare();
void returnPath();
void straightUntilNemoOnRight();
void straightUntilNemo(int startSide);
void finalTurn();

void setup();
void loop();
void subroutineMenu();
void getMenuSelection(Menu menu);
void printToDisplay(const char *str);

void printSensorReadings();
void hBridgeTest();



// Main Menu definition
Menu mainMenu(
  "Main Menu",
  {
    {"Run Competition", runCompetition},
    {"Debug Competition", debugCompetition},
    {"Entertainment", runEntertainment},
    {"Run Subroutines", subroutineMenu},
  }
);

// Subroutine Menu definition
Menu subMenu(
  "Subroutines",
  {
    {"Straight until Nemo", straightUntilNemoOnRight},
    {"Right until Nemo", rightUntilNemo},
    {"Left until Nemo", leftUntilNemo},
    {"Pivot until Nemo", pivotUntilNemo},
    {"Sweep perimeter", perimeter},
    {"Sweep inner square", innerSquare},
    {"Return path", returnPath},
    {"Final turn", finalTurn},
    {"Set windmill with pot", setWindmillWithPot},
    {"Set bin with pot", setBinWithPot},
    {"Bin raise on detect", raiseBinOnDetect},
    {"Raise bin", raiseBin},
    {"Lower bin", lowerBin},
    {"Show sensor readings", printSensorReadings},
    {"Run motors fwd/back", hBridgeTest},
    {"Back", []() -> void {}},
  }
);

#endif
