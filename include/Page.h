#pragma once

#include<raylib.h>
#include "Button.h"
#include "Variables.h"
#include "InputField.h"
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
    Operation currentOperation;
    InputType currentInput;
    //input
    vector<string> options = {"RANDOM", "KEYBOARD", "FILE"};
    int selectedIndex;  // position hiện tại
    Button optionButton; // op hiện tại
    Button prevButton;  // chuyển trái
    Button nextButton; 

    Button insertButton, createButton, deleteButton, searchButton;
    vector<Button> operationButtons;
    vector<Vector2> subButtonPosition;

    bool isInsertExpanded = false; 
    bool isCreateExpanded = false; 
    bool isDeleteExpanded = false;  
    bool isSearchExpanded = false;  

    bool isPlaying;
    MyRec head;
    Rectangle bottom;
    Rectangle side;
    Button Ok;
    TextBox textbox;
    float animationSpeed;
    MyRec speedSliding;
    ButtonFromImage back1, next1, pause1, play1;
    ButtonFromImage back2, next2, pause2, play2;
    ButtonFromImage home, home2;
    Texture2D background1, background2;
 

    void init();
    void draw();
    void event();
    void reset();

    void handleInput();
    // FUNC func = FUNC::NONE;

};