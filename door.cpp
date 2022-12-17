#include "Arduino.h"

#include "door.h"

uint8_t Door::DOOR_SENSOR_PIN;
unsigned long Door::last_ms = 0;
bool Door::door_open = false;
uint16_t Door::x = 0;

void Door::setup(uint8_t door_sensor_pin) {
  DOOR_SENSOR_PIN = door_sensor_pin;
  pinMode(DOOR_SENSOR_PIN, INPUT);
}

bool Door::loop(unsigned long time_since_boot, uint16_t delta) {
  if (!digitalRead(DOOR_SENSOR_PIN)) {
    // door is open
    door_open = true;
  } else {
    // door is closed
    door_open = false;
  }


  if (door_open) {
    if (x <= FADE_DUR_MS - delta) x += delta;
    else x = FADE_DUR_MS;
  } else {
    if (x >= delta) x -= delta;
    else x = 0;
  }
}

const float ONE_THOUSAND_OVER_PI = 1000.0 / 3.1415926536;

uint8_t Door::get_brightness() {
  uint8_t y = sin(((int16_t)x - (int16_t)FADE_DUR_MS_HALF) / ONE_THOUSAND_OVER_PI) * 127 + 127;
  return y;
}