#include "Variables.h"
#include "Utils.h"
#include <Servo.h>
#include <LiquidCrystal.h>

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

Servo master_servo;

LiquidCrystal master_lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
uint8_t seconds_to_start = 3;

uint8_t to_send_to_slave = 0;
uint8_t received_from_slave = 0;
