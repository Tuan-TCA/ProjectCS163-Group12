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

extern Color MyColor1;
extern Color MyColor2;
extern Color MyColor3;
extern Color MyColor4;
extern Color MyColor5;
extern Texture2D resizedImage(const char* imagePath, float width, float height);
extern void UpdateColorsBasedOnSwitchState();

class Vertex {
public:
    Vector2 position;
    int value;
    int radius;
    Color color, ringColor, textColor;
    bool isPressing;
    bool isColorHighlighting;
    float af;
    Vertex(){
        radius = 20; 
        color = WHITE;
        af = 0;
        isColorHighlighting = false;
        ringColor = MyColor4;
        textColor = MyColor4;
        isPressing = false;
        }
    Vertex(Vector2 pos, int value) : position(pos), color(WHITE), value(value) {}
    void Update(float deltaTime){
        float colorSpeed = 0.4;
        if(isColorHighlighting){
            af += colorSpeed * deltaTime;
            if(af > 1) {af = 1; isColorHighlighting = false;}
        }
        // else{
        //     af -= colorSpeed * deltaTime;
        //     if(af< 0) {af = 0; isColorHighlighting = true;}
        // }
        ringColor = ColorLerp(ringColor, ORANGE, af);
    }
    void Draw() {
        DrawCircleV(position, radius, color); 
        DrawTextEx(
            FONT,
            to_string(value).c_str(), 
            {position.x - MeasureText(to_string(value).c_str(), 20) / 2, 
            position.y - MeasureText(to_string(value).c_str(), 20) / 2 - radius * 0.2f}, 
            20,
            12,
            textColor
            );
        DrawRing(position, radius, radius + 5, 0, 360, 100, ringColor);
    }

    void SetColor(Color newColor) {
        color = newColor;
    }

    void SetRingColor(Color newColor){
        ringColor = newColor;
    }

    void SetTextColor(Color newColor){
        textColor = newColor;
    }

    bool isClicked(){
        return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(GetMousePosition(), position,radius);
    }
    
};


class Edge {
public:
    Vertex* start;
    Vertex* end;
    int w;
    float af;
    Color color;
    bool isColorHighlighting;
    
    Edge(){color = MyColor4;}
    Edge(Vertex* s, Vertex* e, int w) : 
        start(s), 
        end(e), 
        w(w), 
        color(MyColor4),
        af(0),
        isColorHighlighting(false)
         {}


    void Update(float deltaTime){
        float colorSpeed = 0.4;
         if(isColorHighlighting){
            af += colorSpeed * deltaTime;
            if(af > 1) {af = 1; isColorHighlighting = false;}
        }
        // else{
        //     af -= colorSpeed * deltaTime;
        //     if(af< 0) {af = 0; isColorHighlighting = true;}
        // }
        color = ColorLerp(color, ORANGE, af);

    }
    void Draw() {
       
        DrawLineEx(start->position, end->position, 4, color);
        DrawText(to_string(w).c_str(), (start->position.x + end->position.x + 20) / 2 , (start->position.y+end->position.y + 30) / 2 , 20, color);
    }

    bool isClicked(){
        return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointLine(GetMousePosition(), start->position, end->position, 5);
    }
};