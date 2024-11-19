#include <Variables.h>
#include <Game.h>
#include <Arduino.h>
#include <Utils.h>
#include <SPI.h>

void whileGameIdle()
{
    // Read the start button with debouncing
    int button_start_input = digitalRead(MASTER_BUTTON_START);

    if (button_start_input != start_button_last_state)
    {
        start_button_last_debounce_time = millis();
    }

    if ((millis() - start_button_last_debounce_time) > BUTTON_DEBOUNCE_START)
    {
        if (button_start_input != start_button_state)
        {
            start_button_state = button_start_input;
            if (start_button_state == LOW)
            {
                start_button_action = true;
            }
        }
    }
    start_button_last_state = button_start_input;

    // If the start button is pressed
    if (start_button_action)
    {

        // Move game to starting state
        game_state = GAME_STATE_STARTING;
        game_current_state_start_time = millis();
        seconds_to_start = 3;

        // Print Starting state on LCD
        master_lcd.clear();
        master_lcd.setCursor(0, 0);
        master_lcd.print("Get Ready!");
        master_lcd.setCursor(0, 1);
        master_lcd.print("Starting in ");
        master_lcd.setCursor(13, 1);
        master_lcd.print(seconds_to_start);

        // Reset player scores
        current_player = 0;
        player_1_score = 0;
        player_2_score = 0;
    }
}

void whileGameStarting()
{
    // Every second, update the remaining seconds to start
    if (millis() - game_current_state_start_time > 1000 * (3 - seconds_to_start + 1))
    {
        master_lcd.setCursor(13, 1);
        master_lcd.print(--seconds_to_start);
    }

    // If the starting delay is over
    if (millis() - game_current_state_start_time > STARTING_DELAY)
    {
        game_state = GAME_STATE_PLAYING;
        game_current_state_start_time = millis();

        // Reset values and determine random starting player
        player_1_score = 0;
        player_2_score = 0;
        to_send_to_slave = 0;
        received_from_slave = 0;
        current_player = random(0, 2);

        master_servo.write(0);
    }
}

void whileGamePlaying()
{
    // Daca este necesar sa trimitem din nou date catre slave
    if (received_from_slave == 0 && to_send_to_slave == 0)
    {
        if (current_player == PLAYER_1)
        {
            to_send_to_slave |= BTN_PLAYER_1;
        }
        else
        {
            to_send_to_slave |= BTN_PLAYER_2;
        }

        // Determinam cu random culoarea care trebuie apasata
        uint8_t led_to_activate = random(0, 3); // 0 red // 1 yellow // 2 blue

        if (led_to_activate == 0)
        {
            to_send_to_slave |= BTN_RED;
        }
        else if (led_to_activate == 1)
        {
            to_send_to_slave |= BTN_YELLOW;
        }
        else
        {
            to_send_to_slave |= BTN_BLUE;
        }

        // Trimitem datele catre slave
        digitalWrite(SS, LOW);
        received_from_slave = SPI.transfer(to_send_to_slave);
        digitalWrite(SS, HIGH);

        // Salvam timpul de start pentru calculul scorului
        game_player_receive_button_start_time = millis();
    }
    // Daca am primit un raspuns de la slave
    else if ((received_from_slave & SPI_SLAVE_TRANSMIT) == SPI_SLAVE_TRANSMIT)
    {
        // Verificam daca butonul apasat este cel pe care l-am trimis initial
        if (received_from_slave == (to_send_to_slave | SPI_SLAVE_TRANSMIT))
        {
            // Jucatorul primeste scor bazat pe timpul de reactie, max 2 secunde
            uint16_t player_press_delay = millis() - game_player_receive_button_start_time;

            // pe baza astuia calculam scor
            if (current_player == PLAYER_1)
            {
                if (player_press_delay > MAX_PLAYER_REACTION - MIN_SCORE)
                {
                    player_1_score += MIN_SCORE;
                }
                else
                {
                    player_1_score += (MAX_PLAYER_REACTION - player_press_delay);
                }
            }
            else
            {
                if (player_press_delay > MAX_PLAYER_REACTION - MIN_SCORE)
                {
                    player_2_score += MIN_SCORE;
                }
                else
                {
                    player_2_score += (MAX_PLAYER_REACTION - player_press_delay);
                }
            }
        }

        // Afisam scorul curent pe LCD (actualizat)
        writeScoreLCD(player_1_score, player_2_score, 0);

        // Actualizam jucatorul
        current_player = !current_player;

        // Resetam datele trimise / primite
        to_send_to_slave = 0;
        received_from_slave = 0;
    }
    else
    {
        // Nu am primit date relevante de la slave, facem polling la fiecare 10 ms
        _delay_ms(10);

        digitalWrite(SS, LOW);
        received_from_slave = SPI.transfer(ACK);

        digitalWrite(SS, HIGH);

        // Daca au trecut LIMIT_PLAYER_REACTION secunde, trecem la urmatorul jucator
        if (millis() - game_player_receive_button_start_time > LIMIT_PLAYER_REACTION)
        {
            received_from_slave = 0;
            to_send_to_slave = 0;

            current_player = !current_player;
        }
    }

    // Rotim servomotorul
    master_servo.write(SERVO_ANGLE);

    // Verificam daca jocul s-a incheiat
    if (millis() - game_current_state_start_time > PLAY_MAX_TIME)
    {
        game_state = GAME_STATE_IDLE;
        start_button_last_debounce_time = 0;
        start_button_state = LOW;
        start_button_last_state = HIGH;
        start_button_action = LOW;

        writeScoreLCD(player_1_score, player_2_score, 1);

        digitalWrite(SS, LOW);
        SPI.transfer(END);
        digitalWrite(SS, HIGH);

        master_servo.write(0);
    }
}

void writeScoreLCD(uint32_t player_1_score, uint32_t player_2_score, uint8_t with_winner)
{
    master_lcd.clear();
    master_lcd.setCursor(0, 0);
    if (with_winner)
    {
        if (player_1_score > player_2_score)
            master_lcd.print("(W) P 1: ");
        else
            master_lcd.print("(L) P 1: ");

        master_lcd.setCursor(9, 0);
    }
    else
    {
        master_lcd.print("P 1: ");
        master_lcd.setCursor(5, 0);
    }
    master_lcd.print(player_1_score);

    master_lcd.setCursor(0, 1);
    if (with_winner)
    {
        if (player_1_score > player_2_score)
            master_lcd.print("(L) P 2: ");
        else
            master_lcd.print("(W) P 2: ");

        master_lcd.setCursor(9, 1);
    }
    else
    {
        master_lcd.print("P 2: ");
        master_lcd.setCursor(5, 1);
    }
    master_lcd.print(player_2_score);
}
