#include "Menu.h"
#include "Variables.h"
#include<bits/stdc++.h>

void Menu::init() {
    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
}

void Menu::draw() {
    ClearBackground(RAYWHITE);
    string title = "Visualization App";
    DrawText(title.c_str(), screenWidth*0.2, screenHeight*0.1, 128, GRAY);

    for(auto &button : buttons) {
        button.Draw();
    }
}

int Menu::modeRetrieve() {
    for(int i = 0; i < buttons.size(); i++) {
        if(buttons[i].IsClicked()) {
            return i+1;
        }
    }
    return -1;
}