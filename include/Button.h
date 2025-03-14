#pragma once
#include "raylib.h"
#include "Variables.h"
#include<bits/stdc++.h>
#include <string>
using namespace std;

class MyRec {
private:
    Rectangle bounds;
    Color color;
    Color textColor;
    string label;

public:
    MyRec() {};
    MyRec(float x, float y, float width, float height, string labelText, Color buttonColor, Color textCol) {
        bounds = {x, y, width, height};
        label = labelText;
        color = buttonColor;
        textColor = textCol;
    }

    void Draw() {
        DrawRectangleRec(bounds, color);
        int textWidth = MeasureText(label.c_str(), 40);
        DrawText(label.c_str(), bounds.x + (bounds.width - textWidth) / 2, bounds.y + (bounds.height - 40) / 2, 40, textColor);
    }

    void DrawRounded(){
        DrawRectangleRounded(bounds, 20, 0, BLUE2);
        DrawText(label.c_str(), bounds.x + (bounds.width - MeasureText(label.c_str(), 40)) / 2, bounds.y + (bounds.height - 40) / 2, 40, textColor);
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

    Button() {
        bounds = {0,0,0,0};
        label = "";
        color = WHITE;
        hoverColor = WHITE;
        textColor = WHITE;
        isHovered = false;
    }

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

    virtual void Draw() {
        Update();
        DrawRectangleRec(bounds, isHovered ? hoverColor : color);
        int textWidth = MeasureText(label, 20);
        DrawText(label, bounds.x + (bounds.width - textWidth) / 2, bounds.y + (bounds.height - 20) / 2, 20, textColor);
    }

    void DrawRounded(){
        Update();
        DrawRectangleRounded(bounds, 20, 0,isHovered ? BLUE2 : BLUE1);
        int textWidth = MeasureText(label, 20);
        DrawText(label, bounds.x + (bounds.width - textWidth) / 2, bounds.y + (bounds.height - 20) / 2, 20, textColor);
    }

    void DrawText2D () {
        Update();
        Rectangle sourceRec = {0,0, (float) image.width, (float) image.height};
        Vector2 origin = {0,0};
        DrawTexturePro(image, sourceRec, bounds, origin, 0.0f, isHovered ? LIGHTGRAY : YELLOW);
    }

    Rectangle getBound(){
        return bounds;
    }
    bool isOver(){
        return isHovered;
    }
    bool IsClicked() {
        Update();
        return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }
};

class TextBox: public Button {
public:
    Button box;
    string inputText;
    bool active;
    vector<int> nums;
    
    void Draw() override {
        box.Draw();
        string displayText = inputText;
        if (active && ((int)(GetTime() * 2) % 2 == 0)) { // Nhấp nháy con trỏ
            displayText += "|";
        }
        DrawText(displayText.c_str(), box.bounds.x+ 5, box.bounds.y + 5, 20, textColor);
    }

    void HandleInput(bool Add, bool Del) {
        if (box.IsClicked()) {
            active = true;
        }
        if (active) {
            int key = GetCharPressed();
            while (key > 0) {
                if (key >= '0' && key <= '9') {
                    inputText += (char)key;
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && !inputText.empty()) {
                inputText.pop_back();
            }

            if ((Add || IsKeyPressed(KEY_ENTER)) && !inputText.empty()) {
                nums.push_back(stoi(inputText));
                inputText = "";
                active = false;
            }
            else
            if ((Del) && !inputText.empty()) {
                auto it = find(nums.begin(), nums.end(), stoi(inputText));
                if(it!=nums.end())
                    nums.erase(it);
                inputText = "";
                active = false;
            }
        }
    }
};

class ButtonFromImage : public Button {
private:
    Texture2D texture;
    Texture2D textureOver;
public:
    ButtonFromImage() : Button(0, 0, 0, 0, "", RAYWHITE, RAYWHITE, RAYWHITE), texture({ 0 }), textureOver({ 0 }) {}
    ButtonFromImage(const char* imagePath, const char* imageOverPath, float x, float y, float width, float height)
        : Button(x, y, width, height, "", RAYWHITE, RAYWHITE, RAYWHITE) {
        texture = resizedImage(imagePath, width, height);
        textureOver = resizedImage(imageOverPath, width, height);
    }

    void Draw() override {
        Update();
        DrawTexture(!isOver() ? texture : textureOver, bounds.x, bounds.y, WHITE);
    }
};

