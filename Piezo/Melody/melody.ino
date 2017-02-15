/* The following sketch has been lifted gracefully from https://www.arduino.cc/en/Tutorial/toneMelody
 * And modified for LabLib use, basically just changed the pin used - to be more in line with the other piezo pages
 * 
  */

#include "pitches.h" // a nice little addition that has a wide range of tone frequencies
int piezoPin = 5; // must be PWM

// notes in the melody - these are all included in the pitches.h file
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc. - nice for doing a little composition :)
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {

    // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(piezoPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

// as we only play the melody once we dont really need the loop - all the fun is in the setup part
void loop() {

}
