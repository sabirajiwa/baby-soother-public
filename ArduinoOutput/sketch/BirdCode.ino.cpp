#include <Arduino.h>
#line 1 "/Users/alexsem/Documents/Coursework/BABY-SILENCER/BirdCode/BirdCode.ino"
#import <Adafruit_NeoPixel.h>


#define NUM_PIXELS 7
#define PIXEL_PIN 9

Adafruit_NeoPixel pixels(NUM_PIXELS, PIXEL_PIN, NEO_GRBW + NEO_KHZ800);

#line 9 "/Users/alexsem/Documents/Coursework/BABY-SILENCER/BirdCode/BirdCode.ino"
void program1();
#line 14 "/Users/alexsem/Documents/Coursework/BABY-SILENCER/BirdCode/BirdCode.ino"
void program2();
#line 19 "/Users/alexsem/Documents/Coursework/BABY-SILENCER/BirdCode/BirdCode.ino"
void program3();
#line 25 "/Users/alexsem/Documents/Coursework/BABY-SILENCER/BirdCode/BirdCode.ino"
void cycle();
#line 33 "/Users/alexsem/Documents/Coursework/BABY-SILENCER/BirdCode/BirdCode.ino"
void setup();
#line 39 "/Users/alexsem/Documents/Coursework/BABY-SILENCER/BirdCode/BirdCode.ino"
void loop();
#line 9 "/Users/alexsem/Documents/Coursework/BABY-SILENCER/BirdCode/BirdCode.ino"
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

