#ifndef DRAW_H
#define DRAW_H

#include "raylib.h"

// Hàm vẽ toàn bộ scene (UI, node, mũi tên cong, highlight)
void DrawScene(int screenWidth, int screenHeight,
               float pulseScale, float arrowProgress,
               const Rectangle &inputBox, const Rectangle &insertButton,
               const Rectangle &deleteButton, const Rectangle &sliderBar,
               const Rectangle &animSliderBar,
               const char* inputText, bool inputActive,
               float effectSpeed, float animSpeed,
               bool sliderActive, bool animSliderActive);

#endif // DRAW_H
