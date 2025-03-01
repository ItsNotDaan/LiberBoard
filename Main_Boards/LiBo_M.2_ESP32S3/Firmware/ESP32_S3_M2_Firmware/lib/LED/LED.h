#include <Arduino.h>
#include <FastLED.h>

#define DATA_PIN    46
#define NUM_LEDS    1
#define BRIGHTNESS  30
#define LED_TYPE    WS2812B
#define COLOR_ORDER RGB

// Define the array of leds
#define UPDATES_PER_SECOND 100

CRGB leds[NUM_LEDS];

void RGB_LED(bool state, int r, int g, int b);