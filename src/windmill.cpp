#include "windmill.hpp"

void Windmill::start() {
  pinMode(outputPin, OUTPUT);
  uint32_t channel = STM_PIN_CHANNEL(
    pinmap_function(digitalPinToPinName(timerPin), PinMap_PWM)
  );
  pwm_start(
    digitalPinToPinName(outputPin),
    200,
    speed,
    RESOLUTION_10B_COMPARE_FORMAT
  );
  timer.pause();
  timer.setPWM(
    channel,
    timerPin,
    1,
    dutycycle,
    [&]() -> void {on();},
    [&]() -> void {off();}
  );
  // sets period of timer (rather than freq, to allow for periods of > 1 sec)
  timer.setOverflow(1000 * period, MICROSEC_FORMAT);
  timer.resumeChannel(channel);
}

void Windmill::stop() {
  timer.pause();
  windmillOff(outputPin);
}

void Windmill::on() {
  pwm_start(
    digitalPinToPinName(outputPin),
    200,
    speed,
    RESOLUTION_10B_COMPARE_FORMAT
  );
}

void Windmill::off() {
  pwm_start(
    digitalPinToPinName(outputPin),
    200,
    0,
    RESOLUTION_10B_COMPARE_FORMAT
  );
}

// Ignore out-of-range speeds
void Windmill::setSpeed(unsigned int speed) {
  if (speed >= 0 && speed < 1024) {
    this->speed = speed;
  }
}
