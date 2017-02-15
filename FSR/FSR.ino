int fsrPin = A5; // FSR is connected to analog pin 5 (A5)
int ledPin = 13; // we use the internal LED (pin 13) on the arduino uno
int threshold = 750; // threshold value to react to, input range is between 0 and 1023

void setup() {
  // begin serial
  Serial.begin(9600);
  // LED pinMode
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // read the fsr signal value
  int fsrSignal = analogRead(fsrPin);
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
