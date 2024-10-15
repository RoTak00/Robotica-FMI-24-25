#ifndef T2_H
#define T2_H


#include <util/delay.h>
#include <usart.c>
#include <avr/io.h>

#define CLOCK_SPEED 12000000
#define BAUD 28800
#define MYUBRR CLOCK_SPEED/16/BAUD-1

#define BUFFER_LEN 20

#include <string.h>

void LED_init()
{
    // setam output
    DDRD |= (1 << PD5); // RED
    DDRD |= (1 << PD7); // GREEN
    DDRB |= (1 << PB3); // BLUE

    // oprim toate culorile
    PORTD |= (1 << PD5); // RED
    PORTD |= (1 << PD7); // GREEN
    PORTB |= (1 << PB3); // BLUE
}

void LED_on()
{
    PORTD &= ~(1 << PD5); // RED
    PORTD &= ~(1 << PD7); // GREEN
    PORTB &= ~(1 << PB3); // BLUE
}

void LED_off()
{
    PORTD |= (1 << PD5); // RED
    PORTD |= (1 << PD7); // GREEN
    PORTB |= (1 << PB3); // BLUE
}

void LED_red()
{
    PORTD &= ~(1 << PD5); // RED
    PORTD |= (1 << PD7); // GREEN
    PORTB |= (1 << PB3); // BLUE
}

void LED_green()
{
    PORTD |= (1 << PD5); // RED
    PORTD &= ~(1 << PD7); // GREEN
    PORTB |= (1 << PB3); // BLUE
}

void LED_blue()
{
    PORTD |= (1 << PD5); // RED
    PORTD |= (1 << PD7); // GREEN
    PORTB &= ~(1 << PB3); // BLUE
}


uint8_t t2()
{
  USART0_init(MYUBRR);
  LED_init();

  char command_buffer[BUFFER_LEN] = {0};

  uint8_t read_index = 0;
  USART0_print("Enter a command: \n");

  while(1)
  {
    command_buffer[read_index] = USART0_receive();

    if(command_buffer[read_index] == '\n')
    {   
        command_buffer[read_index] = '\0';
        command_buffer[read_index - 1] = '\0';

            if (strcmp(command_buffer, "on") == 0)
            {
                LED_on();
            }
            else if (strcmp(command_buffer, "off") == 0)
            {
                LED_off();
            }
            else if (strcmp(command_buffer, "red") == 0)
            {
                LED_red();
            }
            else if (strcmp(command_buffer, "green") == 0)
            {
                LED_green();
            }
            else if (strcmp(command_buffer, "blue") == 0)
            {
                LED_blue();
            }
            else 
            {
                USART0_print("Invalid command\n");
            }

        read_index = 0;
        for(int i = 0; i < BUFFER_LEN; i++)
        {
            command_buffer[i] = 0;
        }
    }
    else 
    {
        read_index = (read_index + 1) % BUFFER_LEN;
    }

  }
}

#endif