# FlexSensor

The FlexSensor works much like an [FSR](../FSR/)
It can be used to detect when the sensor is bent. A popular use-case is to detect when a finger is bent in a glove, or attached to the body. 

<img src="https://cdn.sparkfun.com//assets/parts/1/6/8/6/08606-03-L.jpg" width="300">

## Setup

The sensor setup is almost identical to the FSR and other analog input sensors

### Hardware

<img src="http://zebweb.dk/lablibimg/flexsensor_wiring.png">

The FlexSensor is connected to the Analog 5 input, and bridged with a 10k ohm Resistor, and also supplied 5v power from the arduino

### Software

A FlexSensor sketch is supplied with the library which is pretty straight forward.
The sketch sets a threshold value, this threshold should always be set from a base level, so setup the sensor, measure its output levels at idle and desired positions and use these values to determine triggers. 

