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
    TextBox textbox;
    Button home = Button(screenWidth*0.9f, 0, screenHeight*0.1, screenHeight*0.1, "Home", DARKGRAY, LIGHTGRAY, WHITE);
    vector <Button> functions;
    void init(MODE mode);
    void draw();
    void actions();
};