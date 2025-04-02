#pragma once

#include<raylib.h>
#include "Button.h"
#include "Variables.h"

using namespace std;


enum class Operation {
    Insert,
    Create,
    Delete,
    Search,
    Update,
    Algorithm
};

enum class InputType {
    Random,
    Keyboard,
    File
};
class Page {
protected:
vector<string> OperationOptions;
public:
    //input
    InputType currentInput;
    vector<string> InputOptions = {"RANDOM", "KEYBOARD", "FILE"};
    int selectedInputIndex; 
    Button InputOptionButton; 
    Button InputPrevButton; 
    Button InputNextButton; 
    virtual void RANDOM_INPUT(); 
    virtual void KEYBOARD_INPUT();
    virtual void FILE_INPUT();
    //operations
    Operation currentOperation;
    
    int selectedOperationIndex;
    Button OperationOptionButton;
    Button OperationPrevButton;
    Button OperationNextButton;

    //others
    int newValue, oldValue;
    bool isPlaying;
    MyRec head;
    Rectangle bottom;
    Rectangle side;
    bool isExpanding = false;
    bool isClosing = false;
    float animatingTime = 0;
    Button Ok;
    TextBox textbox;
    TextBox oldTextBox;
    TextBox newTextBox;
    
    Rectangle workplace = {screenWidth * 0.28f, screenHeight * 0.14f, screenWidth * 0.68f, screenHeight * 0.72f};
    MyRec speedSliding;
    // Slider timeSlider;
    ButtonFromImage back1, next1, pause1, play1;
    ButtonFromImage back2, next2, pause2, play2;
    ButtonFromImage home, home2;
    Texture2D background1, background2;
    Rectangle codeDisplayPLace;

    virtual void init();
    virtual void draw();
    virtual void event();
    virtual void reset();
    virtual void updateSide();
    void handleInput();
};