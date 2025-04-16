#pragma once
#include <string>
#include <iostream>
#include <vector>
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
extern bool pause;
extern float volume;

extern Color MyColor1;
extern Color MyColor2;
extern Color MyColor3;
extern Color MyColor4;
extern Color MyColor5;
extern Color MyColor6;
extern Color MyColor7;

extern Texture2D resizedImage(const char* imagePath, float width, float height);
extern void UpdateColorsBasedOnSwitchState();
extern Vector2 operator+(Vector2 a, Vector2 b);
extern Vector2 operator-(Vector2 a, Vector2 b);
extern Vector2 operator*(Vector2 a, float b);
extern Vector2 operator/(Vector2 a, float b);
extern bool operator!=(Vector2 a, Vector2 b);
extern bool operator!=(Color a, Color b);
extern Rectangle operator-(Rectangle a, Rectangle b);
extern Rectangle operator+(Rectangle a, Rectangle b);
extern Rectangle operator*(Rectangle a, float b);
extern bool operator!=(Rectangle a, Rectangle b);
class Drawable { // base class of vertex, edge
public:
    virtual void startAnimation(Color target, float duration) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
   
    virtual ~Drawable() {} 
    bool isAnimating;
    virtual void SetColor() = 0;
     virtual void print() = 0;
    virtual void reset() = 0;

     bool doneAnimation = 0;
};

extern string getMODE();
