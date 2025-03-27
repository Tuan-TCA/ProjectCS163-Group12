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
    MST
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
    int selectedInputIndex;  // position hiện tại
    Button InputOptionButton; // op hiện tại
    Button InputPrevButton;  // chuyển trái
    Button InputNextButton; 

    //operations
    Operation currentOperation;
    Button insertButton, createButton, deleteButton, searchButton;
    vector<Button> operationButtons;
    vector<Vector2> subButtonPosition;
    bool isInsertExpanded = false; 
    bool isCreateExpanded = false; 
    bool isDeleteExpanded = false;  
    bool isSearchExpanded = false;  

    // vector<string> OperationOptions;
    // int selectedOperationIndex;
    // Button OperationOptionButton;
    // Button OperationPrevButton;
    // Button OperationNextButton;

    //others
    bool isPlaying;
    MyRec head;
    Rectangle bottom;
    Rectangle side;
    Button Ok;
    TextBox textbox;

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