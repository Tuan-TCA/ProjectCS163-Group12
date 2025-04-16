#pragma once

#include "Variables.h"

class Vertex : public Drawable {
public:
    Vector2 position;
    int value;
    int radius;
    Color color, ringColor, textColor;
    bool isPressing;
    float duration;
    Color targetColor;
    float animationTime;
    bool doneAnimation;
    bool fullColor;
    // bool isBacktracked = false;
    Vertex(){
        radius = 20; 
        color = WHITE;
        doneAnimation = false;
        isAnimating = false;
        ringColor = MyColor4;
        textColor = MyColor4;
        isPressing = false;
        duration = 1;
        }
    Vertex(Vector2 pos, int value) : position(pos), color(WHITE), value(value) {}

    void startAnimation(Color target, float duration) override;
    
    void Update(float deltaTime) override;
    void Draw() override;
    bool isClicked();
    void print();
    void SetColor() override;
    void reset() override;
};
