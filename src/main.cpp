#include "main.hpp"
#include "windmill.hpp"

Windmill wm{
  0,
  WINDMILL_SPEED,
  WINDMILL_PULSE_PERIOD,
  WINDMILL_PULSE_DUTYCYCLE,
  WINDMILL_TIMER_PIN,
  HardwareTimer(TIM1)
};

void runCompetition(){
  printToDisplay("Running Competition\n:)");
  delay(3000);
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

  pinMode(NEMO, INPUT_PULLUP);
  attachInterrupt(NEMO, nemoDetect, FALLING);

  // Windmill Setup
  pinMode(WINDMILL, OUTPUT);
  uint32_t channel = STM_PIN_CHANNEL(
    pinmap_function(digitalPinToPinName(WINDMILL_TIMER_PIN), PinMap_PWM));
  pwm_start(digitalPinToPinName(WINDMILL), 256, wm.currentSpeed, RESOLUTION_10B_COMPARE_FORMAT);
  wm.timer.pause();
  wm.timer.setPWM(
    channel,
    WINDMILL_TIMER_PIN,
    1,
    wm.dutycycle,
    []() -> void {windmillPulseLow(WINDMILL);},
    [&]() -> void {windmillPulseHigh(WINDMILL, wm.currentSpeed);}
  );
  // sets period of timer (rather than freq, to allow for periods of > 1 sec)
  wm.timer.setOverflow(1000 * wm.period, MICROSEC_FORMAT);
  wm.timer.resumeChannel(channel);

  // if servo is connected to same power supply as BP, do not run this block
  //binServo.attach(BIN_SERVO);
  //binServo.write(BIN_MIN);
}


void loop() {
  unsigned int choice = getMenuSelection(mainMenu);
  mainMenu.callbacks[choice]();

  printToDisplay("Returning to \nMain Menu");
  delay(MENU_WAIT_TIME);
}


void lowerBin(){
  binServo.write(BIN_MIN);
}
void raiseBin(){
  binServo.write(BIN_MAX);
}


void leftUntilNemo(){
  consumeTrigger(); // reset nemo
  double kd = 0;
  double kp = 0;
  double gain = 0.5;
  while(!digitalRead(CONFIRM) && !consumeTrigger()){
    kp = analogRead(DEBUG_POT) * gain / 5000.0;
    sprintf(buffer, "kp: %.3f", kp);
    printToDisplay(buffer);
    navi.correctToTape(0,MOTOR_BASE_SPEED,kp,kd);
  }
  navi.stop();
}


void rightUntilNemo(){
  consumeTrigger(); // reset nemo
  while(!digitalRead(CONFIRM) && !consumeTrigger()){
    navi.start(MOTOR_BASE_SPEED,0);
  }
  navi.stop();
}

void pivotUntilNemo(){
  consumeTrigger(); // reset nemo
  while(!digitalRead(CONFIRM) && !consumeTrigger()){
    navi.start(MOTOR_BASE_SPEED,-MOTOR_BASE_SPEED);
  }
  navi.stop();
}

void nemoDetect(){
  nemoTriggered = true;
}

bool consumeTrigger(){
  if (!nemoTriggered){
    return false;
  }
  nemoTriggered = false;
  return true;
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
  int percentage = analogRead(DEBUG_POT) * 100 / 1023;
  while(!digitalRead(CONFIRM) && !digitalRead(CYCLE)){
    percentage = analogRead(DEBUG_POT) * 100 / 1023;
    sprintf(buffer,
      "Windmill power: %d%%\n\nUP to save\nDOWN to stop",
      percentage);
    printToDisplay(buffer);
    wm.currentSpeed = percentage;
  }
  if(digitalRead(CYCLE)){
    wm.currentSpeed = 0;
  } else if(digitalRead(CONFIRM)){
    wm.targetSpeed = percentage;
    saveValues();
  }
}

void setBinWithPot(){
  while(!digitalRead(CONFIRM)){
    int angle = (int)analogRead(DEBUG_POT) * 180 / 1023;
    sprintf(buffer, "Bin angle: %d", angle);
    printToDisplay(buffer);
    binServo.write(angle);
  }
}

void straightUntilNemo(){
  consumeTrigger(); // reset nemo
  double kd = 0;
  double kp = 0;
  double gain = 0.5;
  while(!digitalRead(CONFIRM) && !consumeTrigger()){
    kp = analogRead(DEBUG_POT) * gain / 5000.0;
    sprintf(buffer, "kp: %.4f", kp);
    printToDisplay(buffer);
    navi.correctToTape(MOTOR_BASE_SPEED,MOTOR_BASE_SPEED,kp,kd);
    delay(50);
  }
  navi.stop();
  printToDisplay("Done!");
  delay(2000);
}

unsigned int getMenuSelection(Menu menu){
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
  return menu.select();
}

void subroutineMenu(){
  int choice = getMenuSelection(subMenu);
  callback_function_t func = subMenu.callbacks[choice];
  func();
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
