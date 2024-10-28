#ifndef T3_H
#define T3_H

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile short buzzer_type_action = 0;
volatile short buzzer_action = 0;

ISR(INT2_vect)
{
    buzzer_type_action = 1;
}

ISR(PCINT3_vect)
{
    if ((PIND & (1 << PD6)) == 0)
    {
        buzzer_action = 1;
    }
    else
    {
        buzzer_action = 0;
    }
}

#define BUZZER_100_US (int)(1000000UL / 100 / 2)
#define BUZZER_200_US (int)(1000000UL / 200 / 2)
#define BUZZER_300_US (int)(1000000UL / 300 / 2)

short buzzer_state = 100;

int t3()
{

    // Enable interrupt PD6
    PCICR |= (1 << PCIE3);
    PCMSK3 |= (1 << PCINT30);

    // Enable button input PD6
    DDRD &= ~(1 << PD6);
    PORTD |= (1 << PD6);

    // Enable interrupt PB2 on falling edge
    EICRA |= (1 << ISC21);
    EICRA &= ~(1 << ISC20);
    // Enable interrupt on INT2
    EIMSK |= (1 << INT2);

    // Enable button input PB2
    DDRB &= ~(1 << PB2);
    PORTB |= (1 << PB2);

    // Enable red LED
    DDRD |= (1 << PD5); // red
    DDRD |= (1 << PD7); // green
    DDRB |= (1 << PB3); // blue

    // Enable Buzzer
    DDRD |= (1 << PD4);

    // Only RED LED
    PORTD |= (1 << PD5);
    PORTD |= (1 << PD7);
    PORTB &= ~(1 << PB3);

    sei();

    while (1)
    {
        if (buzzer_action == 1)
        {
            PORTD ^= (1 << PD4);

            if (buzzer_state == 100)
            {
                _delay_us(BUZZER_100_US);
            }
            else if (buzzer_state == 200)
            {
                _delay_us(BUZZER_200_US);
            }
            else if (buzzer_state == 300)
            {
                _delay_us(BUZZER_300_US);
            }
        }
        else
        {
            PORTD &= ~(1 << PD4);
        }

        if (buzzer_type_action == 1)
        {
            if (buzzer_state == 100)
            {
                buzzer_state = 200;
                buzzer_type_action = 0;

                PORTD |= (1 << PD5);
                PORTD &= ~(1 << PD7);
                PORTB |= (1 << PB3);
            }
            else if (buzzer_state == 200)
            {
                buzzer_state = 300;
                buzzer_type_action = 0;

                PORTD &= ~(1 << PD5);
                PORTD |= (1 << PD7);
                PORTB |= (1 << PB3);
            }
            else if (buzzer_state == 300)
            {
                buzzer_state = 100;
                buzzer_type_action = 0;

                PORTD |= (1 << PD5);
                PORTD |= (1 << PD7);
                PORTB &= ~(1 << PB3);
            }
        }
    }

    return 1;
}

#endif