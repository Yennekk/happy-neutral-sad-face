#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C address for the OLED (usually 0x3C or 0x3D)
#define OLED_ADDR 0x3C

// Create an OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Center of the face (adjusted downwards)
const int centerX = SCREEN_WIDTH / 2;
const int centerY = SCREEN_HEIGHT / 2 + 10; // Verschiebt das Gesicht nach unten

// Radius of the face
const int faceRadius = 20;

// Radius of the eyes
const int eyeRadius = 3;

// Timer for animation
unsigned long previousMillis = 0;
const unsigned long interval = 1000; // Change face every 1000ms (1 second)

// State for the face (0 - Happy, 1 - Neutral, 2 - Sad)
int faceState = 0;

void setup() {
  // Initialize Serial (optional for debugging)
  Serial.begin(115200);

  // Initialize OLED display
  if (!display.begin(SSD1306_PAGEADDR, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Clear and initialize the display
  display.clearDisplay();
  display.display();
}

void drawFace(int state) {
  // Draw face (circle)
  display.drawCircle(centerX, centerY, faceRadius, SSD1306_WHITE);

  // Draw eyes
  display.fillCircle(centerX - 7, centerY - 7, eyeRadius, SSD1306_WHITE); // Left eye
  display.fillCircle(centerX + 7, centerY - 7, eyeRadius, SSD1306_WHITE); // Right eye

  // Draw the mouth based on the state
  switch (state) {
    case 0:  // Happy
      // Draw smile (using lines to simulate an arc)
      display.drawLine(centerX - 10, centerY + 5, centerX - 5, centerY + 10, SSD1306_WHITE);
      display.drawLine(centerX - 5, centerY + 10, centerX + 5, centerY + 10, SSD1306_WHITE);
      display.drawLine(centerX + 5, centerY + 10, centerX + 10, centerY + 5, SSD1306_WHITE);
      break;
    case 1:  // Neutral
      // Draw neutral mouth (a straight line)
      display.drawLine(centerX - 10, centerY + 5, centerX + 10, centerY + 5, SSD1306_WHITE);
      break;
    case 2:  // Sad
      // Draw sad mouth (using lines to simulate an arc)
      display.drawLine(centerX - 10, centerY + 5, centerX - 5, centerY, SSD1306_WHITE);
      display.drawLine(centerX - 5, centerY, centerX + 5, centerY, SSD1306_WHITE);
      display.drawLine(centerX + 5, centerY, centerX + 10, centerY + 5, SSD1306_WHITE);
      break;
  }
}

void loop() {
  // Get current time
  unsigned long currentMillis = millis();

  // Change face every 1 second
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Clear the display
    display.clearDisplay();

    // Draw the face with the current state
    drawFace(faceState);

    // Update the face state for the next frame
    faceState = (faceState + 1) % 3; // Cycle through Happy (0), Neutral (1), and Sad (2)

    // Update the display
    display.display();
  }
}


