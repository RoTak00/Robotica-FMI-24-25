#include <string.h>
#include <stdio.h>

#include <util/delay.h>
#include <avr/io.h>

#include "usart.h"
#include "mpl3115a2.h"
#include "twi.h"

#define PM_BAUD 9600

int main222()
{
	// Initialize USART for writing to serial console.
	USART0_init(CALC_USART_UBRR(PM_BAUD));
	USART0_use_stdio();

	// TODO 2: Initialize I2C (including GPIO)
	twi_init();

	// TODO 2: Search all slaves with adresses within range 0x00-0x7F
	twi_discover();

	// TODO 3.1: Initialize TWI and MPL3115A2 sensor.

	mpl3115a2_init();

	while (1)
	{
		int8_t temp;
		mpl3115a2_read_temperature(&temp);
		USART0_print("Temperature: ");
		char temp_str[6];
		sprintf(temp_str, "%d", temp);
		USART0_print(temp_str);
		USART0_print("\n");
		// mpl3115a2_read_pressure(TODO);
		// mpl3115a2_read_temperature(TODO);

		// TODO 3.2: Read temperature and pressure using the MPL3115A2 driver
		_delay_ms(1000);
	}

	return 0;
}
