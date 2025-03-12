#include "Objects.h"
#include <cmath>

#ifndef DEG2RAD
    #define DEG2RAD (PI/180.0f)
#endif

Node::Node(int value) : data(value), next(nullptr) {
    pos = { 400.0f, 250.0f };
    targetPos = pos;
}

void DrawArrowLine(Vector2 start, Vector2 end, Color color) {
    DrawLineV(start, end, color);
    float arrowSize = 10.0f;
    float angle = atan2f(end.y - start.y, end.x - start.x);

    Vector2 arrowLeft = {
        end.x - arrowSize * cosf(angle - DEG2RAD * 30),
        end.y - arrowSize * sinf(angle - DEG2RAD * 30)
    };
    Vector2 arrowRight = {
        end.x - arrowSize * cosf(angle + DEG2RAD * 30),
        end.y - arrowSize * sinf(angle + DEG2RAD * 30)
    };

    DrawLineV(end, arrowLeft, color);
    DrawLineV(end, arrowRight, color);
}
