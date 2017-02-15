#include <MedianFilter.h>

int fsrPin = A5; // FSR is connected to analog pin 5 (A5)
int ledPin = 13; // we use the internal LED (pin 13) on the arduino uno
int threshold = 750; // threshold value to react to, input range is between 0 and 1023

// in this version we use a median filter as described in LabLib filtering: https://github.com/LabToolsAU/LabLib/tree/master/filtering
MedianFilter mf(5, 0); // we use a median of 5 values, each starting at 0

void setup() {
  // begin serial
  Serial.begin(9600);
  // LED pinMode
  pinMode(ledPin, OUTPUT);

  // setup the filter
  for(int i=0; i<5; i++) mf.in(analogRead(fsrPin));
}

void loop() {
  // put a reading from the fsrPin into the filter
  mf.in(analogRead(fsrPin));
  // we then read our mediated value from the filter
  int fsrSignal = mf.out();
  // rest of the sketch is the same as the basic example
  
  // print it out
  Serial.print("FSR Signal: ");
  Serial.println(fsrSignal);

  // react to it :)
  if(fsrSignal > threshold){
    // if signal is higher than threshold 
    digitalWrite(ledPin, HIGH); // turn on LED
    Serial.println("The Pressure!!!");
  } else {
    digitalWrite(ledPin, LOW); // turn LED off!
  }
  
  delay(200); // 200ms delay
}
