#pragma once

#include<raylib.h>

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
    Color color;

    Vertex(Vector2 pos) : position(pos), color(WHITE) {}

    void Draw() {
        DrawCircleV(position, 20, color);  // Vẽ đỉnh
    }

    void SetColor(Color newColor) {
        color = newColor;
    }
};


class Edge {
public:
    Vertex* start;
    Vertex* end;

    Edge(Vertex* s, Vertex* e) : start(s), end(e) {}

    void Draw() {
        DrawLineV(start->position, end->position, LIGHTGRAY);  // Vẽ cạnh
    }
};