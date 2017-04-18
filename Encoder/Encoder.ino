/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

//64 ticks pr revolution

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEncoder(3,2);
//   avoid using pins with LEDs attached

static int buttonPin = 4;
long oldPosition  = -999; //global variable to store encoder position
long newPosition = oldPosition;

bool speedOrPosition = false; //true=speed, false=position
bool sendZero=false;
float TIMEUNITS=100.0; //timebase for speed calculation - IF speed readout reaches infinity (inf) increase this.
float currentSpeed; //in ticks pr TIMEUNITS
long positionTimeStamp;


void setup() {


  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP); //Button is active low, so interna pull-up is usable. yay!
  Serial.println("Basic Encoder Test:");

  positionTimeStamp=millis();
}


void loop() {
  newPosition = myEncoder.read();

  if (newPosition != oldPosition) { //only react to change.
    currentSpeed=calculateSpeed();
    oldPosition = newPosition;
    
    if(!speedOrPosition) Serial.println(newPosition); //print position
    else {
        Serial.println(currentSpeed); //print speed
        sendZero=true;
      }
      
  }

  if(checkButton()) {
    speedOrPosition=!speedOrPosition; //flip the boolean
    delay(20); //debounce
  }

  if(speedOrPosition && millis()>positionTimeStamp+100 && sendZero){
    Serial.println(0);
    sendZero=false;
  }
  
}



bool checkButton()
{

  //TODO: remember to debounce on button press.

  bool buttonPresed=false;

  if(!digitalRead(buttonPin)) { //button is active low.
    buttonPresed=true;    
    Serial.println("button!");
    while(!digitalRead(buttonPin)); //wait for button release
    } 
    
    return buttonPresed;
}

float calculateSpeed() {

   float deltaTime = ((float)millis() - (float)positionTimeStamp)/TIMEUNITS;
   positionTimeStamp = millis();
   
   float deltaPosition =  (float)newPosition - (float)oldPosition;

   return deltaPosition/deltaTime;

}