#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h"
#include <memory>
#include "Objects.h"

// Biến toàn cục cho danh sách liên kết vòng và trạng thái animation
extern std::shared_ptr<Node> head;
extern bool isTraversing;
extern std::shared_ptr<Node> traversalNode;
extern std::shared_ptr<Node> pendingNode;
extern Vector2 traversalHighlight;
extern int traversalStage;

#endif // GLOBALS_H
