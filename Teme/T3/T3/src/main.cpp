#include <Variables.h>
#include <Utils.h>
#include <Game.h>
#include <Arduino.h>
#include <SPI.h>

void setup()
{
  initSerial();
  initSPIMaster();
  initButtons();
  initServo();
  initLCD();
  initVars();
}

void loop()
{
  switch (game_state)
  {
  case GAME_STATE_IDLE:
    whileGameIdle();
    break;
  case GAME_STATE_STARTING:
    whileGameStarting();
    break;
  case GAME_STATE_PLAYING:
    whileGamePlaying();
    break;
  }
}
