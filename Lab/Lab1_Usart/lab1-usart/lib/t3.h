#ifndef T3_H
#define T3_H

#define MORSE_LUNG  3
#define MORSE_SCURT 1


#include <util/delay.h>
#include <usart.c>
#include <avr/io.h>

#define CLOCK_SPEED 12000000
#define BAUD 28800
#define MYUBRR CLOCK_SPEED/16/BAUD-1

#define BUFFER_LEN 64

/* Literele alfabetului in cod Morse */
char* morse_alphabet[] = {
    (char*)"13",    // a
    (char*)"3111",  // b
    (char*)"3131",  // c
    (char*)"311",   // d
    (char*)"1",     // e
    (char*)"1131",  // f
    (char*)"331",	// g
    (char*)"1111",	// h
    (char*)"11",	// i
    (char*)"1333",	// j
    (char*)"313",	// k
    (char*)"1311",	// l
    (char*)"33",	// m
    (char*)"31",	// n
    (char*)"333",	// o
    (char*)"1331",	// p
    (char*)"3313",	// q
    (char*)"131",	// r
    (char*)"111",	// s
    (char*)"3",	    // t
    (char*)"113",	// u
    (char*)"1113",	// v
    (char*)"133",	// w
    (char*)"3113",	// x
    (char*)"3133",	// y
    (char*)"3311"	// z
};

/* apelati functia pentru a obtine un ton lung/scurt,
 * folosind macro-urile MORSE_LUNG si MORSE_SCURT
 */
void speaker_morse(int tip)
{
    int delay = 1;
    int i;
    DDRD |= (1 << PD4);     // PD4 trebuie sa fie output

    for (i = 0; i < tip * 50 / delay; i++)
    {
        PIND = (1 << PD4);  // alternam starea iesirii
        _delay_ms(1);
    }
}


int t3()
{
    USART0_init(MYUBRR);

  char command_buffer[BUFFER_LEN] = {0};

  uint8_t read_index = 0;
  USART0_print("Enter a name: \n");

  while(1)
  {
    command_buffer[read_index] = USART0_receive();

    if(command_buffer[read_index] == '\n')
    {   
        command_buffer[read_index] = '\0';
        command_buffer[read_index - 1] = '\0';

        for (int m_index = 0; command_buffer[m_index] != '\0'; m_index++)
        {
            int c = command_buffer[m_index] - 'a';

            if(c < 0 || c > 25)
                continue;

            for (int i = 0; morse_alphabet[c][i] != '\0'; i++)
            {
                if(morse_alphabet[c][i] == '1')
                    speaker_morse(MORSE_LUNG);
                else
                    speaker_morse(MORSE_SCURT);

                _delay_ms(100);
            }

            _delay_ms(500);

        }

        read_index = 0;
        for(int i = 0; i < BUFFER_LEN; i++)
        {
            command_buffer[i] = '\0';
        }
    }
    else 
    {
        read_index = (read_index + 1) % BUFFER_LEN;
    }
  }
    
}

#endif