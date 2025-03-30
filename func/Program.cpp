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
    LL.init();
    graph.init();
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
            page.init();
            
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
    else if (mode == MODE::HASHTB) {
        page.event();
    
        // Xử lý CREATE với table size nhập từ bàn phím
        if (page.currentOperation == Operation::Create && !page.textbox.nums.empty()) {
            int size = page.textbox.nums[0];  // Lấy table size từ input
            page.textbox.nums.erase(page.textbox.nums.begin());
    
            if (B) delete B;  // Xoá bảng cũ nếu có
            B = new HashTableChaining(size);  // Khởi tạo bảng mới với kích thước
    
            page.textbox.inputText = "";  // Reset input
        }
    
        if (B) B->EventHashTableInPage(page);
    }
    if(mode == MODE::AVL) {
        // AVL Tree
        // avl.event();
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
        //LL.draw();
        page.draw();
        if(B)
        B->DrawHashTableInPage(page);
        else {
            B = new HashTableChaining(3);
            B->DrawHashTableInPage(page);
        }
    }
    if (mode == MODE::AVL) {
        // avl.draw();
    }
    if (mode == MODE::GRAPH) {

        graph.draw();
    }
}



