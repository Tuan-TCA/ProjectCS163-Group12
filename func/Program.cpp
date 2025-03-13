#include "Program.h"
#include <raylib.h>

Program::Program () {
    InitWindow(screenWidth, screenHeight, "Visualization App - CS 163 - Group 12");
    SetTargetFPS(60);
    mode = MODE::MENU;
}

void Program::run() {
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
            page.init(mode);
        }
        else if(x == 2) {
            mode = MODE::HASHTB;
            page.init(mode);
        }
        else if(x == 3) {
            mode = MODE::AVL;
            page.init(mode);
        }
        else if(x == 4) {
            mode = MODE::GRAPH;
            page.init(mode);
        }
    }

    if (mode == MODE::LL) {
        // Linked List event
         if(page.home.IsClicked()) {
            mode = MODE::MENU;
        }
    }
    if(mode == MODE::HASHTB) {
        // Hash Table
        if(page.home.IsClicked()) {
            mode = MODE::MENU;
        }
    }
    if(mode == MODE::AVL) {
        // AVL Tree
        if(page.home.IsClicked()) {
            mode = MODE::MENU;
        }
    }
    if(mode == MODE::GRAPH) {
        // Graph   
        if(page.home.IsClicked()) {
            mode = MODE::MENU;
        }
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
    if (mode == MODE::HASHTB) {
        //LL.draw();
        page.draw();       
    }
    if (mode == MODE::AVL) {
        //LL.draw();
        page.draw();       
    }
    if (mode == MODE::GRAPH) {
        //LL.draw();
        page.draw();       
    }
     
}



