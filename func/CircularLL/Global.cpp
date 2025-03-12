#include "Globals.h"

// Định nghĩa các biến toàn cục (phải có đúng 1 lần trong project)
std::shared_ptr<Node> head = nullptr;
bool isTraversing = false;
std::shared_ptr<Node> traversalNode = nullptr;
std::shared_ptr<Node> pendingNode = nullptr;
Vector2 traversalHighlight = { 0, 0 };
int traversalStage = 0;
