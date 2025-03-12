#include "Draw.h"
#include "Globals.h"
#include "Animation.h"
#include "Objects.h"
#include "Utils.h"
#include <cstdio>
#include <cmath>

void DrawScene(int screenWidth, int screenHeight,
               float pulseScale, float arrowProgress,
               const Rectangle &inputBox, const Rectangle &insertButton,
               const Rectangle &deleteButton, const Rectangle &sliderBar,
               const Rectangle &animSliderBar,
               const char* inputText, bool inputActive,
               float effectSpeed, float animSpeed,
               bool sliderActive, bool animSliderActive)
{
    // Vẽ input box
    DrawRectangleRec(inputBox, inputActive ? BLUE : LIGHTGRAY);
    DrawRectangleLines((int)inputBox.x, (int)inputBox.y, (int)inputBox.width, (int)inputBox.height, GRAY);
    DrawText(inputText, (int)inputBox.x + 5, (int)inputBox.y + 10, 20, DARKGRAY);

    // Vẽ nút Insert
    DrawRectangleRec(insertButton, GREEN);
    DrawRectangleLines((int)insertButton.x, (int)insertButton.y, (int)insertButton.width, (int)insertButton.height, DARKGREEN);
    DrawText("Insert", (int)insertButton.x + 25, (int)insertButton.y + 10, 20, DARKGREEN);

    // Vẽ nút Delete
    DrawRectangleRec(deleteButton, PINK);
    DrawRectangleLines((int)deleteButton.x, (int)deleteButton.y, (int)deleteButton.width, (int)deleteButton.height, MAROON);
    DrawText("Delete", (int)deleteButton.x + 25, (int)deleteButton.y + 10, 20, MAROON);

    // Vẽ slider pulsing effect
    DrawRectangleRec(sliderBar, GRAY);
    float sliderRange = (3.0f - 0.5f);
    float sliderVal = (effectSpeed - 0.5f) / sliderRange;
    int knobX = (int)(sliderBar.x + sliderVal * sliderBar.width);
    DrawCircle(knobX, (int)sliderBar.y + 5, 10, sliderActive ? DARKBLUE : BLUE);
    DrawText("Pulse Speed", (int)sliderBar.x, (int)sliderBar.y - 20, 20, DARKGRAY);

    // Vẽ slider animation speed
    DrawRectangleRec(animSliderBar, GRAY);
    float animRange = (3.0f - 0.5f);
    float animVal = (animSpeed - 0.5f) / animRange;
    int knobX2 = (int)(animSliderBar.x + animVal * animSliderBar.width);
    DrawCircle(knobX2, (int)animSliderBar.y + 5, 10, animSliderActive ? DARKBLUE : BLUE);
    DrawText("Animation Speed", (int)animSliderBar.x, (int)animSliderBar.y - 20, 20, DARKGRAY);

    // Vẽ danh sách node
    if (head) {
        auto temp = head;
        do {
            // Vẽ node
            DrawCircleV(temp->pos, 30 * pulseScale, BLUE);
            char nodeValue[8];
            sprintf(nodeValue, "%d", temp->data);
            int textWidth = MeasureText(nodeValue, 20);
            DrawText(nodeValue, (int)temp->pos.x - textWidth / 2, (int)temp->pos.y - 10, 20, WHITE);

            // Tính toán vẽ mũi tên cong
            Vector2 start = temp->pos;
            Vector2 end = temp->next->pos;
            Vector2 midPoint = { (start.x + end.x) * 0.5f, (start.y + end.y) * 0.5f };
            Vector2 center = { (float)screenWidth / 2, (float)screenHeight / 2 - 50 };
            Vector2 outDir = { midPoint.x - center.x, midPoint.y - center.y };
            float outDist = sqrtf(outDir.x * outDir.x + outDir.y * outDir.y);
            if (outDist > 0.1f) {
                outDir.x /= outDist;
                outDir.y /= outDist;
            }
            Vector2 curvePoint = { midPoint.x + outDir.x * 40.0f, midPoint.y + outDir.y * 40.0f };

            // Tính 2 điểm offset
            Vector2 startOff = LerpVector2(start, curvePoint, 0.2f);
            Vector2 endOff   = LerpVector2(end, curvePoint, 0.2f);

            // Vẽ từng đoạn nhỏ trên đường cong
            for (float t = 0.0f; t <= 1.0f; t += 0.1f) {
                Vector2 p0 = LerpVector2(startOff, curvePoint, t);
                Vector2 p1 = LerpVector2(curvePoint, endOff, t);
                Vector2 p  = LerpVector2(p0, p1, t);
                if (t > 0.0f) {
                    float prevT = t - 0.1f;
                    Vector2 pp0 = LerpVector2(startOff, curvePoint, prevT);
                    Vector2 pp1 = LerpVector2(curvePoint, endOff, prevT);
                    Vector2 pp  = LerpVector2(pp0, pp1, prevT);
                    DrawLineV(pp, p, DARKBLUE);
                }
            }

            // Tính vị trí đầu mũi tên di chuyển
            float arrowT = fmodf(arrowProgress + (float)temp->data * 0.1f, 1.0f);
            if (arrowT > 0.1f && arrowT < 0.9f) {
                float adjT = (arrowT - 0.1f) / 0.8f;
                Vector2 aP0 = LerpVector2(startOff, curvePoint, adjT);
                Vector2 aP1 = LerpVector2(curvePoint, endOff, adjT);
                Vector2 arrowP = LerpVector2(aP0, aP1, adjT);

                Vector2 nextP0 = LerpVector2(startOff, curvePoint, adjT + 0.05f);
                Vector2 nextP1 = LerpVector2(curvePoint, endOff, adjT + 0.05f);
                Vector2 nextP = LerpVector2(nextP0, nextP1, adjT + 0.05f);

                float arrowAngle = atan2f(nextP.y - arrowP.y, nextP.x - arrowP.x);
                float arrowSize = 10.0f;
                Vector2 arrowLeft = {
                    arrowP.x - arrowSize * cosf(arrowAngle - DEG2RAD * 30),
                    arrowP.y - arrowSize * sinf(arrowAngle - DEG2RAD * 30)
                };
                Vector2 arrowRight = {
                    arrowP.x - arrowSize * cosf(arrowAngle + DEG2RAD * 30),
                    arrowP.y - arrowSize * sinf(arrowAngle + DEG2RAD * 30)
                };

                DrawCircleV(arrowP, 5, RED);
                DrawLineV(arrowP, arrowLeft, RED);
                DrawLineV(arrowP, arrowRight, RED);
            }

            temp = temp->next;
        } while (temp != head);
    }

    // Vẽ highlight traversal
    DrawTraversalHighlight();

    // Nếu đang thêm node mới (stage 1)
    if (isTraversing && traversalStage == 1 && pendingNode) {
        DrawCircleV(pendingNode->pos, 30 * pulseScale, BLUE);
        char nodeValue[8];
        sprintf(nodeValue, "%d", pendingNode->data);
        int textWidth = MeasureText(nodeValue, 20);
        DrawText(nodeValue, (int)pendingNode->pos.x - textWidth / 2, (int)pendingNode->pos.y - 10, 20, WHITE);
    }

    // Vẽ thông tin
    DrawText("Circular Linked List Visualization", 10, 10, 30, DARKGRAY);
    DrawText("Enter a value and click Insert to add a node", 10, 40, 20, DARKGRAY);

    // Vẽ số node
    int count = 0;
    if (head) {
        auto temp = head;
        do { count++; temp = temp->next; } while (temp != head);
    }
    char countText[64];
    sprintf(countText, "Nodes: %d", count);
    DrawText(countText, 600, 30, 20, DARKBLUE);
}
