#ifndef T2_H
#define T2_H

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile short action = 0;

ISR(INT2_vect)
{
    action = 1;
}

int t2()
{

    // Enable interrupt PB2 on falling edge
    EICRA |= (1 << ISC21);
    EICRA &= ~(1 << ISC20);
    // Enable interrupt on INT2
    EIMSK |= (1 << INT2);

    // Enable red LED
    DDRD |= (1 << PD5);

    // Enable button input
    DDRB &= ~(1 << PB2);
    PORTB |= (1 << PB2);

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