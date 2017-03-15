int flexPin = A5; // flex sensor is connected to Analog In 5
int flexThreshold = 175; // threshold for our trigger function
// threshold should be set after a baselevel has been established
int ledPin = 13; // LED pin to light up (13 is internal LED on the Arduino UNO)
void setup() {
  // Open the serial so we can write out our values
  Serial.begin(9600); 
  // setup the LED pin for output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int flexVal = analogRead(flexPin);
  // Remember that we can't combine primitive types in strings (e.g. java's str+str)
  // we need to use two print statements
  Serial.print("Flex Val: ");
  Serial.println(flexVal);

  if(flexVal < flexThreshold){
    Serial.println("FLEX BABY FLEX!");
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(500); // run loop every ½ second
} 
