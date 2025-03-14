#include "Menu.h"
#include "Variables.h"
#include<bits/stdc++.h>

void Menu::init() {
    buttons = {
        Button(screenWidth*0.4, screenHeight*0.3, screenWidth*0.2, screenHeight*0.1, "Linked List", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.4, screenHeight*0.45, screenWidth*0.2, screenHeight*0.1, "Hash Table", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.4, screenHeight*0.60, screenWidth*0.2, screenHeight*0.1, "Tree", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.4, screenHeight*0.75, screenWidth*0.2, screenHeight*0.1, "Graph", DARKGRAY, LIGHTGRAY, WHITE)
    };
}

void Menu::draw() {
    ClearBackground(RAYWHITE);
    string title = "Visualization App";
    DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
    DrawText(title.c_str(), screenWidth*0.2, screenHeight*0.1, screenWidth * 0.0667f, GRAY);

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