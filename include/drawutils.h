#pragma once
#include <raylib.h>
#include <string>
using namespace std;

// Vẽ một node (hình tròn + text bên trong)
void DrawNode(Vector2 center, int key, int choose, int radius, int fontSize,
              Color ring, Color fill, Color chooseColor, Color visitColor, Color textColor);

// Vẽ mũi tên giữa hai vị trí, có lùi đầu/cuối khỏi node một khoảng (dựa vào bán kính)
void DrawArrowHTB(Vector2 start, Vector2 end, float radius, float arrowSize, Color arrowColor);

void DrawFadingNode(Vector2 pos, int key, float alpha, int radius, int fontSize, Color baseColor, Color textColor);