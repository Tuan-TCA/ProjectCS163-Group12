#pragma once
#include "raylib.h"
#include<bits/stdc++.h>
using namespace std;

class MyRec {
private:
    Rectangle bounds;
    Color color;
    Color textColor;
    const char* label;

public:
    MyRec() {};
    MyRec(float x, float y, float width, float height, const char* labelText, Color buttonColor, Color textCol) {
        bounds = {x, y, width, height};
        label = labelText;
        color = buttonColor;
        textColor = textCol;
    }

    void Draw() {
        DrawRectangleRec(bounds, color);
        int textWidth = MeasureText(label, 40);
        DrawText(label, bounds.x + (bounds.width - textWidth) / 2, bounds.y + (bounds.height - 40) / 2, 40, textColor);
    }

};  

class Button {
public:
    Rectangle bounds;
    Color color;
    Color hoverColor;
    Color textColor;
    const char* label;
    bool isHovered;
    Texture2D image;

    Button(float x, float y, float width, float height, const char* labelText, Color buttonColor, Color hoverCol, Color textCol) {
        bounds = {x, y, width, height};
        label = labelText;
        color = buttonColor;
        hoverColor = hoverCol;
        textColor = textCol;
        isHovered = false;
    }
        

    void Update() {
        Vector2 mousePoint = GetMousePosition();
        isHovered = CheckCollisionPointRec(mousePoint, bounds);
    }

    void Draw() {
        Update();
        DrawRectangleRec(bounds, isHovered ? hoverColor : color);
        int textWidth = MeasureText(label, 20);
        DrawText(label, bounds.x + (bounds.width - textWidth) / 2, bounds.y + (bounds.height - 20) / 2, 20, textColor);
    }

    void DrawText2D () {
        Update();
        Rectangle sourceRec = {0,0, (float) image.width, (float) image.height};
        Vector2 origin = {0,0};
        DrawTexturePro(image, sourceRec, bounds, origin, 0.0f, WHITE);
    }

    bool IsClicked() {
        Update();
        return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }
};
