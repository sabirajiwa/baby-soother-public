// the aim of the following code is to include a button which switches between melodies produced by the dove
// ZMEE022 - 23/11/2023

int Song1Pin = 3 ;
int Song2Pin = 4 ;
int Song3Pin = 5 ;
int ButtonPin = 11;
int ButtonCounter ;

void song1() 
{
  Serial.print("Song 1") ;
  digitalWrite( Song1Pin , HIGH ) ;
  digitalWrite( Song2Pin , LOW ) ;
  digitalWrite( Song3Pin , LOW ) ;

  //delay(5000) ;
  //digitalWrite( Song1Pin , LOW ) ;
}

void song2() 
{
  Serial.print("Song 2") ;
  digitalWrite( Song1Pin , LOW ) ;
  digitalWrite( Song2Pin ,HIGH ) ;
  digitalWrite( Song3Pin , LOW ) ;
}

void song3()
{
  Serial.print("Song 3") ;
  digitalWrite( Song1Pin , LOW ) ;
  digitalWrite( Song2Pin , LOW ) ;
  digitalWrite( Song2Pin , HIGH ) ;
}

void setup() 
{

  Serial.begin(9600);

  pinMode(Song1Pin, OUTPUT);
  pinMode(Song2Pin, OUTPUT);
  pinMode(Song3Pin, OUTPUT);
  pinMode(ButtonPin, INPUT);

}// end setup

void loop() 
{
  
  if( digitalRead(ButtonPin) == HIGH && ButtonCounter == 0 )
  {
    Serial.println("Button pressed once, song 1 selected") ;
    song1() ;
    ButtonCounter++ ;
  }
  else if( digitalRead(ButtonPin) == HIGH && ButtonCounter == 1 )
  {
    Serial.println("Button pressed twice, song 2 selected") ;
    song2() ;
    ButtonCounter++ ;
  }
  else if( digitalRead(ButtonPin) == HIGH && ButtonCounter == 2 )
  {
    Serial.println("Button pressed thrice, song 3 selected") ;
    song3() ;
    ButtonCounter++ ;
  }

  if(ButtonCounter == 3)
  { 
    ButtonCounter = 0 ;
  }

  Serial.println(ButtonCounter) ;
  delay(1000) ;

}// end loop