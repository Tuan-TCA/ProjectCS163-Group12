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

void Page::init(MODE mode) {
    head = MyRec(0,0,screenWidth,screenHeight*0.1, getMODE(mode).c_str(), PURPLE, RED);
    bottom = {0,screenHeight*0.9f,(float)screenWidth,screenHeight*0.1f};
    side = {0,screenHeight*0.3f,screenWidth*0.3f,screenHeight*0.6f};
    home.image = LoadTexture("res\\back_home.png");
    
}

void Page::draw() {
    ClearBackground(RAYWHITE);
    head.Draw();
    DrawRectangleRec(bottom, GREEN);
    DrawRectangleRec(side, PINK);
    home.DrawText2D();
    for(auto &button : functions) {
        button.Draw();
    }
}