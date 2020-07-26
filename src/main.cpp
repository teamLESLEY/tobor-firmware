#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <tape.hpp>
#include <motor.hpp>
#include <Servo.h>
#include <navigation.hpp>
#include <config.h>
#include "menu.hpp"

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


void nemo_detect(){
}

void setup(){

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  // Inputs
  pinMode(DEBUG_UP, INPUT_PULLUP);
  pinMode(DEBUG_DOWN, INPUT_PULLUP);
  pinMode(DEBUG_POT, INPUT);

  pinMode(NEMO, INPUT_PULLUP);
  attachInterrupt(NEMO, nemo_detect, FALLING);

  // Outputs
  pinMode(WINDMILL, OUTPUT);

  binServo.attach(BIN_SERVO);
  binServo.write(BIN_MIN);

}


void fullLeftTurn(){}
void fullRightTurn(){}
void pivot(){}
void halfRightTurn(){}

void straightUntilNemo(){
  while(true/*nemo has yet to be triggered */){}
}

void runCompetition(){

  // turn on windmill

  // follow tape to first flag

  // turns

  // blah blah blah

  // pivot

  // align to bin

  // dump cans
}


void menu(){

  //attachInterrupt(DEBUG_UP, cycleActiveMenu, RISING);

  Menu mainMenu("Main Menu",3, display);
  /*mainMenu.show();
  delay(3000);
  mainMenu.cycle();
  delay(1000);

  for(int i = 0; i < 7; i++){
    mainMenu.cycle();
    delay(1000);
  }
*/
  int result = mainMenu.select();


  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Selected: ");
  display.println(result);
  delay(5000);
  display.display();


  //Fancy stuff

  //select competition
  runCompetition();

}



void loop() {
    menu();
}