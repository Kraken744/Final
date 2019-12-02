#include <Arduino.h>
#include <avr/io.h>
#include "i2c.h"


void initI2C()
{
	TWSR &= ~((1 << TWPS0) | (1 << TWPS1)); // Set prescaler to 1
	TWBR = 32; // This gives an SCL of 200 kHz
	TWCR |= (1 << TWINT) | (1 << TWEN);
}

void beginTransmission(unsigned char address) // begin transmission to Slave with given address
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // Initiate
	while(!(TWCR & (1 << TWINT)));	//wait until complete

	TWDR = address; // Set address of device
	TWCR = (1 << TWEN) | (1 << TWINT); // Trigger action
	while(!(TWCR & (1 << TWINT)));	//wait until complete
}

void endTransmission() // Stops transmission and disconnects Slave from Master
{
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTO);	//Send Stop command
	while(!(TWCR & (1 << TWSTO)));	//wait until complete

	
}

void write(unsigned char data) // Sends data to Slave
{
	TWDR = data;	//Sends data to slave
	TWCR = (1 << TWEN) | (1 << TWINT); // Trigger action
	while(!(TWCR & (1 << TWINT)));	//wait until complete
}

void requestFrom(unsigned char address, unsigned char regAddr) // read data from slave
{
	beginTransmission(address); // Connect to device for transmission
	write(regAddr); // sends register address
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA); // Second start
	while(!(TWCR & (1 << TWINT)));	//wait until complete

	TWDR = address + 1; // Set to address plus read bit
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // Trigger action and acknowledge
	while(!(TWCR & (1 << TWINT)));	//wait until complete

	TWCR = (1 << TWINT) | (1 << TWEN); // Trigger action
	while(!(TWCR & (1 << TWINT)));	//wait until complete

	//TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); // Stop condition
	endTransmission();	//Stops transmission
}

unsigned char read() // Returns the last byte
{
	return TWDR;
}