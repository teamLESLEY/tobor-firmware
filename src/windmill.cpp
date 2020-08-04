#include "windmill.hpp"

void setupWindmill(Windmill& wm) {
  pinMode(wm.outputPin, OUTPUT);
  uint32_t channel = STM_PIN_CHANNEL(
    pinmap_function(digitalPinToPinName(wm.timerPin), PinMap_PWM)
  );
  pwm_start(
    digitalPinToPinName(wm.outputPin),
    256,
    wm.speed,
    RESOLUTION_10B_COMPARE_FORMAT
  );
  wm.timer.pause();
  wm.timer.setPWM(
    channel,
    wm.timerPin,
    1,
    wm.dutycycle,
    [&]() -> void {windmillPulseLow(wm.outputPin);},
    [&]() -> void {windmillPulseHigh(wm.outputPin, wm.speed);}
  );
  // sets period of timer (rather than freq, to allow for periods of > 1 sec)
  wm.timer.setOverflow(1000 * wm.period, MICROSEC_FORMAT);
  stopWindmill(wm);
}

void startWindmill(Windmill& wm) {
  uint32_t channel = STM_PIN_CHANNEL(
    pinmap_function(digitalPinToPinName(wm.timerPin), PinMap_PWM)
  );
  wm.timer.resumeChannel(channel);
}

void stopWindmill(Windmill& wm) {
  wm.timer.pause();
  windmillPulseLow(wm.outputPin);
}

void windmillPulseHigh(uint32_t pin, unsigned int speed){
  analogWrite(pin, speed * 1023 / 100);
}

void windmillPulseLow(uint32_t pin) {
  analogWrite(pin, 0);
}
