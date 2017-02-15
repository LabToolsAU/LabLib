
// input sketch for Piezo elements
int piezoPin = A5; // analog 5 in on the arduino

void setup() {
  // begin the serial
  Serial.begin(9600);
}

void loop() {
  // we read from the analog pin and print out the results
  int piezoIn = analogRead(piezoPin);
  Serial.print("Analog 5: ");
  Serial.println(piezoIn);

  // the piezoIn value could then be used to trigger something at a given threshold
  if(piezoIn > 50){
    Serial.println("Knock");
  }
  delay(100);
}
