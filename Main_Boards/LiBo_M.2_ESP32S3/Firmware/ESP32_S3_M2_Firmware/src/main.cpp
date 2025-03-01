#include <Arduino.h>
#include <LED.h>

/*To do:
  - Add the SPI flash memory. DONE
  - Add the RGB LED. DONE
  - Check the USB connection.
  - Add some DSP functions in Espressif IoT Development Framework.
  - Add a WiFi connection. 
  - Add a Bluetooth connection.

*/

void setup() {
  // put your setup code here, to run once:
  
  //Init LED
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:
  RGB_LED(true, 255, 0, 0);
  delay(1000);
  RGB_LED(false, 0, 0, 0);
  delay(1000);
}

// ESP32S3 PINS	ESP32S3 PIN_FUNCT	USED_PINS	M.2_USED_PINS	EXTRA_INFORMATION
// 1	LNA_IN	-	-	-
// 2	VDD3P3	-	-	-
// 3	VDD3P3	-	-	-
// 4	CHIP_PU	CHIP_PU	73	-
// 5	GPIO0	CHIP_BOOT	71	-
// 6	GPIO1	GPIO1	67	-
// 7	GPIO2	GPIO2	65	-
// 8	GPIO3	GPIO3	61	-
// 9	GPIO4	GPIO4	59	-
// 10	GPIO5	GPIO5	55	-
// 11	GPIO6	GPIO6	53	-
// 12	GPIO7	GPIO7	49	-
// 13	GPIO8	GPIO8	47	-
// 14	GPIO9	GPIO9	43	-
// 15	GPIO10	GPIO10	41	-
// 16	GPIO11	GPIO11	37	-
// 17	GPIO12	GPIO12	35	-
// 18	GPIO13	GPIO13	31	-
// 19	GPIO14	GPIO14	29	-
// 20	VDD3P3_RTC	-	-	-
// 21	XTAL_32K_P	-	-	-
// 22	XTAL_32K_N	-	-	-
// 23	GPIO17	GPIO17	24	-
// 24	GPIO18	GPIO18	22	-
// 25	GPIO19/USB_D-	USB_D-	25	Solder_Pad
// 26	GPIO20/USB_D+	USB_D+	23	Solder_Pad
// 27	GPIO21	GPIO21	10	-
// 28	SPICS1	SPICS1	8	-
// 29	VDD_SPI	-	-	-
// 30	SPIHD	-	-	-
// 31	SPIWP	-	-	-
// 32	SPICS0	-	-	-
// 33	SPICLK	-	-	-
// 34	SPIQ	-	-	-
// 35	SPID	-	-	-
// 36	SPICLK_N	SPICLK_N	28	-
// 37	SPICLK_P	SPICLK_P	30	-
// 38	GPIO33	GPIO33	34	-
// 39	GPIO34	GPIO34	36	-
// 40	GPIO35	GPIO35	40	-
// 41	GPIO36	GPIO36	42	-
// 42	GPIO37	GPIO37	46	-
// 43	GPIO38	GPIO38	48	-
// 44	MTCK	MTCK	53	-
// 45	MTDO	MTDO	54	-
// 46	VDD3P3_CPU	-	-	-
// 47	MTDI	MTDI	58	-
// 48	MTMS	MTMS	60	-
// 49	U0TXD	U0TXD	64	-
// 50	U0RXD	U0RXD	66	-
// 51	GPIO45	GPIO45	70	Pull_Up_Res/Strapping Pins
// 52	GPIO46	GPIO46	72	RGB_LED
// 53	XTAL_N	-	-	-
// 54	XTAL_P	-	-	-
// 55	VDDA	-	-	-
// 56	VDDA	-	-	-
// 57	GND	-	-	-
