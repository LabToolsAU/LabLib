Exponential low-pass filtering of ADC measurements, with voltage calculation thrown in.

This can be used to smooth measurements in a running loop. be careful with delays() other places in your code, since this will halt the operation of the filter.

The filter has a beta value which determines the weight of new values. 

A high beta value will filter more noise but slow down the response of the filter.

Read more about how/why the filter works here: http://hackaday.com/2016/08/28/filtering-noisy-data-with-an-arduino/
