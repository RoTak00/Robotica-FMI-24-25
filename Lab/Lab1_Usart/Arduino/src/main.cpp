#include <Arduino.h>

#define LED_BLUE 3
#define LED_GREEN 15
#define LED_RED 13

#define BTN_PB2 2

void setup()
{
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  pinMode(BTN_PB2, INPUT_PULLUP);

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_GREEN, LOW);

  Serial.begin(28800);
}

void loop()
{
  char command = Serial.read();

  if (command == '1')
  {

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, LOW);
  }
  else if (command == '0')
  {

    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_GREEN, HIGH);
  }
  else if (command == 'r')
  {

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_GREEN, HIGH);
  }
  else if (command == 'g')
  {

    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_GREEN, LOW);
  }

  else if (command == 'b')
  {

    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_GREEN, HIGH);
  }
  delay(100);
}
