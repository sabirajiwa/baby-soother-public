#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(2,3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int buttonNext = 2;
int buttonPause = 3;
int buttonPrevious = 4;

boolean isPlaying = false;

void setup() {
    pinMode(buttonPause, INPUT);
    digitalWrite(buttonPause, HIGH);
    pinMode(buttonNext, INPUT);
    digitalWrite(buttonNext, HIGH);
    pinMode(buttonPrevious, INPUT);
    digitalWrite(buttonPrevious, HIGH);

    mySoftwareSerial.begin(9600);
    Serial.begin(9600);

    delay(1000);

    Serial.println();
    Serial.println("DFPlayer Mini Demo");
    Serial.println("Initializing DFPlayer...");

    if (!myDFPlayer.begin(mySoftwareSerial)) {
        Serial.println("Unable to begin:");
        Serial.println("1.Please recheck the connection!");
        Serial.println("2.Please insert the SD card!");
        while (true);
    }
    Serial.println(F("DFPlayer Mini online."));

    myDFPlayer.setTimeOut(500);

    //----Set volume----
    myDFPlayer.volume(10); //Set volume value (0~30).
    //myDFPlayer.volumeUp(); //Volume Up
    //myDFPlayer.volumeDown(); //Volume Down

    //----Set different EQ----
    myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
    //  myDFPlayer.EQ(DFPLAYER_EQ_POP);
    //  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
    //  myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
    //  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
    //  myDFPlayer.EQ(DFPLAYER_EQ_BASS);

    myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

    myDFPlayer.play(1); //Play the first song
    isPlaying = true;
    Serial.println("Playing..");
}

void loop() {
    if (digitalRead(buttonPause) == LOW) {
        if (isPlaying) {
            myDFPlayer.pause();
            isPlaying = false;
            Serial.println("Paused..");
        } else {
            isPlaying = true;
            myDFPlayer.start();
            Serial.println("Playing..");
        }
        delay(500);
    }
    if (digitalRead(buttonNext) == LOW) {
        if (isPlaying) {
            myDFPlayer.next();
            Serial.println("Next Song..");
        }
        delay(500);
    }

    if (digitalRead(buttonPrevious) == LOW) {
        if (isPlaying) {
            myDFPlayer.previous();
            Serial.println("Previous Song..");
        }
        delay(500);
    }
}