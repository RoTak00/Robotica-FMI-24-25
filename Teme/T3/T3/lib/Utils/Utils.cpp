
#include <Utils.h>
#include <Variables.h>
#include <Arduino.h>
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal.h>

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
    master_servo.attach(SERVO_PIN);
}

void initLCD()
{

    master_lcd.begin(16, 2);
    master_lcd.clear();
    master_lcd.setCursor(0, 0);
    master_lcd.print("Welcome!");
    master_lcd.setCursor(0, 1);
    master_lcd.print("Press BTN start");

    master_lcd.noCursor();
}

void initVars()
{
    randomSeed(analogRead(0));

    game_state = GAME_STATE_IDLE;
}

void printByte(uint8_t b)
{
    Serial.println("BYTE START");
    if ((b & BTN_PLAYER_1) == BTN_PLAYER_1)
        Serial.println("BTN_PLAYER1");
    if ((b & BTN_PLAYER_2) == BTN_PLAYER_2)
        Serial.println("BTN_PLAYER2");
    if ((b & BTN_RED) == BTN_RED)
        Serial.println("BTN_RED");
    if ((b & BTN_YELLOW) == BTN_YELLOW)
        Serial.println("BTN_YELLOW");
    if ((b & BTN_BLUE) == BTN_BLUE)
        Serial.println("BTN_BLUE");

    if ((b & ACK) == ACK)
        Serial.println("ACK");
    if ((b & END) == END)
        Serial.println("END");
    if ((b & SPI_SLAVE_TRANSMIT) == SPI_SLAVE_TRANSMIT)
        Serial.println("SPI_SLAVE_TRANSMIT");

    Serial.println();
}