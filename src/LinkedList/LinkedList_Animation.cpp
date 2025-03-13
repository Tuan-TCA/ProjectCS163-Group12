// #include <AllLibrary.h>

void DrawArrow(Vector2 start, Vector2 end, float arrowSize, Color color) {
    float arrowAngle = PI/6;
    float angle = atan2f(end.y - start.y, end.x - start.x);
    Vector2 arrowHead = {end.x, end.y};

    Vector2 left = {arrowHead.x - arrowSize * cos(angle + arrowAngle), 
                    arrowHead.y - arrowSize * sin(angle + arrowAngle)};
    Vector2 right = {arrowHead.x - arrowSize * cos(angle - arrowAngle), 
                     arrowHead.y - arrowSize * sin(angle - arrowAngle)};

    DrawLineEx(start, arrowHead, 5, color);
    DrawLineEx(arrowHead, left, 3, color);
    DrawLineEx(arrowHead, right, 3, color);
}

void DrawLinkedList(LinkedListNode* head) {
    if (!head) {
        DrawText("Linked List is empty!", screenWidth / 2 - 100, screenHeight / 2, 20, RED);
        return;
    }

    int r = 50;  
    int font_size = 40; 
    int spacing = 50; 
    int total = 0;  // Tổng số node

    LinkedListNode* temp = head;
    while (temp) {
        total++;
        temp = temp->next;
    }

    // Tính center
    int totalWidth = total * (2 * r + spacing) - spacing;
    Vector2 center = {screenWidth / 2 - totalWidth / 2 + r, screenHeight / 2};

    while (head) {

        DrawCircleV(center, r, BLUE);

        string s = to_string(head->val);
        DrawText(s.c_str(), center.x - font_size / 2, center.y - font_size / 2, font_size, WHITE);

        // Vẽ mũi tên nếu có node tiếp theo
        if (head->next) {
            Vector2 newCenter = {center.x + spacing + 2 * r, center.y};
            DrawArrow({center.x + r, center.y}, {newCenter.x - r, newCenter.y}, 15, BLACK);
            center = newCenter;
        }

        head = head->next;
    }
}
