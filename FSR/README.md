# FSR (Force Sensing Resistor)

The FSR is a cool little force sensitive resistor, typically used as a pressure pad.
The Basic lab kit comes with two types, essentially the same but in different sizes:

<img src="http://iainmccurdy.org/sensorsworkshop/images/fsr_schematic.jpg" width="300">
<img src="http://sensorembedded.com/images/FORCE_SENSOR_RESISTOR_ROUND_0.5_FSR402.jpg" width="300">

Wiring is the same and can be seen on the Square FSR image or below on the hardware wiring diagram

## Setup

### Hardware (wiring)

<img src="http://zebweb.dk/lablibimg/fsr_wiring.png">

The FSR is connected to 5v on the left (+) pin and to the arduino analog input (ADC) on the right (-) pin. On the Arduino we also connect the analog pin with a 10K resistor to keep our input 0 when we are not applying any pressure

### Software

LabLib supplies two examples. 

* [Simple FSR example](FSR.ino)
* [Simple FSR example using MedianFilter](FsrMedian.ino)

The first example is the very basic way to read the input from the FSR and can be found in the [FSR.ino](FSR.ino) sketch. The second example [FsrMedian.ino](FsrMedian.ino) is basically the same example but using a median filter (introduced in [filtering](https://github.com/LabToolsAU/LabLib/tree/master/filtering))

The Median Filter is used to get consistent readings from the FSR (and is generally a good idea to use for anything reading from analog on the arduino). Often when using sensors to read you get errors, the median filter simply gives the median of the 5 latest readings and discards anything "out of the ordinary"

