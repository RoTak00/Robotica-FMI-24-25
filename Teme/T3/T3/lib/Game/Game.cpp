#include <Variables.h>
#include <Game.h>
#include <Arduino.h>
#include <Utils.h>
#include <SPI.h>

void whileGameIdle()
{

    int button_start_input = digitalRead(MASTER_BUTTON_START);
    // If the switch changed, due to noise or pressing:
    if (button_start_input != start_button_last_state)
    {
        // reset the debouncing timer
        start_button_last_debounce_time = millis();
    }

    if ((millis() - start_button_last_debounce_time) > BUTTON_DEBOUNCE_START)
    {
        // if the button state has changed:
        if (button_start_input != start_button_state)
        {
            start_button_state = button_start_input;
            // only toggle the LED if the new button state is HIGH
            if (start_button_state == LOW)
            {
                start_button_action = true;
            }
        }
    }
    start_button_last_state = button_start_input;

    if (start_button_action)
    {

        game_state = GAME_STATE_STARTING;
        game_current_state_start_time = millis();

        current_player = 0;
        player_1_score = 0;
        player_2_score = 0;

        SPI.transfer(HELLO);
    }
}

void whileGameStarting()
{

    if (millis() - game_current_state_start_time > STARTING_DELAY)
    {
        game_state = GAME_STATE_PLAYING;
        game_current_state_start_time = millis();
    }
}

void whileGamePlaying()
{
    uint8_t to_send_to_slave = 0;
    uint8_t received_from_slave = 0;

    if (current_player == PLAYER_1)
    {
        to_send_to_slave |= BTN_PLAYER_1;
    }
    else
    {
        to_send_to_slave |= BTN_PLAYER_2;
    }

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

    received_from_slave = SPI.transfer(to_send_to_slave);

    if (received_from_slave != ACK)
    {
        // something went wrong
        die();
    }
    game_player_receive_button_start_time = millis();

    received_from_slave = SPI.transfer(ACK);

    if (received_from_slave == to_send_to_slave)
    {
        // calculate score based on time
        uint16_t player_press_delay = millis() - game_player_receive_button_start_time;

        // pe baza astuia calculam scor
        if (current_player == PLAYER_1)
        {
            player_1_score += max((2000 - player_press_delay), 200);
        }
        else
        {
            player_2_score += max((2000 - player_press_delay), 200);
        }
    }

    current_player = !current_player;

    if (millis() - game_current_state_start_time > PLAY_MAX_TIME)
    {
        game_state = GAME_STATE_IDLE;
        Serial.println("Game ended");
        Serial.print("Player 1 score: ");
        Serial.println(player_1_score);
        Serial.print("Player 2 score: ");
        Serial.println(player_2_score);
    }
}
