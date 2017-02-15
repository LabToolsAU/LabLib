# Piezo

Piezo elements can be used for both input and output on the arduino.
In LabLib we have several examples

## Output

One of the simplest ways to use a Piezo for output is using the built-in tone() methods in arudino

```C
tone(pin, frequency, duration); 
```

### Setup

#### Hardware (Wiring)
<img src="http://zebweb.dk/lablibimg/piezo_pin5.png" width="200">

Wire the piezo element up to the Arduino Uno as pictured above
The Piezo + wire (red) is wired to pin 5, and - (blue) to GND

#### Software

Fairly simple examples are included
* [Simple Tone Example](SimpleExample/SimpleExample.ino)
* [Melody](Melody/Melody.ino) (Taken from: https://www.arduino.cc/en/Tutorial/toneMelody and edited slightly) 

The SimpleExample simply plays a tone on/off like an alarm clock
The Melody example shows how you can play an entire melody using tone and piezos, and also comes with a very interresting [pitches.h](Melody/pitches.h) file that has a bunch of notes already mapped out into tone frequencies.

##### Things to notice
The tone() method exists in two versions
```C
tone(pin, frequency, duration); // with duration
tone(pin, frequency); // without duration
```
When using the version without duration the tone will play until interupted by noTone(pin).
e.g.
```C
int piezoPin = 5; // pin with the piezo in
tone(piezoPin, 440); // tone on the pin at 440Hz frequency
delay(1000); // wait (let it play) for 1 sec.
noTone(piezoPin); // stop it
```

## Input
Piezos can also be used for inputs, this can be a little tricky but can be used in a lot of interresting ways

The [input example sketch](Input/PiezoInput.ino) shows a very crude way of reading input from the piezo via analog in on the Arduino
A more detailed example and explanation can be found at https://www.arduino.cc/en/Tutorial/Knock

### Setup

#### Hardware (wiring)

<img src="http://zebweb.dk/lablibimg/piezo_input.png" width="200">

Note the resistor (1M) between the analog input A5 and GND, this serves to pull down the value when the piezo is not being tapped or knocked. Smaller resistance can be used but will require more force, so just stick with 1M

#### Software
We read the analog value and react, as shown in [the input example](Input/PiezoInput.ino) sketch.
