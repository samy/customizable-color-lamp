#include <Adafruit_NeoPixel.h>

int DELAYVAL = 500; // Time (in milliseconds) to pause between pixels

//PIN number for the potentiometer which manages the red color
int RED_PIN = 10;
//PIN number for the potentiometer which manages the green color
int GREEN_PIN = 11;
//PIN number for the potentiometer which manages the blue color
int BLUE_PIN = 12;
int pinsByColors[] = {RED_PIN, BLUE_PIN, GREEN_PIN};

const int COLOR_LEDS_COUNT = 3;
const int BRIGHTNESS_LEDS_COUNT = 1;

const int LED_PIN = 13;

// max value of the signal when the potentiometer is at max
const int MAX_VALUE = 640;

// min diff in potentiometers values to change output
const int PT_THRESHOLD = 2*MAX_VALUE/100;

// Index for color settings
const int RED = 0;
const int BLUE = 1;
const int GREEN = 2;

int redLevel = 0;
int blueLevel = 0;
int greenLevel = 0;
int colorsLevels[COLOR_LEDS_COUNT] = {redLevel, blueLevel, greenLevel};
int* previousColorsLevels;

int brightnessLevel = 0;
int brightnessLevels[BRIGHTNESS_LEDS_COUNT] = {brightnessLevel};
int* previousbrightnessLevels;

Adafruit_NeoPixel pixels(COLOR_LEDS_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(LED_PIN, OUTPUT); // declare the LED_PIN as an OUTPUT
  pixels.begin();
  pixels.clear(); // Set all pixel colors to 'off'

}

void getLevelsFromPotentiometers(int (& colorsLevels)[3]) {
  for (int i = 0; i < COLOR_LEDS_COUNT; i++) {
    colorsLevels[i] = round(255 * analogRead(pinsByColors[i]) / MAX_VALUE);
  }
}

void adjustLEDsColor() {
  for (int i = 0; i < COLOR_LEDS_COUNT; i++) {
    pixels.setPixelColor(i, pixels.Color(colorsLevels[RED], colorsLevels[GREEN], colorsLevels[BLUE]));
  }
  pixels.show();   // Send the updated pixel colors to the hardware.
}

void adjustLEDsBrightness() {
  pixels.setBrightness(brightnessLevels[0]);
  pixels.show();   // Send the updated pixel colors to the hardware.
}

int isPotentiometersDiffEnough(int previousValues[], int newValues[]) {
  for(int i = 0;i < sizeof(previousValues);i++) {
      if (abs(previousValues[i] - newValues[i]) >= PT_THRESHOLD) {
        return 1;
      }
  }
  return 0;
}

void loop() {
  previousColorsLevels = colorsLevels;
  getLevelsFromPotentiometers(colorsLevels);
  if (isPotentiometersDiffEnough(previousColorsLevels, colorsLevels)) {
    adjustLEDsColor();
  }
  if (isPotentiometersDiffEnough(previousbrightnessLevels, brightnessLevels)) {
    adjustLEDsBrightness();
  }
  delay(DELAYVAL); // Pause before next pass through loop
}
