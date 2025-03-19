#pragma once
#include<raylib.h>
#include "Button.h"
#include "Variables.h"
#include<bits/stdc++.h>
#include "InputField.h"
using namespace std;

class Page {
public:
    MyRec head;
    Rectangle bottom;
    Rectangle side;
    Button Ok;
    TextBox textbox;
    vector <Button> functions;
    ButtonFromImage home, home2;
    Texture2D background1, background2;

    FUNC func = FUNC::NONE;

    void init();
    void draw();
    void event();
};