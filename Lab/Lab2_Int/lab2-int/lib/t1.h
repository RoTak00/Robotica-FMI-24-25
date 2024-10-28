#ifndef T1_H
#define T1_H

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile short action = 0;

ISR(PCINT3_vect)
{
    if ((PIND & (1 << PD6)) == 0)
    {
        action = 1;
    }
}

int t1()
{

    PCICR |= (1 << PCIE3);
    PCMSK3 |= (1 << PCINT30);

    // Enable red LED
    DDRD |= (1 << PD5);

    // Enable button input
    DDRD &= ~(1 << PD6);
    PORTD |= (1 << PD6);

    sei();

    while (1)
    {
        if (action == 1)
        {
            PORTD ^= (1 << PD5);
            action = 0;
        }

        _delay_ms(250);
    }

    return 1;
}

#endif
