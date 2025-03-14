#pragma once

#include<raylib.h>
#include<bits/stdc++.h>

enum class MODE {
    MENU, LL, HASHTB, AVL, GRAPH    
};

extern MODE mode;

extern const int screenWidth, screenHeight;

extern Color BLUE1;
extern Color BLUE2;
extern Color BLUE3;
extern Color BLUE4;
extern Color BLUE5;
extern Texture2D resizedImage(const char* imagePath, float width, float height);