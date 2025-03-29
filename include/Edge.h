#pragma once
#include <iostream>
#include<raylib.h>
#include "Vertex.h"
using namespace std;

class Edge : public Drawable {
public:
    Vertex* start;
    Vertex* end;
    int w;
    Color color, textColor;
    float animationTime;
    Color targetColor;
    float duration; 
    Vector2 endEdge;
    Edge(){color = MyColor4;}
    Edge(Vertex* s, Vertex* e, int w) : 
        start(s), 
        end(e), 
        w(w), 
        color(MyColor4),
        textColor(MyColor4)
         {}


    void Update(float deltaTime) override;
    void Draw() override;
    bool isClicked();
 
    void startAnimation(Color target, float duration) override;
    void print();
    float length();
    void SetColor(Color targetColor) override;
    void reset() override;
};