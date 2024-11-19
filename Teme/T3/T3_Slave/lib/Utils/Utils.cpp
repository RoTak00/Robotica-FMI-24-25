#include <Utils.h>
#include <Variables.h>
#include <Arduino.h>
#include <SPI.h>

void initSerial()
{
    Serial.begin(9600);
}

void initButtons()
{
    pinMode(PLAYER0_Buttons, INPUT);
    pinMode(PLAYER1_Buttons, INPUT);
}

void initLEDs()
{
    // player 0
    pinMode(PLAYER0_Blue, OUTPUT);
    pinMode(PLAYER0_Yellow, OUTPUT);
    pinMode(PLAYER0_Red, OUTPUT);
    pinMode(PLAYER0_R, OUTPUT);
    pinMode(PLAYER0_G, OUTPUT);
    pinMode(PLAYER0_B, OUTPUT);

    // player 1
    pinMode(PLAYER1_Blue, OUTPUT);
    pinMode(PLAYER1_Yellow, OUTPUT);
    pinMode(PLAYER1_Red, OUTPUT);
    pinMode(PLAYER1_R, OUTPUT);
    pinMode(PLAYER1_G, OUTPUT);
    pinMode(PLAYER1_B, OUTPUT);
}

uint8_t colorAnalog(int analogValue)
{
    if (analogValue < NO_BTN_LIMIT)
        return NO_BTN;
    if (analogValue < BTN_RED_LIMIT)
        return BTN_RED;
    if (analogValue < BTN_YELLOW_LIMIT)
        return BTN_YELLOW;
    if (analogValue < BTN_BLUE_LIMIT)
        return BTN_BLUE;
    return INCORRECT;
}

void initSPISlave()
{
    pinMode(MISO, OUTPUT);
    SPCR |= _BV(SPE);
    SPI.attachInterrupt();
}