#include "Edge.h"
#include <cmath>

void Edge::Update(float deltaTime){
    if(isAnimating){
        animationTime += deltaTime;
        float t = animationTime / (duration / animationSpeed);
        if(t > 1) {
            t = 1; 
            isAnimating = false;
        }
         color = ColorLerp(color, ORANGE, t);
    }
}
void Edge::startAnimation(Color target, float duration) {
    targetColor = target;
    animationTime = 0.0f;
    isAnimating = true;
    this->duration = duration;
}
void Edge::Draw() {
    
    DrawLineEx(start->position, end->position, 4, color);
    DrawText(to_string(w).c_str(), (start->position.x + end->position.x + 20) / 2 , (start->position.y+end->position.y + 30) / 2 , 20, color);
}

bool Edge::isClicked(){
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointLine(GetMousePosition(), start->position, end->position, 5);
}

void Edge::print(){
    cout << start->value << " - " << end->value << endl;
}

float Edge::length(){
    return sqrt(pow( start->position.x - end->position.x,2) + pow(start->position.y - end->position.y, 2));
}