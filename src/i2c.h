#ifndef I2C_H
#define I2C_H

void initI2C();
void beginTransmission(unsigned char address);
void endTransmission();
void write(unsigned char data);
void requestFrom(unsigned char address, unsigned char regAddr);
unsigned char read();

#endif