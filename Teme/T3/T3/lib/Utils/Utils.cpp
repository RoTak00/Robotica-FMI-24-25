
#include <Utils.h>
#include <Variables.h>
#include <Arduino.h>
#include <SPI.h>

void initSerial()
{
    Serial.begin(9600);
}

void initSPIMaster()
{
    SPI.begin(); // Begins the SPI commnuication

    SPI.setClockDivider(SPI_CLOCK_DIV8); // Sets clock for SPI communication at 8 (16/8=2Mhz)

    digitalWrite(SS, HIGH);
}

void initSPISlave()
{
}

void initButtons()
{
    pinMode(MASTER_BUTTON_START, INPUT_PULLUP);

    start_button_last_debounce_time = millis();
}

void initServo()
{
}

void initLCD()
{
}

void initVars()
{
    randomSeed(analogRead(0));

    game_state = GAME_STATE_IDLE;
}