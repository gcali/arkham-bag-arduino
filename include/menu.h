#include "my-button.h"

enum class State
{
    MENU,
    DRAWING,
    DRAWN
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
