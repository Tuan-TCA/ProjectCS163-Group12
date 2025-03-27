#pragma once
#include <string>
#include <iostream>
#include<raylib.h>
using namespace std;

enum class MODE {
    MENU, LL, HASHTB, AVL, GRAPH    
};
extern const float subWidth;
extern const float subHeight;

extern char filePath[50];

extern Font FONT;
extern MODE mode;
extern bool switchState; // true: red, false: blue
extern const int screenWidth, screenHeight;
extern float animationSpeed;

extern Color MyColor1;
extern Color MyColor2;
extern Color MyColor3;
extern Color MyColor4;
extern Color MyColor5;
extern Texture2D resizedImage(const char* imagePath, float width, float height);
extern void UpdateColorsBasedOnSwitchState();

class Drawable { // base class of vertex, edge
public:
    virtual void startAnimation(Color target, float duration) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
   
    virtual ~Drawable() {} 
    bool isAnimating;
    virtual void SetColor(Color targetColor) = 0;
     virtual void print(){}
    virtual void reset() = 0;
};

