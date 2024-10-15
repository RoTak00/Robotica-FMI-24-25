#ifndef T2_H
#define T2_H


#include <util/delay.h>
#include <usart.c>
#include <avr/io.h>

#define CLOCK_SPEED 12000000
#define BAUD 28800
#define MYUBRR CLOCK_SPEED/16/BAUD-1



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

  char command = 0;

  USART0_print("Enter a command: \n");

  while(1)
  {
    command = USART0_receive();

    switch(command)
    {
        case '0':
            LED_off();
            break;
        case '1':
            LED_on();
            break;
        case 'r':
            LED_red();
            break;
        case 'g':
            LED_green();
            break;
        case 'b':
            LED_blue();
            break;
        default:
            USART0_print("Invalid command\n");
            break;
    }

    _delay_ms(10);
  }
}

#endif