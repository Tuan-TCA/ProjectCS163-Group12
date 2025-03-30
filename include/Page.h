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
    Update
};

enum class InputType {
    Random,
    Keyboard,
    File
};
class Page {
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
    vector<string> OperationOptions = {"INSERT", "CREATE", "UPDATE", "DELETE", "SEARCH"};
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
    Button Ok;
    TextBox textbox;
    TextBox oldTextBox;
    TextBox newTextBox;
    
    MyRec speedSliding;
    Slider timeSlider;
    ButtonFromImage back1, next1, pause1, play1;
    ButtonFromImage back2, next2, pause2, play2;
    ButtonFromImage home, home2;
    Texture2D background1, background2;
 

    virtual void init();
    virtual void draw();
    virtual void event();
    void reset();
    virtual void handleInput();
};