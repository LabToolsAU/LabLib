The HX711 amplifier is used to interface load cells
=========================================

Serial data is clocked out of the amplifier using two pins (clock and data). Code in this folder is pretty much copy-pasted from [sparkfuns excellent loadcell code](https://github.com/sparkfun/HX711-Load-Cell-Amplifier)

Getting started
---------------

Download [this library](https://github.com/bogde/HX711/archive/master.zip) and extract it in your [Arduino libraries folder](https://www.arduino.cc/en/Guide/Libraries#toc5).

Hook up the HX711 as shown here:

![HX711!](hx711_wiring.png "HX711")

Mounting
--------

Sparkfun has an excellent tutorial for mounting loadcells [here](https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide)

There are also several instructables to seek out for inspiration...

[This image](https://cdn.instructables.com/F4Q/FWBS/ISCBDSO4/F4QFWBSISCBDSO4.LARGE.jpg) from [here](http://www.instructables.com/id/Arduino-Load-Cell-Scale/) should give you an idea

Calibration
-----------

* Get something with a known weight (100-10000grams).

* Upload the loadCellCalibration.ino sketch to your arduino, open the serial monitor and follow the guide.

* Note the calibration factor and use this in your loadCell.ino sketch

It calibrates the scale following these points:

1. Call set_scale() with no parameter.
2. Call tare() with no parameter.
3. Place a known weight on the scale and call get_units(10).
4. Divide the result in step 3 to your known weight. You should get about the parameter you need to pass to set_scale.
5. Adjust the parameter in step 4 until you get an accurate reading.


Running
-------

loadCell.ino contains the code needed to measure the weight of an object and print the weight to the serial monitor. Modify the code to your needs.


More?
-----

Additional settings, like offset and tareing can be found in the HX711SerialBegin.ino example in the HX711 library that you downloaded and put in your arduino libraries folder.

A lot more info about load cells (and strain gauges) is available at [sparkfun](https://learn.sparkfun.com/tutorials/getting-started-with-load-cells)