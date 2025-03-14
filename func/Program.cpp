#include "Program.h"
#include <raylib.h>
#include <iostream>

Program::Program () {

    InitWindow(screenWidth, screenHeight, "Visualization App - CS 163 - Group 12");
    SetTargetFPS(60);
    mode = MODE::MENU;
}

void Program::init(){
    menu.init();
    page.init();
}
void Program::run() {
    init();
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        event();
        draw();
        EndDrawing();

    }
    CloseWindow();
}

void Program::event() {
    if(mode == MODE::MENU) {
        int x;
        x = menu.modeRetrieve();
        if(x == 1) {
            mode = MODE::LL;
            std::cout<<"Linked list"; 
        }
        else if(x == 2) {
            mode = MODE::HASHTB;
        }
        else if(x == 3) {
            mode = MODE::AVL;
        }
        else if(x == 4) {
            mode = MODE::GRAPH;
        }
    }
    else if(mode == MODE::LL) {
        // Linked List
         page.Update();
        page.actions();
    }
    else if(mode == MODE::HASHTB) {
        // Hash Table
    }
    else if(mode == MODE::AVL) {
        // AVL Tree
    }
    else if(mode == MODE::GRAPH) {
        // Graph    
    }
}

void Program::draw() {
    if (mode == MODE::MENU) {
        menu.draw();
    } 
    if (mode == MODE::LL) {
        //LL.draw();    
        page.draw();
        
    }

}



