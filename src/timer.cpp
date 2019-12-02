#include <Arduino.h>
#include <avr\io.h>
#include "timer.h"

void initTimer()
{
	// Set Timer 1 to CTC mode
	TCCR1A &= ~(1 << WGM10);
	TCCR1A &= ~(1 << WGM11);
	TCCR1B |= (1 << WGM12);
	TCCR1B &= ~(1 << WGM13);
	// Set counting register to 0
	TCNT1 = 0;
}

void delayMs(unsigned int ms)
{
	// Put flag down
	TIFR1 |= (1 << OCF1A);

	// Set timer for Prescaler 64 and 249 counts
	OCR1AL = 249;
	TCCR1B |= (1 << CS10) | (1 << CS11);
	TCCR1B &= ~(1 << CS12);

	unsigned int count = 0;
	TCNT1 = 0;

	while (count < ms)
	{
		if (TIFR1 & (1 << OCF1A))
		{
			count++;
			TIFR1 |= (1 << OCF1A);
		}
	}
}