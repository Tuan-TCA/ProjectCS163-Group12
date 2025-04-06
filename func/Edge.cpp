#include "Edge.h"
#include "Variables.h"
#include <cmath>

void Edge::Update(float deltaTime){

    if(isAnimating){
        
        if(kind_ani == 1){
             animationTime += deltaTime;
            float t = animationTime / (duration / 2.0 / animationSpeed);
            if(!fullRED){
            
             if(t > 1) {
                t = 1; 
                fullRED = true;
                animationTime = 0;
            }
                color = ColorLerp(color, SKYBLUE, t);
                textColor = ColorLerp(textColor, SKYBLUE, t);
            }
            else{
                if(t > 1) {
                t = 1; 
     
                doneAnimation = true;
                isAnimating = false;

                animationTime = 0;
                }
                color = ColorLerp(color, targetColor, t);
                textColor = ColorLerp(color, targetColor, t);
            }
        }
        if(kind_ani == 0){
            animationTime += deltaTime;
            float t = animationTime / (0.6  / animationSpeed);
            if(t > 1) {
                t = 1; 
                animationTime = 0;
                doneAnimation = true;
                isAnimating = false;
                fullRED = false;
            }

            textColor = ColorLerp(textColor, targetColor, t);
        Vector2 delta = end->position - start->position;   
            delta = delta * t;     
            endEdge = start->position + delta;
        }
    }

    if (!doneAnimation ){
        if(kind_ani == 0) color = MyColor4;
    }else{
        color = targetColor;
    }

}
void Edge::startAnimation(Color target, float duration) {
    // targetColor = target;
    animationTime = 0.0f;
    isAnimating = true;
    // isDisappearing = false;
    this->duration = duration;
    fullRED = false;
    
}
void Edge::Draw() {
    DrawLineEx(start->position, end->position, 4,  color);
    if (isAnimating && kind_ani == 0) {
        
        if(endEdge != end->position) DrawLineEx(start->position, endEdge, 4, targetColor);
    } 
    if(isWeightVisible) DrawText(to_string(w).c_str(), (start->position.x + end->position.x + 20) / 2 , (start->position.y + end->position.y + 30) / 2 , 20, textColor);
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

void Edge::SetColor(){ // after having done an animation
    this->textColor = targetColor;
    this->color = targetColor;
    doneAnimation = true;
    // isDisappearing = false;
    fullRED = false;
}

void Edge::reset(){ // before ...
    textColor = MyColor4;
    color = MyColor4;
    endEdge = start->position;
    animationTime = 0.0f;
    isAnimating = false;
    doneAnimation = false;
    // isDisappearing = false;
    fullRED= false;
    kind_ani = 0;
}

