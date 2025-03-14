#include "Menu.h"
#include "Variables.h"
#include<bits/stdc++.h>

void Menu::init() {
    font = LoadFont("res/font/romulus.png");
    buttons = {
        AnimatedButton(screenWidth*0.4, screenHeight*0.3, screenWidth*0.2, screenHeight*0.1, "Linked List", BLUE1, BLUE1, WHITE),
        AnimatedButton(screenWidth*0.4, screenHeight*0.45, screenWidth*0.2, screenHeight*0.1, "Hash Table", BLUE1, BLUE1, WHITE),
        AnimatedButton(screenWidth*0.4, screenHeight*0.60, screenWidth*0.2, screenHeight*0.1, "Tree", BLUE1, BLUE1, WHITE),
        AnimatedButton(screenWidth*0.4, screenHeight*0.75, screenWidth*0.2, screenHeight*0.1, "Graph", BLUE1, BLUE1, WHITE)
    };
}

void Menu::draw() {
    ClearBackground(BLUE1);
    string title = "Visualization App\n";
    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE3);
    DrawTextEx(font, title.c_str(), {screenWidth*0.2f, screenHeight*0.1f}, screenWidth * 0.0667, 5, BLUE4);
    DrawTextEx(font, "\n\nCS163 - GROUP 6", {screenWidth*0.3f, screenHeight*0.1f}, screenWidth * 0.04, 5, BLUE4);
    for(auto &button : buttons) {
        button.Update();
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