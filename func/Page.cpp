#include "Page.h"
#include "Variables.h"
#include <raylib.h>
using namespace std;

string getMODE(MODE mode) {
    if(mode == MODE::LL) return "Linked List";
    if(mode == MODE::HASHTB) return "Hash Table";
    if(mode == MODE::AVL) return "AVL Tree";
    if(mode == MODE::GRAPH) return "Graph";
    return "";
}

void Page::init() {
    home = ButtonFromImage("res/back.png", "res/back-isOver.png", screenWidth*0.016f, screenHeight*0.016f, screenWidth*0.05f, screenWidth*0.05f); 
    background = resizedImage("res/BackGround.png", screenWidth, screenHeight);     
    head = MyRec(0, 10, screenWidth, screenHeight*0.08, getMODE(mode).c_str(), BLUE2, WHITE);
    bottom = {0,screenHeight*0.88f,(float)screenWidth,screenHeight*0.12f};
    side = {0,screenHeight / 2 - screenHeight * 0.63f / 2,screenWidth*0.25f,screenHeight*0.63f};
}

void Page::draw() {
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    head.Draw();
    DrawRectangleRec(bottom, BLUE2);
    DrawRectangleRec(side, BLUE3);
    input.Draw();
    home.Draw();
    for(auto &button : functions) {
        button.Draw();
    }
}
void Page::Update(){
    input.Update();

    if (input.isFocus() && IsKeyPressed(KEY_ENTER)) {  
        if (input.textLength > 0) {
            TraceLog(LOG_INFO, input.text);
            //Do linked list,.. action
        }
        input.textLength = 0;
        input.text[0] = '\0';
    }
    if(mode == MODE::MENU){
        input.textLength = 0;
        input.text[0] = '\0';
    }
}
void Page::actions(){
    if(home.IsClicked()){
        mode = MODE::MENU;
    }
    
}

