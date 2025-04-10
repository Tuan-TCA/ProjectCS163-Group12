#pragma once
#include <raylib.h>
#include "Button.h"
#include "Variables.h"
using namespace std;

class Menu
{
public:
    SwitchThemeButton SwitchTheme;
    vector<AnimatedImageButton> buttons1;
    vector<AnimatedImageButton> buttons2;
    Font font; 
    void init();
    void draw();
    int modeRetrieve();
};