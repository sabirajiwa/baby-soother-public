# 1 "/Users/alexsem/Documents/Coursework/BABY-SILENCER/BirdCode/BirdCode.ino"
# 2 "/Users/alexsem/Documents/Coursework/BABY-SILENCER/BirdCode/BirdCode.ino" 2





Adafruit_NeoPixel pixels(7, 9, ((3 << 6) | (1 << 4) | (0 << 2) | (2)) /*|< Transmit as G,R,B,W*/ + 0x0000 /*|< 800 KHz data transmission*/);

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
  attachInterrupt(((2) == 2 ? 0 : ((2) == 3 ? 1 : -1)), cycle, 3);
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
