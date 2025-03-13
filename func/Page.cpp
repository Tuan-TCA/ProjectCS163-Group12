#include "Page.h"
#include <raylib.h>
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

}

void Page::draw() {
    ClearBackground(RAYWHITE);
    head.Draw();
    DrawRectangleRec(bottom, GREEN);
    DrawRectangleRec(side, PINK);
    home.Draw();
    for(auto &button : functions) {
        button.Draw();
    }
}