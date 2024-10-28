#include <Arduino.h>

// function definitions

void initPins();
void initValues();
void initTimers();
void onGameFree();
void onGameRunning();
void onNewWord();
void onChangeFree();
void onChangeStarting();
void onChangeRunning();
void startStopInterrupt();
void difficultyInterrupt();
void ledOff();
void ledWhite();
void ledGreen();
void ledRed();
void onDifficultyChange();

// words
char *words[] = {
    "hello", "world", "arduino", "coding",
    "example", "function", "variable", "constant",
    "bicycle", "car", "motorcycle", "bus",
    "train", "plane", "ship", "boat",
    "muscle", "bone", "programming", "javascript",
    "python", "voltage", "operation", "temperature",
    "humidity", "shade", "dehydration", "plant"};

const int wordCount = 28;

// Pins
const int redPin = 10;
const int greenPin = 8;
const int bluePin = 9;
const int startStopPin = 2;
const int difficultyPin = 3;

// compare values
// pentru numararea din secunda in secunda
const int baseCompareMatch = 62500;
const int baudRate = 9600;

// Magic Numbers
const unsigned int debounceDelay = 500;
const unsigned int startingBlinkDuration = 500;
const unsigned int startingDuration = 3000;

const unsigned int gameTimer = 30;
const unsigned int easyTimer = 10;
const unsigned int mediumTimer = 5;
const unsigned int hardTimer = 2;

// Timer / Debouncing values
unsigned long lastStartStopInterruptTime = 0;
unsigned long lastDifficultyInterruptTime = 0;

volatile int wordAppearanceTimer = easyTimer;
volatile unsigned int gameRunningTimer = gameTimer;

// Button states
char startStopButtonPressed = false;
char difficultyButtonPressed = false;

// Interrupt states
char showNewWord = false;
char endGame = false;

// Strings
String chosenWord;
String guessedWord = "";
String inputBuffer = "";

// timers
unsigned long timer1 = 0;
unsigned long timeAtStartOfTimer1 = 0;

// Blink helpers
unsigned int blinkHelper1 = 0;

unsigned int guessedWordCount = 0;

enum state
{
  idle,
  starting,
  running
};

enum difficulty
{
  easy,
  medium,
  hard
};

state gameState;
difficulty gameDifficulty;

// Functii de initializare

void initPins()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(startStopPin, INPUT_PULLUP);
  pinMode(difficultyPin, INPUT_PULLUP);

  // Attach Interrupts to the 2 hardware interrupts
  attachInterrupt(digitalPinToInterrupt(startStopPin), startStopInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(difficultyPin), difficultyInterrupt, FALLING);

  Serial.begin(baudRate);
}

void initValues()
{
  // setam valori initiale
  onChangeFree();

  randomSeed(millis());
  Serial.println("Welcome to Arduino TypeRacer");
}

void initTimers()
{
  // pregatim interrupt-ul timer
  noInterrupts();

  // Initialize Timer1
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = baseCompareMatch;

  // Set prescaler to 256
  TCCR1B |= (1 << CS12);

  // Enable timer interrupt for compare mode
  TIMSK1 |= (1 << OCIE1A);

  // Enable all interrupts
  interrupts();
}

// Functi running

// Game is in the free state, taking Difficulty Change input
// and waiting for a start button press
void onGameFree()
{
  if (startStopButtonPressed)
  {
    onChangeStarting();
    Serial.println("\nStarting!");
    startStopButtonPressed = false;
  }

  if (difficultyButtonPressed)
  {
    onDifficultyChange();
    difficultyButtonPressed = false;
  }
}

// Game is starting, only allow stopping
void onGameStarting()
{
  // reset
  if (startStopButtonPressed)
  {
    Serial.println("\nGame aborted!");
    onChangeFree();
    startStopButtonPressed = false;
  }

  timer1 = millis() - timeAtStartOfTimer1;

  if (timer1 > startingBlinkDuration * blinkHelper1)
  {
    if (blinkHelper1 % 2 == 0)
    {
      ledWhite();
    }
    else
    {
      ledOff();
    }

    blinkHelper1 += 1;
  }

  if (timer1 > startingDuration)
  {

    Serial.println("\nGo!");
    onChangeRunning();
  }
}

void onGameRunning()
{
  // reset
  if (startStopButtonPressed)
  {
    Serial.println("\nGame aborted!");
    onChangeFree();
    startStopButtonPressed = false;
  }

  // Whenever we get a new word, show it
  if (showNewWord == true)
  {
    onNewWord();
    showNewWord = false;
  }

  // game ends when the timer runs out
  if (endGame == true)
  {
    Serial.println("Game over!");
    Serial.print("You have guessed ");
    Serial.print(guessedWordCount);
    Serial.println(" words correctly");
    onChangeFree();

    endGame = false;
  }

  // Check if there's any input
  if (inputBuffer.length() > 0)
  {
    char inputChar = inputBuffer.charAt(0); // Get the first character
    inputBuffer.remove(0, 1);               // Remove the first character from buffer

    // Check if it's a backspace
    if (inputChar == '\b' && guessedWord.length() > 0)
    {
      guessedWord.remove(guessedWord.length() - 1); // Remove last character from guessedWord

      if (chosenWord.startsWith(guessedWord))
      {
        ledGreen();
      }
      else
      {
        ledRed();
      }
    }
    // Check if it's an alphabetic character
    else if (isAlpha(inputChar))
    {
      inputChar = tolower(inputChar); // Convert to lowercase
      guessedWord += inputChar;

      if (guessedWord == chosenWord)
      {

        guessedWordCount += 1;
        Serial.println("\nCorrect!");
        showNewWord = true;
      }

      // Check if guessedWord is a prefix of chosenWord
      if (chosenWord.startsWith(guessedWord))
      {
        ledGreen();
      }
      else
      {
        ledRed();
      }
    }
  }
}

// Main functions
void setup()
{
  initPins();
  initValues();
  initTimers();
}

void loop()
{
  if (gameState == idle)
  {
    onGameFree();
  }
  else if (gameState == starting)
  {
    onGameStarting();
  }
  else if (gameState == running)
  {
    onGameRunning();
  }
}

// Interrupts and Events
ISR(TIMER1_COMPA_vect)
{

  if (gameState != running)
    return;

  wordAppearanceTimer -= 1;
  gameRunningTimer -= 1;

  if (wordAppearanceTimer <= 0)
  {
    showNewWord = true;
  }

  if (gameRunningTimer <= 0)
  {
    endGame = true;
  }
}

void serialEvent()
{
  while (Serial.available())
  {
    inputBuffer += (char)Serial.read(); // Add character to buffer
  }
}

void startStopInterrupt()
{
  unsigned long currentTime = millis();
  if (currentTime - lastStartStopInterruptTime > debounceDelay)
  {
    startStopButtonPressed = true;
    lastStartStopInterruptTime = currentTime;
  }
}

void difficultyInterrupt()
{
  // Dificultatea poate fi schimbata doar in idle
  if (gameState != idle)
    return;

  unsigned long currentTime = millis();
  if (currentTime - lastDifficultyInterruptTime > debounceDelay)
  {
    difficultyButtonPressed = true;
    lastDifficultyInterruptTime = currentTime;
  }
}

void onDifficultyChange()
{
  // Dificultatea poate fi modificata doar daca suntem in idle
  if (gameState != idle)
    return;

  if (gameDifficulty == easy)
  {
    gameDifficulty = medium;
    Serial.println("Medium mode on!");
  }
  else if (gameDifficulty == medium)
  {
    gameDifficulty = hard;
    Serial.println("Hard mode on!");
  }
  else
  {
    gameDifficulty = easy;
    Serial.println("Easy mode on!");
  }
}

void onNewWord()
{

  if (gameDifficulty == easy)
  {
    wordAppearanceTimer = easyTimer;
  }
  else if (gameDifficulty == medium)
  {
    wordAppearanceTimer = mediumTimer;
  }
  else if (gameDifficulty == hard)
  {
    wordAppearanceTimer = hardTimer;
  }

  int wordIndex = random(wordCount);
  chosenWord = String(words[wordIndex]);
  guessedWord = "";
  inputBuffer = "";
  ledGreen();

  Serial.println("\nNew word:");
  Serial.println(chosenWord);
}

// Jumping from one state to the other

void onChangeFree()
{

  ledWhite();

  gameState = idle;
  gameDifficulty = easy;
}

void onChangeStarting()
{
  ledOff();

  // Folosite pentru a masura 3 secunde
  timeAtStartOfTimer1 = millis();
  timer1 = 0;
  blinkHelper1 = 1;

  gameState = starting;
}

void onChangeRunning()
{
  ledGreen();

  gameRunningTimer = gameTimer;
  wordAppearanceTimer = 0;
  guessedWordCount = 0;

  gameState = running;
}

// Helper functions

void ledWhite()
{
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
}

void ledOff()
{
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void ledGreen()
{
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}

void ledRed()
{
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}
