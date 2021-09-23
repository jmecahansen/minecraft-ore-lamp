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
#define LED_COLOR_DARKER_DIAMOND 0x94EBFF
#define LED_COLOR_DARKER_EMERALD 0x3A9157
#define LED_COLOR_DARKER_LAPIS_LAZULI 0x1D5085
#define LED_COLOR_DARKER_REDSTONE 0xD95757
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
int led_mode;

// initialization
void setup(void) {
    // wait for 3 seconds
    delay(3000);

    // initialize the LED strip
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_COUNT);

    // set the initial LED mode
    led_mode = 0;

    // initialize LED mode button (input)
    pinMode(BUTTON_PIN, INPUT);
}

// main loop
void loop(void) {
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

    // 
    switch (led_mode) {
        case LED_MODE_DIAMOND_FADING:
            fill_gradient_RGB(leds, 0, LED_COLOR_DIAMOND, LED_COUNT - 1, LED_COLOR_DARKER_DIAMOND, LONGEST_HUES);
            FastLED.show();
            delay(1000);
            fill_gradient_RGB(leds, 0, LED_COLOR_DARKER_DIAMOND, LED_COUNT - 1, LED_COLOR_DIAMOND, LONGEST_HUES);
            FastLED.show();
            delay(1000);
            break;
        case LED_MODE_DIAMOND_STILL:
            // set all LEDs to the appropriate color
            for (int i = 0; i < LED_COUNT; i++) {
                leds[i] = LED_COLOR_DIAMOND;
            }

            FastLED.show();
            break;
        case LED_MODE_EMERALD_FADING:
            break;
        case LED_MODE_EMERALD_STILL:
            // set all LEDs to the appropriate color
            for (int i = 0; i < LED_COUNT; i++) {
                leds[i] = LED_COLOR_EMERALD;
            }

            FastLED.show();
            break;
        case LED_MODE_LAPIS_LAZULI_FADING:
            break;
        case LED_MODE_LAPIS_LAZULI_STILL:
            // set all LEDs to the appropriate color
            for (int i = 0; i < LED_COUNT; i++) {
                leds[i] = LED_COLOR_LAPIS_LAZULI;
            }

            FastLED.show();
            break;
        case LED_MODE_REDSTONE_FADING:
            break;
        case LED_MODE_REDSTONE_STILL:
            // set all LEDs to the appropriate color
            for (int i = 0; i < LED_COUNT; i++) {
                leds[i] = LED_COLOR_REDSTONE;
            }

            FastLED.show();
            break;
        case LED_MODE_RGB:
            for (int j = 0; j < 3; j++) {
                memset(leds, 0, LED_COUNT * 3);

                for (int k = 0; k < 256; k++) {
                    for (int i = 0; i < LED_COUNT; i++) {
                        switch (j) {
                            case 0:
                                leds[i].r = k;
                                break;
                            case 1:
                                leds[i].g = k;
                                break;
                            case 2:
                                leds[i].b = k;
                                break;
                        }
                    }

                    FastLED.show();
                    delay(3);
                }

                for (int k = 255; k >= 0; k--) {
                    for (int i = 0; i < LED_COUNT; i++) {
                        switch (j) {
                            case 0:
                                leds[i].r = k;
                                break;
                            case 1:
                                leds[i].g = k;
                                break;
                            case 2:
                                leds[i].b = k;
                                break;
                        }
                    }

                    FastLED.show();
                    delay(3);
                }
            }

            break;
    }
}
