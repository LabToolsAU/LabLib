Examples of how to filter ADC (or any other) measurements, with voltage calculation thrown in.

This can be used to smooth measurements in a running loop. be careful with delays() other places in your code, since this will halt the operation of the filters.

we use a median filter [https://en.wikipedia.org/wiki/Median_filter#Worked_1D_example] to reject outlier values.
get the library here: https://github.com/daPhoosa/MedianFilter (unzip in your arduino libraries folder)

We can also choose to use an exponential moving average filter (or use both) to smooth incoming data and reject noise. 
get the library here: https://github.com/sofian/MovingAverage (unzip in your arduino libraries folder)
Read more about how/why the exponential filter works here: http://hackaday.com/2016/08/28/filtering-noisy-data-with-an-arduino/

