#pragma once
#include <raylib.h>
#include "Button.h"
#include "Variables.h"
#include <bits/stdc++.h>
using namespace std;

class Menu
{
public:
    vector<Button> buttons = {
        Button(screenWidth*0.4, screenHeight*0.3, screenWidth*0.2, screenHeight*0.1, "Linked List", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.4, screenHeight*0.45, screenWidth*0.2, screenHeight*0.1, "Hash Table", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.4, screenHeight*0.60, screenWidth*0.2, screenHeight*0.1, "Tree", DARKGRAY, LIGHTGRAY, WHITE),
        Button(screenWidth*0.4, screenHeight*0.75, screenWidth*0.2, screenHeight*0.1, "Graph", DARKGRAY, LIGHTGRAY, WHITE)
    };

    void init();
    void draw();
    int modeRetrieve();
};