#include "Page.h"
#include "Variables.h"
#include <raylib.h>
#include <bits/stdc++.h>
#include <string>
#include <iostream>
using namespace std;

string getMODE() {
    if(mode == MODE::LL) return "Linked List";
    if(mode == MODE::HASHTB) return "Hash Table";
    if(mode == MODE::AVL) return "AVL Tree";
    if(mode == MODE::GRAPH) return "Graph";
    return "";
}


void Page::init() {
    head = MyRec(0, 10, (float) screenWidth, screenHeight*0.08f, getMODE().c_str(), BLUE2, WHITE);
    home = ButtonFromImage("res/button/back.png", "res/button/back-isOver.png", screenWidth*0.016f, screenHeight*0.016f, screenWidth*0.05f, screenWidth*0.05f); 
    background = resizedImage("res/BackGround.png", screenWidth, screenHeight);     
    bottom = {0,screenHeight*0.88f,(float)screenWidth,screenHeight*0.12f};
    side = {0,screenHeight / 2 - screenHeight * 0.63f / 2,screenWidth*0.25f,screenHeight*0.63f};
    textbox = TextBox(5, screenHeight / 2 - screenHeight*0.63f * 0.15f, screenWidth*0.25f - 10, screenHeight*0.63f * 0.15f, "", WHITE, WHITE, BLACK);
    functions = vector<Button> { 
        Button(screenWidth*0.2, screenHeight*0.60, screenWidth*0.05, screenHeight*0.02, "Create", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.2, screenHeight*0.65, screenWidth*0.05, screenHeight*0.02, "Insert", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.2, screenHeight*0.70, screenWidth*0.05, screenHeight*0.02, "Search", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.2, screenHeight*0.75, screenWidth*0.05, screenHeight*0.02, "Delete", DARKGRAY, LIGHTGRAY, WHITE)
    };
}

void Page::draw() {
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    head.Draw();

    DrawRectangleRec(bottom, BLUE2);
    DrawRectangleRec(side, BLUE3);
    textbox.Draw();
    home.Draw();
    for(auto &button : functions) {
        button.Draw();
    }
}



void Page::event() {
    if(home.IsClicked()) {
        mode = MODE::MENU;
        return;
    }
    bool add = functions[1].IsClicked();
    bool del = functions[3].IsClicked();
    textbox.HandleInput(add, del);
    add = 0;del=0;
    for (auto x: textbox.nums) cout<<x<<" ";std::cout<<endl;
}
