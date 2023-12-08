#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define PIN_SERVO 9
#define PIN_NEOPIXEL 8

#define NUMPIXELS 16
#define BRIGHTNESS 10

// Constants for servo control
#define SERVOMIN  600  // This is the 'minimum' pulse length in microseconds
#define SERVOMAX  2400 // This is the 'maximum' pulse length in microseconds

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

int c = 0;

const uint32_t RED = pixels.Color(50, 0, 0, 0);
const uint32_t GREEN = pixels.Color(0, 50, 0, 0);
const uint32_t BLUE = pixels.Color(0, 0, 50, 0);
const uint32_t CYAN = pixels.Color(0, 50, 50, 0);
const uint32_t PURPLE = pixels.Color(50, 0, 50, 0);
const uint32_t YELLOW = pixels.Color(50, 50, 0, 0);
const uint32_t WHITE = pixels.Color(50, 50, 50, 0);
const uint32_t OFF = pixels.Color(0, 0, 0, 0);

void setup() {
  delay(1000); // Delay for 1 second
  Serial.begin(9600);
  pixels.begin();
  pinMode(PIN_SERVO, OUTPUT);
}

void loop() {
  int Voltage = analogRead(2);   //Reads the voltage across the potential divider
  int LightLevel = map(Voltage, 0, 1023, 0, 10);    //Maps the voltage to a variable lightlevel
  Serial.println(LightLevel);
  if (LightLevel < 2) {
    Serial.println("LightLevel < 2");
    Colour_Christmas();
  // sweepServo(0, 90, 5);
  setServoPosition(0);
  delay(1000);
  setServoPosition(90);
  delay(100);
  } else {
    Serial.println("LightLevel >= 2");
    pixels.clear();
    pixels.show();
    delay(100);
  }
}

void rainbowCycle(uint8_t wait) {
  for (int j = 0; j < 256 * 5; j++) {
    for (int i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

void Colour_Christmas(){    //Sets all but the middle pixel to rotating rainbow colours
  // Serial.println("Case Christmas");
  uint32_t colours [6] = {RED, GREEN, RED, GREEN, RED, GREEN};
  for(int i = 1; i < 8; i++){
    pixels.setPixelColor(i, colours[c]);
    pixels.show();
    delay(50);
    c++;
    if(c == 6){   //Resets the colour back to the start of the array
      c = 0;
    }
  }
}

void sweepServo(int startPos, int endPos, int step) {
  Serial.print("Sweeping from ");
  for (int pos = startPos; pos <= endPos; pos += step) {
    setServoPosition(pos);
    delay(15);
  }
  for (int pos = endPos; pos >= startPos; pos -= step) {
    setServoPosition(pos);
    delay(15);
  }
}

void setServoPosition(int pos) {
  int pulseWidth = map(pos, 0, 180, SERVOMIN, SERVOMAX);
  digitalWrite(PIN_SERVO, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(PIN_SERVO, LOW);
  delayMicroseconds(20000 - pulseWidth);  // 20ms - pulseWidth
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


