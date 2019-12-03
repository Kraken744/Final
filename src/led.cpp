
#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

/* Initialize PA0, PA1,  to outputs */
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
