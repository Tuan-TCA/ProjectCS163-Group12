#include "Page.h"
#include <raylib.h>
#include<bits/stdc++.h>
using namespace std;

string getMODE(MODE mode) {
    if(mode == MODE::LL) return "Linked List";
    if(mode == MODE::HASHTB) return "Hash Table";
    if(mode == MODE::AVL) return "AVL Tree";
    if(mode == MODE::GRAPH) return "Graph";
    return "";
}

void Page::init(MODE newmode) {
    head = MyRec(0,0,(float) screenWidth,screenHeight*0.1f, getMODE(mode).c_str(), YELLOW, RED);
    bottom = {0,screenHeight*0.9f,(float)screenWidth,screenHeight*0.1f};
    side = {0,screenHeight*0.3f,screenWidth*0.3f,screenHeight*0.6f};
    textbox.box = {0.1f*screenWidth, 0.7f*screenHeight, 0.1f*screenWidth, 0.05f*screenHeight, "", RED, BLUE,YELLOW};
    home.image = LoadTexture("res/back_home.png");
    functions = vector<Button> { 
        Button(screenWidth*0.2, screenHeight*0.60, screenWidth*0.05, screenHeight*0.02, "Create", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.2, screenHeight*0.65, screenWidth*0.05, screenHeight*0.02, "Insert", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.2, screenHeight*0.70, screenWidth*0.05, screenHeight*0.02, "Search", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.2, screenHeight*0.75, screenWidth*0.05, screenHeight*0.02, "Delete", DARKGRAY, LIGHTGRAY, WHITE)
    };
}

void Page::draw() {
    ClearBackground(RAYWHITE);
    head.Draw();
    
    DrawRectangleRec(bottom, GREEN);
    DrawRectangleRec(side, PINK);
    textbox.Draw();
    home.DrawText2D();
    for(auto &button : functions) {
        button.Draw();
    }
}



void Page::actions() {
    if(home.IsClicked()) {
        mode = MODE::MENU;
        return;
    }
    bool add = functions[1].IsClicked();
    bool del = functions[3].IsClicked();
    textbox.HandleInput(add, del);
    add = 0;del=0;
    for(auto x: textbox.nums) cout<<x<<" ";cout<<endl;
}