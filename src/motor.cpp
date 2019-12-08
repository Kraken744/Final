#include <avr/io.h>
#include "motor.h"

//B2 (51)
void initPump(){
    DDRB |=  (1<<DDB2);
}
void motorOn(){
    PORTB &= ~(1 << PORTB2);  

}
void motorOff(){
    PORTB |= (1 << PORTB2);

}

