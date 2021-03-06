The MPU6050 is a gyroscope/accelerometer Inertial Measurement Unit
==================================================================

Getting started
===============

Libraries
---------

Get the [i2CdevLib from here](https://github.com/jrowberg/i2cdevlib/archive/master.zip).

Extract the zip file somewhere temporary, you need to dig out 2 folders from the **Arduino _subfolder_**:

The **I2Cdev** folder and the **MPU6050** folder.

**Beware that there are several I2Cdev folders in the zip file. _You specifically need to get the one in the Arduino subfolder!_**

Put these in your [Arduino libraries folder](https://www.arduino.cc/en/Guide/Libraries#toc5).

Connecting to the Uno
---------------------

![6050!](mpu_6050.jpg "6050")



The examples we have provided
=============================

The MPU6050 can do a lot of really crazy calculations with positional data, so the code in these examples can get pretty intimidating. We have tried simplifying it by placing all the nasty code somewhere out of sight, and split the usage of the device into two examples that shold cover a pretty wide range of use cases:

1: **mpu6050pitchRollYaw:** printout of yaw, pitch, roll. 
---------------------------------------------------------
As described here:

![YAAAAAW!](http://doc.aldebaran.com/2-1/_images/rollPitchYaw.png "YPR")

You can of course choose to do something else than print it out... maybe even use an if statement?? :)

2: **mpu6050Jerk:** printout of movement in 3 axes (semi stable)
----------------------------------------------------------------
Up/Down (Z+/Z-) , Left/Right (Y+/Y-), Forward/Backward (X+/X-)

Motion is determined as a jerk move above a certain threshold. (minimumJerk)



Precision? (**mpu6050calibration**)
-----------------------------------

Each MPU6050 has it own specific calibration values. The sensor works with a default calibration, but better results are achieved after a calibration on your own hardware in order to get offsets for your individial unit. 

The calibration sketch has a howto guide in the comments of the sketch, but it will basically output 4 values that can be put into the setOffset parts in the MPU6050_setup() functions in the sketches in the first and second examples eg the lines that go:

```c++
    mpu.setXGyroOffset(-133);
    mpu.setYGyroOffset(132);
    mpu.setZGyroOffset(122);
    
    mpu.setXAccelOffset(-1488);
    mpu.setYAccelOffset(-51);
    mpu.setZAccelOffset(1413); 
```

