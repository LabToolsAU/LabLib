Why?
====

Running this calibration will greatly increase the accuracy and reliability of your MPU6050 module.

**You should do this for _each_ sensor module that you have and _somehow_ keep note of which module has which offsets.**

How?
====

Snatched from the comment in the ino file:
------------------------------------------

1. Put the MPU6050 in a flat and horizontal surface, and leave it operating for 5-10 minutes so its temperature gets stabilized. **Tape it so it doesn't move**
2. Run this program.  A "----- done -----" line will indicate that it has done its best. With the current accuracy-related constants (NFast = 1000, NSlow = 10000), it will take a few minutes to get there.
3. Along the way, it will generate a dozen or so lines of output, showing that for each of the 6 desired offsets, it is 
  * first, trying to find two estimates, one too low and one too high, and
  * then, closing in until the bracket can't be made smaller.

The line just above the "done" line will look something like:
```c++
[567,567] --> [-1,2]  [-2223,-2223] --> [0,1] [1131,1132] --> [16374,16404] [155,156] --> [-1,1]  [-25,-24] --> [0,3] [5,6] --> [0,4]
```

As will have been shown in interspersed header lines, the six groups making up this line describe the optimum offsets for the X acceleration, Y acceleration, Z acceleration, X gyro, Y gyro, and Z gyro, respectively.  In the sample shown just above, the trial showed that +567 was the best offset for the X acceleration, -2223 was best for Y acceleration, and so on.


***Note these values somewhere, and put them into your code (in the MPU6050_setup() function) where it says something like:***

```c++
    mpu.setXGyroOffset(-133);
    mpu.setYGyroOffset(132);
    mpu.setZGyroOffset(122);
    
    mpu.setXAccelOffset(-1488);
    mpu.setYAccelOffset(-51);
    mpu.setZAccelOffset(1413); 
```

