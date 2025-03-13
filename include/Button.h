#pragma once
#include "raylib.h"

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
private:
    Rectangle bounds;
    Color color;
    Color hoverColor;
    Color textColor;
    const char* label;
    bool isHovered;

public:
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

    void DrawText2D (string link) {
        Texture2D image = LoadTexture(link.c_str());
        Rectangle sourceRec = {0,0, (float) image.width, (float) image.height};
        Rectangle destRec = {}
        DrawText
    }

    bool IsClicked() {
        return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }
};
