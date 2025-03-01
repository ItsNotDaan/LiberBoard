#include <LED.h>

void RGB_LED(bool state, int r, int g, int b) {
  if (state) {
    leds[0] = CRGB(r, g, b);
    FastLED.show();
  } else {
    leds[0] = CRGB( 0, 0, 0);
    FastLED.show();
  }
}