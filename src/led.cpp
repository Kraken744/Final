#include <avr/io.h>
#include "led.h"

//Pin 22 = Red
//Pin 23 = Green

void initLED(){

  // DDRAx  direction as output
  DDRA |=  (1<<DDA0) | (1<<DDA1) ;
}


void ledWaterOff(){

   PORTA |= (1 << PORTA0); //red on
   PORTA &= ~(1 << PORTA1);  //green off
}

void ledWaterOn(){

   PORTA |= (1 << PORTA1); //green on
   PORTA &= ~(1 << PORTA0);  //red off

}
