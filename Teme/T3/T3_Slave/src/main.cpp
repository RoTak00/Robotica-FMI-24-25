#include <Arduino.h>
#include <SPI.h>
#include <Utils.h>
#include <Variables.h>


void setup() {
  initSerial();
  initButtons();
  initLEDs();
  initSPISlave();
}

byte slave_receive = 0, slave_send = 0, data_received = 0;

ISR(SPI_STC_vect)
{
  data_received = 1;
  slave_receive = SPDR;
}

void whilePlaying() {
  // player 0
  if (player == 0) {
    // citim butonul apasat de player 0
    uint8_t color0 = colorAnalog(analogRead(PLAYER0_Buttons));
    // initializam mesajul care trebuie transmis
    uint8_t send = SPI_SLAVE_TRANSMIT | SPI_BTN_PLAYER_0;

    // debouncing
    if (color0 != player0_button_last_state) 
    {
      player0_button_last_debounce_time = millis();
    }
    if ((millis() - player0_button_last_debounce_time) > BUTTON_DEBOUNCE_START)
    {
      if (color0 != player0_button_state)
      {
        player0_button_state = color0;
        // aprindem led speific fiecarui buton
        // setam bitul pentru fiecare culoare
        // trimitam raspuns masterului
        switch (color0)
        {
          case BTN_RED:
            digitalWrite(PLAYER0_Red, HIGH);
            digitalWrite(PLAYER0_Blue, LOW);
            digitalWrite(PLAYER0_Yellow, LOW);
            send |= SPI_BTN_RED;
            SPDR = send;
            break;
          case BTN_BLUE:
            digitalWrite(PLAYER0_Blue, HIGH);
            digitalWrite(PLAYER0_Red, LOW);
            digitalWrite(PLAYER0_Yellow, LOW);
            send |= SPI_BTN_BLUE;
            SPDR = send;
            break;
          case BTN_YELLOW:
            digitalWrite(PLAYER0_Blue, LOW);
            digitalWrite(PLAYER0_Red, LOW);
            digitalWrite(PLAYER0_Yellow, HIGH);
            send |= SPI_BTN_YELLOW;
            SPDR = send;
            break;
          default:
            break;
        }
        Serial.println(send);
      }
    }
    player0_button_last_state = color0;
  }

  //player 1
  if (player == 1) {
    uint8_t color1 = colorAnalog(analogRead(PLAYER1_Buttons));
    uint8_t send = SPI_SLAVE_TRANSMIT | SPI_BTN_PLAYER_1;
    if (color1 != player1_button_last_state) 
    {
      player1_button_last_debounce_time = millis();
    }
    if ((millis() - player1_button_last_debounce_time) > BUTTON_DEBOUNCE_START)
    {
      if (color1 != player1_button_state)
      {
        player1_button_state = color1;
        switch (color1)
        {
          case BTN_RED:
            digitalWrite(PLAYER1_Red, HIGH);
            digitalWrite(PLAYER1_Blue, LOW);
            digitalWrite(PLAYER1_Yellow, LOW);
            send |= SPI_BTN_RED;
            SPDR = send;
            break;
          case BTN_BLUE:
            digitalWrite(PLAYER1_Blue, HIGH);
            digitalWrite(PLAYER1_Red, LOW);
            digitalWrite(PLAYER1_Yellow, LOW);
            send |= SPI_BTN_BLUE;
            SPDR = send;
            break;
          case BTN_YELLOW:
            digitalWrite(PLAYER1_Blue, LOW);
            digitalWrite(PLAYER1_Red, LOW);
            digitalWrite(PLAYER1_Yellow, HIGH);
            send |= SPI_BTN_YELLOW;
            SPDR = send;
            break;
          default:
            break;
        }
        Serial.println(send);
      }
    }
    player1_button_last_state = color1;
  }
} 

void loop() {
  if(data_received)
  {
    SPDR = slave_receive;
    data_received = 0;
    // daca primim semnalul de done inseamna ca jocul s-a termina si inchidem toate ledurile
    if ((slave_receive & DONE) == DONE) {
      Serial.print(slave_receive);
      player = NOT_PLAYING;
      digitalWrite(PLAYER1_R, LOW);
      digitalWrite(PLAYER1_G, LOW);
      digitalWrite(PLAYER1_B, LOW);
      digitalWrite(PLAYER1_Blue, LOW);
      digitalWrite(PLAYER1_Yellow, LOW);
      digitalWrite(PLAYER1_Red, LOW);
      digitalWrite(PLAYER0_R, LOW);
      digitalWrite(PLAYER0_G, LOW);
      digitalWrite(PLAYER0_B, LOW);
      digitalWrite(PLAYER0_Blue, LOW);
      digitalWrite(PLAYER0_Yellow, LOW);
      digitalWrite(PLAYER0_Red, LOW);
    }

    if ((slave_receive & SPI_BTN_PLAYER_0) == SPI_BTN_PLAYER_0) {
      player = 0;
      // inchidem toate ledurile celuilalt jucator
      digitalWrite(PLAYER1_R, LOW);
      digitalWrite(PLAYER1_G, LOW);
      digitalWrite(PLAYER1_B, LOW);
      digitalWrite(PLAYER1_Blue, LOW);
      digitalWrite(PLAYER1_Yellow, LOW);
      digitalWrite(PLAYER1_Red, LOW);
      Serial.print("Player 0:");
      Serial.println(slave_receive);
      if ((slave_receive & SPI_BTN_BLUE) == SPI_BTN_BLUE) {
        digitalWrite(PLAYER0_B, HIGH);
        digitalWrite(PLAYER0_R, LOW);
        digitalWrite(PLAYER0_G, LOW);
      }
      if ((slave_receive & SPI_BTN_RED) == SPI_BTN_RED) {
        digitalWrite(PLAYER0_B, LOW);
        digitalWrite(PLAYER0_R, HIGH);
        digitalWrite(PLAYER0_G, LOW);
      }
      if ((slave_receive & SPI_BTN_YELLOW) == SPI_BTN_YELLOW) {
        digitalWrite(PLAYER0_B, LOW);
        digitalWrite(PLAYER0_R, HIGH);
        digitalWrite(PLAYER0_G, HIGH);
      }
    }
    if ((slave_receive & SPI_BTN_PLAYER_1) == SPI_BTN_PLAYER_1) {
      player = 1;
      // inchidem toate ledurile celuilalt jucator
      digitalWrite(PLAYER0_R, LOW);
      digitalWrite(PLAYER0_G, LOW);
      digitalWrite(PLAYER0_B, LOW);
      digitalWrite(PLAYER0_Blue, LOW);
      digitalWrite(PLAYER0_Yellow, LOW);
      digitalWrite(PLAYER0_Red, LOW);
      Serial.print("Player 1:");
      Serial.println(slave_receive);
      if ((slave_receive & SPI_BTN_BLUE) == SPI_BTN_BLUE) {
        digitalWrite(PLAYER1_B, HIGH);
        digitalWrite(PLAYER1_R, LOW);
        digitalWrite(PLAYER1_G, LOW);
      }
      if ((slave_receive & SPI_BTN_RED) == SPI_BTN_RED) {
        digitalWrite(PLAYER1_B, LOW);
        digitalWrite(PLAYER1_R, HIGH);
        digitalWrite(PLAYER1_G, LOW);
      }
      if ((slave_receive & SPI_BTN_YELLOW) == SPI_BTN_YELLOW) {
        digitalWrite(PLAYER1_B, LOW);
        digitalWrite(PLAYER1_R, HIGH);
        digitalWrite(PLAYER1_G, HIGH);
      }
    }
  }
  whilePlaying();
}
