#include <avr/io.h>
#include <util/delay.h>

void ex2()
{
  DDRD |= (1 << PD5);
  
PORTD &= ~(1 << PD5);
  

  return;
}