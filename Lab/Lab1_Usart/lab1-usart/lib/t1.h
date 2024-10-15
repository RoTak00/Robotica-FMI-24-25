#ifndef T1_H
#define T1_H

#include <util/delay.h>
#include <usart.c>
#include <avr/io.h>


#define CLOCK_SPEED 12000000
#define BAUD 28800
#define MYUBRR CLOCK_SPEED/16/BAUD-1


void BTN_init()
{
    DDRB &= ~(1 << PB2);
    PORTB |= (1 << PB2);
}


uint8_t t1()
{
  USART0_init(MYUBRR);
  BTN_init();

    while(1)
    {

        if(!(PINB & (1 << PB2)))
        {
            USART0_print("Pressed\n");
        }


        _delay_ms(50);
    }
  
}

#endif