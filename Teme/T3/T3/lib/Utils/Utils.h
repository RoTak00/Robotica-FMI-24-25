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

#define ACK (1 << 6)
#define END (1 << 7)
#define SPI_SLAVE_TRANSMIT (1 << 5)

#define GAME_STATE_IDLE (1 << 0)
#define GAME_STATE_STARTING (1 << 4)
#define GAME_STATE_PLAYING (1 << 1)

#define PLAYER_1 0
#define PLAYER_2 1

#define MASTER_BUTTON_START 2

#define BUTTON_DEBOUNCE_START 100
#define STARTING_DELAY 3000

#define PLAY_MAX_TIME 10000

#define MAX_PLAYER_REACTION 2000

#define LIMIT_PLAYER_REACTION 5000
#define MIN_SCORE 200

#define SERVO_ANGLE ((int)(((float)(millis() - game_current_state_start_time) / (float)PLAY_MAX_TIME) * 180))
#define SERVO_PIN 3

#define LCD_RS 9
#define LCD_EN 8
#define LCD_D7 7
#define LCD_D6 6
#define LCD_D5 5
#define LCD_D4 4

#define die() exit(1)

void printByte(uint8_t b);

#endif