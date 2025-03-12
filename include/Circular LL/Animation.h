#ifndef ANIMATION_H
#define ANIMATION_H

#include "raylib.h"

// Nội suy tuyến tính giữa 2 Vector2
Vector2 LerpVector2(Vector2 start, Vector2 end, float t);

// Cập nhật vị trí targetPos cho các node khi số node thay đổi
void UpdateNodePositions(int screenWidth, int screenHeight);

// Cập nhật quá trình traversal (tìm node cuối, thêm node mới)
void UpdateTraversal(float animSpeed, int screenWidth, int screenHeight);

// Vẽ highlight cho quá trình traversal
void DrawTraversalHighlight();

#endif // ANIMATION_H
