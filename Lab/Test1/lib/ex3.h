#include <avr/io.h>
#include <util/delay.h>

void ex3()
{
  DDRD |= (1 << PD5); // red
  DDRD |= (1 << PD7); // green
  DDRB |= (1 << PB3); // blue

  DDRB &= ~(1 << PB2); // input change colors
  PORTB |= (1 << PB2); // enable pull-up resistor

  // setari initiale pentru led-uri
  PORTD |= (1 << PD5);
  PORTD &= ~(1 << PD7);
  PORTB |= (1 << PB3);

  char active = 0;
  char clicked = 0;

  // va fi pornit doar rosu

  while (1)
  {
    char button = ((PINB & (1 << PB2)) == 0);
    // daca butonul e apasat
    if (!clicked && button)
    {
      clicked = 1;
      if(active == 0)
      {
        active = 1;
        PORTD &= ~(1 << PD5); // pornim rosu
        PORTD |= (1 << PD7); // oprim verde
      }
      else if (active == 1)
      {
        active = 2;
        PORTD |= (1 << PD5); // oprim rosu
        PORTB &= ~(1 << PB3); // pornim blue
      }
      else if (active == 2)
      {
        active = 0;
        PORTB |= (1 << PB3); // oprim blue
        PORTD &= ~(1 << PD7); // pornim verde
      }
    }
    else if(clicked && !button)
    {
      clicked = 0;
    }

    _delay_ms(100);
  }

  return;
}