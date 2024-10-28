#ifndef T5_H
#define T5_H

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define f_cpu 12000000UL
#define prescaler 8UL
#define f_int 1000UL
#define tc ((f_cpu) / (f_int) / (prescaler)) - 1

#define DEBOUNCE_DELAY 100
volatile unsigned long long milliseconds = 0;

void init_timer()
{
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS11); // prescaler 8
    OCR1A = tc;

    TIMSK1 |= (1 << OCIE1A);

    sei();

    milliseconds = 0;
}

ISR(TIMER1_COMPA_vect)
{
    milliseconds++;
}

unsigned long long millis()
{
    cli();
    unsigned long long ret_value = milliseconds;
    sei();
    return ret_value;
}

volatile short button_action = 0;
volatile unsigned int last_update = 0;
ISR(INT2_vect)
{
    unsigned long long t = millis();
    if (t - last_update > DEBOUNCE_DELAY)
    {
        button_action = 1;
        last_update = t;
    }
}

int t5()
{
    init_timer();

    // Enable red LED
    DDRD |= (1 << PD5);

    // Enable interrupt PB2 on falling edge
    EICRA |= (1 << ISC21);
    EICRA &= ~(1 << ISC20);
    // Enable interrupt on INT2
    EIMSK |= (1 << INT2);

    // Enable button input
    DDRB &= ~(1 << PB2);
    PORTB |= (1 << PB2);

    sei();

    while (1)
    {
        if (button_action == 1)
        {
            PORTD ^= (1 << PD5);
            button_action = 0;
        }
        _delay_ms(1);
    }

    return 1;
}

#endif