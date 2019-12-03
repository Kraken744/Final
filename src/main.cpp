//Temperature Sensor Code for Final Project
#include <Arduino.h>
#include "timer.h"
#include "i2c.h"
#include "tempConv.h"
#include "lcd.h"
#include "led.h"


typedef enum stateType_enum {
  standby, check, watering
} stateType;

volatile stateType state = check;


void setup() {

	Serial.begin(9600);
	sei();
	initI2C();
	initTimer();
	initLCD();
	initLED();
}

int main()
{
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

	while (1) {
		delayMs(1000);

		// Read Data from TEMP register
		requestFrom(0x9A, 0x00); //request the TEMP register of the device
		temp = read();

    	//Convert to Fahrenheit
    	temp = convToF(temp);

		// Print data
		Serial.print("Temperature is: ");
		Serial.println(temp);
    	Serial.println(" F");

		Serial.println();
	
		switch(state) {

      	case check: //Checks to see if plant should be watered

			//take temperature (AND SOIL MOISTURE?) sensor(s) out of standby
			//measures temperature and soil moisture 
			//print temperature to LCD
			//if temperature is above 1 Celsius (as sensor tolerance is +/- 1C) and soil is dry, state = watering
			//else, state = standby     
			break;

      	case watering:	//Water plant for BLANK seconds of time, with indications to user with use of LEDs

			ledWaterOn();	//sets LEDs to watering state
			//turn water pump on
			//delay a certain amount of time
			//turn waterpump off
			ledWaterOff();	//sets LEDs to standby state
			state = standby;
			break;

      	case standby:	//Sets sensor(s) to standby to conserve power, and delays to next check

			//set sensor(s) to standby
			//delay one hour
			state = check;
			break;
    	}
	}
	return 0;
}