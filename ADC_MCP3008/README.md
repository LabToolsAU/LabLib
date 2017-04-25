ADC_MCP3008
===========

The MCP2008 is an 8 channel 10bit analog to digital converter. Use it to sample analog signals from eg. flex sensors or LDRs (coupled as voltage dividers)

Why?
====

Measuring analog voltages from sensors is pretty cool.

What?
=====

The code example instantiates a single ADC object, which can then be polled for a voltage from each of its 8 channels.


Use the [Serial Plotter](https://rheingoldheavy.com/new-arduino-serial-plotter/) (CTRL/CMD+SHIFT+L) for a nice visual representation of the analog values. 

How?
=====

Get the MCP3008 library from [here](https://github.com/nodesign/MCP3008/archive/master.zip), and unpack it in your [Arduino libraries folder](https://www.arduino.cc/en/Guide/Libraries#toc5).

Hook up the ADC as follows:

![Hookup](arduinoWiring.png "MCP3008_wiring")

Several ADCs can be connected to one arduino, edit the code to instantiate one ADC object per physical device. They can share the datapins, but need seperate CS (chip select) pins.

Hooking up Sensors?
===================

Most sensors that rely on a change in resistance need to be coupled as voltage dividers to work with an ADC. Have a look at the [FSR readme](../FSR/README.md) for a nice example.