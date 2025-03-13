#pragma once

#include "Button.h"
#include "Menu.h"
#include "Page.h"
#include "Program.h"
#include "Variables.h"


enum class MODE {
    MENU, LL, HASHTB, AVL, GRAPH    
};

extern MODE mode;

extern const int screenWidth, screenHeight;


MODE mode; //pointer của trang 
const int screenWidth = 1920, screenHeight = 1080;
