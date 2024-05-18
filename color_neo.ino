#include <FastLED.h>

#define LED_PIN D1
#define NUM_LEDS 10 // Number of LED pixels

CRGB leds[NUM_LEDS];

int currentColor = -1;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.show();
}

void loop() {
  // Check if there is available serial data
  if (Serial.available() > 0) {
    String emotionInput = Serial.readStringUntil('\n');
    // Set color based on the received emotion
    setColorFromSerialInput(emotionInput);
  }

  // Display the current color
  displayColor();

  delay(100); // Small delay to avoid flooding the serial buffer
}

void displayColor() {
  // Check if there is a valid color
  if (currentColor >= 0) {
    // Set the corresponding color based on the current emotion
    switch (currentColor) {
      case 0:
        setColor(0, 0, 255); // Blue
        break;
      case 1:
        setColor(0, 255, 0); // Green
        break;
      case 2:
        setColor(255, 0, 0); // Red
        break;
      case 3:
        setColor(255, 255, 0); // Yellow
        break;
      case 4:
        setColor(0, 255, 255); // Cyan
        break;
      case 5:
        setColor(255, 0, 255); // Magenta
        break;
      case 6:
        setColor(255, 255, 255); // White
        break;
      default:
        setColor(0, 0, 0); // Off
        break;
    }
  }
}

void setColor(uint8_t red, uint8_t green, uint8_t blue) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(red, green, blue);
  }
  FastLED.show();
}

void setColorFromSerialInput(String emotionInput) {
  emotionInput.trim(); // Remove leading/trailing whitespaces

  // Set color based on the received emotion
  if (emotionInput == "angry") {
    currentColor = 2; // Red
  } else if (emotionInput == "disgust") {
    currentColor = 4; // Green
  } else if (emotionInput == "fear") {
    currentColor = 0; // Blue
  } else if (emotionInput == "happy") {
    currentColor = 3; // Yellow
  } else if (emotionInput == "sad") {
    currentColor = 1; // Cyan
  } else if (emotionInput == "surprise") {
    currentColor = 5; // Magenta
  } else if (emotionInput == "neutral") {
    currentColor = 6; // White
  } else if (emotionInput == "blank") {
    currentColor = -1; // Off
  }
}
