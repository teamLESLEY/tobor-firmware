#include "windmill.hpp"

void windmillPulseHigh(uint32_t pin, unsigned int speed){
  analogWrite(pin, speed * 1023 / 100);
}

void windmillPulseLow(uint32_t pin) {
  analogWrite(pin, 0);
}
