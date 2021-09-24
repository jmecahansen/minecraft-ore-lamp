/*
 * Project: Minecraft Ore Lamp
 * Description: Minecraft-based ore lamp with LED (WS2812B) lighting controlled with an Arduino Nano board
 * Creation date: 2021-09-23
 * Author: Julio María Meca Hansen <jmecahansen@gmail.com>
 * License: MIT
 */

// includes
#include <FastLED.h>

// constant definitions
#define BUTTON_PIN 7
#define COLOR_ORDER RGB
#define FLOW_BACKWARD 1
#define FLOW_FORWARD 0
#define LED_BRIGHTNESS_MAXIMUM 200
#define LED_BRIGHTNESS_MINIMUM 100
#define LED_COLOR_DIAMOND 0xB9F2FF
#define LED_COLOR_EMERALD 0x50C878
#define LED_COLOR_LAPIS_LAZULI 0x2B6199
#define LED_COLOR_REDSTONE 0xE46B71
#define LED_COUNT 60
#define LED_MODE_DIAMOND_FADING 1
#define LED_MODE_DIAMOND_STILL 0
#define LED_MODE_EMERALD_FADING 3
#define LED_MODE_EMERALD_STILL 2
#define LED_MODE_LAPIS_LAZULI_FADING 5
#define LED_MODE_LAPIS_LAZULI_STILL 4
#define LED_MODE_REDSTONE_FADING 7
#define LED_MODE_REDSTONE_STILL 6
#define LED_MODE_RGB 8
#define LED_PIN 6
#define LED_TYPE WS2812B

// variable definitions
CRGB leds[LED_COUNT];
int button_state;
uint8_t brightness;
uint8_t flow;
uint8_t hue;
uint8_t led_mode;

// main loop
void loop() {
    // check the button status
    button_state = digitalRead(BUTTON_PIN);

    if (button_state == HIGH) {
        // if pressed, switch to a different mode
        led_mode++;

        // if pressed on the last LED mode (LED_MODE_RGB), set it back to the first mode (LED_MODE_DIAMOND_STILL)
        if (led_mode > LED_MODE_RGB) {
            led_mode = LED_MODE_DIAMOND_STILL;
        }
    }

    // evaluate the button state
    switch (led_mode) {
        case LED_MODE_DIAMOND_FADING:
            // set the color for all LEDs
            fill_solid(leds, LED_COUNT, LED_COLOR_DIAMOND);

            // fade the brightness level
            EVERY_N_MILLISECONDS (150) {
                if (flow == FLOW_BACKWARD) {
                    brightness--;

                    if (brightness == LED_BRIGHTNESS_MINIMUM) {
                        flow = FLOW_FORWARD;
                    }
                } else if (flow == FLOW_FORWARD) {
                    brightness++;

                    if (brightness == LED_BRIGHTNESS_MAXIMUM) {
                        flow = FLOW_BACKWARD;
                    }
                }
            }

            // set the brightness level
            FastLED.setBrightness(LED_BRIGHTNESS_MAXIMUM);

            // exit the switch() block
            break;
        case LED_MODE_DIAMOND_STILL:
            // set the color for all LEDs
            fill_solid(leds, LED_COUNT, LED_COLOR_DIAMOND);

            // set the brightness level
            FastLED.setBrightness(LED_BRIGHTNESS_MAXIMUM);

            // exit the switch() block
            break;
        case LED_MODE_EMERALD_FADING:
            // set the color for all LEDs
            fill_solid(leds, LED_COUNT, LED_COLOR_EMERALD);

            // fade the brightness level
            EVERY_N_MILLISECONDS (150) {
                if (flow == FLOW_BACKWARD) {
                    brightness--;

                    if (brightness == LED_BRIGHTNESS_MINIMUM) {
                        flow = FLOW_FORWARD;
                    }
                } else if (flow == FLOW_FORWARD) {
                    brightness++;

                    if (brightness == LED_BRIGHTNESS_MAXIMUM) {
                        flow = FLOW_BACKWARD;
                    }
                }
            }

            // set the brightness level
            FastLED.setBrightness(LED_BRIGHTNESS_MAXIMUM);

            // exit the switch() block
            break;
        case LED_MODE_EMERALD_STILL:
            // set the color for all LEDs
            fill_solid(leds, LED_COUNT, LED_COLOR_EMERALD);

            // set the brightness level
            FastLED.setBrightness(LED_BRIGHTNESS_MAXIMUM);

            // exit the switch() block
            break;
        case LED_MODE_LAPIS_LAZULI_FADING:
            // set the color for all LEDs
            fill_solid(leds, LED_COUNT, LED_COLOR_LAPIS_LAZULI);

            // fade the brightness level
            EVERY_N_MILLISECONDS (150) {
                if (flow == FLOW_BACKWARD) {
                    brightness--;

                    if (brightness == LED_BRIGHTNESS_MINIMUM) {
                        flow = FLOW_FORWARD;
                    }
                } else if (flow == FLOW_FORWARD) {
                    brightness++;

                    if (brightness == LED_BRIGHTNESS_MAXIMUM) {
                        flow = FLOW_BACKWARD;
                    }
                }
            }

            // set the brightness level
            FastLED.setBrightness(LED_BRIGHTNESS_MAXIMUM);

            // exit the switch() block
            break;
        case LED_MODE_LAPIS_LAZULI_STILL:
            // set the color for all LEDs
            fill_solid(leds, LED_COUNT, LED_COLOR_LAPIS_LAZULI);

            // set the brightness level
            FastLED.setBrightness(LED_BRIGHTNESS_MAXIMUM);

            // exit the switch() block
            break;
        case LED_MODE_REDSTONE_FADING:
            // set the color for all LEDs
            fill_solid(leds, LED_COUNT, LED_COLOR_REDSTONE);

            // fade the brightness level
            EVERY_N_MILLISECONDS (150) {
                if (flow == FLOW_BACKWARD) {
                    brightness--;

                    if (brightness == LED_BRIGHTNESS_MINIMUM) {
                        flow = FLOW_FORWARD;
                    }
                } else if (flow == FLOW_FORWARD) {
                    brightness++;

                    if (brightness == LED_BRIGHTNESS_MAXIMUM) {
                        flow = FLOW_BACKWARD;
                    }
                }
            }

            // set the brightness level
            FastLED.setBrightness(LED_BRIGHTNESS_MAXIMUM);

            // exit the switch() block
            break;
        case LED_MODE_REDSTONE_STILL:
            // set the color for all LEDs
            fill_solid(leds, LED_COUNT, LED_COLOR_REDSTONE);

            // set the brightness level
            FastLED.setBrightness(LED_BRIGHTNESS_MAXIMUM);

            // exit the switch() block
            break;
        case LED_MODE_RGB:
            // set the color for all LEDs
            fill_solid(leds, LED_COUNT, CHSV(hue, 255, 255));

            // set the brightness level
            FastLED.setBrightness(LED_BRIGHTNESS_MAXIMUM);

            // increase the hue level every 150 milliseconds 
            EVERY_N_MILLISECONDS(150) {
                hue++;
            }

            // exit the switch() block
            break;
    }

    // update
    FastLED.show();
}

// initialization
void setup() {
    // initialize the LED strip
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_COUNT);

    // set the initial brightness level
    brightness = LED_BRIGHTNESS_MAXIMUM;

    // set the initial button state
    button_state = LOW;

    // set the initial flow value
    flow = FLOW_FORWARD;

    // set the initial hue level
    hue = 0;

    // set the initial LED mode
    led_mode = 0;

    // initialize LED mode button (input)
    pinMode(BUTTON_PIN, INPUT);
}
