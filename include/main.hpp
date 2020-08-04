#ifndef MAIN_HPP
#define MAIN_HPP

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <vector>
#include <string>
#include <stdarg.h>
#include "tape.hpp"
#include "motor.hpp"
#include "navigation.hpp"
#include "config.h"
#include "menu.hpp"

#define CONFIRM DEBUG_UP
#define CYCLE DEBUG_DOWN

#define MENU_WAIT_TIME 500
#define CYCLE_WAIT_TIME 200

TwoWire Wire2(DISPLAY_SDA, DISPLAY_SCL);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire2, OLED_RESET);

TapeSensor tape(TAPE_L, TAPE_R, THRESHOLD);
Motor::DCMotor motorL(MOTOR_L_FORWARD, MOTOR_L_REVERSE, MIN_PWM_LEFT);
Motor::DCMotor motorR(MOTOR_R_FORWARD, MOTOR_R_REVERSE, MIN_PWM_RIGHT);
Motor::Navigator navi(motorL, motorR, tape);

Servo binServo;

char buffer [147];

bool nemoTriggered = false;

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
void straightUntilNemo();

void setup();
void loop();
void subroutineMenu();
unsigned int getMenuSelection(Menu menu);
void emptyFunc();
void printToDisplay(const char *str);

void printSensorReadings();
void hBridgeTest();



// Main Menu definition
const vector<string> mainOpts{"Run Competition", "Entertainment", "Set Values", "Run Subroutines"};
const vector<callback_function_t> mainCallbacks{runCompetition, runEntertainment, emptyFunc, subroutineMenu};
Menu mainMenu("Main Menu", mainOpts, mainCallbacks);

// Subroutine Menu definition
const vector<string> subOpts{
  "Straight until Nemo",
  "Right until Nemo",
  "Left until Nemo",
  "Pivot until Nemo",
  "Set windmill with pot",
  "Set bin with pot",
  "Bin raise on detect",
  "Raise bin",
  "Lower bin",
  "Show sensor readings",
  "Run motors fwd/back",
  "Back"
  };
const vector<callback_function_t> subCallbacks{
  straightUntilNemo, 
  rightUntilNemo, 
  leftUntilNemo, 
  pivotUntilNemo,
  setWindmillWithPot,
  setBinWithPot,
  raiseBinOnDetect,
  raiseBin,
  lowerBin,
  printSensorReadings,
  hBridgeTest,
  emptyFunc};
Menu subMenu("Subroutines", subOpts, subCallbacks);

#endif