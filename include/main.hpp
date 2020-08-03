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
#include "windmill.hpp"

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

Servo binServo; 

using std::vector;
using std::string;

void saveValues();
void loadValues();

void runCompetition();
void runEntertainment();

void nemoDetect();
bool consumeTrigger();

void setWindmillWithPot();

void lowerBin();
void raiseBin();
void setBinWithPot();
void raiseBinOnDetect();

void leftUntilNemo();
void rightUntilNemo();
void pivotUntilNemo();
void straightUntilNemoOnRight();
void straightUntilNemo(int startSide);

void setup();
void loop();
void subroutineMenu();
unsigned int getMenuSelection(Menu menu);
void emptyFunc();
void printToDisplay(const char *str);

void printSensorReadings();
void hBridgeTest();



// Main Menu definition
Menu mainMenu(
  "Main Menu",
  {
    {"Run Competition", runCompetition},
    {"Entertainment", runEntertainment},
    {"Set Values", emptyFunc},
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
    {"Set windmill with pot", setWindmillWithPot},
    {"Set bin with pot", setBinWithPot},
    {"Bin raise on detect", raiseBinOnDetect},
    {"Raise bin", raiseBin},
    {"Lower bin", lowerBin},
    {"Show sensor readings", printSensorReadings},
    {"Run motors fwd/back", hBridgeTest},
    {"Back", emptyFunc},
  }
);

#endif
