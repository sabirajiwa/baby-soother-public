//-----------------------------------------Libraries-----------------------------------------
#include <Adafruit_NeoPixel.h>    //Includes the Neopixel library
//#include <Servo.h>    //Includes the Servo library


//-----------------------------------------Constants-----------------------------------------
const int PIN = 8;     //Pin the Neopixel is connected to
const int NUM_LEDS = 28;    //Number of LED's (4 per Neopixel)
const int LDRPin = A2;   //Pin the LDR potential divider is conected to


//-----------------------------------------Variables-----------------------------------------
int c = 0;    //Integer that iterates the colours of the Neopixels
int Voltage;    //Voltage reading taken from the potential divider
//int song_pin1 = 3;
//int song_pin2 = 4;
//int song_pin3 = 5;


//----------------------------------Initializing Components----------------------------------
//Servo Wing_servo;   //Intitializes the servo that moves the wings
//Servo Beak_sevro;   //Intitializes the servo that moves the beak

Adafruit_NeoPixel pixel = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);


//----------------------------------------RGBW values----------------------------------------
//Initializes the RGBW values of the colours to 32-bit unsigned integers
const uint32_t RED = pixel.Color(50, 0, 0, 0);
const uint32_t GREEN = pixel.Color(0, 50, 0, 0);
const uint32_t BLUE = pixel.Color(0, 0, 50, 0);
const uint32_t CYAN = pixel.Color(0, 50, 50, 0);
const uint32_t PURPLE = pixel.Color(50, 0, 50, 0);
const uint32_t YELLOW = pixel.Color(50, 50, 0, 0);
const uint32_t WHITE = pixel.Color(50, 50, 50, 0);
const uint32_t OFF = pixel.Color(0, 0, 0, 0);



//---------------------------------------Setup function---------------------------------------
void setup(){
  pixel.setBrightness(40);    //Sets brightness as 40 out of 255
  pixel.begin();
  Serial.begin(9600);

//  Wing_servo.attach(9);   //Pin the servo that moves the wings is conected to
//  Beak_sevro.attach(10);    //Pin the servo that moves the beak is conected to

  attachInterrupt(digitalPinToInterrupt(2), cycle, FALLING);

//  pinMode(song_pin1, OUTPUT);   //Initializes the first melody generator
//  pinMode(song_pin2, OUTPUT);   //Initializes the second melody generator
//  pinMode(song_pin3, OUTPUT);   //Initializes the third melody generator
}


//------------------------------Functions to control the servos-------------------------------
// void Flap_Wings(){    
//   //Slowly rotates the wing servo from 5 dgrees to 85 degrees
//   Serial.println("Flapping Wings");
//   for (int Wing_angle = 5; Wing_angle < 85; Wing_angle += 5){
//     Wing_servo.write(Wing_angle);
//     delay(50);
//   }
//   //Slowly rotates the wing servo from 85 dgrees to 5 degrees
//   for (int Wing_angle = 85; Wing_angle > 5; Wing_angle -= 5){
//     Wing_servo.write(Wing_angle);
//     delay(50);
//   }
// }

// void Open_Beak(){
//   //Slowly rotates the beak servo from 0 dgrees to 10 degrees
//   for (int Beak_angle = 0; Beak_angle < 10; Beak_angle += 1){
//   Wing_servo.write(Beak_angle);
//   delay(50);
//   }
// }

// void Close_Beak(){
//   //Slowly rotates the beak servo from 10 dgrees to 0 degrees
//   for (int Beak_angle = 10; Beak_angle > 10; Beak_angle -= 1){
//   Wing_servo.write(Beak_angle);
//   delay(50);
//   }
// }


//-----------------------------Functions to control the Neopixels-----------------------------
void Colour_Red(){   //Sets all but the middle pixel to red
  Serial.println("Case Colour red");
  for(int i = 1; i < 7; i++){
    pixel.setPixelColor(i, RED);
    pixel.show();
    delay(25);
  }
}

void Colour_Green(){   //Sets all but the middle pixel to green
  Serial.println("Case Colour green");
  for(int i = 1; i < 7; i++){
    pixel.setPixelColor(i, GREEN);
    pixel.show();
    delay(25);
  }
}

void Colour_Blue(){   //Sets all but the middle pixel to blue
  Serial.println("Case Colour blue");
  for(int i = 1; i < 7; i++){
    pixel.setPixelColor(i, BLUE);
    pixel.show();
    delay(25);
  }
}

void Colour_Rainbow(){    //Sets all but the middle pixel to rotating rainbow colours
  Serial.println("Case Rainbow");
  uint32_t colours [6] = {PURPLE, BLUE, CYAN, GREEN, YELLOW, RED};
  for(int i = 1; i < 8; i++){
    pixel.setPixelColor(i, colours[c]);
    pixel.show();
    delay(50);
    c++;
    if(c == 6){   //Resets the colour back to the start of the array
      c = 0;
    }
  }
}

void Colour_Christmas(){    //Sets all but the middle pixel to rotating rainbow colours
  Serial.println("Case Christmas");
  uint32_t colours [6] = {RED, GREEN, RED, GREEN, RED, GREEN};
  for(int i = 1; i < 8; i++){
    pixel.setPixelColor(i, colours[c]);
    pixel.show();
    delay(50);
    c++;
    if(c == 6){   //Resets the colour back to the start of the array
      c = 0;
    }
  }
}

void Colour_Off(){    //Turns off all pixels
  Serial.println("Case off");
  for(int i = 1; i < 7; i++){
    pixel.setPixelColor(i, OFF);
    pixel.show();
  }
}


//-------------------------Functions to control the melody generators-------------------------
// void song1(){
//   Serial.println("Song 1");
//   digitalWrite( song_pin1, HIGH);
//   digitalWrite( song_pin2, LOW);
//   digitalWrite( song_pin3, LOW);
// }

// void song2(){
//   Serial.println("Song 2");
//   digitalWrite( song_pin1, LOW);
//   digitalWrite( song_pin2, HIGH);
//   digitalWrite( song_pin3, LOW);
// }

// void song3(){
//   Serial.println("Song 3");
//   digitalWrite( song_pin1, LOW);
//   digitalWrite( song_pin2, LOW);
//   digitalWrite( song_pin3, HIGH);
// }


//---------------------------------Function to control Button---------------------------------
volatile int cycleCount = 1;    //CycleCount represents which mode is running
void cycle(){
  noInterrupts();   //Allows button to be pressed and change mode even if code is currently running a delay
  Colour_Off();   //Turns off piexels between sequences
  cycleCount++;   //Changes between modes
  if (cycleCount > 5){
    cycleCount = 1;   //If pressed in mode 3 the device will reset back to mode 1
  }
}



void loop(){
  Voltage = analogRead(LDRPin);   //Reads the voltage across the potential divider
  int LightLevel = map(Voltage, 0, 1023, 0, 10);    //Maps the voltage to a variable lightlevel
  if (LightLevel < 2){   //When lightlevel = 0 the room is dark and the device is turned on
    Serial.println(cycleCount);
    switch (cycleCount){
    case 1:
      Colour_Red();   //Runs the red light sequence
//      Open_Beak();    //Opens the birds mouth
//      song1();    //Plays the first melody
//      Close_Beak();   //Closes the beak
//      Flap_Wings();   //Slowly flaps the wings up and down once
      break;

    case 2:
      Colour_Green();   //Runs the green light sequence
      // Open_Beak();    //Opens the birds mouth
      // song1();    //Plays the first melody
      // Close_Beak();   //Closes the beak
      // Flap_Wings();   //Slowly flaps the wings up and down once
      break;

    case 3:
      Colour_Blue();   //Runs the blue light sequence
      // Open_Beak();    //Opens the birds mouth
      // song1();    //Plays the first melody
      // Close_Beak();   //Closes the beak
      // Flap_Wings();   //Slowly flaps the wings up and down once
      break;

    case 4:
      Colour_Rainbow();    //Runs the rainbow light sequence
      // Open_Beak();    //Opens the birds mouth
      // song2();    //Plays the second melody
      // Close_Beak();   //Closes the beak
      // Flap_Wings();   //Slowly flaps the wings up and down once
      break;

    case 5:
      Colour_Christmas();   //Runs the christmas light sequence
      // Open_Beak();    //Opens the birds mouth
      // song2();    //Plays the third melody
      // Close_Beak();   //Closes the beak
      // Flap_Wings();   //Slowly flaps the wings up and down once
      break;

    }
  }
  else{
    Colour_Off();   //When lightlevel = 1 the room is light and the device is turned off
  }
}