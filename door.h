class Door {
public:
  static const uint8_t FPS = 60;
  static unsigned long last_ms;
  static void setup(uint8_t door_sensor_pin);
  static bool loop(unsigned long time_since_boot, uint16_t delta);
  static uint8_t get_brightness();
private:
  static uint8_t DOOR_SENSOR_PIN;
  static const uint16_t FADE_DUR_MS = 1000;
  static const uint16_t FADE_DUR_MS_HALF = FADE_DUR_MS / 2;

  static bool door_open;
  static uint16_t x;
};