#import <Adafruit_NeoPixel.h>

#define NUM_PIXELS 7
#define PIXEL_PIN 9

Adafruit_NeoPixel pixels(NUM_PIXELS, PIXEL_PIN, NEO_GRBW + NEO_KHZ800);

void program1() {
  Serial.println("Program 1");
}

void program2() {
  Serial.println("Program 2");
}

void program3() {
  Serial.println("Program 3");
}

int cycleCount = 1;
void cycle() {
    cycleCount++;
    if (cycleCount > 3)
      cycleCount = 1;
}

void setup() {
  Serial.begin(9600);
  // attachInterrupt(digitalPinToInterrupt(2), cycle, FALLING);
}

unsigned long lastMillis = 0;

void loop() {
  lastMillis = millis();
  if (millis() >= lastMillis + 1000) {
      switch (cycleCount) {
      case 1:
        program1();
        break;
      case 2:
        program2();
        break;
      case 3:
        program3();
        break;
    }}
}
