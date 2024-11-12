#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart.h"
#include "timers.h"

/* Configuration constants: */
#define PM_BAUD 28800

#define RGB_PULSE 1
#define RGB_HSV 2

#define LED_ANIMATION RGB_PULSE
#define SPEAKER_ENABLED 0

/**
 * Initialize the GPIOs of LEDs / speaker etc.
 */
int GPIO_init()
{
    /* RGB led directions & default PORTs to 1 (OFF state) */
    DDRB |= (1 << PB3);
    DDRD |= (1 << PD5) | (1 << PD7);
    PORTB |= (1 << PB3);
    PORTD |= (1 << PD5) | (1 << PD7);
    return 0;
}

int main()
{
    /* initialize peripheral modules: */
    GPIO_init();
    USART0_init(CALC_USART_UBRR(PM_BAUD));
    USART0_use_stdio();

    if (SPEAKER_ENABLED)
    {
        Timer1_init_ctc();
    }
    else
    {
        Timer0_init_pwm();
        Timer1_init_pwm();
    }
    Timer2_init_systicks();
    /* TODO add more *_init_*() calls here? */

    sei(); /* activate global interrupts */

    printf("It's timer hammer!\n");

    uint32_t last_ping = 0;

    while (1)
    {
        /* Print alive message */
        if (SYSTICKS_PASSED(last_ping, 3000))
        {
            last_ping = systicks;
            printf("Stayin' alive! [ticks=%i]\n", systicks);
        }
        if (LED_ANIMATION == RGB_PULSE)
        {
            /*
             * Pulse de LEDs based on a triangle wave:
             * y = (P - abs(t % (2*P) - P) )
             * Note: outputs values between [0, 3000]!
             */
            int wave_red = (3000 - abs(((unsigned long long)systicks % 6000) - 3000));

            int wave_blue = (3000 - abs(((unsigned long long)(systicks * 2) % 6000) - 3000));
            /* rescale [0, 3000] to [0, 255] using ceil(3000 / 255) */
            OCR1A = (wave_red / 12);

            /* TODO task 1 & 2: do the same for other LEDs */

            OCR0A = (wave_blue / 12);
        }
        else if (LED_ANIMATION == RGB_HSV)
        {
            /* TODO task 3: output all different Hue colors */
        }
        if (SPEAKER_ENABLED)
        {
            /* TODO task 4 (bonus): you know what you have to do ;) */
        }
    }

    return 0;
}
