//exponentialFilter.ino
//example sketch to pull and filter measurements from eg. an ADC
//the filter has a beta value which determines the weight of new values. 
//A high beta value will filter more noise but slow down the response of the filter.
static float filterBeta=32; //1, 2 , 4, 8, 16, 32, 64, 128 and so on...

//where is the data coming from?
static unsigned int adcPin=A0;

//the filtered value for printing or whatever:
unsigned long ADCfiltered=1; //default to 0V

//the filtered value converted to a voltage:
//adcFiltered ranges from 0-1023 corresponding to a voltage between 0 and adcMAXvoltage
static float adcMAXvoltage = 5; //5V for arduino uno, 3,1V for some nodeMCU boards (like the D1 mini), 1V for others (like the adafruit Huzzar).
float vADC=0; //converted value of adcFiltered


void setup() {
	Serial.begin(115200);
  //seed the filter with 4x$filterBeta measurements (eliminates the need for a settling time)
   for(int i=0; i<=4*filterBeta; i++) ADCfiltered=((ADCfiltered*filterBeta)+analogRead(adcPin))/(filterBeta+1); //low pass filtering of ADC0
   
}

void loop() {

	ADCfiltered=((ADCfiltered*filterBeta)+analogRead(adcPin))/(filterBeta+1); //pull a value from the ADC pin and merge into the filter.

	vADC=adcMAXvoltage/(float)1023*(float)ADCfiltered; //ADC -> voltage

	//debug printout:	
	Serial.print("ADCfiltered: "); Serial.println(ADCfiltered);
	Serial.print("voltage: "); Serial.println(vADC);
	Serial.println();


}
