#include <avr/io.h>
#include <util/delay.h>
#include "spi.h"

void SPI_init()
{

	/* TODO1: set MOSI and SCK output, all others input */
	DDRB = (1 << PB5) | (1 << PB7);
	/* TODO1: set SS PIN as output and set it on HIGH */
	DDRB |= (1 << PB4);
	PORTB |= (1 << PB4);

	/* TODO1: enable SPI, set it as Master, set clock rate at fosc/16 */
	SPCR0 = (1 << SPE0) | (1 << MSTR0) | (1 << SPR00);
}

uint8_t SPI_exchange(uint8_t data)
{
	// TODO1: send a byte of data to the slave and return the response byte received from him in this transmission
	SPDR0 = data;
	loop_until_bit_is_set(SPSR0, SPIF0);
	return SPDR0;
}
