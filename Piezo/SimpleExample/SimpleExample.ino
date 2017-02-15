// super simple piezo sound example - makes an alarm clock like pattern

int piezoPin = 5; // the pin where the piezo (+) wire is connected to

void setup(){
  // stub method
}

void loop(){
  tone(piezoPin, 440, 200); // play a tone at 440hz for 200ms on the piezoPin
  delay(500); // wait 500ms - which gives us a 300ms break between tones

  // when using the tone() method without duration we need to call noTone after playing
  // the below code yields the same result as the two lines above
  tone(piezoPin, 440);
  delay(200); // ms
  noTone(piezoPin);
  delay(300); // ms - break between tones
}

