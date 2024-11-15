#ifndef LIB_UTILS
#define LIB_UTILS

#include <Arduino.h>

void initSerial();
void initSPIMaster();
void initSPISlave();
void initButtons();
void initServo();
void initLCD();
void initVars();

#define BTN_PLAYER_1 (1 << 0)
#define BTN_PLAYER_2 (1 << 1)
#define BTN_RED (1 << 2)
#define BTN_YELLOW (1 << 3)
#define BTN_BLUE (1 << 4)

#define AWAIT_RECEIVE (1 << 5)
#define ACK (1 << 6)
#define HELLO (1 << 7)

#define GAME_STATE_IDLE (1 << 0)
#define GAME_STATE_STARTING (1 << 4)
#define GAME_STATE_PLAYING (1 << 1)

#define PLAYER_1 0
#define PLAYER_2 1

#define MASTER_BUTTON_START 2

#define BUTTON_DEBOUNCE_START 100
#define STARTING_DELAY 3000

#define PLAY_MAX_TIME 15000

#define SERVO_ANGLE (((millis() - game_current_state_start_time) / PLAY_MAX_TIME) * 180)

#define die() exit(1)

#endif