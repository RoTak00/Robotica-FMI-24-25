#include <Arduino.h>

#define LED1 10
#define LED2 9
#define LED3 8
#define LED4 7

// Din ceva motiv, LED-ul meu RGB are pinii
// RED -> COMMON (-) -> BLUE -> GREEN
#define RGB_RED 6
#define RGB_GREEN 4
#define RGB_BLUE 5

#define BTN_START 3
#define BTN_STOP 2

// Timp debounce pentru butonul de start si butonul de stop
#define DEBOUNCE_START_DELAY 50
#define DEBOUNCE_STOP_DELAY 1000

// Durata incarcarii unui LED
#define CHARGE_TIME_PER_LED 3000
// Durata blink-ului unui LED in starea CHARGING
#define BLINK_PER_LED 300
// Numarul de LED-uri de charging
#define NO_CHARGING_LEDS 4
// Durata blink-ului unui LED in starea ENDING
#define ENDING_BLINK_PER_LED 500
// Dupa cate blink-uri se termina starea ENDING
#define ENDING_BLINKS 3

enum StationState
{
  FREE,
  CHARGING,
  ENDING
};

StationState state = FREE;

// buttons
char start_button_action = false;
char stop_button_action = false;

int start_button_state = LOW;
int start_button_last_state = HIGH;
unsigned long start_button_last_debounce_time;

int stop_button_state = LOW;
int stop_button_last_state = HIGH;
unsigned long stop_button_last_debounce_time;
// end buttons

// Charging state
unsigned int charging_time_elapsed = 0;
unsigned int charging_start_time = 0;
unsigned short current_charging_led = 0;
// Helper folosit pentru starea led-urilor (par si impar)
unsigned short current_charging_blink_helper = 0;

// Ending state
unsigned int ending_time_elapsed = 0;
unsigned int ending_start_time = 0;
unsigned short ending_blink_helper = 0;

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);

  pinMode(BTN_START, INPUT);
  pinMode(BTN_STOP, INPUT);

  start_button_last_debounce_time = millis();
  stop_button_last_debounce_time = millis();
}

void loop()
{
  /* DEBOUNCING PRELUAT DIN
  https://deepbluembedded.com/arduino-button-debouncing/
  */

  start_button_action = false;
  stop_button_action = false;

  // BUTON START
  int start_input = digitalRead(BTN_START);
  // If the switch changed, due to noise or pressing:
  if (start_input != start_button_last_state)
  {
    // reset the debouncing timer
    start_button_last_debounce_time = millis();
  }

  if ((millis() - start_button_last_debounce_time) > DEBOUNCE_START_DELAY)
  {

    // if the button state has changed:
    if (start_input != start_button_state)
    {
      start_button_state = start_input;
      // only toggle the LED if the new button state is HIGH
      if (start_button_state == LOW)
      {
        start_button_action = true;
      }
    }
  }
  start_button_last_state = start_input;

  // END BUTON START

  // BUTON STOP
  int stop_input = digitalRead(BTN_STOP);
  // If the switch changed, due to noise or pressing:
  if (stop_input != stop_button_last_state)
  {
    // reset the debouncing timer
    stop_button_last_debounce_time = millis();
  }

  if ((millis() - stop_button_last_debounce_time) > DEBOUNCE_STOP_DELAY)
  {

    // if the button state has changed:
    if (stop_input != stop_button_state)
    {
      stop_button_state = stop_input;
      // only toggle the LED if the new button state is HIGH
      if (stop_button_state == LOW)
      {
        stop_button_action = true;
      }
    }
  }
  stop_button_last_state = stop_input;

  // END BUTON stop

  if (state == FREE)
  {
    // LED-uri incarcare oprite
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);

    // led RGB verde
    digitalWrite(RGB_GREEN, HIGH);
    digitalWrite(RGB_RED, LOW);
    digitalWrite(RGB_BLUE, LOW);

    // daca e apasat butonul de start,
    // trecem in CHARGING
    if (start_button_action == true)
    {
      state = CHARGING;
      charging_start_time = millis();
      current_charging_led = 0;
      current_charging_blink_helper = 0;

      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);

      digitalWrite(RGB_GREEN, LOW);
      digitalWrite(RGB_RED, HIGH);
      digitalWrite(RGB_BLUE, LOW);
    }
  }
  else if (state == CHARGING)
  {
    // verificam cat timp a trecut de la
    // inceputul incarcarii
    charging_time_elapsed = millis() - charging_start_time;

    // la fiecare 3 secunde
    if (charging_time_elapsed > CHARGE_TIME_PER_LED * (current_charging_led + 1))
    {
      digitalWrite(LED1 - current_charging_led, HIGH);
      current_charging_led += 1;
    }

    // pe baza helper-ului stim cand trebuie sa clipeasca
    // led-ul activ
    if (charging_time_elapsed > BLINK_PER_LED * current_charging_blink_helper)
    {
      // LED1 - current_charging_led este led-ul curent
      // Does not work in C probably
      digitalWrite(LED1 - current_charging_led, (current_charging_blink_helper % 2) ? HIGH : LOW);
      current_charging_blink_helper += 1;
    }

    // daca toate cele 4 led-uri au fost incarcate,
    // trecem in animatia de ending
    if (current_charging_led == NO_CHARGING_LEDS || (stop_button_action == true && charging_time_elapsed > DEBOUNCE_STOP_DELAY))
    {
      state = ENDING;
      ending_time_elapsed = 0;
      ending_start_time = millis();
      ending_blink_helper = 0;

      digitalWrite(RGB_GREEN, LOW);
      digitalWrite(RGB_RED, HIGH);
      digitalWrite(RGB_BLUE, LOW);
    }
  }
  else if (state == ENDING)
  {
    ending_time_elapsed = millis() - ending_start_time;

    if (ending_time_elapsed > ENDING_BLINK_PER_LED * ending_blink_helper)
    {
      short int to_write = ending_blink_helper % 2 ? HIGH : LOW;
      digitalWrite(LED1, to_write);
      digitalWrite(LED2, to_write);
      digitalWrite(LED3, to_write);
      digitalWrite(LED4, to_write);

      ending_blink_helper += 1;
    }

    // un blink inseamna blink on + blink off (deci 2*500ms)
    if (ending_blink_helper > ENDING_BLINKS * 2)
    {
      state = FREE;

      digitalWrite(RGB_GREEN, HIGH);
      digitalWrite(RGB_RED, LOW);
      digitalWrite(RGB_BLUE, LOW);
    }
  }
}
