
#include <Arduino.h>
#include <avr/io.h>
#include "timer.h"
#include "i2c.h"
#include "tempConv.h"
#include "lcd.h"
#include "led.h"
#include "adc.h"


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
	initADC0();
}

int main()
{
	setup();
	unsigned int moistureVolt = 0;
	int temp = 0;

	while (1) {
	    

		switch(state) {

      	case check: //Checks to see if plant should be watered

			//take temperature sensor out of standby
			beginTransmission(0x92); // Target sensor with 10011010, 1001101 is address, 0 is write for start sequence =>0x92
			write(0x01); // command byte selects the CONFIG register
  			write(0x00); //take the device out of standby
			endTransmission(); 

			//measures temperature and moisture and converts temp to Fahrenheit
			requestFrom(0x92, 0x00); //request the TEMP register of the device
			temp = read();
			moistureVolt = readMoisture();	//takes in soil moisture
    		temp = convToF(temp);

			//print temperature to LCD	TEST/////////////////////////////////////////////////////////////////////////////////////////////////////////////
			Serial.flush();
			writeString("Temperature is: ");
			moveCursor(0,40);
			//writeString(temp);

			//Checks to see if next state is water or standby
			if ((temp > 33.8) && (moistureVolt <= 250)) {	//as sensor tolerance is +/- 1C (33.8F) //CHANGE 2.5 TO CORRECT VOLTAGE//////////////////////////
				 state = watering; 
				 }
			else { 
				//put temperature sensor into standby
				beginTransmission(0x92); // Target sensor with 10011010, 1001101 is address, 0 is write for start sequence =>0x92
				write(0x01); // command byte selects the CONFIG register
				write(0x80); //put the device in standby
				endTransmission(); 


				state = standby; 
				}    
			break;

      	case watering:	//Water plant for 5 seconds of time, with indications to user with use of LEDs

			ledWaterOn();	//sets LEDs to watering state
			//turn water pump on
			delayMs(5000);	//delay 5 seconds 
			//turn waterpump off
			ledWaterOff();	//sets LEDs to standby state
			state = check;
			break;

      	case standby:	//Delays to next check

			for (int i = 0; i < 60; ++i){	//delays one hour
				delayMs(60000);	//delay one minute
			}
			state = check;
			break;
    	}
	}
	return 0;
}