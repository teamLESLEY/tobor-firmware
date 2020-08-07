#include "main.hpp"
#include "windmill.hpp"

int debugToneNum = 0;
bool debugging = false;

// Track 1:

int note_freqs1[450] = {233,0,233,0,233,0,233,0,233,0,233,0,207,0,233,0,233,0,233,0,233,0,233,0,233,0,207,0,233,0,233,0,233,0,233,0,233,0,233,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,233,0,174,0,233,0,233,0,261,0,293,0,311,0,349,0,349,0,349,0,369,0,415,0,466,0,466,0,466,0,415,0,369,0,415,0,369,0,349,0,349,0,311,0,311,0,349,0,369,0,349,0,311,0,277,0,277,0,311,0,349,0,311,0,277,0,261,0,261,0,293,0,329,0,391,0,349,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,233,0,174,0,233,0,233,0,261,0,293,0,311,0,349,0,349,0,349,0,369,0,415,0,466,0,554,0,523,0,440,0,349,0,369,0,466,0,440,0,349,0,349,0,369,0,466,0,440,0,349,0,293,0,311,0,369,0,349,0,277,0,233,0,261,0,261,0,293,0,329,0,391,0,349,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,233,0,174,0,233,0,233,0,261,0,293,0,311,0,349,0,349,0,349,0,369,0,415,0,466,0,466,0,466,0,415,0,369,0,415,0,369,0,349,0,349,0,311,0,311,0,349,0,369,0,349,0,311,0,277,0,277,0,311,0,349,0,311,0,277,0,261,0,261,0,293,0,329,0,391,0,349,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,233,0,174,0,233,0,233,0,261,0,293,0,311,0,349,0,349,0,349,0,369,0,415,0,466,0,554,0,523,0,440,0,349,0,369,0,466,0,440,0,349,0,349,0,369,0,466,0,440,0,349,0,293,0,311,0,369,0,349,0,277,0,233,0,261,0,261,0,293,0,329,0,391,0,349,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,174,0,233,0};      

int durations1[450] = {0,959,1280,1439,1440,1599,1600,1759,1760,1919,1920,2239,2240,2399,2400,3199,3200,3359,3360,3519,3520,3679,3680,3839,3840,4159,4160,4319,4320,5119,5120,5279,5280,5439,5440,5599,5600,5759,5760,5999,6000,6119,6120,6239,6240,6479,6480,6599,6600,6719,6720,6959,6960,7079,7080,7199,7200,7439,7440,7679,7680,8159,8160,8999,9000,9119,9120,9239,9240,9359,9360,9479,9480,9599,9600,10799,10800,11039,11040,11199,11200,11359,11360,11519,11520,12799,12800,12959,12960,13119,13120,13279,13280,13439,13440,13759,13760,13919,13920,14879,14880,15359,15360,15599,15600,15719,15720,15839,15840,16799,16800,17039,17040,17279,17280,17519,17520,17639,17640,17759,17760,18719,18720,18959,18960,19199,19200,19439,19440,19559,19560,19679,19680,20639,20640,21119,21120,21359,21360,21479,21480,21599,21600,21839,21840,21959,21960,22079,22080,22319,22320,22439,22440,22559,22560,22799,22800,23039,23040,23519,23520,24359,24360,24479,24480,24599,24600,24719,24720,24839,24840,24959,24960,26159,26160,26399,26400,26559,26560,26719,26720,26879,26880,28319,28320,28799,28800,29279,29280,30239,30240,30719,30720,32159,32160,32639,32640,33119,33120,34079,34080,34559,34560,35999,36000,36479,36480,36959,36960,37919,37920,38399,38400,39839,39840,40319,40320,40799,40800,41759,41760,42239,42240,42479,42480,42599,42600,42719,42720,43679,43680,44159,44160,44399,44400,44519,44520,44639,44640,44879,44880,44999,45000,45119,45120,45359,45360,45479,45480,45599,45600,45839,45840,46079,46080,46559,46560,47399,47400,47519,47520,47639,47640,47759,47760,47879,47880,47999,48000,49199,49200,49439,49440,49599,49600,49759,49760,49919,49920,51199,51200,51359,51360,51519,51520,51679,51680,51839,51840,52159,52160,52319,52320,53279,53280,53759,53760,53999,54000,54119,54120,54239,54240,55199,55200,55439,55440,55679,55680,55919,55920,56039,56040,56159,56160,57119,57120,57359,57360,57599,57600,57839,57840,57959,57960,58079,58080,59039,59040,59519,59520,59759,59760,59879,59880,59999,60000,60239,60240,60359,60360,60479,60480,60719,60720,60839,60840,60959,60960,61199,61200,61439,61440,61919,61920,62759,62760,62879,62880,62999,63000,63119,63120,63239,63240,63359,63360,64559,64560,64799,64800,64959,64960,65119,65120,65279,65280,66719,66720,67199,67200,67679,67680,68639,68640,69119,69120,70559,70560,71039,71040,71519,71520,72479,72480,72959,72960,74399,74400,74879,74880,75359,75360,76319,76320,76799,76800,78239,78240,78719,78720,79199,79200,80159,80160,80639,80640,80879,80880,80999,81000,81119,81120,82079,82080,82559,82560,82799,82800,82919,82920,83039,83040,83279,83280,83399,83400,83519,83520,83759,83760,83879,83880,83999,84000,84239,84240,84479,84480,86399};



// Track 2:

int note_freqs2[606] = {146,0,146,0,146,0,146,0,146,0,130,0,130,0,130,0,130,0,130,0,130,0,130,0,138,0,138,0,138,0,138,0,138,0,138,0,138,0,138,0,130,0,130,0,130,0,130,0,130,0,130,0,130,0,130,0,130,0,130,0,174,0,146,0,146,0,130,0,146,0,146,0,146,0,155,0,174,0,195,0,207,0,233,0,233,0,261,0,293,0,311,0,349,0,207,0,207,0,233,0,261,0,277,0,184,0,184,0,207,0,233,0,261,0,277,0,277,0,261,0,233,0,277,0,207,0,207,0,207,0,184,0,207,0,207,0,207,0,184,0,207,0,184,0,184,0,184,0,207,0,233,0,207,0,184,0,174,0,174,0,174,0,184,0,207,0,184,0,174,0,174,0,174,0,155,0,174,0,184,0,195,0,220,0,233,0,261,0,220,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,174,0,146,0,146,0,130,0,146,0,146,0,146,0,155,0,174,0,195,0,207,0,233,0,233,0,261,0,293,0,311,0,349,0,207,0,207,0,233,0,261,0,277,0,311,0,261,0,261,0,220,0,246,0,311,0,261,0,220,0,220,0,246,0,311,0,261,0,220,0,220,0,246,0,311,0,233,0,233,0,174,0,155,0,155,0,164,0,174,0,195,0,195,0,220,0,233,0,261,0,220,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,174,0,146,0,146,0,130,0,146,0,146,0,146,0,155,0,174,0,195,0,207,0,233,0,233,0,261,0,293,0,311,0,349,0,207,0,207,0,233,0,261,0,277,0,184,0,184,0,207,0,233,0,261,0,277,0,277,0,261,0,233,0,277,0,207,0,207,0,207,0,184,0,207,0,207,0,207,0,184,0,207,0,184,0,184,0,184,0,207,0,233,0,207,0,184,0,174,0,174,0,174,0,184,0,207,0,184,0,174,0,174,0,174,0,155,0,174,0,184,0,195,0,220,0,233,0,261,0,220,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,174,0,146,0,146,0,130,0,146,0,146,0,146,0,155,0,174,0,195,0,207,0,233,0,233,0,261,0,293,0,311,0,349,0,207,0,207,0,233,0,261,0,277,0,311,0,261,0,261,0,220,0,246,0,311,0,261,0,220,0,220,0,246,0,311,0,261,0,220,0,220,0,246,0,311,0,233,0,233,0,174,0,155,0,155,0,164,0,174,0,195,0,195,0,220,0,233,0,261,0,220,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,110,0,146,0};

int durations2[606] = {0,959,1280,1439,1440,1599,1600,1759,1760,1919,1920,2239,2240,2399,2400,3199,3200,3359,3360,3519,3520,3679,3680,3839,3840,4159,4160,4319,4320,5119,5120,5279,5280,5439,5440,5599,5600,5759,5760,5999,6000,6119,6120,6239,6240,6479,6480,6599,6600,6719,6720,6959,6960,7079,7080,7199,7200,7439,7440,7679,7680,8159,8160,8319,8320,8479,8480,8639,8640,8999,9000,9119,9120,9239,9240,9359,9360,9479,9480,9599,9600,9959,9960,10079,10080,10199,10200,10319,10320,10439,10440,10559,10560,10799,10800,11039,11040,11199,11200,11359,11360,11519,11520,11879,11880,11999,12000,12119,12120,12239,12240,12359,12360,12479,12480,12959,12960,13119,13120,13279,13280,13439,13440,13759,13760,13919,13920,14079,14080,14239,14240,14399,14400,14719,14720,14879,14880,15039,15040,15199,15200,15359,15360,15599,15600,15719,16080,16199,16200,16319,16320,16799,16800,17039,17040,17279,17280,17519,17520,17639,18000,18119,18120,18239,18240,18719,18720,18959,18960,19199,19200,19439,19440,19559,19920,20039,20040,20159,20160,20399,20400,20519,20520,20639,20640,20879,20880,21119,21120,21359,21360,21479,21480,21599,21600,21839,21840,21959,21960,22079,22080,22319,22320,22439,22440,22559,22560,22799,22800,23039,23040,23519,23520,23679,23680,23839,23840,23999,24000,24359,24360,24479,24480,24599,24600,24719,24720,24839,24840,24959,24960,25319,25320,25439,25440,25559,25560,25679,25680,25799,25800,25919,25920,26159,26160,26399,26400,26559,26560,26719,26720,26879,26880,28319,28320,28799,28800,29279,29280,30239,30240,30719,30720,32159,32160,32639,32640,33119,33120,34079,34080,34559,34560,35999,36000,36479,36480,36959,36960,37919,37920,38399,38400,39839,39840,40319,40320,40799,40800,41759,41760,42239,42240,42479,42480,42599,42960,43079,43080,43199,43200,43439,43440,43559,43560,43679,43680,43919,43920,44159,44160,44399,44400,44519,44520,44639,44640,44879,44880,44999,45000,45119,45120,45359,45360,45479,45480,45599,45600,45839,45840,46079,46080,46559,46560,46719,46720,46879,46880,47039,47040,47399,47400,47519,47520,47639,47640,47759,47760,47879,47880,47999,48000,48359,48360,48479,48480,48599,48600,48719,48720,48839,48840,48959,48960,49199,49200,49439,49440,49599,49600,49759,49760,49919,49920,50279,50280,50399,50400,50519,50520,50639,50640,50759,50760,50879,50880,51359,51360,51519,51520,51679,51680,51839,51840,52159,52160,52319,52320,52479,52480,52639,52640,52799,52800,53119,53120,53279,53280,53439,53440,53599,53600,53759,53760,53999,54000,54119,54480,54599,54600,54719,54720,55199,55200,55439,55440,55679,55680,55919,55920,56039,56400,56519,56520,56639,56640,57119,57120,57359,57360,57599,57600,57839,57840,57959,58320,58439,58440,58559,58560,58799,58800,58919,58920,59039,59040,59279,59280,59519,59520,59759,59760,59879,59880,59999,60000,60239,60240,60359,60360,60479,60480,60719,60720,60839,60840,60959,60960,61199,61200,61439,61440,61919,61920,62079,62080,62239,62240,62399,62400,62759,62760,62879,62880,62999,63000,63119,63120,63239,63240,63359,63360,63719,63720,63839,63840,63959,63960,64079,64080,64199,64200,64319,64320,64559,64560,64799,64800,64959,64960,65119,65120,65279,65280,66719,66720,67199,67200,67679,67680,68639,68640,69119,69120,70559,70560,71039,71040,71519,71520,72479,72480,72959,72960,74399,74400,74879,74880,75359,75360,76319,76320,76799,76800,78239,78240,78719,78720,79199,79200,80159,80160,80639,80640,80879,80880,80999,81360,81479,81480,81599,81600,81839,81840,81959,81960,82079,82080,82319,82320,82559,82560,82799,82800,82919,82920,83039,83040,83279,83280,83399,83400,83519,83520,83759,83760,83879,83880,83999,84000,84239,84240,84479,84480,86399};

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
  rightTurn();

  // side 2
  straight();
  rightTurn();

  // side 3
  // straight();
  // rightTurn();

  // side 4
  // straight();
  // rightTurn();
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
  bin.setAngle(BIN_MIN);
  wm.start();
  unsigned long start = millis();

  while((millis() - start) < FIRST_FLAG_TIME) {
    straight();
  }


  backspin();

  finalTurn();
  delay(100);
  raiseBinOnDetect();

  delay(3000);
  wm.stop();
  wm.setSpeed(0);

  delay(10000);
  lowerBin();
}

void debugCompetition(){
  printToDisplay("Debugging Competition\n:)");
  debugging = true;
  competition();
}

void runCompetition(){
  while(!digitalRead(CONFIRM)){
    sprintf(buffer,
        "Tape L: %d\nTape R: %d\n\nUP to run\nDOWN to exit",
        tape.getLeftReading(),
        tape.getRightReading());
    printToDisplay(buffer);

    if(digitalRead(CYCLE)){
      return;
    }
    delay(5);
  }
  printToDisplay("Running Competition\n:)");
  debugging = false;
  competition();
}

void play_pwm_note(int pin, int freq){
  if (freq == 0) pwm_stop(digitalPinToPinName(pin));
  else pwm_start(digitalPinToPinName(pin), freq, 50, RESOLUTION_10B_COMPARE_FORMAT);
}

void all_speakers_off(){
  pwm_start(digitalPinToPinName(SOP), 512, 0, RESOLUTION_10B_COMPARE_FORMAT);
    pwm_start(digitalPinToPinName(ALTO), 512, 0, RESOLUTION_10B_COMPARE_FORMAT);
}


void runEntertainment(){
  wm.setSpeed(WINDMILL_SPEED);
  raiseBin();
  delay(1000);
  wm.setSpeed(0);
  double transpose = 1.5;
  double tempo = 1;
  unsigned int i1 = 0;
  unsigned int i2 = 0;
  unsigned int i3 = 0;

  uint32_t startTime = millis();
  uint32_t elapsedTime = millis();

  while(i1 < sizeof(note_freqs1) || i2 < sizeof(note_freqs2)) {
    elapsedTime = millis() - startTime;
    if (i1 < sizeof(note_freqs1) && elapsedTime > durations1[i1]/tempo){
      tone(SOP, note_freqs1[i1]*transpose);
      i1++;
    }
    if (i2 < sizeof(note_freqs2) && elapsedTime > durations2[i2]/tempo){
      play_pwm_note(ALTO, note_freqs2[i2]*transpose);
      i2++;
    }
  }
}

void setup(){
  Serial.begin(9600);
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

  pinMode(SOP, OUTPUT);
  pinMode(ALTO, OUTPUT);

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
  navi.drive(-R_TURN_L_MOTOR_SPEED, -R_TURN_R_MOTOR_SPEED, RIGHT_TURN_CORRECTION_DURATION);
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
  double kderiv = K_DERIVATIVE;
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
  backspin();
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

void finalTurn() {
  navi.driveUntilNemo(-PIVOT_SPEED, PIVOT_SPEED, 0);
  navi.drive(PIVOT_CORRECTION_SPEED, -PIVOT_CORRECTION_SPEED, PIVOT_CORRECTION_DURATION);
}
