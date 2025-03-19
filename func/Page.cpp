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
    subButtonPosition.push_back({screenWidth*0.24f, screenHeight / 2 - screenHeight*0.63f * 0.5f + 5});
    subButtonPosition.push_back({screenWidth*0.24f + screenHeight*0.63f * 0.15f + 5 , screenHeight / 2 - screenHeight*0.63f * 0.5f + 5});
    subButtonPosition.push_back({screenWidth*0.24f + screenHeight*0.63f * 0.15f * 2 + 10 , screenHeight / 2 - screenHeight*0.63f * 0.5f + 5});
    subWidth = screenHeight*0.63f * 0.15f;
    subHeight = screenHeight*0.63f * 0.15f;
    insertButton = Button(5, screenHeight / 2 - screenHeight*0.63f * 0.5f + 5, screenWidth*0.24f - 10, screenHeight*0.63f * 0.15f, "INSERT", MyColor1, Fade(MyColor1, 0.8f), WHITE);
    createButton = Button(5, screenHeight / 2 - screenHeight*0.63f * 0.5f + 5, screenWidth*0.24f - 10, screenHeight*0.63f * 0.15f, "CREATE", MyColor1, Fade(MyColor1, 0.8f), WHITE);
    deleteButton = Button(5, screenHeight / 2 - screenHeight*0.63f * 0.5f + 5, screenWidth*0.24f - 10, screenHeight*0.63f * 0.15f, "DELETE", MyColor1, Fade(MyColor1, 0.8f), WHITE);
    searchButton = Button(5, screenHeight / 2 - screenHeight*0.63f * 0.5f + 5, screenWidth*0.24f - 10, screenHeight*0.63f * 0.15f, "SEARCH", MyColor1, Fade(MyColor1, 0.8f), WHITE);

    operationButtons.push_back(Button(screenWidth*0.24f, screenHeight / 2 - screenHeight*0.63f * 0.5f + 5, screenHeight*0.63f * 0.15f , screenHeight*0.63f * 0.15f, "Insert", MyColor1, MyColor2, WHITE));
    operationButtons.push_back(Button(120, 50, 100, 30, "Create", MyColor1, MyColor2, WHITE));
    operationButtons.push_back(Button(120, 90, 100, 30, "Delete", MyColor1, MyColor2, WHITE));
    operationButtons.push_back(Button(120, 130, 100, 30, "Search", MyColor1, MyColor2, WHITE));
    currentOperation = Operation::Insert;

    Ok = Button(10 + screenWidth*0.25f - 100, screenHeight / 2 - screenHeight*0.63f * 0.15f, 73, screenHeight*0.63f * 0.15f, "OK", MyColor1, MyColor2, WHITE);
    head = MyRec(0, 10, (float) screenWidth, screenHeight*0.08f, getMODE().c_str(), MyColor2, WHITE);
    home = ButtonFromImage("res/button/back.png", "res/button/back-isOver.png", screenWidth*0.016f, screenHeight*0.016f, screenWidth*0.05f, screenWidth*0.05f); 
    home2 = ButtonFromImage("res/button/homeII_1.png", "res/button/homeII_2.png", screenWidth*0.016f, screenHeight*0.016f, screenWidth*0.05f, screenWidth*0.05f); 

    background1 = resizedImage("res/BackGround.png", screenWidth, screenHeight);   
    background2 = resizedImage("res/background_theme2.png", screenWidth, screenHeight);    
    bottom = {0,screenHeight*0.88f,(float)screenWidth,screenHeight*0.12f};
    side = {0,screenHeight / 2 - screenHeight * 0.63f / 2,screenWidth*0.24f,screenHeight*0.63f};
    textbox = TextBox(5, screenHeight / 2 - screenHeight*0.63f * 0.15f, screenWidth*0.25f - 100, screenHeight*0.63f * 0.15f, "", WHITE, WHITE, BLACK);
    functions = vector<Button> { 
        Button(screenWidth*0.2, screenHeight*0.60, screenWidth*0.05, screenHeight*0.02, "Create", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.2, screenHeight*0.65, screenWidth*0.05, screenHeight*0.02, "Insert", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.2, screenHeight*0.70, screenWidth*0.05, screenHeight*0.02, "Search", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.2, screenHeight*0.75, screenWidth*0.05, screenHeight*0.02, "Delete", DARKGRAY, LIGHTGRAY, WHITE)
    };
}
void Page::reset(){
    currentOperation = Operation::Insert;
    isInsertExpanded = false; 
    isCreateExpanded = false;
    isDeleteExpanded = false;  
    isSearchExpanded = false;  
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
    for(auto &button : functions) {
        button.Draw();
    }
    if(currentOperation == Operation::Insert){
        insertButton.Draw();
        if (isInsertExpanded) {
            DrawRectangle(0,0,screenWidth,screenHeight,Fade(GRAY, 0.2));
            operationButtons[1].Draw(MyColor1, Fade(MyColor1, 0.8f));  
            operationButtons[2].Draw(MyColor1, Fade(MyColor1, 0.8f)); 
            operationButtons[3].Draw(MyColor1, Fade(MyColor1, 0.8f));  
        }
    }
     if (currentOperation == Operation::Create){
        createButton.Draw();
        if (isCreateExpanded) {
            DrawRectangle(0,0,screenWidth,screenHeight,Fade(GRAY, 0.2));
            operationButtons[0].Draw(MyColor1, Fade(MyColor1, 0.8f));  
            operationButtons[2].Draw(MyColor1, Fade(MyColor1, 0.8f)); 
            operationButtons[3].Draw(MyColor1, Fade(MyColor1, 0.8f));  
        }
    }
     if(currentOperation == Operation::Delete){
        deleteButton.Draw();
        if (isDeleteExpanded) {
            DrawRectangle(0,0,screenWidth,screenHeight,Fade(GRAY, 0.2));
            operationButtons[0].Draw(MyColor1, Fade(MyColor1, 0.8f));  
            operationButtons[1].Draw(MyColor1, Fade(MyColor1, 0.8f)); 
            operationButtons[3].Draw(MyColor1, Fade(MyColor1, 0.8f));  
        }
    }
     if (currentOperation == Operation::Search){
        searchButton.Draw();
        if (isSearchExpanded) {
            DrawRectangle(0,0,screenWidth,screenHeight,Fade(GRAY, 0.2));
            operationButtons[0].Draw(MyColor1, Fade(MyColor1, 0.8f));  
            operationButtons[1].Draw(MyColor1, Fade(MyColor1, 0.8f)); 
            operationButtons[2].Draw(MyColor1, Fade(MyColor1, 0.8f));  
        }
    }
}

void Page::event() {
    if(!switchState ? home.IsClicked(): home2.IsClicked() ) {
        mode = MODE::MENU;
        textbox.resetTextbox();
        reset();
        return;
    }
    textbox.HandleInput();

    
    if(Ok.IsClicked() && !textbox.inputText.empty()){
        textbox.nums.push_back(stoi(textbox.inputText));
         TraceLog(LOG_INFO, textbox.inputText.c_str());
        textbox.inputText = "";
    }
  
    if(currentOperation == Operation::Insert){
        if (insertButton.IsClicked()) {
            isInsertExpanded = !isInsertExpanded; 
            operationButtons[1].bounds = Rectangle{subButtonPosition[0].x, subButtonPosition[0].y, subWidth, subHeight };
            operationButtons[2].bounds = Rectangle{subButtonPosition[1].x, subButtonPosition[1].y, subWidth, subHeight };
            operationButtons[3].bounds = Rectangle{subButtonPosition[2].x, subButtonPosition[2].y, subWidth, subHeight };
        }

        if (isInsertExpanded) {
            if (operationButtons[1].IsClicked()) {
                currentOperation = Operation::Create;
                isInsertExpanded = !isInsertExpanded;
                isCreateExpanded = false;
                textbox.resetTextbox();
            }
            if (operationButtons[2].IsClicked()) {
                currentOperation = Operation::Delete;
                isInsertExpanded = !isInsertExpanded;
                isDeleteExpanded = false;
                textbox.resetTextbox();
            }
            if (operationButtons[3].IsClicked()) {
                currentOperation = Operation::Search;
                isInsertExpanded = !isInsertExpanded;
                isSearchExpanded = false;
                textbox.resetTextbox();
            }
        }
    }
    if (currentOperation == Operation::Create){
        if (createButton.IsClicked()){
            isCreateExpanded = !isCreateExpanded;
            operationButtons[0].bounds = Rectangle{subButtonPosition[0].x, subButtonPosition[0].y, subWidth, subHeight };
            operationButtons[2].bounds = Rectangle{subButtonPosition[1].x, subButtonPosition[1].y, subWidth, subHeight };
            operationButtons[3].bounds = Rectangle{subButtonPosition[2].x, subButtonPosition[2].y, subWidth, subHeight };
        }

        if(isCreateExpanded){
            if (operationButtons[0].IsClicked()) {
                currentOperation = Operation::Insert;
                isCreateExpanded != isCreateExpanded;
                isInsertExpanded = false;
                textbox.resetTextbox();
            }
            if (operationButtons[2].IsClicked()) {
                currentOperation = Operation::Delete;
                isCreateExpanded != isCreateExpanded;
                isDeleteExpanded = false;
                textbox.resetTextbox();
            }
            if (operationButtons[3].IsClicked()) {
                currentOperation = Operation::Search;
                isCreateExpanded != isCreateExpanded;
                isSearchExpanded = false;
                textbox.resetTextbox();
            }
        }
    }
     if (currentOperation == Operation::Delete){
        if(deleteButton.IsClicked()){
            isDeleteExpanded = !isDeleteExpanded;
            operationButtons[0].bounds = Rectangle{subButtonPosition[0].x, subButtonPosition[0].y, subWidth, subHeight };
            operationButtons[1].bounds = Rectangle{subButtonPosition[1].x, subButtonPosition[1].y, subWidth, subHeight };
            operationButtons[3].bounds = Rectangle{subButtonPosition[2].x, subButtonPosition[2].y, subWidth, subHeight };
        }

        if(isDeleteExpanded){
            if (operationButtons[0].IsClicked()) {
                currentOperation = Operation::Insert;
                isDeleteExpanded = !isDeleteExpanded;
                isInsertExpanded = false;
                textbox.resetTextbox();
            }
            if (operationButtons[1].IsClicked()) {
                currentOperation = Operation::Create;
                isDeleteExpanded = !isDeleteExpanded;
                isCreateExpanded = false;
                textbox.resetTextbox();
            }
            if (operationButtons[3].IsClicked()) {
                currentOperation = Operation::Search;
                isDeleteExpanded = !isDeleteExpanded;
                isSearchExpanded = false;
                textbox.resetTextbox();
            }
        }
    }
     if(currentOperation == Operation::Search){
        if(searchButton.IsClicked()){
            isSearchExpanded = !isSearchExpanded;
            operationButtons[0].bounds = Rectangle{subButtonPosition[0].x, subButtonPosition[0].y, subWidth, subHeight };
            operationButtons[1].bounds = Rectangle{subButtonPosition[1].x, subButtonPosition[1].y, subWidth, subHeight };
            operationButtons[2].bounds = Rectangle{subButtonPosition[2].x, subButtonPosition[2].y, subWidth, subHeight };
        }

        if(isSearchExpanded){
            if (operationButtons[0].IsClicked()) {
                currentOperation = Operation::Insert;
                isDeleteExpanded = !isDeleteExpanded;
                isInsertExpanded = false;
                textbox.resetTextbox();
            }
            if (operationButtons[1].IsClicked()) {
                currentOperation = Operation::Create;
                isDeleteExpanded = !isDeleteExpanded;
                isCreateExpanded = false;
                textbox.resetTextbox();
            }
            if (operationButtons[2].IsClicked()) {
                currentOperation = Operation::Delete;
                isDeleteExpanded = !isDeleteExpanded;
                isDeleteExpanded = false;
                textbox.resetTextbox();
            }
        }
    }
}

