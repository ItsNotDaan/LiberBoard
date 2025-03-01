#include <LED.h>

void RGB_LED(bool state, int r, int g, int b) {
  //Hardwired to be GRB.
  if (state) {
    leds[0] = CRGB(g, r, b);
    FastLED.show();
  } else {
    leds[0] = CRGB( 0, 0, 0);
    FastLED.show();
  }
}