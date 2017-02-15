 
/* SoundSensor sketch - taken from https://learn.sparkfun.com/tutorials/electret-mic-breakout-board-hookup-guide?_ga=1.169443297.1171021963.1487176620
  *  Gracefully lifted, re commented and edited for LabLib
   */
   
// define the sample window
const int sampleWindow = 250; // in ms - we sample at 4Hz or 4 times pr second (this will also delay the loop with the sampletime)
unsigned int knock; // to store the values we get from the electret/microphone
int ledPin = 13; // onboard arduino LED pin
int micPin = A5;

float voltageIn = 5.0; // the voltage we are supplying the component with (5.0 or 3.3)

void setup() 
{
   // open serial and setup the pinmode for the LED
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() 
{
 unsigned long start= millis();  // Start of sample window
 unsigned int peakToPeak = 0;   // peak-to-peak level

 unsigned int signalMax = 0;
 unsigned int signalMin = 1024;

 // collect data for 250 miliseconds
 while (millis() - start < sampleWindow)
 {
   // we read from ADC on analog 5 into the "knock" variable.
   knock = analogRead(micPin);
      if (knock < 1024) // if our reading is inside our range (max 10-bit ADC range is 1024, so its basically all readings)
      {
         if (knock > signalMax) // if the reading is higher than current max
         {
           signalMax = knock; // we save a new max value
         }
      else if (knock < signalMin) // if reading is less than current min.
        {
         signalMin = knock; // we save a new min value
         }
     }
 }
 peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
 double volts = (peakToPeak * voltageIn) / 1024;  // convert to volts 

// we then print the volts as converted above, and react to it by switching the LED on (or off)
Serial.println(volts);
 if (volts >=1.0)
 {
  //turn on LED
  digitalWrite(ledPin, HIGH);
   delay(500);
  Serial.println("Knock Knock");
 }
 else
 {
 //turn LED off
 digitalWrite(ledPin, LOW);
 }
}  
