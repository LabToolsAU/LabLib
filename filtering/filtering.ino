//filtering.ino
//example sketch to pull and filter measurements from eg. an ADC

//we use a median filter [https://en.wikipedia.org/wiki/Median_filter#Worked_1D_example] to reject outlier values.
//get the library here: https://github.com/daPhoosa/MedianFilter (unzip in your arduino libraries folder)
#include <MedianFilter.h>
MedianFilter mf(5, 0); //a window of 5 values, all starting at value 0.

//we can also choose to use an exponential moving average filter (or use both) to smooth incoming data and reject noise. 
//get the library here: https://github.com/sofian/MovingAverage (unzip in your arduino libraries folder)
#include <MovingAverage.h>
MovingAverage exp(0.1f); //new values are weigted at 0.1 (10%)



//where is the data coming from?
static unsigned int adcPin=A0;

//the final filtered value for printing or whatever:
unsigned long ADCfiltered=1; //default to 0V

//the filtered value converted to a voltage:
//adcFiltered ranges from 0-1023 corresponding to a voltage between 0 and adcMAXvoltage
static float adcMAXvoltage = 5; //5V for arduino uno. 3,2V for some nodeMCU boards (like the D1 mini). 1V for others (like the adafruit Huzzar).
float vADC=0; //converted value of adcFiltered



void setup() {
	Serial.begin(115200);
  
   for(int i=0; i<5; i++) mf.in(analogRead(adcPin));  //fill the median filter with ADC measurements (runs 5 times).

   	exp.reset(mf.out());  //Initialize the average with the filtered value from the median filter.
}

void loop() {

	mf.in(analogRead(adcPin)); //pull a value from the ADC pin and merge into the median filter.

	ADCfiltered=exp.update(mf.out()); //get the median from the median filter and feed it to the exponential filter

	vADC=adcMAXvoltage/(float)1023*(float)ADCfiltered; //ADC -> voltage

	//debug printout:	
	/*Serial.print("ADCfiltered: "); Serial.println(ADCfiltered);
	Serial.print("voltage: ");*/ Serial.println(vADC);
	//Serial.println();


}
