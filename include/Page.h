#include<raylib.h>
#include "Button.h"
#include "Variables.h"
#include<bits/stdc++.h>
#include "InputField.h"
using namespace std;


enum class Operation {
    Insert,
    Create,
    Delete,
    Search
};

class Page {
public:
    Operation currentOperation;
    Button insertButton, createButton, deleteButton, searchButton;
    vector<Button> operationButtons;
    vector<Vector2> subButtonPosition;
    float subWidth, subHeight;
    bool isInsertExpanded = false; 
    bool isCreateExpanded = false; 
    bool isDeleteExpanded = false;  
    bool isSearchExpanded = false;  

    MyRec head;
    Rectangle bottom;
    Rectangle side;
    Button Ok;
    TextBox textbox;
    vector <Button> functions;
    ButtonFromImage home, home2;
    Texture2D background1, background2;

    void init();
    void draw();
    void event();
    void reset();
};