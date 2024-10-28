#ifndef T6_H
#define T6_H

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

volatile short color_action = 0;
volatile short freq_action = 0;
volatile unsigned int last_color_update = 0;
volatile unsigned int last_freq_update = 0;
volatile unsigned int last_blink_update = 0;
ISR(INT2_vect)
{
    unsigned long long t = millis();
    if (t - last_color_update > DEBOUNCE_DELAY)
    {
        color_action = 1;
        last_color_update = t;
    }
}

ISR(PCINT3_vect)
{
    if ((PIND & (1 << PD6)) == 0)
    {
        unsigned long long t = millis();
        if (t - last_freq_update > DEBOUNCE_DELAY)
        {
            freq_action = 1;
            last_freq_update = t;
        }
    }
}

void init_buttons()
{

    // Enable interrupt PB2 on falling edge
    EICRA |= (1 << ISC21);
    EICRA &= ~(1 << ISC20);
    // Enable interrupt on INT2
    EIMSK |= (1 << INT2);

    // Enable button input PB2
    DDRB &= ~(1 << PB2);
    PORTB |= (1 << PB2);

    // Enable interrupt PCINT30
    PCICR |= (1 << PCIE3);
    PCMSK3 |= (1 << PCINT30);

    // Enable button input PD6
    DDRD &= ~(1 << PD6);
    PORTD |= (1 << PD6);

    sei();
}

void init_led()
{
    // Enable LED
    DDRD |= (1 << PD5);
    DDRD |= (1 << PD7);
    DDRB |= (1 << PB3);

    // LED red
    PORTD &= ~(1 << PD5);
    PORTD |= (1 << PD7);
    PORTB |= (1 << PB3);
}

short current_color_state = 0;
short current_freq_state = 0;
int t6()
{
    init_timer();
    init_buttons();
    init_led();

    while (1)
    {
        if (color_action == 1)
        {
            if (current_color_state == 0)
            {

                PORTD |= (1 << PD5);
                PORTD &= ~(1 << PD7);
                PORTB |= (1 << PB3);
            }
            else if (current_color_state == 1)
            {

                PORTD |= (1 << PD5);
                PORTD |= (1 << PD7);
                PORTB &= ~(1 << PB3);
            }
            else
            {

                PORTD &= ~(1 << PD5);
                PORTD |= (1 << PD7);
                PORTB |= (1 << PB3);
            }
            current_color_state = (current_color_state + 1) % 3;
            color_action = 0;
        }

        if (freq_action == 1)
        {
            if (current_freq_state == 0)
            {
                current_freq_state = 50;
            }
            else if (current_freq_state == 50)
            {
                current_freq_state = 100;
            }
            else if (current_freq_state == 100)
            {
                current_freq_state = 500;
            }
            else if (current_freq_state == 500)
            {
                current_freq_state = 0;

                if (current_color_state == 0)
                {
                    PORTD &= ~(1 << PD5);
                    PORTD |= (1 << PD7);
                    PORTB |= (1 << PB3);
                }
                else if (current_color_state == 1)
                {
                    PORTD |= (1 << PD5);
                    PORTD &= ~(1 << PD7);
                    PORTB |= (1 << PB3);
                }
                else
                {
                    PORTD |= (1 << PD5);
                    PORTD |= (1 << PD7);
                    PORTB &= ~(1 << PB3);
                }
            }

            freq_action = 0;
        }

        if (current_freq_state != 0)
        {
            unsigned int t = millis();
            if (t - last_blink_update > current_freq_state)
            {
                if (current_color_state == 0)
                {
                    PORTD ^= (1 << PD5);
                }
                else if (current_color_state == 1)
                {
                    PORTD ^= (1 << PD7);
                }
                else
                {
                    PORTB ^= (1 << PB3);
                }
                last_blink_update = t;
            }
        }

        _delay_ms(1);
    }

    return 1;
}

#endif