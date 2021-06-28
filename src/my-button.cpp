#include "my-button.h"
#include <Arduino.h>

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
