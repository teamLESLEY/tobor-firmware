#include "main.hpp"
#include "windmill.hpp"

int debugToneNum = 0;
bool debugging = false;

Windmill wm{
  WINDMILL_SPEED,
  WINDMILL_PULSE_PERIOD,
  WINDMILL_PULSE_DUTYCYCLE,
  WINDMILL,
  WINDMILL_TIMER_PIN,
  HardwareTimer(TIM1)
};

void backspin(){
  navi.drive(-0.8, -0.8, HARD_STOP_TIME);
}

void debugTone(){
  if(debugToneNum % 12 != 4 && debugToneNum % 12 != 11){
    debugToneNum++;
  }
  debugToneNum++;
  int freq = 440 * pow(2, debugToneNum / 12.0);
  tone(SOPRANO, freq);
}

void finisher(){
  tiltBin();
  wm.stop();

  // pivot (absorb 3 tape passes, waiting 100 ms afer each pass)
  for(int i = 0; i < 3; i++){
    navi.driveUntilDory(MOTOR_BASE_SPEED, -MOTOR_BASE_SPEED, 200);
  }
  // reverse to bin
  navi.driveUntilDory(-MOTOR_BASE_SPEED, -MOTOR_BASE_SPEED, 100);
  delay(300);
  raiseBin();
  delay(5000);
  // binServo.detach();
}

void raiseBin() {
  bin.setAngle(BIN_MAX);
}

void rightTurn(int skipped){
  backspin();
  for(int i = 0; i < skipped + 1; i++){
    navi.driveUntilNemo(R_TURN_L_MOTOR_SPEED, R_TURN_R_MOTOR_SPEED);
  }
  navi.driveUntilDory(MOTOR_BASE_SPEED, MOTOR_BASE_SPEED/2); // recovery
}

void straight(){
  navi.tapeFollowUntilNemo(MOTOR_BASE_SPEED, MOTOR_BASE_SPEED, kp, kd);
}


void perimeter(){

  // side 1
  straight();
  straight();
  rightTurn();

  // side 2
  straight();
  straight();
  rightTurn();

  // side 3
  straight();
  rightTurn();
}


void innerSquare(){
  // finish driving 4th side of outer square & turn onto inner square
  straight();
  rightTurn();

  // side 1
  straight();
  straight();
  rightTurn(2);   // skips when crossing and reentering outer square

  // side 2
  straight();
  rightTurn(2);

  // side 3
  straight();
  rightTurn(2);
}

void returnPath(){
  // finish side 4 of inner square
  straight();

  // skip first 2 nemo flags
  for(int i = 0; i < 3; i++){
    navi.tapeFollowUntilNemo(MOTOR_BASE_SPEED, 0, kp, kd);
  }
  // lock onto and finish side 1
  straight();
  rightTurn();

  // side 2 (first half)
  straight();
  rightTurn(1);

  // middle cutback
  straight(); // entering inner square
  straight(); // exiting inner square
  straight(); // exiting outer square
}

void waitForConfirm(){
  if (debugging){
    printToDisplay("Waiting for confirm\n (UP)");
    while (!digitalRead(CONFIRM))
    ;
  }
}

void competition(){
  delay(200);

  perimeter();
  innerSquare();
  returnPath();
  
}

void debugCompetition(){
  printToDisplay("Debugging Competition\n:)");
  debugging = true;
  competition();
}

void runCompetition(){
  printToDisplay("Running Competition\n:)");
  debugging = false;
  competition();
}

void runEntertainment(){
  printToDisplay("Running Entertainment\n:)");
  delay(3000);
}

void setup(){
  // loadValues();

  kp = K_PROPORTIONAL / 10000.0;
  kd = K_DERIVATIVE / 100.0;

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  // Inputs
  pinMode(DEBUG_UP, INPUT_PULLUP);
  pinMode(DEBUG_DOWN, INPUT_PULLUP);
  pinMode(DEBUG_POT, INPUT);

  // if servo is connected to same power supply as BP, do not run this block
}

void loop() {
  getMenuSelection(mainMenu);

  printToDisplay("Returning to \nMain Menu");
  delay(MENU_WAIT_TIME);
}


void lowerBin(){
  bin.setAngle(BIN_MIN);
}

void tiltBin(){
  bin.setAngle((BIN_MAX + 2 * BIN_MIN) / 3);
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
  wm.start();
  unsigned int speed = analogRead(DEBUG_POT);
  while(!digitalRead(CONFIRM) && !digitalRead(CYCLE)){
    speed = analogRead(DEBUG_POT);
    sprintf(
      buffer,
      "Windmill power: %d\n\nUP to save\nDOWN to stop",
      speed
    );
    printToDisplay(buffer);
    wm.setSpeed(speed);
  }
  if (digitalRead(CYCLE)) {
    wm.stop();
  }
}

void setBinWithPot(){
  while(!digitalRead(CONFIRM)){
    int angle = (int)analogRead(DEBUG_POT) * 180 / 1023;
    sprintf(buffer, "Bin angle: %d", angle);
    printToDisplay(buffer);
    bin.setAngle(angle);
  }
}

void straightUntilNemo(int startSide){
  double kderiv = 0;
  double kprop = 0;
  double gain = 0.5;

  while(!digitalRead(CONFIRM)){
    kprop = analogRead(DEBUG_POT) * gain / 5000.0;
    sprintf(buffer,
        "Setting kp: %d\n\nTape L: %d\nTape R: %d\n\nUP to run\nDOWN to exit",
        (int) analogRead(DEBUG_POT),
        tape.getLeftReading(),
        tape.getRightReading()
        );
    printToDisplay(buffer);
    if(digitalRead(CYCLE)){
      return;
    }
    delay(5);
  }
  navi.tapeFollowUntilNemo(MOTOR_BASE_SPEED, MOTOR_BASE_SPEED, kprop, kderiv,startSide);
}

void straightUntilNemoOnRight(){
  straightUntilNemo(TapeSide::RIGHT);
  printToDisplay("Done!");
  delay(1000);
}

void getMenuSelection(Menu menu) {
  menu.show(display);
  while (!digitalRead(CONFIRM)) {
    if (digitalRead(CYCLE)) {
      menu.cycle();
      menu.show(display);
      delay(CYCLE_WAIT_TIME);
    }
  }
  while (digitalRead(CONFIRM)); // Wait until CONFIRM is released
  // for unknown reasons, menu fails in second iteration unless this is included.
  printToDisplay("Loading...");
  delay(MENU_WAIT_TIME);
  menu.select();
}

void subroutineMenu() {
  getMenuSelection(subMenu);
}

void raiseBinOnDetect(){
  while( ! (bin.onLeft() && bin.onRight()) ) {
    sprintf(buffer,
      "Left: %d\nRight: %d", bin.onLeft(), bin.onRight());
    printToDisplay(buffer);

    motorL.setSpeed(- MOTOR_BASE_SPEED * (!bin.onLeft()));
    motorR.setSpeed(- MOTOR_BASE_SPEED * (!bin.onRight()));
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
