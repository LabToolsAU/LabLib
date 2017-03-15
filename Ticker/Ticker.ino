/*
  Basic Ticker usage
  
  Ticker is an object that will call a given function with a certain period.
  Each Ticker calls one function. You can have as many Tickers as you like,
  memory being the only limitation.
  
  A function may be attached to a ticker and detached from the ticker.
  There are two variants of the attach function: attach and attach_ms.
  The first one takes period in seconds, the second one in milliseconds.
  
*/

#include <Ticker.h>

Ticker blinker;
Ticker fader;

static int blinkPin = 12;
static int fadePin = 13;


void blink(){
  int state = digitalRead(blinkPin);  // get the current state of the blink pin
  digitalWrite(blinkPin, !state);     // set pin to the opposite state
}

void fade(){
//variables for fading (static means they retain their values between runs)
static unsigned int fadeVal;
static bool fadeDir; //true=rising, false=falling

//change directions at endpoints
if(fadeVal==0) fadeDir=true;
else if (fadeVal==255) fadeDir=false;

analogWrite(fadePin, fadeVal); 

if(fadeDir) fadeVal++;
else fadeVal--;

}

void setup(){

  //set outputs
  pinMode(blinkPin, OUTPUT);
  pinMode(fadePin, OUTPUT);
  //set initial values:
  digitalWrite(blinkPin, LOW);
  digitalWrite(fadePin, LOW);
  
  // toggle the blinkPin every 0.5s
  blinker.attach(0.5, blink);

  // change the brightness of the LED attached to the fadePin every 20mS (50 times pr second)
  fader.attach_ms(20, fade);

}

void loop() {

//OH LOOK! AN EMPTY LOOP! BUT THE ARDUINO IS DOING THINGS! :D

}