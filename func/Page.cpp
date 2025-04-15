#include <raylib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <random>
#include <raymath.h>
#include "ControlAnimation.h"
#include "Page.h"
#include "Variables.h"
using namespace std;

int lastInsertedKey;



void Page::updateSide(){
    InputOptionButton.bounds = Rectangle{side.x + (side.x + side.width) * 0.15f, side.y + screenHeight*0.63f * 0.15f + 10 , screenWidth*0.24f * 0.7f, screenHeight*0.63f * 0.15f};
    InputPrevButton.bounds = Rectangle{side.x + 5,side.y + screenHeight*0.63f * 0.15f + 10 ,  screenWidth*0.24f * 0.15f - 10, screenHeight*0.63f * 0.15f};
    InputNextButton.bounds = Rectangle{side.x + (side.x + side.width) * 0.85f + 5, side.y + screenHeight*0.63f * 0.15f + 10,  screenWidth*0.24f * 0.15f - 10, screenHeight*0.63f * 0.15f};
    OperationOptionButton.bounds = Rectangle{side.x + (side.x + side.width) * 0.15f, side.y + 5, screenWidth*0.24f * 0.7f, screenHeight*0.63f * 0.15f};
    OperationPrevButton.bounds = Rectangle{side.x + 5, side.y + 5, screenWidth*0.24f * 0.15f - 10, screenHeight*0.63f * 0.15f};
    OperationNextButton.bounds = Rectangle{side.x + (side.x + side.width) * 0.85f + 5,side.y + 5,  screenWidth*0.24f * 0.15f - 10,screenHeight*0.63f * 0.15f};
    Ok.bounds = Rectangle{side.x + (side.x  + side.width) * 0.74f, side.y + screenHeight*0.63f * 0.3f + 15, 73, screenHeight*0.63f * 0.15f};
    textbox.bounds = Rectangle{side.x + 5, side.y + screenHeight*0.63f * 0.3f + 15, screenWidth*0.25f - 100, screenHeight*0.63f * 0.15f};
    oldTextBox.bounds = Rectangle{side. x + 5, side.y + screenHeight*0.63f * 0.36f, screenWidth*0.08f, screenHeight*0.63f * 0.11f};
    newTextBox.bounds = Rectangle{side.x + screenWidth*0.08f + 10, side.y + screenHeight*0.63f * 0.36f, screenWidth*0.08f, screenHeight*0.63f * 0.11f};
    theme.bounds = {setting_menu.x + setting_menu.width * 0.6f, setting_menu.y + 5, setting_menu.width*0.3f, setting_menu.width*0.3f * 0.61f};

}

void Page::init() {
    FONT2 = LoadFont("res/font/MouldyCheeseRegular-WyMWG.ttf"); 
    selectedInputIndex = 0;
    InputOptionButton = Button((side.x + side.width) * 0.15f, side.y + screenHeight*0.63f * 0.15f + 10 , screenWidth*0.24f * 0.7f, screenHeight*0.63f * 0.15f, InputOptions[selectedInputIndex].c_str(), WHITE, LIGHTGRAY, MyColor5);
    InputPrevButton = Button(side.x + 5,side.y + screenHeight*0.63f * 0.15f + 10 ,  screenWidth*0.24f * 0.15f - 10, screenHeight*0.63f * 0.15f, "<", WHITE, LIGHTGRAY, MyColor5);
    InputNextButton = Button((side.x + side.width) * 0.85f + 5, side.y + screenHeight*0.63f * 0.15f + 10,  screenWidth*0.24f * 0.15f - 10, screenHeight*0.63f * 0.15f, ">", WHITE, LIGHTGRAY, MyColor5);
    currentInput = InputType::Keyboard;

    OperationOptions  = {"INSERT", "CREATE", "DELETE", "SEARCH", "UPDATE"};
    selectedOperationIndex = 0;
    OperationOptionButton = Button((side.x + side.width) * 0.15f, side.y + 5, screenWidth*0.24f * 0.7f, screenHeight*0.63f * 0.15f, OperationOptions[selectedOperationIndex].c_str(), MyColor7, Fade(MyColor7, 0.8f), WHITE);
    OperationPrevButton = Button(side.x + 5, side.y + 5, screenWidth*0.24f * 0.15f - 10, screenHeight*0.63f * 0.15f, "<", MyColor7, Fade(MyColor7, 0.8f), WHITE);
    OperationNextButton = Button((side.x + side.width) * 0.85f + 5,side.y + 5,  screenWidth*0.24f * 0.15f - 10,screenHeight*0.63f * 0.15f, ">", MyColor7, Fade(MyColor7, 0.8f), WHITE);
    currentOperation = Operation::Insert;

    Ok = Button((side.x  + side.width) * 0.74f, side.y + screenHeight*0.63f * 0.3f + 15, 73, screenHeight*0.63f * 0.15f, "OK", MyColor1, MyColor2, WHITE);
    head = MyRec(0, 10, (float) screenWidth, screenHeight*0.08f, getMODE().c_str(), MyColor2, WHITE);
    home = ButtonFromImage("res/button/back.png", "res/button/back-isOver.png", screenWidth*0.016f, screenHeight*0.016f, screenWidth*0.05f, screenWidth*0.05f); 
    home2 = ButtonFromImage("res/button/homeII_1.png", "res/button/homeII_2.png", screenWidth*0.016f, screenHeight*0.016f, screenWidth*0.05f, screenWidth*0.05f); 

    isPlaying = false;
    back1 = ButtonFromImage("res/button/1_backward.png", "res/button/1_backward.png", screenWidth / 2 -   screenWidth * 0.05f * 3 / 2 , screenHeight*0.926f,  screenWidth * 0.04f, screenWidth*0.04f );
    backward1 = ButtonFromImage("res/button/1-prev.png", "res/button/1-prev.png", screenWidth / 2 -   screenWidth * 0.05f * 3 / 2 - 25  - screenWidth * 0.04f, screenHeight*0.926f,  screenWidth * 0.04f, screenWidth*0.04f);
    next1 = ButtonFromImage("res/button/1_forward.png", "res/button/1_forward.png", screenWidth / 2 +   screenWidth * 0.05f - 20, screenHeight*0.926f,  screenWidth * 0.04f, screenWidth*0.04f );
    forward1 = ButtonFromImage("res/button/1-next.png", "res/button/1-next.png", screenWidth / 2 +   screenWidth * 0.05f  + 5 + screenWidth * 0.04f, screenHeight*0.926f,  screenWidth * 0.04f, screenWidth*0.04f);
    play1 = ButtonFromImage("res/button/1-play.png", "res/button/1-play.png", screenWidth / 2 -   screenWidth * 0.05f / 2  , screenHeight*0.92f,  screenWidth * 0.05f, screenWidth*0.05f);
    pause1 = ButtonFromImage("res/button/1-pause.png", "res/button/1-pause.png", screenWidth / 2 -   screenWidth * 0.05f / 2  , screenHeight*0.92f,  screenWidth * 0.05f, screenWidth*0.05f);
    backward2 = ButtonFromImage("res/button/2-prev.png", "res/button/2-prev.png",screenWidth / 2 -   screenWidth * 0.05f * 3 / 2 - 25  - screenWidth * 0.04f, screenHeight*0.926f,  screenWidth * 0.04f, screenWidth*0.04f);
    back2 = ButtonFromImage("res/button/2_backward.png", "res/button/2_backward.png", screenWidth / 2 -   screenWidth * 0.05f * 3 / 2 , screenHeight*0.926f,  screenWidth * 0.04f, screenWidth*0.04f );
    next2 = ButtonFromImage("res/button/2_forward.png", "res/button/2_forward.png", screenWidth / 2 +   screenWidth * 0.05f - 20, screenHeight*0.926f,  screenWidth * 0.04f, screenWidth*0.04f );
    forward2 = ButtonFromImage("res/button/2-next.png", "res/button/2-next.png", screenWidth / 2 +   screenWidth * 0.05f  + 5 + screenWidth * 0.04f, screenHeight*0.926f,  screenWidth * 0.04f, screenWidth*0.04f);
    pause2 = ButtonFromImage("res/button/2-pause.png", "res/button/2-pause.png", screenWidth / 2 -   screenWidth * 0.05f / 2  , screenHeight*0.92f,  screenWidth * 0.05f, screenWidth*0.05f);
    play2 = ButtonFromImage("res/button/2-play.png", "res/button/2-play.png", screenWidth / 2 -   screenWidth * 0.05f / 2  , screenHeight*0.92f,  screenWidth * 0.05f, screenWidth*0.05f);
    // timeSlider = Slider({screenWidth * 0.05f , screenHeight*0.936f,  screenWidth * 0.3f ,screenHeight * 0.095f / 3 * 0.9f}, 0.0f, 1.0f);
    
    codeDisplayPLace = Rectangle{screenWidth * 0.01f, screenHeight * 0.56f, screenWidth * 0.24f - 12.0f, screenHeight * 0.35f};
    speedSliding = MyRec(screenWidth * 0.712f , screenHeight*0.936f,  screenWidth * 0.182f * 0.38f,screenHeight * 0.095f / 3 * 0.9f, "", MyColor3, WHITE);
    background1 = resizedImage("res/BackGround.png", screenWidth, screenHeight);   
    background2 = resizedImage("res/background_theme2.png", screenWidth, screenHeight);    
    bottom = {screenWidth / 2 -   screenWidth * 0.05f * 3 / 2 - 50 - screenWidth * 0.04f,screenHeight*0.905f,(float) (screenWidth * 0.31),screenHeight*0.09f};
    pseudocode = {""};
    pseudocodeX = codeDisplayPLace.x  + 5;
    pseudocodeY = codeDisplayPLace.y  + 10;
    side = {0,screenHeight / 2 - screenHeight * 0.64f / 2,screenWidth*0.24f,screenHeight*0.305f};
    textbox = TextBox(side.x + 5, side.y + screenHeight*0.63f * 0.3f + 15, screenWidth*0.25f - 100, screenHeight*0.63f * 0.15f, "", WHITE, WHITE, BLACK);
    oldTextBox = TextBox(side. x + 5, side.y + screenHeight*0.63f * 0.36f, screenWidth*0.08, screenHeight*0.63f * 0.11f, "", WHITE, WHITE, BLACK);
    newTextBox = TextBox(side.x + screenWidth*0.08f + 10, side.y + screenHeight*0.63f * 0.36f, screenWidth*0.08, screenHeight*0.63f * 0.11f, "", WHITE, WHITE, BLACK);
    oldTextBox.resetTextbox();
    newTextBox.resetTextbox();
    textbox.resetTextbox();
    lineHeight = 20.0f;

    setting_menu = Rectangle{screenWidth * 0.8f, screenHeight * 0.7f, screenWidth * 0.19f, screenHeight * 0.18f};
    theme = SwitchThemeButton(setting_menu.x + 5, setting_menu.y + 5, setting_menu.width*0.43f, 50, "", MyColor1, MyColor1, WHITE);

    camera.target = { (float)GetScreenWidth()/2, (float)GetScreenHeight()/2 };
        camera.offset = { (float)GetScreenWidth()/2, (float)GetScreenHeight()/2 };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
}

void Page::reset(){
    isExpanding             = false;
    isExpandingCodePlace    = false;
    isClosingCodePlace      = false;
    isExpandingSide         = false;
    isClosingSide           = false;
    selectedInputIndex      = 0;
    selectedOperationIndex  = 0;
    textbox.reset();
}

void Page::draw() {
    ClearBackground(RAYWHITE);
    DrawTexture(switchState ? background2 : background1, 0, 0, WHITE);
    head.Draw(MyColor2, getMODE());
    DrawRectangleRounded(bottom, 20, 20, MyColor2);
    DrawRectangleRec(side, MyColor3);
    DrawRectangleRounded({-10, screenHeight / 2 - screenHeight * 0.64f / 2, 30,screenHeight*0.305f }, 0.5f, 30, MyColor3);
    DrawText(">", 5, screenHeight / 2 - screenHeight * 0.64f / 2 + screenHeight*0.305f /2.0f, 20, WHITE);
    DrawRectangleRounded(codeDisplayPLace, 0.1f, 40,MyColor6);
    DrawRectangleRoundedLinesEx(codeDisplayPLace, 0.1f, 20, 4, MyColor3);
    DrawRectangleRounded({screenWidth * 0.7f , screenHeight*0.934f , screenWidth * 0.182f,screenHeight * 0.095f / 3}, 20, 20, WHITE); //speed control
    speedSliding.DrawRounded(MyColor3);

    //SETTING
     DrawRectangleRounded(setting_menu, 0.42f, 30, MyColor3);
    theme.Draw();
    DrawTextEx(FONT, "THEME", {setting_menu.x + 20, setting_menu.y + 18}, 30, 2, WHITE);


    // timeSlider.Draw();
    stringstream ss;
    ss << fixed << std::setprecision(1) << animationSpeed;
    std::string formattedSpeed = ss.str();
    formattedSpeed.push_back('x');
    DrawText(formattedSpeed.c_str(), screenWidth * 0.906f, screenHeight * 0.935f, 30, WHITE);

    if(currentInput != InputType::File){
        if (currentOperation == Operation::Update) {
            DrawTextEx(FONT, "OLD", {oldTextBox.bounds.x + oldTextBox.bounds.width /2 - 20, oldTextBox.bounds.y - 20}, 20, 2, WHITE);
            DrawTextEx(FONT ,"NEW", {newTextBox.bounds.x + newTextBox.bounds.width / 2 - 20, newTextBox.bounds.y - 20}, 20, 2, WHITE);
            
            newTextBox.Draw(20); 
            oldTextBox.Draw(20);
        }
        else {
            textbox.Draw();
        }

        Ok.Draw(Fade(MyColor2, 0.7f), MyColor2);
    }
    else{
        DrawRectangle(side.x * 1.2f + 5, side.y + screenHeight*0.63f * 0.3f + 15, screenWidth*0.24f - 10, screenHeight*0.63f * 0.15f, WHITE);
        DrawText("DROP FILE HERE", side.x * 1.2f + 30, screenHeight / 2 - screenHeight*0.63f * 0.118f, 25, GRAY);
        //drop file field
    }
    

    if(switchState){
        isPlaying ? play2.Draw() : pause2.Draw();
        backward2.Draw();
        forward2.Draw();
        back2.Draw();
        next2.Draw();
        home2.Draw(); }
    else{ 
        isPlaying ? play1.Draw() : pause1.Draw();
        backward1.Draw();
        forward1.Draw();
        back1.Draw();
        next1.Draw();
        home.Draw();
    }
    //Input
    if(currentOperation != Operation::Algorithm){
        InputOptionButton.textColor = MyColor5;
        InputOptionButton.Draw(LIGHTGRAY, WHITE);
        InputPrevButton.Draw(LIGHTGRAY, WHITE);
        InputNextButton.Draw(LIGHTGRAY, WHITE);
    }
    //Operation
    OperationOptionButton.Draw(Fade(MyColor7, 0.8f), MyColor7);
    OperationPrevButton.Draw(Fade(MyColor7, 0.8f), MyColor7);
    OperationNextButton.Draw(Fade(MyColor7, 0.8f), MyColor7);
}
float Page::Lerp(float start, float end, float amount) {
    return start + amount * (end - start);
}

void Page::event() {
    if(!switchState ? home.IsClicked(): home2.IsClicked() ) {
        mode = MODE::MENU;

        reset();
        return;
    }
    float deltaTime = GetFrameTime();
    Vector2 mousePos = GetMousePosition();
    //SETTING
    Rectangle targetPlace = Rectangle{screenWidth * 0.8f, screenHeight * 0.7f, screenWidth * 0.19f, screenHeight * 0.18f};
    Rectangle closedPlace = Rectangle{(float) screenWidth * 0.99f, screenHeight * 0.7f, screenWidth * 0.19f, screenHeight * 0.18f};
    Rectangle checkPlace = Rectangle{screenWidth * 0.9f, screenHeight * 0.7f, screenWidth * 0.5f, screenHeight * 0.18f};
  
        if (CheckCollisionPointRec(mousePos, targetPlace)) {
        if(CheckCollisionPointRec(mousePos, checkPlace)){
        setting_IsOpening = true;
        setting_IsClosing = false;
        animatingTime = 0;
        }
    } else {
        setting_IsClosing = true;
        setting_IsOpening = false;
        animatingTime = 0;
    }

    if (setting_IsOpening) {
        animatingTime += deltaTime;
        float t = animatingTime / 0.1f;
        if (t > 1.0f) {
            t = 1.0f;
            animatingTime = 0.0f;
            setting_IsOpening = false;
        }
        setting_menu.x = Lerp(setting_menu.x, targetPlace.x, t); 
    } else if (setting_IsClosing) {
        animatingTime += deltaTime;
        float t = animatingTime / 0.1f;
        if (t > 1.0f) {
            t = 1.0f;
            animatingTime = 0.0f;
            setting_IsClosing = false;
        }
        setting_menu.x = Lerp(setting_menu.x, closedPlace.x, t);
    }

    //Code state
    pseudocodeX = codeDisplayPLace.x  + 5;
    pseudocodeY = codeDisplayPLace.y  + 10;
    
    
    //cout << lineHeight << endl;
    //animation thui
    Rectangle targetPlace1 = codeDisplayPLace;
    targetPlace1.height = pseudocode.size() * lineHeight + 10;
    targetPlace1.width = textWidth * 1.02f;
    Rectangle deltaRec = targetPlace1 - codeDisplayPLace;
    if(deltaRec != Rectangle{0,0,0,0}) isExpanding = true;
    if(isExpanding){
    animatingTime += deltaTime;
    float t = animatingTime / 0.2f;
    if(t > 1){
        t = 1;
        isExpanding = false;
        animatingTime = 0;
    }
    codeDisplayPLace = codeDisplayPLace + deltaRec * t;
    }
    // TỰ LÀM PHẦN HIGHLIGHT!!!! tham khảo Graph.draw() && psuedo code thi tuy phan

    //Code box event
    Rectangle targetCodePlace = Rectangle{screenWidth * 0.01f, screenHeight * 0.56f, screenWidth * 0.24f - 12.0f, screenHeight * 0.35f};
    Rectangle closeCodePlace = Rectangle{-codeDisplayPLace.width, screenHeight * 0.56f, screenWidth * 0.24f - 12.0f, screenHeight * 0.35f};


    if(isExpandingCodePlace){
        animatingTime += deltaTime;
        float t = animatingTime / 0.2f; // 0.2 is the time interval when animating
        if (t > 1.0f) {
            t = 1.0f;
            animatingTime = 0.0f;
            isExpandingCodePlace = false;
        }
        codeDisplayPLace.x = Lerp(codeDisplayPLace.x, targetCodePlace.x, t); 
    }
    else if (isClosingCodePlace) {
        animatingTime += deltaTime;
        float t = animatingTime / 0.2f; // 0.2 is the time interval when animating
        if (t > 1.0f) {
            t = 1.0f;
            animatingTime = 0.0f;
            isClosingCodePlace = false;
        }
        codeDisplayPLace.x = Lerp(codeDisplayPLace.x, closeCodePlace.x, t); 
    }

    //side event
    
    float sideDuration =0.2f; 
    Rectangle targetPlace2 = Rectangle{0, screenHeight / 2 - screenHeight * 0.64f / 2, screenWidth * 0.3f, screenHeight * 0.54f}; 
    Rectangle closedPlace2 = Rectangle{-side.width, screenHeight / 2 - screenHeight * 0.64f / 2, screenWidth * 0.24f, screenHeight * 0.32f}; 
    Rectangle sidePlace = Rectangle{0,screenHeight / 2 - screenHeight * 0.64f / 2,screenWidth*0.12f,screenHeight*0.32f};
    if (CheckCollisionPointRec(mousePos, targetPlace2)) {
        if(CheckCollisionPointRec(mousePos, sidePlace)){
            isExpandingSide = true;
            isClosingSide = false;
            animatingTime = 0;
        }
    } else {
        isClosingSide = true;
        isExpandingSide = false;
        animatingTime = 0;
    }

    if (isExpandingSide) {
        animatingTime += deltaTime;
        float t = animatingTime / sideDuration;
        if (t > 1.0f) {
            t = 1.0f;
            animatingTime = 0.0f;
            isExpandingSide = false;
        }
        side.x = Lerp(side.x, targetPlace2.x, t); 
    } else if (isClosingSide) {
        animatingTime += deltaTime;
        float t = animatingTime / sideDuration;
        if (t > 1.0f) {
            t = 1.0f;
            animatingTime = 0.0f;
            isClosingSide = false;
        }
        side.x = Lerp(side.x, closedPlace2.x, t);
    }

    updateSide();


    //speed sliding event
    Vector2 mousePoint = GetMousePosition();
    float minX = screenWidth * 0.7f + 1;
    float maxX = screenWidth * 0.7f + screenWidth * 0.181f - speedSliding.bounds.width;
    if (CheckCollisionPointRec(mousePoint, speedSliding.bounds) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        float clampedMouseX = clamp(mousePoint.x - speedSliding.bounds.width / 2, minX, maxX);
        speedSliding.bounds.x = clampedMouseX;
    }
    animationSpeed = clamp(static_cast<float>((speedSliding.bounds.x - minX) * 10 / (maxX - minX)), 0.1f, 10.0f);
    animationSpeed = round(animationSpeed * 10.0) / 10.0; // round up to 1 decimal

    //time slider
    // timeSlider.Update();

    if(play1.IsClicked() || play2.IsClicked() || pause1.IsClicked() || pause2.IsClicked() || (!textbox.active &&  IsKeyPressed(KEY_SPACE))){
        isPlaying = !isPlaying;
        if(!isPlaying) TraceLog(LOG_INFO, "is pausing");
        else TraceLog(LOG_INFO, "is playing");
    }

    //Operation event
   if (OperationPrevButton.IsClicked()) {
        textbox.reset();
        selectedInputIndex = 0;
        selectedOperationIndex = (selectedOperationIndex - 1 + OperationOptions.size()) % OperationOptions.size();
    }

    if (OperationNextButton.IsClicked()) {
        textbox.reset();
        selectedInputIndex = 0;
        selectedOperationIndex = (selectedOperationIndex + 1) % OperationOptions.size();
    }
     OperationOptionButton.label = OperationOptions[selectedOperationIndex].c_str(); 
    if(OperationOptions[selectedOperationIndex] == "INSERT") currentOperation = Operation::Insert;
    if(OperationOptions[selectedOperationIndex] == "CREATE") currentOperation = Operation::Create;
    if(OperationOptions[selectedOperationIndex] == "SEARCH") currentOperation = Operation::Search;
    if(OperationOptions[selectedOperationIndex] == "UPDATE") currentOperation = Operation::Update;
    if(OperationOptions[selectedOperationIndex] == "DELETE") currentOperation = Operation::Delete;

    //INPUT Event
        
    handleInput();

    if (InputPrevButton.IsClicked()) {
        selectedInputIndex = (selectedInputIndex - 1 + InputOptions.size()) % InputOptions.size();
        if(currentOperation != Operation::Insert && currentOperation != Operation::Create){
            if(selectedInputIndex == 2) selectedInputIndex = 1;
            
        }
        
    }

    if (InputNextButton.IsClicked()) {
        selectedInputIndex = (selectedInputIndex + 1) % InputOptions.size();
        if(currentOperation != Operation::Insert && currentOperation != Operation::Create){
            if(selectedInputIndex == 2) selectedInputIndex = 0;
        }
    }
    InputOptionButton.label = InputOptions[selectedInputIndex].c_str(); 
    if (InputOptions[selectedInputIndex] == "KEYBOARD") currentInput = InputType::Keyboard;
    if (InputOptions[selectedInputIndex] == "RANDOM") currentInput = InputType::Random;
    if (InputOptions[selectedInputIndex] == "FILE") currentInput = InputType::File;


    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        // camera.target = GetMousePosition();
        camera.zoom += wheel * 0.1f;
        if (camera.zoom < 0.2f) camera.zoom = 0.2f;
        if (camera.zoom > 5.0f) camera.zoom = 5.0f;
    }
 
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if(!CheckCollisionPointRec(GetMousePosition(), side) && !CheckCollisionPointRec(mousePoint, speedSliding.bounds) ){
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / camera.zoom);
        camera.target = Vector2Add(camera.target, delta);
        }
    }
}

std::mt19937 rng(std::random_device{}());
void Page::RANDOM_INPUT(){
    std::uniform_int_distribution<int> dist(0, 999); // Giới hạn số từ 0-999
    textbox.inputText = {to_string(dist(rng))}; // Lấy số ngẫu nhiên
    
}
void Page::KEYBOARD_INPUT(){
     textbox.HandleInput();
}
void Page::FILE_INPUT(){
    if(IsFileDropped()){
        FilePathList droppedFiles = LoadDroppedFiles();
        TextCopy(filePath,droppedFiles.paths[0]);
        ifstream fin(filePath);
        if(!fin.is_open()) cout << "Cannot open dropped file";
        else{
            textbox.reset();
            int val;
                while (fin >> val) {
                textbox.nums.push_back(val);
            }       
            fin.close();
        }
        UnloadDroppedFiles(droppedFiles); 
    }
}

void Page::handleInput(){

    if(currentOperation == Operation::Update){
        oldTextBox.update();
    newTextBox.update();
    }
    else{
        textbox.update();
    }
     switch (currentOperation) {
        case Operation::Insert:
        case Operation::Create:
            switch (currentInput) {
            case InputType::Random:
                    if (InputOptionButton.IsClicked()) {
                        textbox.reset();
                        RANDOM_INPUT();
                    }
                    textbox.HandleInput();
            break;
            case InputType::Keyboard:
                KEYBOARD_INPUT();
                break;
            case InputType::File:
               FILE_INPUT();
                break;
            default:
                break;
            }
            break;

        case Operation::Search:
        case Operation::Delete:
            switch (currentInput) {
            case InputType::Random:
                if (InputOptionButton.IsClicked()) RANDOM_INPUT();
                textbox.HandleInput();
            break;
            case InputType::Keyboard:
                KEYBOARD_INPUT();
                break;
            default:
                break;
            }

            break;

        case Operation::Update:
            switch (currentInput) {
                case InputType::Random:
                    if (InputOptionButton.IsClicked()) {
                        std::uniform_int_distribution<int> dist(0, 999); 
                        newTextBox.inputText = {to_string(dist(rng))}; 
                        oldTextBox.inputText = {to_string(dist(rng))}; 
                    }
                    newTextBox.HandleInput();
                    oldTextBox.HandleInput();
                    break;
                case InputType::Keyboard:
                    newTextBox.HandleInput();
                    oldTextBox.HandleInput();
                    break;
            }
            break;
        // case Operation::Algorithm:
        //     textbox.HandleInput();
        //     break;
    }

        if ((Ok.IsClicked())) {
            if(currentOperation == Operation::Update){
                if(!oldTextBox.inputText.empty() && !newTextBox.inputText.empty() ){
                    int val = stoi(oldTextBox.inputText[0]);
                    textbox.nums.push_back(val);
                    val = stoi(newTextBox.inputText[0]);
                    textbox.nums.push_back(val);
                    //textbox.nums[0] is old value, [1] is new
                    oldTextBox.resetTextbox();
                    newTextBox.resetTextbox();
                }
            }
            else{
                if(!textbox.inputText.empty()){
                    int val;
                    for(auto& s : textbox.inputText){
                        stringstream ss(s);
                        while(ss >> val){
                            textbox.nums.push_back(val);
                        }
                    }
                    textbox.resetTextbox();
                }
            }

        }    
}

