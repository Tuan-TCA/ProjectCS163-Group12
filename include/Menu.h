#pragma once
#include <raylib.h>
#include "Button.h"
#include "Variables.h"
#include <bits/stdc++.h>
using namespace std;

class Menu
{
public:
    vector<AnimatedButton> buttons;
    Font font; 
    void init();
    void draw();
    int modeRetrieve();
};