# SoundSensor (electret)

The SoundSensor (or electret) comes in different variants, and is a simple microphone than can be connected to an Arduino and used to react to sounds.

<img src="http://zebweb.dk/lablibimg/electret_img.jpg" height="100">

## Setup

### Hardware (wiring)

The component is wired as seen below

<img src="http://zebweb.dk/lablibimg/electret_wiring.png" height="300">

* VCC is connected to 5v or 3.3v (make sure to set the voltageIn correctly in the [SoundSensor sketch](SoundSensor.ino)
* GND to GND (duh)
* OUT (or AUD as it is called on some devices) is connected to an analog in pin (A5 in this case)

### Software

The example [SoundSensor.ino](SoundSensor.ino) sketch can seem a bit daunting at first, but just read along the comments and you should be fine. There are however some things to take notice of

* It is said that the electret works best at 3.3v, but for the example sketch we use 5v. If you change the wiring, remember to update the sketch and set the voltageIn variable accordingly (as also stated above). If you do not, then the voltage conversion done in the sketch will be wrong and will give the wrong result
* The sampleWindow variable is set to 250 ms (or 4Hz) and will run each loop, this means that the sketch is automatically delayed 250ms each loop. Depending on what kind of sound you are trying to catch, this sample window can be reduced drastically (the demo at the bottom of the page uses a 60 hz window (16ms)
* The SoundSensor is just that, a sensor, it cannot (and should not) be used for anything where the actual sound should be recorded for playback. A much more complicated component is required that uses a dedicated ADC (analog/digital converter) TL;DR; do not expect this to function as an actual microphone

## DEMO

This video showcases a demo using, basically the same code as the example code provided here - modified heavily to use neopixels to visualize the music being played. 

<video src="http://zebweb.dk/lablibimg/electret.mp4" controls="true">