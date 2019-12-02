//Temperature Sensor Code for Final Project
#include <Arduino.h>
#include "timer.h"
#include "i2c.h"
#include "tempConv.h"

int main()
{
	Serial.begin(9600);
	sei();
	initI2C();
	initTimer();

	int temp = 0;

	beginTransmission(0x9A); // Target sensor with 10011010, 1001101 is address, 0 is write for start sequence =>0x9A
	write(0x01); // command byte selects the CONFIG register
  write(0x00); //take the device out of standby
	endTransmission(); 

  bool condition = false; //this can be updated later with our 10 minute timer stuff to set device into standby for an hour after watering

 if (condition == true){ //if the device just watered, put in standby for an hour to save power
 beginTransmission(0x9A); // Target sensor with 10011010, 1001101 is address, 0 is write for start sequence =>0x9A
	write(0x01); // command byte selects the CONFIG register
  write(0x80); //put the device in standby
	endTransmission(); 
 }

	Serial.flush();

	while (1)
	{
		delayMs(1000);

		// Read Data from TEMP register
		requestFrom(0x9A, 0x00); //request the TEMP register of the device
		temp = read();

    //Convert to Fahrenheit
    convToF(&temp);

		// Print data
		Serial.print("Temperature is: ");
		Serial.println(temp);
    Serial.println(" F");

		Serial.println();
	}

	return 0;
}