// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

// uses Adafruit NeoPixel, Eventually, MicroTuple, and Array libs.

#include <Arduino.h>
#include <TaskManagerIO.h>
#include <Adafruit_NeoPixel.h>

#include "lights.h"
#include "door.h"

// Which pin on the Arduino is connected to the NeoPixels?
#if defined(ESP8266)
#define LED_PIN D2
#elif defined(ARDUINO_Node32s)
// TODO: this might be the wrong pin
#define LED_PIN 19
#elif defined(ARDUINO_AVR_LEONARDO) || defined(ARDUINO_AVR_PROMICRO)
#define LED_PIN 6
#define DOOR_SENSOR_PIN 7
#else
#error Unknown hardware platform
#endif

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 100

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

void setup() {
  Serial.begin(115200);

  Lights::setup(&strip);
  Door::setup(DOOR_SENSOR_PIN);

  strip.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();   // Turn OFF all pixels ASAP

  taskManager.scheduleFixedRate(1000 / Lights::FPS, [] {
    unsigned long m = millis();
    uint16_t delta = m - Lights::last_ms;
    Lights::last_ms = m;
    if (true) {
      Serial.print("lights delta: ");
      Serial.println(delta);
    }

    Lights::loop(m, delta);
  });

  taskManager.scheduleFixedRate(1000 / Door::FPS, [] {
    unsigned long m = millis();
    uint16_t delta = m - Door::last_ms;
    Door::last_ms = m;
    if (false) {
      Serial.print("door delta: ");
      Serial.println(delta);
    }

    Door::loop(m, delta);
  });

  taskManager.scheduleFixedRate(1000 / Lights::FPS, [] {
    strip.show();
  });
}

void loop() {
  /**
     * Optional:
     * If you wanted to go into a low power mode between tasks, you can use taskManager.microsToNextTask() to determine
     * how long you can sleep before the next execution. If you use interrupts, ensure the low power mode supports them.
     */
  // auto delay = taskManager.microsToNextTask();
  // yourLowPowerMode.sleep(delay);

  taskManager.runLoop();
}