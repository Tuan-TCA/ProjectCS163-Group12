#ifndef UTILS_H
#define UTILS_H

#include "raylib.h"

// Giới hạn value trong [min, max]
float Clamp(float value, float min, float max);

// Tính khoảng cách giữa 2 điểm Vector2
float Vector2Distance(Vector2 v1, Vector2 v2);

#endif // UTILS_H
