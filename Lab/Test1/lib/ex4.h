#include <avr/io.h>
#include <util/delay.h>

void ex4()
{
  // IO
  // OUT
  DDRD |= (1 << PD7); // green
  DDRD |= (1 << PD5); // red
  DDRB |= (1 << PB3); // blue

  // IN
  DDRB &= ~(1 << PB2); // input change colors
  PORTB |= (1 << PB2); // enable pull-up resistor

  DDRD &= ~(1 << PD6); // input change freq
  PORTD |= (1 << PD6); // enable pull-up resistor

  // setari initiale pentru led-uri
  PORTD &= ~(1 << PD7);
  PORTD |= (1 << PD5);
  PORTB |= (1 << PB3);

  int blink = 0;
  int blink_state = 0;
  // culoare activa initial // 0 verde 1 rosu 2 albastru
  char active = 0;

  // status butoane
  char clicked1 = 0;
  char clicked2 = 0;

  while (1)
  {
    char button1 = ((PINB & (1 << PB2)) == 0);
    char button2 = ((PIND & (1 << PD6)) == 0);

    // daca butonul e apasat
    if (!clicked1 && button1)
    {
      clicked1 = 1;
      if (active == 0)
      {
        active = 1;
        PORTD &= ~(1 << PD5); // pornim rosu
        PORTD |= (1 << PD7);  // oprim verde
      }
      else if (active == 1)
      {
        active = 2;
        PORTD |= (1 << PD5);  // oprim rosu
        PORTB &= ~(1 << PB3); // pornim blue
      }
      else if (active == 2)
      {
        active = 0;
        PORTB |= (1 << PB3);  // oprim blue
        PORTD &= ~(1 << PD7); // pornim verde
      }
    }
    else if (clicked1 && !button1)
    {
      clicked1 = 0;
    }

    if (!clicked2 && button2)
    {
      blink = 1 - blink;
      clicked2 = 1;
    }
    else if (clicked2 && !button2)
    {
      clicked2 = 0;
    }

    if (blink && blink_state == 1)
    {

      blink_state = 0;

      PORTB |= (1 << PB3); // oprim blue
      PORTD |= (1 << PD7); // oprim verde
      PORTD |= (1 << PD5); // oprim rosu
    }
    else
    {
      blink_state = 1;

      if (active == 0)
      {
        PORTD &= ~(1 << PD7);
      }
      else if (active == 1)
      {
        PORTD &= ~(1 << PD5);
      }
      else if (active == 2)
      {
        PORTB &= ~(1 << PB3);
      }
    }

    _delay_ms(100);
  }

  return;
}