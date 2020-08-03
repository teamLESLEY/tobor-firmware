#include "main.hpp"


void runCompetition(){
  double kp = 0.02;
  double kd = 0;
  printToDisplay("Running Competition\n:)");
  delay(200);

  //navi.tapeFollowUntilNemo(MOTOR_BASE_SPEED, MOTOR_BASE_SPEED, kp, kd);


  /*straightUntilNemo(TapeSide::RIGHT);
  rightUntilNemo();
  straightUntilNemo(TapeSide::LEFT);*/
  /*
  wm.currentSpeed = wm.targetSpeed;
  straightUntilNemo();
  rightUntilNemo();
  straightUntilNemo();
  leftUntilNemo();
  straightUntilNemo();
  rightUntilNemo();
  straightUntilNemo();
  rightUntilNemo();
  straightUntilNemo();
  pivotUntilNemo();
  wm.currentSpeed = 0;
  raiseBinOnDetect();*/
}

void runEntertainment(){
  printToDisplay("Running Entertainment\n:)");
  delay(3000);
}

void setup(){
  // loadValues();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  // Inputs
  pinMode(DEBUG_UP, INPUT_PULLUP);
  pinMode(DEBUG_DOWN, INPUT_PULLUP);
  pinMode(DEBUG_POT, INPUT);

  // Windmill Setup
  windmill.setup();

  // if servo is connected to same power supply as BP, do not run this block
  //binServo.attach(BIN_SERVO);
  //binServo.write(BIN_MIN);
}


void loop() {
  getMenuSelection(mainMenu);

  printToDisplay("Returning to \nMain Menu");
  delay(MENU_WAIT_TIME);
}


void lowerBin(){
  binServo.write(BIN_MIN);
}

void raiseBin(){
  binServo.attach(BIN_SERVO);
  binServo.write(BIN_MAX);
}


void leftUntilNemo(){
  navi.driveUntilNemo(L_TURN_L_MOTOR_SPEED, L_TURN_R_MOTOR_SPEED);
}


void rightUntilNemo(){
  navi.driveUntilNemo(R_TURN_L_MOTOR_SPEED, R_TURN_R_MOTOR_SPEED);
}

void pivotUntilNemo(){
  navi.driveUntilNemo(MOTOR_BASE_SPEED, - MOTOR_BASE_SPEED);
}

void printSensorReadings(){
  while(!digitalRead(CONFIRM)){
    sprintf(buffer,
      "Tape L: %d\nTape R: %d\n\nNemo: %d",
      tape.getLeftReading(),
      tape.getRightReading(),
      digitalRead(NEMO));
    printToDisplay(buffer);
  }
}


void setWindmillWithPot(){
  int speed = analogRead(DEBUG_POT);
  while(!digitalRead(CONFIRM) && !digitalRead(CYCLE)){
    speed = analogRead(DEBUG_POT);
    sprintf(buffer,
      "Windmill power: %d\n\nUP to save\nDOWN to stop",
      speed);
    printToDisplay(buffer);
    windmill.currentSpeed = speed;
  }
  if(digitalRead(CYCLE)){
    windmill.currentSpeed = 0;
  } else if(digitalRead(CONFIRM)){
    windmill.setSpeed(speed);
    saveValues();
  }
}

void setBinWithPot(){
  binServo.attach(BIN_SERVO);
  while(!digitalRead(CONFIRM)){
    int angle = (int)analogRead(DEBUG_POT) * 180 / 1023;
    sprintf(buffer, "Bin angle: %d", angle);
    printToDisplay(buffer);
    binServo.write(angle);
  }
}

void setLeftMotorWithPot(){
  binServo.attach(BIN_SERVO);
  while(!digitalRead(CONFIRM)){
    int angle = (int)analogRead(DEBUG_POT) * 180 / 1023;
    sprintf(buffer, "Bin angle: %d", angle);
    printToDisplay(buffer);
    binServo.write(angle);
  }
}

void setRightMotorWithPot(){

}

void straightUntilNemo(int startSide){
  double kd = 0;
  double kp = 0;
  double gain = 0.5;

  while(!digitalRead(CONFIRM)){
    kp = analogRead(DEBUG_POT) * gain / 5000.0;
    sprintf(buffer, "Setting kp: %d\n\nUP to run\nDOWN to exit", analogRead(DEBUG_POT));
    printToDisplay(buffer);
    if(digitalRead(CYCLE)){
      return;
    }
    delay(5);
  }
  navi.tapeFollowUntilNemo(MOTOR_BASE_SPEED, MOTOR_BASE_SPEED, kp, kd);
}

void straightUntilNemoOnRight(){
  straightUntilNemo(TapeSide::RIGHT);
  printToDisplay("Done!");
  delay(1000);
}

void getMenuSelection(Menu menu) {
  menu.show(display);
  while(!digitalRead(CONFIRM)){
    if(digitalRead(CYCLE)){
      menu.cycle();
      menu.show(display);
      delay(CYCLE_WAIT_TIME);
    }
  }
  // for unknown reasons, menu fails in second iteration unless this is included.
  printToDisplay("Loading...");
  delay(MENU_WAIT_TIME);
  menu.select();
}

void subroutineMenu() {
  getMenuSelection(subMenu);
}

void raiseBinOnDetect(){
  while(!digitalRead(BIN_DETECT_L) || !digitalRead(BIN_DETECT_R)){
    sprintf(buffer,
      "Left: %d\nRight: %d",
      digitalRead(BIN_DETECT_L),
      digitalRead(BIN_DETECT_R));
    printToDisplay(buffer);
    motorL.setSpeed(- MOTOR_BASE_SPEED * (!digitalRead(BIN_DETECT_L)));
    motorR.setSpeed(- MOTOR_BASE_SPEED * (!digitalRead(BIN_DETECT_R)));
  }
  navi.stop();
  delay(200);
  raiseBin();
}


void hBridgeTest(){
  navi.drive(0.8,0.8,2000);
  navi.drive(-0.8,-0.8,2000);
}


void printToDisplay(const char *str) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.print(str);
    display.display();
}

void emptyFunc(){
}

void saveValues(){

  // drive
  // kp
  // kd
  // gain
  // base speed left (straight)
  // base speed right (straight)
  // base speed left (l turn)
  // base speed right (l turn)
  // base speed left (r turn)
  // base speed right (r turn)

  // windmill
  // speed
  // period
  // duty cycle

  // bin
  // min
  // max
}

void loadValues(){
  // drive
  // kp
  // kd
  // gain
  // base speed left (straight)
  // base speed right (straight)
  // base speed left (l turn)
  // base speed right (l turn)
  // base speed left (r turn)
  // base speed right (r turn)

  // windmill
  // speed
  // period
  // duty cycle

  // bin
  // min
  // max

}
