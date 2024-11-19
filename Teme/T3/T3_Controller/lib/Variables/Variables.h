#ifndef LIB_VARIABLES
#define LIB_VARIABLES

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal.h>

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

extern Servo master_servo;

extern uint8_t to_send_to_slave;
extern uint8_t received_from_slave;

extern LiquidCrystal master_lcd;
extern uint8_t seconds_to_start;

#endif