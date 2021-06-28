enum class ButtonType
{
    A_BUTTON,
    B_BUTTON
};

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
