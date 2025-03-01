#include <Arduino.h>
#include <FastLED.h>

#define DATA_PIN    7
#define NUM_LEDS    1
#define BRIGHTNESS  30
#define LED_TYPE    WS2812B

// Define the array of leds
#define UPDATES_PER_SECOND 100

extern CRGB leds[NUM_LEDS];

void RGB_LED(bool state, int r, int g, int b);  	 