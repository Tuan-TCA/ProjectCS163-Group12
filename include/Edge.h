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
    Color color;
    float animationTime;
    Color targetColor;
    float duration;
    Edge(){color = MyColor4;}
    Edge(Vertex* s, Vertex* e, int w) : 
        start(s), 
        end(e), 
        w(w), 
        color(MyColor4)
      
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