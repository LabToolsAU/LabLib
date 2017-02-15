# PingSensor

The PingSensor is a distance measuring component found in the basic-kit (and many other places). It is basically a sonar that emits an ultrasonic sound and measures the time it takes (in ms) for a reflection of the sound to return to the component. 

### Usage

 * Simple distance measuring
 * Proximity trigger (e.g. do something inside a specific range)
 * Distance trigger (e.g. do something at a specific range, like change the pitch of a tone - a theramin)


### Setup
#### Hardware

![Fritzing Image of Hardware](https://bitbucket.org/repo/77M5o7/images/3028821470-1424201420-2wire_bb.png)
>*Image is taken from the [NewPing bitbucket page](https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home)*

Hook up the wiring as shown in the image, the library does support multiple sensors and single-wire connections but that is out of scope for this page/tutorial, see more at the NewPing bitbucket page if you're interested

#### Software
Add the NewPing library to your arduino project. Download the zip-file from this repo and use the menu; "sketch > include library > add .zip library". Point to the NewPing zip and the library is now added to your Arduino installation. You can then include the library by using "sketch > include library > newping" or include it manually
```c
#include <NewPing.h>
```
A basic example of how to use the library is included in [PingSensor.ino](PingSensor.ino)

### Links and read-worthy stuff
* [Arduino PlayGround on NewPing](http://playground.arduino.cc/Code/NewPing)
* [NewPing Bitbucket Repository and Wiki](https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home)