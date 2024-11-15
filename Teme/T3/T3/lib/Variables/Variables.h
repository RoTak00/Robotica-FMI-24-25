#ifndef LIB_VARIABLES
#define LIB_VARIABLES

#include <Arduino.h>

// Initial values
extern uint8_t game_state;

extern uint64_t start_button_last_debounce_time;
extern uint8_t start_button_state;
extern uint8_t start_button_last_state;
extern uint8_t start_button_action;

extern uint64_t game_current_state_start_time;
extern uint64_t game_player_receive_button_start_time;
extern uint8_t current_player;

extern uint32_t player_1_score;
extern uint32_t player_2_score;

#endif