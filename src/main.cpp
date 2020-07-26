#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <tape.hpp>
#include <motor.hpp>
#include <Servo.h>
#include <navigation.hpp>
#include <pins.hpp>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
TwoWire Wire2(DISPLAY_SDA, DISPLAY_SCL);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire2, OLED_RESET);

TapeSensor tape(TAPE_L, TAPE_R, THRESHOLD);
Motor::DCMotor motorL(MOTOR_L_FORWARD, MOTOR_L_REVERSE, 500);
Motor::DCMotor motorR(MOTOR_R_FORWARD, MOTOR_R_REVERSE, 500);
Motor::Navigator navi(motorL, motorR, tape);

Servo binServo; 

enum drive_modes {TAPE, STOP, R_TURN, L_TURN, ALIGN};

int stage = 0;
int stages[] = {TAPE, ALIGN};
int drive_mode = TAPE;
bool locked = false;
bool isNemoTriggered = false;

void nemo_detect() {
  isNemoTriggered = true;
  if(locked == false){
      stage++;
      locked = true;
        drive_mode = stages[stage];
  delay(20);
  }
}

void hideNemo() {
  isNemoTriggered = false;
}

bool findingNemo() {
  if (isNemoTriggered){
    isNemoTriggered = false;
    return false;
  }
  return true;
}

void dump(){
  binServo.write(BIN_MAX);
  delay(1000);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(TAPE_L, INPUT);
  pinMode(TAPE_R, INPUT);
  pinMode(NEMO, INPUT_PULLUP);
  pinMode(WINDMILL, OUTPUT);

  attachInterrupt(NEMO, nemo_detect, FALLING);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.display();
  delay(3000);

  binServo.attach(BIN);
  binServo.write(BIN_MIN);


  unsigned int p = analogRead(DEBUG_POT);
  unsigned int d = 0;
  unsigned int gain = 500;
// scaling factors (helpful if gain, d and p are taken directly from analog input)
  double kd = gain / 1024.0 * d / 50.0;
  double kp = gain / 1024.0 * p /5000.0;  



  while(findingNemo()){
    navi.correctToTape(MOTOR_BASE_SPEED, MOTOR_BASE_SPEED, kp, kd);
  }
  navi.stop();

}




void loop() {


  // put your main code here, to run repeatedly:

  display.clearDisplay();
  display.setCursor(0,0);
  display.printf("In Mode: %d\n", drive_mode);
  display.println(analogRead(TAPE_L));
  display.println(analogRead(TAPE_R));
  display.println(digitalRead(NEMO));

  display.println("Editing KP");
  unsigned int p = analogRead(DEBUG_POT);
  display.println(p);
  display.display();
  delay(2);

  unsigned int d = 0;
  unsigned int gain = 500;

// scaling factors (helpful if gain, d and p are taken directly from analog input)
  double kd = gain / 1024.0 * d / 50.0;
  double kp = gain / 1024.0 * p /5000.0;         

  switch(drive_mode){
    case drive_modes::STOP: {
      navi.stop();
      break;
    }

    case drive_modes::TAPE: {

      navi.correctToTape(MOTOR_BASE_SPEED, MOTOR_BASE_SPEED, kp, kd);
      break;
    }
    case drive_modes::L_TURN: {

      navi.correctToTape(0, MOTOR_BASE_SPEED, kp, kd);
      break;
    }
    case drive_modes::R_TURN: {

      navi.drive(1, -0.5, 2000);
      drive_mode = TAPE;
      break;
    }
    case drive_modes::ALIGN: {
      locked = true;
      navi.drive(0,0,1000);
      navi.drive(-1,1,50);
      hideNemo();
      while(findingNemo()){
        navi.drive(-1,1,10);
      }
      navi.drive(-1,1,50);
      hideNemo();
      while(findingNemo()){
        navi.drive(-1,1,10);
      }
      delay(500);
      navi.drive(-1,-1,1200);
      delay(500);
      dump();
      delay(1000000);      
      break;
    }
    
  }
}