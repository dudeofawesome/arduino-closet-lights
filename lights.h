#include <Adafruit_NeoPixel.h>

class Lights {
public:
  static const uint8_t FPS = 60;
  static unsigned long last_ms;
  static void setup(Adafruit_NeoPixel* strip);
  static bool loop(unsigned long time_since_boot, uint16_t delta);
private:
  static Adafruit_NeoPixel* strip;
};