#include "Page.h"
#include "Variables.h"
#include <raylib.h>
#include <bits/stdc++.h>
#include <string>
#include <iostream>
using namespace std;

int lastInsertedKey;

string getMODE() {
    if(mode == MODE::LL) return "Linked List";
    if(mode == MODE::HASHTB) return "Hash Table";
    if(mode == MODE::AVL) return "AVL Tree";
    if(mode == MODE::GRAPH) return "Graph";
    return "";
}


void Page::init() {
    Ok = Button(10 + screenWidth * 0.25f - 100, screenHeight / 2 - screenHeight * 0.63f * 0.15f, 
                73, screenHeight * 0.63f * 0.15f, "OK", MyColor1, MyColor2, WHITE);

    head = MyRec(0, 10, (float) screenWidth, screenHeight * 0.08f, getMODE().c_str(), MyColor2, WHITE);
    home = ButtonFromImage("res/button/back.png", "res/button/back-isOver.png", 
                           screenWidth * 0.016f, screenHeight * 0.016f, screenWidth * 0.05f, screenWidth * 0.05f);

    background1 = resizedImage("res/BackGround.png", screenWidth, screenHeight);
    background2 = resizedImage("res/background_theme2.png", screenWidth, screenHeight);
    
    bottom = {0, screenHeight * 0.88f, (float)screenWidth, screenHeight * 0.12f};
    side = {0, screenHeight / 2 - screenHeight * 0.63f / 2, screenWidth * 0.24f, screenHeight * 0.63f};

    textbox = TextBox(5, screenHeight / 2 - screenHeight * 0.63f * 0.15f, 
                      screenWidth * 0.25f - 100, screenHeight * 0.63f * 0.15f, "", WHITE, WHITE, BLACK);

    selectedIndex = 0;
    optionButton = Button(screenWidth * 0.12f, screenHeight * 0.10f, 
        screenWidth * 0.1f, screenHeight * 0.06f, 
        options[selectedIndex].c_str(), DARKGREEN, DARKBLUE, WHITE);

    prevButton = Button(screenWidth * 0.05f, screenHeight * 0.10f, 
                        screenWidth * 0.04f, screenHeight * 0.04f, "<", DARKGRAY, LIGHTGRAY, WHITE);

    nextButton = Button(screenWidth * 0.25f, screenHeight * 0.10f, 
                        screenWidth * 0.04f, screenHeight * 0.04f, ">", DARKGRAY, LIGHTGRAY, WHITE);
}


void Page::draw() {
    ClearBackground(RAYWHITE);
    DrawTexture(switchState ? background2 : background1, 0, 0, WHITE);
    head.Draw(MyColor2, getMODE());
    DrawRectangleRec(bottom, MyColor2);
    DrawRectangleRec(side, MyColor3);
    Ok.Draw(MyColor1, MyColor2);
    textbox.Draw();
    switchState ? home2.Draw() : home.Draw();

    prevButton.Draw();
    optionButton.Draw();
    nextButton.Draw();
}



void Page::event() {
    if (!switchState ? home.IsClicked() : home2.IsClicked()) {
        mode = MODE::MENU;
        textbox.resetTextbox();
        return;
    }

    textbox.HandleInput();

    if (Ok.IsClicked() && !textbox.inputText.empty()) {
        textbox.nums.push_back(stoi(textbox.inputText));
        TraceLog(LOG_INFO, textbox.inputText.c_str());
        textbox.inputText = "";
    }

    if (prevButton.IsClicked()) {
        selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
        optionButton.label = options[selectedIndex].c_str(); 
    }

    if (nextButton.IsClicked()) {
        selectedIndex = (selectedIndex + 1) % options.size();
        optionButton.label = options[selectedIndex].c_str(); 
    }

    if (optionButton.IsClicked()) {
        if (options[selectedIndex] == "CREATE") func = FUNC::CREATE;
        if (options[selectedIndex] == "INSERT") func = FUNC::INSERT;
        if (options[selectedIndex] == "SEARCH") func = FUNC::SEARCH;
        if (options[selectedIndex] == "DELETE") func = FUNC::DELETE;
        if (options[selectedIndex] == "UPDATE") func = FUNC::UPDATE;
    }
}
