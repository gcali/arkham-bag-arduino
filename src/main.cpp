//www.elegoo.com
//2016.12.9

//We always have to include the library
#include "LedControl.h"
#include <EEPROM.h>

int current = 0;
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to LOAD(CS)
 pin 10 is connected to the CLK 
 We have only a single MAX72XX.
 */
LedControl lc = LedControl(12, 10, 11, 1);

void clearScreen()
{
  lc.clearDisplay(0);
}

class MyButton
{
public:
  MyButton(int pin);
  bool read();
  bool state();

private:
  bool pressed;
  bool _state;
  int _pin;
  unsigned long _lastReadTime;
  int _lastRead;
};

MyButton::MyButton(int pin)
{
  _pin = pin;
};
bool MyButton::read()
{
  int val = digitalRead(_pin);
  if (val != _lastRead)
  {
    _lastReadTime = millis();
  }
  _lastRead = val;
  if ((millis() - _lastReadTime) < 50)
  {
    return false;
  }

  if (val == LOW)
  {
    if (!pressed)
    {
      pressed = true;
      _state = !_state;
      return true;
    }
  }
  else
  {
    pressed = false;
  }
  return false;
}

bool MyButton::state()
{
  return _state;
}

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
/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix. 
 (you need at least 5x7 leds to see the whole chars)
 */
byte skull[7] = {
    B01111100,
    B10000010,
    B10101010,
    B10000010,
    B01000100,
    B01010100,
    B00111000};

byte star[7] = {
    B10010010,
    B01010100,
    B00111000,
    B11111110,
    B00111000,
    B01010100,
    B10010010};

byte tomb[7] = {
    B00011100,
    B00111110,
    B00111110,
    B00111110,
    B00111110,
    B00111110,
    B00111110};

void writeSkipping(byte *buf, int skip)
{
  for (int i = 0; i < 8 - skip; i++)
  {
    lc.setRow(0, i + skip, buf[i]);
  }
}

void write(byte *buf)
{
  writeSkipping(buf, 1);
}

void writeNegate(byte *buf)
{
  for (int i = 0; i < 7; i++)
  {
    if (i == 3)
    {
      lc.setRow(0, i + 1, buf[i] | B01100000);
    }
    else
    {
      lc.setRow(0, i + 1, buf[i]);
    }
  }
}

void interval()
{
  delay(1000);
  lc.clearDisplay(0);
}

byte cultist[7] = {
    B00011100,
    B00111110,
    B01110111,
    B01100011,
    B01010101,
    B01000001,
    B01011101};

byte tentacle[7] = {
    B00011110,
    B00111010,
    B01110001,
    B01110000,
    B00111000,
    B00011100,
    B00111110};

byte one[7] = {
    B00000001,
    B00000001,
    B00000001,
    B00000001,
    B00000001,
    B00000001,
    B00000001,
};

byte two[7] = {
    B00001111,
    B00000001,
    B00000001,
    B00001111,
    B00001000,
    B00001000,
    B00001111};

byte three[7] = {
    B00001111,
    B00000001,
    B00000001,
    B00000111,
    B00000001,
    B00000001,
    B00001111};

byte four[7] = {
    B00001001,
    B00001001,
    B00001001,
    B00001111,
    B00000001,
    B00000001,
    B00000001,
};

byte five[7] = {
    B00001111,
    B00001000,
    B00001000,
    B00001111,
    B00000001,
    B00000001,
    B00001111,
};

byte six[7] = {
    B00001111,
    B00001000,
    B00001000,
    B00001111,
    B00001001,
    B00001001,
    B00001111};

byte seven[7] = {
    B00001111,
    B00001001,
    B00001001,
    B00000001,
    B00000001,
    B00000001,
    B00000001,
};

byte eight[7] = {
    B00001111,
    B00001001,
    B00001001,
    B00001111,
    B00001001,
    B00001001,
    B00001111,
};

byte zero[7] = {
    B00001111,
    B00001001,
    B00001001,
    B00001001,
    B00001001,
    B00001001,
    B00001111,
};

bool isFirst = true;

byte *pictures[] = {
    skull,
    star,
    tomb,
    cultist,
    tentacle,
    zero};
void setup()
{
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 4);
  /* and clear the display */
  lc.clearDisplay(0);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonAPin, INPUT_PULLUP);
  pinMode(buttonBPin, INPUT_PULLUP);

  current = EEPROM.read(0);

  //write(pictures[current]);
}

byte randImg[7] = {
    B00111110,
    B00100010,
    B00100010,
    B00111110,
    B00111000,
    B00101100,
    B00100110,
};

byte normal[7] = {
    B00100001,
    B00110001,
    B00111001,
    B00101101,
    B00100111,
    B00100011,
    B00100001};

byte dImg[7] = {
    B00111000,
    B00100100,
    B00100010,
    B00100010,
    B00100010,
    B00100100,
    B00111000,
};

byte gImg[7] = {
    B00111110,
    B00100000,
    B00100000,
    B00101110,
    B00100010,
    B00100010,
    B00111110,
};

byte drawWait[7] = {
    B01111110,
    B01000010,
    B01011010,
    B01011010,
    B01011010,
    B01000010,
    B01111110,
};

bool isChoice = true;
bool isRandom = false;

enum class State
{
  MENU,
  DRAWING,
  DRAWN
};

enum class ButtonType
{
  A_BUTTON,
  B_BUTTON
};

class Menu
{
public:
  Menu();
  void show();
  State handleInput(ButtonType button);

private:
  int currentScreen;
  int isShowing;
};

Menu::Menu()
{
  currentScreen = 0;
  isShowing = -1;
}

void Menu::show()
{
  if (isShowing != currentScreen)
  {
    clearScreen();
    byte *out;
    switch (currentScreen)
    {
    case 0:
      out = dImg;
      break;
    case 1:
      out = gImg;
      break;
    default:
      out = dImg;
      break;
    }
    clearScreen();
    write(out);
    isShowing = currentScreen;
  }
}

State Menu::handleInput(ButtonType currButton)
{
  if (currButton == ButtonType::A_BUTTON)
  {
    currentScreen = (currentScreen + 1) % 2;
  }
  return State::MENU;
}

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
