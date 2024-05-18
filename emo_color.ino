const int redPin = D2;
const int greenPin = D1;
const int bluePin = D0;

int currentColor = -1;
unsigned long lastColorChangeTime = 0;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Check if there is available serial data
  if (Serial.available() > 0) {
    String emotionInput = Serial.readStringUntil('\n');
    // Set color based on the received emotion
    setColorFromSerialInput(emotionInput);
    lastColorChangeTime = millis(); // Reset the last color change time
  }

  // Display the current color
  displayColor();

  // Check if it's time to change the color
  if (millis() - lastColorChangeTime >= 1000) {
    // Send a blank emotion to turn off the LED
    setColorFromSerialInput("blank");
  }

  delay(100); // Small delay to avoid flooding the serial buffer
}

void displayColor() {
  // Check if there is a valid color
  if (currentColor >= 0) {
    // Turn off all colors
    setColor(0, 0, 0);

    // Set the corresponding color based on the current emotion
    switch (currentColor) {
      case 0:
        setColor(255, 0, 0);    // Red
        break;
      case 1:
        setColor(255, 255, 255);  // White
        break;
      case 2:
        setColor(255, 255, 0);  // Yellow
        break;
      case 3:
        setColor(0, 0, 255);    // Blue
        break;
      case 4:
        setColor(128, 0, 128);  // Purple
        break;
      case 5:
        setColor(0, 255, 0);    // Green
        break;
      case 6:
        setColor(160, 80, 0);    // Orange
        break;
      default:
        setColor(0, 0, 0);    // Off
        break;
    }
  }
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void setColorFromSerialInput(String emotionInput) {
  emotionInput.trim(); // Remove leading/trailing whitespaces

  // Set color based on the received emotion
  if (emotionInput == "angry") {
    currentColor = 0;  // Red
  } else if (emotionInput == "disgust") {
    currentColor = 1;  // White
  } else if (emotionInput == "fear") {
    currentColor = 2;  // Yellow
  } else if (emotionInput == "happy") {
    currentColor = 3;  // Blue
  } else if (emotionInput == "sad") {
    currentColor = 4;  // Purple
  } else if (emotionInput == "surprise") {
    currentColor = 5;  // Green
  } else if (emotionInput == "neutral") {
    currentColor = 1;  // White
  } else {
    currentColor = -1;  // Off
  }
}
