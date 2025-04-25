#pragma once
#include "Button.h"
#include "Variables.h"
using namespace std;

class Menu
{
public:
    SwitchThemeButton SwitchTheme;
    ButtonFromImage setting_button1, setting_button2;
    float animatingTime = 0;
    Slider musicVolume;
    bool setting_IsOpening = false,
        setting_IsClosing = false,
        hasOpened = true,
        hasClosed = false;
     Rectangle setting_menu;
    vector<AnimatedImageButton> buttons1;
    vector<AnimatedImageButton> buttons2;
    Font font; 
    void init();
    void event();
    void draw();
    int modeRetrieve();
    float Lerp(float start, float end, float amount);
    Rectangle Lerp(Rectangle a, Rectangle b, float amout);
};