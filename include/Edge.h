#pragma once
#include "Vertex.h"
#include "Variables.h"

class Edge : public Drawable {
public:
    Vertex* start;
    Vertex* end;
    int w;
    Color color, textColor;
    float animationTime;
    Color targetColor;
    bool doneAnimation;
    float duration; 
    Vector2 endEdge;
    bool isWeightVisible = true;
    int kind_ani = 0;
    // bool isDisappearing;
    bool fullRED;
    Edge(){color = MyColor4;}
    Edge(Vertex* s, Vertex* e, int w) : 
        start(s), 
        end(e), 
        w(w), 
        color(MyColor4),
        textColor(MyColor4),
        doneAnimation(false),
    
        fullRED(true)
        {}


    void Update(float deltaTime) override;
    void Draw() override;
    bool isClicked();

    void startAnimation(Color target, float duration) override;
    void print();
    float length();
    void SetColor() override;
    void reset() override;
};