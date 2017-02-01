
#Switches#

As there is so many types of switches we are not going to cover all of them here. For a quick introduction to the different types see: (https://learn.sparkfun.com/tutorials/switch-basics)

There are multiple uses of switches. Each with different advantages and downsides.

##Lowlevel checking of switches##


The simplest way to handle a switch is to check it with the digitalRead() function. And example of this can be seen in [examples/simpleswitch.ino](examples/simpleswitch.ino).

You can also with some logic get the switches to only be activated on certain conditions. An example of a simple way to implement a toggle switch from a pusbutton switch can be found in [examples/togglswitch.ino](examples/togglswitch.ino).



##Switch libraries## 

Sometime we want to do more complicated stuff with switches. For this we can exploit the --POWER OF ABSTRACTION-- and use a library.

###Onebutton###
(https://github.com/mathertel/OneButton)
For platformio see: (http://platformio.org/lib/show/1260/OneButton)

Onebutton is a brilliant library which enables you to attach a callback function to an event on a switch. A callback function is basicly a reference to a function you want to call when something specific happens with a switch. This makes it easy to attach advances behaviors to swicthes and detect things like doubleclick, longpresses and alike.

A simple sketch showing how to implement double and single click on two switches can be found in [examples/OneButton.ino](examples/OneButton.ino)

For a full reference on all the different things that we can listen for with OneButton see the libraries documentation.

--NB:-- In order for the library to work you need to call the ??? function on a regular basis, this means that delays in the main loop is a nogo. If you relay need your delay as is you can implement your own simple delay function as follows and use that instead. However a better approach is to use timers instead of delays. A simple guide to using timers in your code can be found [here](http://playground.arduino.cc/Code/AvoidDelay).