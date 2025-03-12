#include "Animation.h"
#include "Globals.h"
#include "Utils.h"
#include <cmath>

Vector2 LerpVector2(Vector2 start, Vector2 end, float t) {
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    Vector2 result;
    result.x = start.x + (end.x - start.x) * t;
    result.y = start.y + (end.y - start.y) * t;
    return result;
}

void UpdateNodePositions(int screenWidth, int screenHeight) {
    int count = 0;
    if (head) {
        auto temp = head;
        do {
            count++;
            temp = temp->next;
        } while (temp != head);
    }
    // Nếu đang ở stage 1 (thêm node), tính luôn pendingNode
    if (isTraversing && traversalStage == 1) {
        count++;
    }
    if (count == 0) return;

    Vector2 center = { (float)screenWidth / 2, (float)screenHeight / 2 - 50 };
    float circleRadius = 200.0f;

    auto temp = head;
    // Số node thực tế vẽ = count - 1 nếu có pendingNode
    int realCount = count - (isTraversing && traversalStage == 1 ? 1 : 0);
    for (int i = 0; i < realCount; i++) {
        float angle = (2 * PI * i) / count;
        temp->targetPos = {
            center.x + circleRadius * cosf(angle),
            center.y + circleRadius * sinf(angle)
        };
        temp = temp->next;
    }

    // Nếu đang stage 1, gán targetPos cho pendingNode
    if (isTraversing && traversalStage == 1 && pendingNode) {
        float lastAngle = (2 * PI * (count - 1)) / count;
        pendingNode->targetPos = {
            center.x + circleRadius * cosf(lastAngle),
            center.y + circleRadius * sinf(lastAngle)
        };
    }
}

void UpdateTraversal(float animSpeed, int screenWidth, int screenHeight) {
    if (!isTraversing) return;
    float traversalSpeed = 5.0f * animSpeed;

    if (traversalStage == 0) { // Tìm node cuối
        traversalHighlight = LerpVector2(traversalHighlight, traversalNode->pos, GetFrameTime() * traversalSpeed);
        if (Vector2Distance(traversalHighlight, traversalNode->pos) < 5.0f) {
            // Nếu node kế tiếp là head -> đã tới node cuối
            if (traversalNode->next == head) {
                traversalStage = 1;
                UpdateNodePositions(screenWidth, screenHeight);
            } else {
                traversalNode = traversalNode->next;
            }
        }
    } else if (traversalStage == 1) { // Thêm node
        if (pendingNode) {
            pendingNode->pos = LerpVector2(pendingNode->pos, pendingNode->targetPos, GetFrameTime() * traversalSpeed);
            if (Vector2Distance(pendingNode->pos, pendingNode->targetPos) < 5.0f) {
                traversalNode->next = pendingNode;
                pendingNode->next = head;
                isTraversing = false;
                pendingNode = nullptr;
            }
        }
    }
}

void DrawTraversalHighlight() {
    if (isTraversing) {
        DrawCircleV(traversalHighlight, 40, ColorAlpha(RED, 0.3f));
        DrawText("Traversing...", 10, 60, 20, MAROON);
        if (traversalStage == 0)
            DrawText("Finding last node", 10, 90, 20, DARKGRAY);
        else
            DrawText("Adding new node", 10, 90, 20, DARKGRAY);
    }
}
