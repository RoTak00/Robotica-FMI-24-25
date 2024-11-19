#include "Variables.h"

// Define the variables here

uint64_t player0_button_last_debounce_time = 0;
uint8_t player0_button_state = NO_BTN;
uint8_t player0_button_last_state = INCORRECT;

uint64_t player1_button_last_debounce_time = 0;
uint8_t player1_button_state = NO_BTN;
uint8_t player1_button_last_state = INCORRECT;

uint64_t timer = 0;
uint8_t player = NOT_PLAYING;