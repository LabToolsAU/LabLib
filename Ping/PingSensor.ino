#include <NewPing.h> // NewPing lib. better than the original - especially in response time
// more info about the specific library: http://playground.arduino.cc/Code/NewPing

int trigPin = 12; // pin 12 to trigger
int echoPin = 11; // pin 11 to echo
int maxDistance = 400; // cm - which means 4 meters, the sensors are capable of up to about 400-500 cm


// Create a NewPing object with the above variables
NewPing sonar(trigPin, echoPin, maxDistance);

void setup() {
  // Open serial so we can write stuff out to the terminal
  Serial.begin(115200);
}

void loop() {
  delay(50);                      // wait about 50ms between each ping
  unsigned int ms = sonar.ping_median(); // we use ping_median() to get the median values - this is safer and more reliable :)
  // print to serial
  Serial.print("Ping: ");
  Serial.print(sonar.convert_cm(ms)); // we use the convert method to get cm from the ms measurement
  Serial.println("cm");               // you could also use convert_in for inches, or use the builtin ping_cm() or ping_in() methods
                                      // but since we use ping_median() (instead of just sonar.ping) we do our own conversion

  // the above code could then be used to trigger something, like this:
  if(ms > 0 && sonar.convert_cm(ms) < 10){ // we ignore 0 as it is either an error measurement or outside of our set range
    Serial.println("Waaay 2 close man!");
  }
    
}
