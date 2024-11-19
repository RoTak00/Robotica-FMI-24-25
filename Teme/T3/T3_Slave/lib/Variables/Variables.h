#ifndef LIB_VARIABLES
#define LIB_VARIABLES

#include <Arduino.h>

#define NO_BTN 0
#define INCORRECT 0xFF
#define BTN_BLUE (1 << 2)
#define BTN_YELLOW (1 << 1)
#define BTN_RED (1 << 0)
#define NO_BTN_LIMIT 100
#define BTN_RED_LIMIT 200
#define BTN_YELLOW_LIMIT 350
#define BTN_BLUE_LIMIT 750

#define NOT_PLAYING 2

extern uint64_t player0_button_last_debounce_time;
extern uint8_t player0_button_state;
extern uint8_t player0_button_last_state;

extern uint64_t player1_button_last_debounce_time;
extern uint8_t player1_button_state;
extern uint8_t player1_button_last_state;

extern uint8_t player;
extern uint64_t timer;

#endif