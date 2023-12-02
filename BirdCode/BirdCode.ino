#import <Adafruit_NeoPixel.h>


#define NUM_PIXELS 7
#define PIXEL_PIN 9

Adafruit_NeoPixel pixels(NUM_PIXELS, PIXEL_PIN, NEO_GRBW + NEO_KHZ800);

void program1() {
  // Add your program here
  Serial.println("Program 1");
}

void program2() {
  // Add your program here
  Serial.println("Program 2");
}

void program3() {
  // Add your program here
  Serial.println("Program 3");
}

volatile int cycleCount = 1;
void cycle() {
  Serial.println("Interrupt");
    cycleCount++;
    if (cycleCount > 3) {
      cycleCount = 1;
    }
}

void setup() {
  // Add your setup code here
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), cycle, RISING);
}

void loop() {
  // Add your main code here
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
  }

}
