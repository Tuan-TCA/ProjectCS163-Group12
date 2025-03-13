#include<raylib.h>
#include "Button.h"
#include "Variables.h"
#include<bits/stdc++.h>
using namespace std;

class Page {
public:
    MyRec head;
    Rectangle bottom;
    Rectangle side;
    Button home = Button(screenWidth*0.9f, 0, screenHeight*0.1, screenHeight*0.1, "Home", DARKGRAY, LIGHTGRAY, WHITE);
    vector <Button> functions {
        Button(screenWidth*0.2, screenHeight*0.60, screenWidth*0.05, screenHeight*0.02, "Create", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.2, screenHeight*0.65, screenWidth*0.05, screenHeight*0.02, "Insert", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.2, screenHeight*0.70, screenWidth*0.05, screenHeight*0.02, "Search", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.2, screenHeight*0.75, screenWidth*0.05, screenHeight*0.02, "Delete", DARKGRAY, LIGHTGRAY, WHITE)
    };

    void init(MODE mode);
    void draw();
    void actions();
};