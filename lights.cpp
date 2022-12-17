#include "Arduino.h"

#include "lights.h"
#include "door.h"

Adafruit_NeoPixel* Lights::strip;
unsigned long Lights::last_ms = 0;

void Lights::setup(Adafruit_NeoPixel* _strip) {
  strip = _strip;
}

bool Lights::loop(unsigned long time_since_boot, uint16_t delta) {
  uint8_t brightness = Door::get_brightness();

  for (uint16_t i = 0; i < strip->numPixels(); i++) {
    // strip->setPixelColor(i, strip->Color(brightness, brightness / 1.42, brightness / 2.38)); // 3000K
    strip->setPixelColor(i, strip->Color(brightness, brightness / 1.3, brightness / 1.85));  // 3500K
    // strip->setPixelColor(i, strip->Color(brightness, brightness / 1.22, brightness / 1.56));  // 4000K
  }

  // Allow the event chain to continue
  return false;
}