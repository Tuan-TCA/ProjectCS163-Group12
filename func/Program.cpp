#include "Program.h"
#include <raylib.h>
#include <iostream>

Program::Program () {
    InitWindow(screenWidth, screenHeight, "Visualization App - CS 163 - Group 12");
    SetTargetFPS(90);
    mode = MODE::MENU;
}

void Program::init(){
    menu.init();
    LL.init();
    graph.init();
    avl.init();
}
void Program::run() {
    init();
    //cout<<1;
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        event();

        Vector2 mousePos = GetMousePosition();
        char posText[50];
        snprintf(posText, sizeof(posText), "(%d, %d)", (int)mousePos.x, (int)mousePos.y);
        
        // Vẽ text ngay bên cạnh chuột (+10px offset)
        DrawText(posText, mousePos.x + 10, mousePos.y + 10, 20, DARKGRAY);

        draw();
        EndDrawing();
    }
    CloseWindow();
}

void Program::event() {
    if(mode == MODE::MENU) {
        int x;
        x = menu.modeRetrieve();
        //init LinkedList
        if(x == 1) {
            mode = MODE::LL;
            // std::cout<<"Linked list"; 
            LL.init();
        }
        else if(x == 2) {
            mode = MODE::HASHTB;
            page.init();
            
        }
        else if(x == 3) {
            mode = MODE::AVL;
            avl.init();
            
        }
        else if(x == 4) {
            mode = MODE::GRAPH;
            graph.init();
            
        }
    }

    
    else if(mode == MODE::LL) {
        // Linked List
        LL.event();
        //cout<<"K";
    }
    if(mode == MODE::HASHTB) {
        // Hash Table
        // hashtable.event();
    }
    if(mode == MODE::AVL) {
        // AVL Tree
         avl.event();
    }
    if(mode == MODE::GRAPH) {
        // Graph   
        graph.event();
    }
}

void Program::draw() {

    if (mode == MODE::MENU) {
        menu.draw();
    } 
    if (mode == MODE::LL) {
        LL.draw();
    }
     
    if (mode == MODE::HASHTB) {

        // hashtable.draw();
    }
    if (mode == MODE::AVL) {
        avl.draw();
    
    }
    if (mode == MODE::GRAPH) {

        graph.draw();
    }
}



