/*
  Example for MCP3008 - Library for communicating with MCP3008 Analog to digital converter.
  Created by Uros Petrevski, Nodesign.net 2013
  Released into the public domain.

  Edited by robotto (moore@cs.au.dk) in 2017 for the labtools;LabLib
*/

#include <MCP3008.h>


// define pin connections
#define CS_PIN 13
#define CLOCK_PIN 10
#define MOSI_PIN 12
#define MISO_PIN 11

// put pins inside MCP3008 constructor
MCP3008 adc(CLOCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);

void setup() {
 
 // open serial port
 Serial.begin(9600);
  
}


void loop() {
  
  
  int val = adc.readADC(0); // read Chanel 0 from MCP3008 ADC
  Serial.println(val);
  
  
  // iterate thru all channels
  /*
  for (int i=0; i<8; i++) {
   int val = adc.readADC(i);
   Serial.print(val);
   Serial.print("\t");
   }
   Serial.println("");
  */
  
}
