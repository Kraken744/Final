#include <avr/io.h>
#include "led.h"

//Pin 53 = Red
//Pin 52 = Green

void initLED(){

  // DDRAx  direction as output
  DDRB |=  (1<<DDB0) | (1<<DDB1);
}


void ledWaterOff(){

   PORTB |= (1 << PORTB0); //red on
   PORTB &= ~(1 << PORTB1);  //green off
}

void ledWaterOn(){

   PORTB |= (1 << PORTB1); //green on
   PORTB &= ~(1 << PORTB0);  //red off

}
