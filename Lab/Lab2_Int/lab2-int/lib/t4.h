#ifndef T4_H
#define T4_H

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <usart.c>

#define f_cpu 12000000UL
#define prescaler 8UL
#define f_int 1000UL
#define tc ((f_cpu) / (f_int) / (prescaler)) - 1

#define CLOCK_SPEED 12000000
#define BAUD 28800
#define UBBR_VAL CLOCK_SPEED / 16 / BAUD - 1

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
int t4()
{
    init_timer();
    USART0_init(UBBR_VAL);

    unsigned long long last_update = millis();

    while (1)
    {
        if (millis() - last_update > 1000)
        {
            USART0_print("Hello, World!\n");
            last_update = millis();
        }

        _delay_ms(1);
    }

    return 1;
}

#endif