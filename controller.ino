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
uint8_t hue;

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

    // 
    switch (led_mode) {
        case LED_MODE_DIAMOND_FADING:
            CRGB starting_color = LED_COLOR_DIAMOND;
            uint8_t color_steps = (starting_color - LED_COLOR_DARKER_DIAMOND) / 150;

            EVERY_N_MILLISECONDS (150) {
                for (int i = 0; i < LED_COUNT; i++) {
                    fade_to_color(leds[i], starting_color, 5);
                }
            }

            FastLED.show();
            break;
        case LED_MODE_DIAMOND_STILL:
            // set the appropriate value for all LEDs and update
            fill_solid(leds, LED_COUNT, LED_COLOR_DIAMOND);
            FastLED.show();
            break;
        case LED_MODE_EMERALD_FADING:
            break;
        case LED_MODE_EMERALD_STILL:
            // set the appropriate value for all LEDs and update
            fill_solid(leds, LED_COUNT, LED_COLOR_EMERALD);
            FastLED.show();
            break;
        case LED_MODE_LAPIS_LAZULI_FADING:
            break;
        case LED_MODE_LAPIS_LAZULI_STILL:
            // set the appropriate value for all LEDs and update
            fill_solid(leds, LED_COUNT, LED_COLOR_LAPIS_LAZULI);
            FastLED.show();
            break;
        case LED_MODE_REDSTONE_FADING:
            break;
        case LED_MODE_REDSTONE_STILL:
            // set the appropriate value for all LEDs and update
            fill_solid(leds, LED_COUNT, LED_COLOR_REDSTONE);
            FastLED.show();
            break;
        case LED_MODE_RGB:
            // set the appropriate value for all LEDs
            fill_solid(leds, LED_COUNT, CHSV(hue, 255, 255));

            // increase the hue value every 150 milliseconds 
            EVERY_N_MILLISECONDS(150) {
                hue++;
            }

            // update
            FastLED.show();
            break;
    }
}

// initialization
void setup() {
    // initialize the LED strip
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_COUNT);

    // set the initial brigthness level
    FastLED.setBrightness(50);

    // set the initial hue value
    hue = 0;

    // set the initial LED mode
    led_mode = 0;

    // initialize LED mode button (input)
    pinMode(BUTTON_PIN, INPUT);
}
