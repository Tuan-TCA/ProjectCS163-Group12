#include "Page.h"
#include "Variables.h"
#include <raylib.h>
#include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

int lastInsertedKey;

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

    insertButton = Button(5, screenHeight / 2 - screenHeight*0.63f * 0.5f + 5, screenWidth*0.24f - 10, screenHeight*0.63f * 0.15f, "INSERT", MyColor1, Fade(MyColor1, 0.8f), WHITE);
    createButton = Button(5, screenHeight / 2 - screenHeight*0.63f * 0.5f + 5, screenWidth*0.24f - 10, screenHeight*0.63f * 0.15f, "CREATE", MyColor1, Fade(MyColor1, 0.8f), WHITE);
    deleteButton = Button(5, screenHeight / 2 - screenHeight*0.63f * 0.5f + 5, screenWidth*0.24f - 10, screenHeight*0.63f * 0.15f, "DELETE", MyColor1, Fade(MyColor1, 0.8f), WHITE);
    searchButton = Button(5, screenHeight / 2 - screenHeight*0.63f * 0.5f + 5, screenWidth*0.24f - 10, screenHeight*0.63f * 0.15f, "SEARCH", MyColor1, Fade(MyColor1, 0.8f), WHITE);

    selectedIndex = 0;
    optionButton = Button(screenWidth * 0.24f * 0.15f,screenHeight / 2 - screenHeight*0.63f * 0.35f + 10 , screenWidth*0.24f * 0.7f, screenHeight*0.63f * 0.15f, options[selectedIndex].c_str(), WHITE, LIGHTGRAY, MyColor5);
    prevButton = Button(5,screenHeight / 2 - screenHeight*0.63f * 0.35f + 10 ,  screenWidth*0.24f * 0.15f - 10, screenHeight*0.63f * 0.15f, "<", WHITE, LIGHTGRAY, MyColor5);
    nextButton = Button(screenWidth*0.24f * 0.85f + 5,screenHeight / 2 - screenHeight*0.63f * 0.35f + 10 ,  screenWidth*0.24f * 0.15f - 10, screenHeight*0.63f * 0.15f, ">", WHITE, LIGHTGRAY, MyColor5);
    currentInput = InputType::Keyboard;
    operationButtons.push_back(Button(120, 50, 100, 30, "Insert", MyColor1, MyColor2, WHITE));

    operationButtons.push_back(Button(120, 50, 100, 30, "Create", MyColor1, MyColor2, WHITE));
    operationButtons.push_back(Button(120, 90, 100, 30, "Delete", MyColor1, MyColor2, WHITE));
    operationButtons.push_back(Button(120, 130, 100, 30, "Search", MyColor1, MyColor2, WHITE));
    currentOperation = Operation::Insert;

    Ok = Button(10 + screenWidth*0.25f - 100, screenHeight / 2 - screenHeight*0.63f * 0.17f, 73, screenHeight*0.63f * 0.15f, "OK", MyColor1, MyColor2, WHITE);

    isPlaying = false;
    head = MyRec(0, 10, (float) screenWidth, screenHeight*0.08f, getMODE().c_str(), MyColor2, WHITE);
    home = ButtonFromImage("res/button/back.png", "res/button/back-isOver.png", screenWidth*0.016f, screenHeight*0.016f, screenWidth*0.05f, screenWidth*0.05f); 
    home2 = ButtonFromImage("res/button/homeII_1.png", "res/button/homeII_2.png", screenWidth*0.016f, screenHeight*0.016f, screenWidth*0.05f, screenWidth*0.05f); 

    back1 = ButtonFromImage("res/button/1-prev.png", "res/button/1-prev.png", screenWidth / 2 -   screenWidth * 0.05f * 3 / 2 - 20 , screenHeight*0.926f,  screenWidth * 0.04f, screenWidth*0.04f);
    next1 = ButtonFromImage("res/button/1-next.png", "res/button/1-next.png", screenWidth / 2 +   screenWidth * 0.05f , screenHeight*0.926f,  screenWidth * 0.04f, screenWidth*0.04f);
    play1 = ButtonFromImage("res/button/1-play.png", "res/button/1-play.png", screenWidth / 2 -   screenWidth * 0.05f / 2  , screenHeight*0.92f,  screenWidth * 0.05f, screenWidth*0.05f);
    pause1 = ButtonFromImage("res/button/1-pause.png", "res/button/1-pause.png", screenWidth / 2 -   screenWidth * 0.05f / 2  , screenHeight*0.92f,  screenWidth * 0.05f, screenWidth*0.05f);
    back2 = ButtonFromImage("res/button/2-prev.png", "res/button/2-prev.png", screenWidth / 2 -   screenWidth * 0.05f * 3 / 2 - 20 , screenHeight*0.926f,  screenWidth * 0.04f, screenWidth*0.04f);
    next2 = ButtonFromImage("res/button/2-next.png", "res/button/2-next.png", screenWidth / 2 +   screenWidth * 0.05f , screenHeight*0.926f,  screenWidth * 0.04f, screenWidth*0.04f);
    pause2 = ButtonFromImage("res/button/2-pause.png", "res/button/2-pause.png", screenWidth / 2 -   screenWidth * 0.05f / 2  , screenHeight*0.92f,  screenWidth * 0.05f, screenWidth*0.05f);
    play2 = ButtonFromImage("res/button/2-play.png", "res/button/2-play.png", screenWidth / 2 -   screenWidth * 0.05f / 2  , screenHeight*0.92f,  screenWidth * 0.05f, screenWidth*0.05f);
    animationSpeed = 1.0f;
    speedSliding = MyRec(screenWidth * 0.723f , screenHeight*0.936f,  screenWidth * 0.182f * 0.38f,screenHeight * 0.095f / 3 * 0.9f, "", MyColor3, WHITE);
    background1 = resizedImage("res/BackGround.png", screenWidth, screenHeight);   
    background2 = resizedImage("res/background_theme2.png", screenWidth, screenHeight);    
    bottom = {0,screenHeight*0.905f,(float)screenWidth,screenHeight*0.095f};
    side = {0,screenHeight / 2 - screenHeight * 0.64f / 2,screenWidth*0.24f,screenHeight*0.64f};
    textbox = TextBox(5, screenHeight / 2 - screenHeight*0.63f * 0.17f, screenWidth*0.25f - 100, screenHeight*0.63f * 0.15f, "", WHITE, WHITE, BLACK);
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
    DrawRectangleRounded({screenWidth * 0.7f , screenHeight*0.934f , screenWidth * 0.182f,screenHeight * 0.095f / 3}, 20, 20, WHITE); //speed control
    speedSliding.DrawRounded(MyColor3);
    stringstream ss;
    ss << fixed << std::setprecision(1) << animationSpeed;
    std::string formattedSpeed = ss.str();
    DrawText(formattedSpeed.c_str(), screenWidth * 0.9f, screenHeight * 0.934f, 20, WHITE);
    if(currentInput != InputType::File){
    Ok.Draw(MyColor1, MyColor2);
    textbox.Draw();
    }
    else{
        DrawRectangle(5, screenHeight / 2 - screenHeight*0.63f * 0.17f, screenWidth*0.24f - 10, screenHeight*0.63f * 0.15f, WHITE);
        DrawText("DROP FILE HERE", 30, screenHeight / 2 - screenHeight*0.63f * 0.118f, 25, GRAY);
        //drop file field
    }

    if(switchState){
        !isPlaying ? play2.Draw() : pause2.Draw();
        back2.Draw();
        next2.Draw();
        home2.Draw(); }
    else{ 
        !isPlaying ? play1.Draw() : pause1.Draw();
        back1.Draw();
        next1.Draw();
        home.Draw();
    }
    optionButton.Draw( LIGHTGRAY, WHITE);
    prevButton.Draw(LIGHTGRAY, WHITE);
    nextButton.Draw(LIGHTGRAY, WHITE);
    if(currentOperation == Operation::Insert){
        insertButton.Draw(MyColor1, Fade(MyColor1, 0.8f));
        if (isInsertExpanded) {
             DrawTextEx(FONT, "<", {screenWidth*0.22f, screenHeight / 2 - screenHeight*0.63f * 0.44f}, 30, 30, WHITE);
            DrawRectangle(0,0,screenWidth,screenHeight,Fade(GRAY, 0.2));
            
            operationButtons[1].Draw(MyColor1, Fade(MyColor1, 0.8f));  
            operationButtons[2].Draw(MyColor1, Fade(MyColor1, 0.8f)); 
            operationButtons[3].Draw(MyColor1, Fade(MyColor1, 0.8f));  
        }
         else{
       DrawTextEx(FONT, ">", {screenWidth*0.22f, screenHeight / 2 - screenHeight*0.63f * 0.44f}, 30, 30, WHITE);
    }
    }
     if (currentOperation == Operation::Create){
        createButton.Draw(MyColor1, Fade(MyColor1, 0.8f));
        if (isCreateExpanded) {
             DrawTextEx(FONT, "<", {screenWidth*0.22f, screenHeight / 2 - screenHeight*0.63f * 0.44f}, 30, 30, WHITE);
            DrawRectangle(0,0,screenWidth,screenHeight,Fade(GRAY, 0.2));
            operationButtons[0].Draw(MyColor1, Fade(MyColor1, 0.8f));  
            operationButtons[2].Draw(MyColor1, Fade(MyColor1, 0.8f)); 
            operationButtons[3].Draw(MyColor1, Fade(MyColor1, 0.8f));  
        }
         else{
       DrawTextEx(FONT, ">", {screenWidth*0.22f, screenHeight / 2 - screenHeight*0.63f * 0.44f}, 30, 30, WHITE);
    }
    }
     if(currentOperation == Operation::Delete){
        deleteButton.Draw(MyColor1, Fade(MyColor1, 0.8f));
        if (isDeleteExpanded) {
             DrawTextEx(FONT, "<", {screenWidth*0.22f, screenHeight / 2 - screenHeight*0.63f * 0.44f}, 30, 30, WHITE);
            DrawRectangle(0,0,screenWidth,screenHeight,Fade(GRAY, 0.2));
            operationButtons[0].Draw(MyColor1, Fade(MyColor1, 0.8f));  
            operationButtons[1].Draw(MyColor1, Fade(MyColor1, 0.8f)); 
            operationButtons[3].Draw(MyColor1, Fade(MyColor1, 0.8f));  
        }
         else{
       DrawTextEx(FONT, ">", {screenWidth*0.22f, screenHeight / 2 - screenHeight*0.63f * 0.44f}, 30, 30, WHITE);
    }
    }
     if (currentOperation == Operation::Search){
        searchButton.Draw(MyColor1, Fade(MyColor1, 0.8f));
        if (isSearchExpanded) {
             DrawTextEx(FONT, "<", {screenWidth*0.22f, screenHeight / 2 - screenHeight*0.63f * 0.44f}, 30, 30, WHITE);
            DrawRectangle(0,0,screenWidth,screenHeight,Fade(GRAY, 0.2));
            operationButtons[0].Draw(MyColor1, Fade(MyColor1, 0.8f));  
            operationButtons[1].Draw(MyColor1, Fade(MyColor1, 0.8f)); 
            operationButtons[2].Draw(MyColor1, Fade(MyColor1, 0.8f));  
        }
         else{
       DrawTextEx(FONT, ">", {screenWidth*0.22f, screenHeight / 2 - screenHeight*0.63f * 0.44f}, 30, 30, WHITE);
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

    handleInput();

    //speed sliding event
    Vector2 mousePoint = GetMousePosition();
    float minX = screenWidth * 0.7f + 1;
    float maxX = screenWidth * 0.7f + screenWidth * 0.181f - speedSliding.bounds.width;
    if (CheckCollisionPointRec(mousePoint, speedSliding.bounds) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        float clampedMouseX = clamp(mousePoint.x - speedSliding.bounds.width / 2, minX, maxX);
        speedSliding.bounds.x = clampedMouseX;
        cout << speedSliding.bounds.x << endl;
    }
    animationSpeed = clamp(static_cast<float>((speedSliding.bounds.x - minX) * 5 / (maxX - minX)), 0.1f, 5.0f);

    //play & pause event
    if(!isPlaying){
        if(!switchState ? play1.IsClicked() : play2.IsClicked()){
            isPlaying = true;
            TraceLog(LOG_INFO, "is playing");
        }
    }
    else{
        if( isPlaying && !switchState ? pause1.IsClicked() : pause2.IsClicked())
        {
            isPlaying = false;
            TraceLog(LOG_INFO, "is pausing");
        }
    }

    //Operation event
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

    //INPUT Event

    if (prevButton.IsClicked()) {
        selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
        optionButton.label = options[selectedIndex].c_str(); 
    }

    if (nextButton.IsClicked()) {
        selectedIndex = (selectedIndex + 1) % options.size();
        optionButton.label = options[selectedIndex].c_str(); 
    }

        if (options[selectedIndex] == "KEYBOARD") currentInput = InputType::Keyboard;
        if (options[selectedIndex] == "RANDOM") currentInput = InputType::Random;
        if (options[selectedIndex] == "FILE") currentInput = InputType::File;
}

void Page::handleInput(){

    switch (currentInput) {
            case InputType::Random:
                if(optionButton.IsClicked()){
                textbox.inputText = to_string(rand() % 1000); 
                }
                break;
            case InputType::Keyboard:
                textbox.HandleInput(); 
                break;
            case InputType::File:
                if(IsFileDropped()){
                    FilePathList droppedFiles = LoadDroppedFiles();
                    TextCopy(filePath,droppedFiles.paths[0]);
                    ifstream fin(filePath);
                    if(!fin.is_open()) cout << "Cannot open dropped file";
                    else{
                        textbox.resetTextbox();
                        int val;
                         while (fin >> val) {
                            textbox.nums.push_back(val);
                        }       
                        fin.close();
                    }
                    UnloadDroppedFiles(droppedFiles); 
                }
                break;
            default:
                break;
        }

        if (IsKeyPressed(KEY_BACKSPACE) && !textbox.inputText.empty()) {
                textbox.inputText.pop_back();
            }

        if ((Ok.IsClicked() || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) && !textbox.inputText.empty()) {
            textbox.nums.push_back(stoi(textbox.inputText));
            TraceLog(LOG_INFO, textbox.inputText.c_str());
            textbox.inputText = "";
        }    

}

