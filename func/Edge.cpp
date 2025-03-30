#include "Edge.h"
#include "Variables.h"
#include <cmath>

void Edge::Update(float deltaTime){

    if(isAnimating){
        animationTime += deltaTime;
        
         float t = animationTime / (duration / animationSpeed);
        if(t > 1) {
            t = 1; 
            isAnimating = false;
        }

        textColor = ColorLerp(textColor, targetColor, t);
       Vector2 delta = end->position - start->position;   
        delta = delta * t;     
        endEdge = start->position + delta;
        
    }
    else {
        if(endEdge != start->position) endEdge = end->position;
    }

    if (endEdge != end->position){
        color = color;
    }else{
        color = targetColor;
    }

}
void Edge::startAnimation(Color target, float duration) {
    targetColor = target;
    animationTime = 0.0f;
    isAnimating = true;
    this->duration = duration;
}
void Edge::Draw() {
    DrawLineEx(start->position, end->position, 4,  color);
    if (isAnimating) {
        DrawLineEx(start->position, endEdge, 4, targetColor);
    } 
    DrawText(to_string(w).c_str(), (start->position.x + end->position.x + 20) / 2 , (start->position.y + end->position.y + 30) / 2 , 20, textColor);
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

void Edge::SetColor(Color target){
    this->textColor = target;
    this->color = target;
}

void Edge::reset(){
    textColor = MyColor4;
    color = MyColor4;
    endEdge = start->position;
    animationTime = 0.0f;
    isAnimating = false;
}
