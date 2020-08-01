#include "windmill.hpp"

void windmillPulseHigh(){
  analogWrite(WINDMILL, windmill.currentSpeed);
}

void windmillPulseLow(){
  analogWrite(WINDMILL, 0);
}

Windmill::Windmill(int outputPin, int period, int targetSpeed, int dutycycle, int timerPin, HardwareTimer timer)
  : outputPin(outputPin), period(period), targetSpeed(targetSpeed), dutycycle(dutycycle), timerPin(timerPin), timer(timer){
}

  void Windmill::setup(){
    pinMode(outputPin, OUTPUT);
    uint32_t channel = STM_PIN_CHANNEL(
        pinmap_function(digitalPinToPinName(timerPin), PinMap_PWM));  
    pwm_start(digitalPinToPinName(outputPin), 256, 0, RESOLUTION_10B_COMPARE_FORMAT);
    timer.pause();
    timer.setPWM(channel, timerPin, 1, dutycycle, 
        windmillPulseLow, windmillPulseHigh); 
    // sets period of timer (rather than freq, to allow for periods of > 1 sec)
    timer.setOverflow(1000 * period, MICROSEC_FORMAT); 
    timer.resumeChannel(channel);
  }

  void Windmill::start(){
      currentSpeed = targetSpeed;
  }

  void Windmill::setSpeed(int speed){
      targetSpeed = speed;
  }

  void Windmill::stop(){
      currentSpeed = 0;
  }

  void Windmill::detach(){
      timer.pause();
      pwm_stop(digitalPinToPinName(outputPin));
      currentSpeed = 0;
  }