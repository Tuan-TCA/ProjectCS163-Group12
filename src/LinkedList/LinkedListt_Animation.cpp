#include <raylib.h>
#include <LinkedList.h>

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

void DrawRim(Vector2 center, Color RimDark, Color RimBland){
    // BeginDrawing();

    DrawCircleV(center, r, {0, 0, 0, 0});
    //vẽ hình node
    for(int i = 0;  i < 3; i++){
        DrawCircleLines(center.x, center.y, r + i, BLACK);
    }
    //vẽ viền node
    for (int i = 3; i < 8; i++) { 
        DrawCircleLines(center.x, center.y, r + i, RimDark);
    }
    for (int i = 8; i < 15; i++) { 
        DrawCircleLines(center.x, center.y, r + i, RimBland);
    }
    
    // EndDrawing();
}

void Choose(Vector2 center, Color RimDark, Color RimBland, LinkedListNode* head){
    // BeginDrawing();
    ClearBackground(GRAY);
    DrawLinkedList(head);
    DrawRim(center, RimDark, RimBland);
    // EndDrawing();
}

void DrawNewNode(Vector2 center, string value, Color RimDark, Color RimBland, LinkedListNode* head){
    // BeginDrawing();
    ClearBackground(GRAY);
    DrawLinkedList(head);
    DrawRim(center, RimDark, RimBland);
    string s = value;
    int textWidth = MeasureText(s.c_str(), font_size); // bề rộng của node
    DrawText(s.c_str(), center.x - textWidth / 2, center.y - font_size / 2, font_size, WHITE);
    // EndDrawing();
}
void AcceptNode(Vector2 start, Vector2 target, string value, LinkedListNode* head) {
    Vector2 curPos = start;
    int steps = 20; // Số bước để di chuyển từ start → target
    float dx = (target.x - start.x) / steps;
    float dy = (target.y - start.y) / steps;

    // Di chuyển node dần vào hàng
    for (int i = 0; i < steps; i++) {
        curPos.x += dx;
        curPos.y += dy;
        
        BeginDrawing();
        DrawNewNode(curPos, value, {255, 255, 150, 150}, {255, 255, 200, 100}, head);
        EndDrawing();
        WaitTime(0.03);
    }

    // Chuyển từ vàng → xanh lá
    BeginDrawing();
    DrawNewNode(target, value, {150, 255, 150, 150}, {180, 255, 180, 100}, head);
    EndDrawing();
    WaitTime(0.5);

    // Chuyển từ xanh lá → trắng
    BeginDrawing();
    DrawNewNode(target, value, {200, 200, 200, 150}, {230, 230, 230, 100}, head);
    EndDrawing();
}

//sửa hàm vẽ LinkedList thành vẽ theo vị trí node đầu tiên
void DrawLinkedList(LinkedListNode* head) {
    if (!head) {
        DrawText("Linked List is empty!", screenWidth / 2 - 100, screenHeight / 2, 20, RED);
        return;
    }
    Vector2 position = GetPosition(head);
    while (head) {
        DrawRim(position, {200, 200, 200, 150}, {230, 230, 230, 40});
        string s = to_string(head->val);
        int textWidth = MeasureText(s.c_str(), font_size); // bề rộng của node
        DrawText(s.c_str(), position.x - textWidth / 2, position.y - font_size / 2, font_size, WHITE);

        // Vẽ mũi tên nếu có node tiếp theo
        if (head->next) {
            Vector2 newPosition = {position.x + spacing + 2 * r, position.y};
            DrawArrow({position.x + r + 10, position.y}, {newPosition.x - r - 10, newPosition.y}, 15, BLACK);
            position = newPosition;
        }

        head = head->next;
    }
}

Vector2 GetPosition(LinkedListNode* head){
    int total = 0;  // Tổng số node
    LinkedListNode* temp = head;
    while (temp) {
        total++;
        temp = temp->next;
    }
    
    // Tính center
    int totalWidth = total * (2 * r + spacing) - spacing;
    Vector2 center = {screenWidth / 2 - totalWidth / 2 + r, screenHeight / 2};
    return center;
}

void MoveLinkedList(LinkedListNode* head, Vector2 orinalPosition, Vector2 newPosition){
    Vector2 center = orinalPosition;

    cout << newPosition.x - orinalPosition.x << '\n';
    
    string s = to_string(- newPosition.x + orinalPosition.x);

    

    for(int i = 0; center.x > newPosition.x; i++){
        
        center.x-=5;
        BeginDrawing();
        ClearBackground(GRAY); 
        DrawNewLinkedList(head, center); 
        EndDrawing();
        WaitTime(0.1);
    }
}

void DrawNewLinkedList(LinkedListNode* head, Vector2 position){
    if(!head) return;
    while (head) {
        DrawRim(position, {200, 200, 200, 150}, {230, 230, 230, 40});
        string s = to_string(head->val);
        int textWidth = MeasureText(s.c_str(), font_size); 
        DrawText(s.c_str(), position.x - textWidth / 2, position.y - font_size / 2, font_size, WHITE);

        if (head->next) {
            Vector2 newPosition = {position.x + spacing + 2 * r, position.y};
            DrawArrow({position.x + r + 10, position.y}, {newPosition.x - r - 10, newPosition.y}, 15, BLACK);
            position = newPosition;
        }

        head = head->next;
    }
}