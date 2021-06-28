//www.elegoo.com
//2016.12.9

//We always have to include the library
#include <EEPROM.h>
#include <Arduino.h>
#include "screen.h"
#include "my-button.h"
#include "data.h"
#include "menu.h"

int current = 0;

/* we always wait a bit between updates of the display */
unsigned long delaytime1 = 500;
unsigned long delaytime2 = 50;

const int buttonAPin = 6;
const int buttonBPin = 5;
void turnOn()
{
  digitalWrite(LED_BUILTIN, HIGH);
}

void turnOff()
{
  digitalWrite(LED_BUILTIN, LOW);
}

MyButton button = MyButton(buttonAPin);

MyButton buttonB = MyButton(buttonBPin);
void interval()
{
  delay(1000);
  clearScreen();
}

bool isFirst = true;

void setup()
{
  initScreen();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonAPin, INPUT_PULLUP);
  pinMode(buttonBPin, INPUT_PULLUP);

  current = EEPROM.read(0);

  //write(pictures[current]);
}

bool isChoice = true;
bool isRandom = false;

State currentState = State::MENU;
Menu menu = Menu();

void loop()
{

  bool isButtonPressed = false;
  ButtonType buttonPressed;
  if (button.read())
  {
    buttonPressed = ButtonType::A_BUTTON;
    isButtonPressed = true;
  }
  else if (buttonB.read())
  {
    buttonPressed = ButtonType::B_BUTTON;
    isButtonPressed = true;
  }

  switch (currentState)
  {
  case State::MENU:
  {
    menu.show();
    if (isButtonPressed)
    {
      currentState = menu.handleInput(buttonPressed);
    }
    break;
  }

  case State::DRAWING:
  {

    break;
  }

  case State::DRAWN:
  {
    break;
  }

  default:
  {
    break;
  }
  }
  /*
  if (isChoice) {
    if (button.read()) {
      isChoice = false;
      isRandom = true;
      write(randImg);
      interval();
      write(randImg);
      interval();
    }
    if (buttonB.read()) {
      isChoice = false;
      isRandom = false;
      write(normal);
      interval();
      write(normal);
      interval();
    }
    return;
  }

  int len = sizeof pictures / sizeof pictures[0];

  bool hasChanged = false;
  if (button.read()) {
    hasChanged = true;
    current++;
    current %= len;
  }

  if (buttonB.read()) {
    hasChanged = true;
    current--;
    current += len;
    current %= len;
  }

  if (hasChanged) {
    lc.clearDisplay(0);
    write(pictures[current]);
   EEPROM.write(0, current);
  }*/
  /*}
  if (digitalRead(buttonAPin) == LOW) {
    if (button.tryPress()) {
      turnOn();
    }
  }
  else {
    button.release();
  }
  
  byte *pictures[] = {
    skull,
    star,
    tomb,
    cultist,
    tentacle,
    zero
  };
  byte *numbers[] = {
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight
  };
  for (int i = 0; i < sizeof pictures / sizeof pictures[0]; i++) {
    write(pictures[i]);
    interval();
  }
  for (int i = 0; i < sizeof numbers / sizeof numbers[0]; i++) {
    write(numbers[i]);
    interval();
    writeNegate(numbers[i]);
    interval();
  }*/

  //rows();
  //columns();
  //single();
}
