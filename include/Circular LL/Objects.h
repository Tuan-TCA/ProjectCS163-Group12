#ifndef OBJECTS_H
#define OBJECTS_H

#include "raylib.h"
#include <memory>

// Lớp Node cho danh sách liên kết vòng
class Node {
public:
    int data;
    std::shared_ptr<Node> next;
    Vector2 pos;       // Vị trí hiện tại (animation)
    Vector2 targetPos; // Vị trí đích trên vòng tròn

    Node(int value);
};

// Hàm vẽ mũi tên (dùng cho trường hợp cần vẽ đường thẳng + đầu mũi tên)
void DrawArrowLine(Vector2 start, Vector2 end, Color color);

#endif // OBJECTS_H
