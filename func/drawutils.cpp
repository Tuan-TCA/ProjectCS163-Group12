#include "DrawUtils.h"
#include <cmath>

void DrawNode(Vector2 center, int key, int choose, int radius, int fontSize,
              Color ring, Color fill, Color chooseColor, Color visitColor, Color textColor)
{
    string s = to_string(key);

    // Chọn màu vòng ngoài theo trạng thái
    if (choose == 1) {
        DrawCircleV(center, radius, chooseColor);
    }
    else if (choose == -1) {
        DrawCircleV(center, radius, visitColor);
    }
    else {
        DrawCircleV(center, radius, WHITE);
    }

    DrawCircleV(center, radius - 9, ring);   // viền ngoài
    DrawCircleV(center, radius - 4, fill);  // màu nền node

    int adjustedFontSize = max(10, fontSize - (int)s.length() * 3);
    int textWidth = MeasureText(s.c_str(), adjustedFontSize);
    DrawText(s.c_str(), center.x - textWidth / 2, center.y - adjustedFontSize / 2, adjustedFontSize, textColor);
}

void DrawArrowHTB(Vector2 start, Vector2 end, float radius, float arrowSize, Color arrowColor) {
    float angle = atan2f(end.y - start.y, end.x - start.x);

    Vector2 adjustedStart = {
        start.x + radius * cos(angle),
        start.y + radius * sin(angle)
    };
    Vector2 adjustedEnd = {
        end.x - radius * cos(angle),
        end.y - radius * sin(angle)
    };

    Vector2 arrowHead = adjustedEnd;

    Vector2 left = {
        arrowHead.x - arrowSize * cos(angle + PI / 6),
        arrowHead.y - arrowSize * sin(angle + PI / 6)
    };
    Vector2 right = {
        arrowHead.x - arrowSize * cos(angle - PI / 6),
        arrowHead.y - arrowSize * sin(angle - PI / 6)
    };

    DrawLineEx(adjustedStart, arrowHead, 3, arrowColor);
    DrawLineEx(arrowHead, left, 2, arrowColor);
    DrawLineEx(arrowHead, right, 2, arrowColor);
}

void DrawFadingNode(Vector2 pos, int key, float alpha, int radius, int fontSize, Color baseColor, Color textColor) {
    Color fadedColor = baseColor;
    fadedColor.a = static_cast<unsigned char>(alpha * 255);

    Color fadedText = textColor;
    fadedText.a = static_cast<unsigned char>(alpha * 255);

    DrawCircleV(pos, radius, fadedColor);

    std::string s = std::to_string(key);
    int fontAdj = std::max(10, fontSize - (int)s.size() * 3);
    int textWidth = MeasureText(s.c_str(), fontAdj);

    DrawText(s.c_str(), pos.x - textWidth / 2, pos.y - fontAdj / 2, fontAdj, fadedText);
}