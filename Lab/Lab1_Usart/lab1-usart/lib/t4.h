#ifndef T4_H
#define T4_H

#include <util/delay.h>
#include <usart.c>
#include <avr/io.h>
#include <string.h>

#define CLOCK_SPEED 12000000
#define BAUD 28800
#define MYUBRR CLOCK_SPEED/16/BAUD-1

#define BUFFER_LEN 64
#define DELAY_YELLOW 2000
#define DELAY_GREEN 5000

enum AppState
{
    IDLE,
    LIGHT
};

AppState state = IDLE;

void LED_init()
{
     // setam output
    DDRD |= (1 << PD5); // RED
    DDRD |= (1 << PD7); // GREEN
    DDRB |= (1 << PB3); // BLUE

    // pornim rosu
    PORTD &= ~(1 << PD5); // RED
    PORTD |= (1 << PD7); // GREEN
    PORTB |= (1 << PB3); // BLUE
}

void LED_red()
{
    PORTD &= ~(1 << PD5); // RED
    PORTD |= (1 << PD7); // GREEN
    PORTB |= (1 << PB3); // BLUE
}

void LED_yellow()
{
    PORTD &= ~(1 << PD5); // RED
    PORTD &= ~(1 << PD7); // GREEN
    PORTB |= (1 << PB3); // BLUE
}

void LED_green()
{
    PORTD |= (1 << PD5); // RED
    PORTD &= ~(1 << PD7); // GREEN
    PORTB |= (1 << PB3); // BLUE
}

int t4()
{
    USART0_init(MYUBRR);
    LED_init();

    char command_buffer[BUFFER_LEN] = {0};

    uint8_t read_index = 0;
    USART0_print("Waiting for pedestrian: \n");

    while (1)
    {
        if (state == IDLE)
        {
            command_buffer[read_index] = USART0_receive();

            if (command_buffer[read_index] == '\n')
            {
                command_buffer[read_index] = '\0';
                command_buffer[read_index - 1] = '\0';

                if (strcmp(command_buffer, "pieton") == 0)
                {
                    state = LIGHT;
                }

                read_index = 0;
                for (int i = 0; i < BUFFER_LEN; i++)
                {
                    command_buffer[i] = '\0';
                }
            }
            else
            {
                read_index = (read_index + 1) % BUFFER_LEN;
            }
        }

        else if (state == LIGHT)
        {
            LED_yellow();

            _delay_ms(DELAY_YELLOW);

            LED_green();

            _delay_ms(DELAY_GREEN);

            LED_red();
            state = IDLE;
        }
    }
    
}

#endif