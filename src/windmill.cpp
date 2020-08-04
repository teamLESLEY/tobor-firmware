#include "windmill.hpp"

void startWindmill(Windmill& wm) {
  pinMode(wm.outputPin, OUTPUT);
  uint32_t channel = STM_PIN_CHANNEL(
    pinmap_function(digitalPinToPinName(wm.timerPin), PinMap_PWM)
  );
  pwm_start(
    digitalPinToPinName(wm.outputPin),
    200,
    wm.speed,
    RESOLUTION_10B_COMPARE_FORMAT
  );
  wm.timer.pause();
  wm.timer.setPWM(
    channel,
    wm.timerPin,
    1,
    wm.dutycycle,
    [&]() -> void {windmillOn(wm.outputPin, wm.speed);},
    [&]() -> void {windmillOff(wm.outputPin);}
  );
  // sets period of timer (rather than freq, to allow for periods of > 1 sec)
  wm.timer.setOverflow(1000 * wm.period, MICROSEC_FORMAT);
  wm.timer.resumeChannel(channel);
}

void stopWindmill(Windmill& wm) {
  wm.timer.pause();
  windmillOff(wm.outputPin);
}

void windmillOn(uint32_t pin, unsigned int speed){
  pwm_start(
    digitalPinToPinName(pin),
    200,
    speed,
    RESOLUTION_10B_COMPARE_FORMAT
  );
}

void windmillOff(uint32_t pin) {
  pwm_start(
    digitalPinToPinName(pin),
    200,
    0,
    RESOLUTION_10B_COMPARE_FORMAT
  );
}
