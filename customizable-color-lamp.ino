#include <Adafruit_NeoPixel.h>

int DELAYVAL = 500; // Time (in milliseconds) to pause between pixels

int RED_PIN = 10;
int GREEN_PIN = 10;
int BLUE_PIN = 10;
int pinsByColors[] = {RED_PIN, BLUE_PIN, GREEN_PIN};

const int LED_NUMBERS = 3;

const int LED_PIN = 13;

// max value of the signal when the potentiometer is at max
const int MAX_VALUE = 640;

// Index for color settings
const int RED = 0;
const int BLUE = 1;
const int GREEN = 2;

int redLevel = 0;
int blueLevel = 0;
int greenLevel = 0;
int colorsLevels[] = {redLevel, blueLevel, greenLevel};

Adafruit_NeoPixel pixels(LED_NUMBERS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(LED_PIN, OUTPUT); // declare the LED_PIN as an OUTPUT
  pixels.begin();
}

void loop() {
  getLevelsFromPotentiometers();
  adjustLEDsColor();
}

void getLevelsFromPotentiometers() {
  for (int i = 0; i < 3; i++) {
    colorsLevels[i] = round(255 * analogRead(pinsByColors[i]) / MAX_VALUE);
  }
}

void adjustLEDsColor() {
  pixels.clear(); // Set all pixel colors to 'off'

  for (int i = 0; i < LED_NUMBERS; i++) {
    pixels.setPixelColor(i, pixels.Color(colorsLevels[RED], colorsLevels[BLUE],
                                         colorsLevels[GREEN]));
    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(DELAYVAL); // Pause before next pass through loop
  }
}