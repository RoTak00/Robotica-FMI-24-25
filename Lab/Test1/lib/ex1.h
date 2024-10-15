#include <avr/io.h>
#include <util/delay.h>

void ex1()
{
  /* Setăm pinul 7 al portului D ca pin de ieșire. */
  DDRD |= (1 << PD7);

  while (1)
  {
    /* Inversăm starea pinului. */
    PORTD ^= (1 << PD7);
    _delay_ms(500);
  }

  return;
}