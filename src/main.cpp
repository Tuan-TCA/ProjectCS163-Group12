#include "raylib.h"
#include "Globals.h"
#include "Objects.h"
#include "Utils.h"
#include "Animation.h"
#include "Operations.h"
#include "Draw.h"
#include <cstring>
#include <string>
#include<cmath>

// Giao diện
Rectangle inputBox     = { 50, 530, 200, 40 };
Rectangle insertButton = { 300, 530, 100, 40 };
Rectangle deleteButton = { 450, 530, 100, 40 };
Rectangle sliderBar    = { 50, 500, 200, 10 };
Rectangle animSliderBar= { 300, 500, 200, 10 };

char inputText[33] = "\0";
bool inputActive = false, sliderActive = false, animSliderActive = false;
float effectSpeed = 1.0f, animSpeed = 1.0f;
float arrowAnimTimer = 0.0f;
const float arrowAnimDuration = 1.0f;
int lastNodeCount = 0;

int main() {
    const int screenWidth = 800, screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Circular Linked List Visualization");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();

        // Check activation of input box & sliders
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            inputActive = CheckCollisionPointRec(mousePoint, inputBox);
            sliderActive = CheckCollisionPointRec(mousePoint, sliderBar);
            animSliderActive = CheckCollisionPointRec(mousePoint, animSliderBar);
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            sliderActive = animSliderActive = false;
        }

        // Handle input box
        if (inputActive) {
            int key = GetCharPressed();
            while (key > 0) {
                if (((key >= '0' && key <= '9') || (key == '-' && strlen(inputText) == 0))
                    && strlen(inputText) < 32)
                {
                    int len = strlen(inputText);
                    inputText[len] = (char)key;
                    inputText[len + 1] = '\0';
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && strlen(inputText) > 0)
                inputText[strlen(inputText) - 1] = '\0';
            if (IsKeyPressed(KEY_ENTER) && strlen(inputText) > 0) {
                try {
                    int value = std::stoi(std::string(inputText));
                    InsertNode(value, screenWidth, screenHeight);
                } catch (...) { }
                inputText[0] = '\0';
                inputActive = false;
            }
        }

        // Update sliders
        if (sliderActive) {
            float newSpeed = 0.5f + ((mousePoint.x - sliderBar.x) / sliderBar.width) * (3.0f - 0.5f);
            effectSpeed = Clamp(newSpeed, 0.5f, 3.0f);
        }
        if (animSliderActive) {
            float newAnimSpeed = 0.5f + ((mousePoint.x - animSliderBar.x) / animSliderBar.width) * (3.0f - 0.5f);
            animSpeed = Clamp(newAnimSpeed, 0.5f, 3.0f);
        }

        // Handle buttons
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mousePoint, insertButton) && strlen(inputText) > 0) {
                try {
                    int value = std::stoi(std::string(inputText));
                    InsertNode(value, screenWidth, screenHeight);
                } catch (...) { }
                inputText[0] = '\0';
            }
            if (CheckCollisionPointRec(mousePoint, deleteButton))
                DeleteNode();
        }

        // Update traversal
        UpdateTraversal(animSpeed, screenWidth, screenHeight);

        // Tính hiệu ứng pulsing
        float pulseScale = 1.0f + 0.1f * sinf(GetTime() * effectSpeed);

        // Đếm node
        int count = 0;
        if (head) {
            auto temp = head;
            do { count++; temp = temp->next; } while (temp != head);
        }

        // Nếu số node thay đổi và không đang isTraversing -> reset arrowAnimTimer
        if (count != lastNodeCount && !isTraversing) {
            arrowAnimTimer = 0.0f;
            lastNodeCount = count;
            UpdateNodePositions(screenWidth, screenHeight);
        } else {
            arrowAnimTimer += GetFrameTime() * animSpeed;
        }

        float arrowProgress = Clamp(arrowAnimTimer / arrowAnimDuration, 0.0f, 1.0f);

        // Di chuyển node đến targetPos
        if (count > 0) {
            auto temp = head;
            for (int i = 0; i < count; i++) {
                float t = GetFrameTime() * animSpeed * 5.0f;
                t = Clamp(t, 0.0f, 1.0f);
                temp->pos = LerpVector2(temp->pos, temp->targetPos, t);
                if (Vector2Distance(temp->pos, temp->targetPos) < 1.0f) {
                    temp->pos = temp->targetPos;
                }
                temp = temp->next;
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawScene(screenWidth, screenHeight,
                      pulseScale, arrowProgress,
                      inputBox, insertButton, deleteButton,
                      sliderBar, animSliderBar,
                      inputText, inputActive, effectSpeed, animSpeed,
                      sliderActive, animSliderActive);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
