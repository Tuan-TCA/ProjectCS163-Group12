#pragma once
#include <raylib.h>
#include "Button.h"
#include "Variables.h"
#include <bits/stdc++.h>
#include "InputField.h"
using namespace std;

class Page {
public:
    MyRec head;
    Rectangle bottom;
    Rectangle side;
    Button Ok;
    TextBox textbox;
    ButtonFromImage home, home2;
    Texture2D background1, background2;

    FUNC func;

    vector<string> options = {"CREATE", "INSERT", "SEARCH", "DELETE", "UPDATE"};
    int selectedIndex;  // position hiện tại
    Button optionButton; // op hiện tại
    Button prevButton;  // chuyển trái
    Button nextButton;  // chuyển phải

    void init();
    void draw();
    void event();
};
