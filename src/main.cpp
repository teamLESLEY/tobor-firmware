#include "main.hpp"


void runCompetition(){
  printfToDisplay("Running Competition\n:)");
  delay(3000);
  // turn on windmill
  // follow tape to first flag
  // turns
  // blah blah blah
  // pivot
  // align to bin
  // dump cans
}


void runEntertainment(){
  printfToDisplay("Running Entertainment\n:)");
  delay(3000);
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

  // if servo is connected to same power supply as BP, do not run this block
  binServo.attach(BIN_SERVO);
  binServo.write(BIN_MIN);
}


void loop() {
  unsigned int choice = getMenuSelection(mainMenu);
  mainMenu.callbacks[choice]();
  
  printfToDisplay("Returning to \nMain Menu");
  delay(MENU_WAIT_TIME);
}




void lowerBin(){
  binServo.write(BIN_MIN);
}
void raiseBin(){
  binServo.write(BIN_MAX);
}


void fullLeftTurn(){}
void fullRightTurn(){}
void pivot(){}
void halfRightTurn(){}
void nemo_detect(){
}

void setWindmill(double percentage){
  int freq = 512;
  int speed = freq * percentage;
  pwm_start(digitalPinToPinName(WINDMILL),512,speed,RESOLUTION_10B_COMPARE_FORMAT);
}


void printSensorReadings(){
  while(!digitalRead(CONFIRM)){
    printfToDisplay("Tape L: %4.d \nTape R: %4.d \n\n Nemo: %1.d", 
      tape.getLeftReading(), 
      tape.getRightReading(), 
      digitalRead(NEMO));
  }
}




void setWindmillWithPot(){
  while(!digitalRead(CONFIRM) && !digitalRead(CYCLE)){
    double percentage = analogRead(DEBUG_POT) / 1023.0;
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Windmill power: ");
    display.print((int) (percentage * 100));
    display.print("%\n");
    display.println("UP to confirm");
    display.println("DOWN to stop");
    display.display();
    setWindmill(percentage);
  }
  if(digitalRead(CYCLE)){
    setWindmill(0);
  }
}

void setBinWithPot(){
  while(!digitalRead(CONFIRM)){
    int angle = analogRead(DEBUG_POT) * 180 / 1023;
    printfToDisplay("Bin angle: %d", angle);
    binServo.write(angle);
  }
}



void straightUntilNemo(){
  while(true/*nemo has yet to be triggered */){}
}



unsigned int getMenuSelection(Menu menu){
  menu.show(display);
  while(!digitalRead(CONFIRM)){
    if(digitalRead(CYCLE)){
      menu.cycle();
      menu.show(display);
      delay(150);
    }
  }
  // for unknown reasons, menu fails in second iteration unless this is included. 
  // do not remove
  printfToDisplay("Loading...");
  delay(MENU_WAIT_TIME);
  return menu.select();
}

void subroutineMenu(){

  int choice = getMenuSelection(subMenu);
  callback_function_t func = subMenu.callbacks[choice];
  func();
}



void raiseBinOnDetect(){}
void hBridgeTest(){}


void printfToDisplay(const char *format, ...) {
    display.clearDisplay();
    display.setCursor(0,0);
    va_list args;
    va_start(args, format);
    display.printf(format, args);
    va_end(args);
    display.display();
}

void emptyFunc(){
}