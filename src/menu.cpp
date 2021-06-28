#include "menu.h"
#include "screen.h"
#include "data.h"

Menu::Menu()
{
    currentScreen = 0;
    isShowing = -1;
}

#define DRAW_SCREEN 1
#define GENERATE_SCREEN 0

void Menu::show()
{
    if (isShowing != currentScreen)
    {
        clearScreen();
        byte *out;
        switch (currentScreen)
        {
        case DRAW_SCREEN:
            out = dImg;
            break;
        case GENERATE_SCREEN:
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
        return State::MENU;
    }
    else
    {
        switch (currentScreen)
        {
        case DRAW_SCREEN:
            return State::DRAWING;
        default:
            return State::MENU;
        }
    }
}

Menu menu = Menu();