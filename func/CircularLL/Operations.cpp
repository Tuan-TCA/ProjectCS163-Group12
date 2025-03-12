#include "Operations.h"
#include "Globals.h"
#include "Objects.h"
#include "Animation.h"
#include <memory>

void InsertNode(int value, int screenWidth, int screenHeight) {
    if (isTraversing) return;

    auto newNode = std::make_shared<Node>(value);
    newNode->pos = { (float)screenWidth / 2, (float)screenHeight / 2 };

    if (!head) {
        head = newNode;
        newNode->next = head;
        return;
    }

    // Bắt đầu traversal để tìm node cuối
    isTraversing = true;
    traversalNode = head;
    traversalHighlight = head->pos;
    traversalStage = 0;
    pendingNode = newNode;
}

void DeleteNode() {
    if (!head || isTraversing) return;

    if (head->next == head) {
        head = nullptr;
    } else {
        auto tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }
        head = head->next;
        tail->next = head;
    }
}
