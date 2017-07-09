Ticker
======

__ONLY AVAILABLE FOR THE ESP8266 based boards (wemos, nodeMCU, etc). Does not compile for avr based Arduinos like the UNO__

Allows you to define functions to be run at specific intervals, regardless of what the rest of the code is doing.

__From the example code:__ Ticker is an object that will call a given function with a certain period.

Each Ticker calls one function. You can have as many Tickers as you like, memory being the only limitation.
  
A function may be attached to a ticker and detached from the ticker.
There are two variants of the attach function: attach and attach_ms.
The first one takes period in seconds, the second one in milliseconds.


Why?
====

Sometimes we want to read a sensor or update an LED while the arduino is doing something else. Ticker handles this quite nicely.

Howto
=====

 * Include ticker.h  
 * Write your asynchronous function(s)
 * Instantiate a ticker object, name it something relevant.
 * Attach the ticker to your async function with an interval.
 * (Detach the ticker when no longer needed)

Also:

 * Attach can be called again on a ticker object with a different value, thus overriding the first interval.

The code
========

The code attaches two tickers to two different functions (fade and blink), one uses the attach method and the other uses the attach_ms method.