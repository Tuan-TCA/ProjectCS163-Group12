#include "Vertex.h"
#include "Variables.h"
void Vertex::Update(float deltaTime){
    if(isAnimating){
        animationTime += deltaTime;
        if(!fullColor){
            float t = animationTime / (duration / 2.0 / animationSpeed);
            if(t > 1) {
                t = 1; 
                animationTime = 0;
                 fullColor = true;
            }
            textColor = ColorLerp(textColor, WHITE, t);
            color = ColorLerp(color, targetColor, t);
            ringColor = ColorLerp(ringColor, targetColor, t);
        }
        else{
            float t = animationTime / (duration / 2.0 / animationSpeed);
            if(t > 1) {
                t = 1; 
                animationTime = 0;
                 isAnimating = false;
                 doneAnimation = true;
            }
            textColor = ColorLerp(textColor, targetColor, t);
            color = ColorLerp(color, WHITE, t);
        }
    }
    else{
        fullColor = false;
    }
}
    
void Vertex::Draw() {
    DrawCircleV(position, radius + 0.5f, color); 
    DrawTextEx(
        FONT,
        to_string(value).c_str(), 
        {position.x - MeasureText(to_string(value).c_str(), 20) / 2, 
        position.y - MeasureText(to_string(value).c_str(), 20) / 2 - radius * 0.2f}, 
        20,
        1,
        textColor
        );
    DrawRing(position, radius, radius + 5, 0, 360, 200, ringColor);
}
bool Vertex::isClicked(){
        return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(GetMousePosition(), position,radius);
}

void Vertex::startAnimation(Color target, float duration) {
        targetColor = target;
        animationTime = 0.0f;
        isAnimating = true;
        fullColor = false;
        this->duration = duration;
}
void Vertex::print(){
    cout << value << endl;
}

void Vertex::SetColor(Color target){
    this->color = WHITE;
    this->ringColor = target;
    this->textColor = target;
}

void Vertex::reset(){
    doneAnimation = false;
     isAnimating = false;
        color = WHITE;
        ringColor = MyColor4;
        textColor = MyColor4;
        animationTime = 0;
}

