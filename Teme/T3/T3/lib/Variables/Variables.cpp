#include "Variables.h"

// Define the variables here
uint8_t game_state = 0;

uint64_t start_button_last_debounce_time = 0;
uint8_t start_button_state = LOW;
uint8_t start_button_last_state = HIGH;
uint8_t start_button_action = LOW;

uint64_t game_current_state_start_time = 0;
uint64_t game_player_receive_button_start_time = 0;

uint32_t player_1_score = 0;
uint32_t player_2_score = 0;

uint8_t current_player = 0;