#include "adc.h"
#include "timer.h"
#include <avr/io.h>

void initADC0() {   //Uses A0 as input
    
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1);

    //Right justified ADLAR = 0
    ADMUX &= ~(1 << ADLAR);

    // Set ADC0 as single-ended input with MUX[5:0] = 0b000000
    ADMUX &=  ~(1 << MUX0);
    ADMUX &=  ~(1 << MUX1);
    ADMUX &=  ~(1 << MUX2);
    ADMUX &=  ~(1 << MUX3);
    ADMUX &=  ~(1 << MUX4);
    ADCSRB &= ~(1 << MUX5);

    // set Auto Trigger Source Selection
    // set to free-running mode ADTS[2:0] = 0b000
    ADCSRB &= ~(1 << ADTS2 | 1 << ADTS1 | 1 << ADTS0);

    //enable auto-triggering and turn-on ADC
    ADCSRA |= (1 << ADATE) | (1 << ADEN);

    //set the pre-scaler to 128
    //ADC clock frequency is 16 Mhz divided by pre-scaler = 125KHz
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    //ADC0 pin digital input disable input buffer as 1 as we are intaking analog instead
    DIDR0 |= (1<< ADC0D);


    // start the first conversion
    ADCSRA |= (1 << ADSC);
}

unsigned int readMoisture(){
    unsigned int moistureAnalog = 0;

	// read in ADCL first then read ADCH
    moistureAnalog = ADCL;
    moistureAnalog += ((unsigned int) ADCH) << 8;


    return moistureAnalog;
}
