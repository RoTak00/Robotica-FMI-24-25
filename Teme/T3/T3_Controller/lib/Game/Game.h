#ifndef LIB_GAME
#define LIB_GAME

#include <Arduino.h>

void whileGameIdle();
void whileGameStarting();
void whileGamePlaying();

void writeScoreLCD(uint32_t player_1_score, uint32_t player_2_score, uint8_t with_winner);
#endif