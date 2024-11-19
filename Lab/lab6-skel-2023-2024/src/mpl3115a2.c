/**
 *  mpl3115a2.c - MPL3115A2 library for ATMega324P
 *  Datasheet: https://www.nxp.com/docs/en/data-sheet/MPL3115A2.pdf
 */

#include "mpl3115a2.h"
#include <util/delay.h>

void mpl3115a2_init(void)
{
    // Initialize MPL3115A2 with altimetry and wait for data to be ready
    twi_start();
    twi_write(MPL3115A2_ADDRESS << 1);
    twi_write(MPL3115A2_PT_DATA_CFG);
    twi_write(0x07);

    twi_start();
    twi_write(MPL3115A2_ADDRESS << 1);
    twi_write(MPL3115A2_CTRL_REG1);
    twi_write(0x39);
}

void mpl3115a2_read_temperature(int8_t *temperature)
{
    twi_start();
    twi_write(MPL3115A2_ADDRESS << 1);
    twi_write(MPL3115A2_STATUS);

    twi_start();
    twi_write((MPL3115A2_ADDRESS << 1) | 0x01);

    // Wait for data ready.
    uint8_t sta = 0x00;
    while (!(sta & 0x08))
    {
        twi_read_ack(&sta);
    }
    twi_read_nack(&sta);

    // TODO 3.1: stop I2C transaction
    twi_stop();
    // TODO 3.2: Read the temperature from the sensor
    twi_start();

    *temperature = 0x00;

    twi_write((MPL3115A2_ADDRESS << 1));

    twi_write(MPL3115A2_T_MSB);

    twi_start();

    twi_write((MPL3115A2_ADDRESS << 1) | 0x01);

    twi_read_nack((uint8_t *)temperature);

    twi_stop();
}
void mpl3115a2_read_pressure(uint32_t *pressure)
{
}