#include "LinkedList.h"
#include<bits/stdc++.h>
#include <raylib.h>
using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
    workplace = {400,300,600,600};
    // position = {workplace.x*1.1f, workplace.y*1.1f};
    isInserting = false;
}

Vector2 LinkedList::GetPosition(int count){
    int d = 2 * radius * count + (count - 1)*spacing;
    int X = max((W/2 - d/2) + radius, 0) + 400;
    int Y = H/2;
    Vector2 center = {X, Y};
    return center; 
}

int LinkedList::CountNode(Node* head){
    if(!head) return 0;
    int cnt = 0;
    Node* tmp = head;
    while(tmp){
        cnt++;
        tmp = tmp->next;
    }
    return cnt;
}

void LinkedList::DrawArrow(Vector2 start, Vector2 end) {
    start = {start.x + radius, start.y};
    end = {end.x - radius, end.y};
    float arrowAngle = PI/6;
    float angle = atan2f(end.y - start.y, end.x - start.x);
    Vector2 arrowHead = {end.x, end.y};

    Vector2 left = {arrowHead.x - arrow_size * cos(angle + arrowAngle), 
                    arrowHead.y - arrow_size * sin(angle + arrowAngle)};
    Vector2 right = {arrowHead.x - arrow_size * cos(angle - arrowAngle), 
                     arrowHead.y - arrow_size * sin(angle - arrowAngle)};

    DrawLineEx(start, arrowHead, 5, arrow_color);
    DrawLineEx(arrowHead, left, 3, arrow_color);
    DrawLineEx(arrowHead, right, 3, arrow_color);
}

void LinkedList::DrawNode(Vector2 center, int key, int choose){
    string s = to_string(key);

    // BeginDrawing();
    // ClearBackground(GRAY);
    //Draw circle
    if (choose == 1){
        DrawCircleV(center, radius, choose_color);
    }
    if (choose == -1){
        cout << center.x << ' ' << key << '\n';
        DrawCircleV(center, radius, visit_color);
    }
    if (choose == 0){
        DrawCircleV(center, radius, WHITE);
    }
    DrawCircleV(center, radius - 9, ring);
    DrawCircleV(center, radius - 10, circle);

    int Fs = max(10, static_cast<int>(font_size-s.size()*3));
    //Draw text
    int wNode =  MeasureText(s.c_str(), Fs);
    DrawText(s.c_str(), center.x - wNode / 2, center.y - Fs/2, Fs, text_color);

    // EndDrawing();
}


void LinkedList::DrawLL(Vector2 pos) {

    if (!head){
        cout << "Head is null\n";
        return;
    }
    Node * cur = head;
    int num = CountNode(head);
    Vector2 center = pos;

    // cout << center.x;

    while (cur){
        DrawNode(center, cur->val, 0);
        Vector2 newCenter = {center.x + 2 * radius + spacing, center.y};
        if (cur->next){
            DrawArrow(center, newCenter);
        }
        cur = cur->next;
        center = newCenter;
    }
}

void LinkedList::EventLLinPage(Page &page) {
    if(page.func == FUNC::CREATE) {
        //CreateLL;
    }
    if(page.func == FUNC::INSERT) {
        if(page.textbox.nums.size() > 0) {
            lastInsertedKey = page.textbox.nums[0];
            page.textbox.nums.erase(page.textbox.nums.begin());
            isInserting = true;
            page.textbox.inputText = "";
        }   
        Node* cur = head; while(cur) {cout<<cur->val<<" "; cur = cur->next;} cout<<endl;
    }
    if(page.func == FUNC::SEARCH) {
        //SearchLL;
    }
    if(page.func == FUNC::DELETE) {
        //DeleteLL;
    }

    if (Pos.x > NewPos.x){
        Pos = {Pos.x - 5, Pos.y};
    }
    else{
        Pos = NewPos;
    }
}


void LinkedList::DrawLLinPage(Page page) {
    if(page.func == FUNC::CREATE) {
        //DrawLL();
    }
    if(page.func == FUNC::INSERT) {
        if (isInserting) {
            DrawInsert(lastInsertedKey);
            isInserting = false;
        }
        else{
            DrawLL(Pos);
        }
    }
    if(page.func == FUNC::SEARCH) {
        //SearchLLDraw;
    }
    if(page.func == FUNC::DELETE) {
        //DeleteLLDraw;
    }
    
    //BeginDrawing();
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //EndDrawing();   
}


void LinkedList::DrawInsert(int key) {
    if (!head) {
        head = new Node(key, nullptr);
        Pos = GetPosition(CountNode(head));
        NewPos = Pos;
        return;
    }
    Pos = GetPosition(CountNode(head));
    Vector2 center = Pos;
    DrawLL(center);

    Node * a = head;
    Node * b = new Node(0, a);
    while (a){
        BeginDrawing();
        DrawLL(Pos);
        DrawNode(center, a->val, -1);
        EndDrawing();
        a = a->next;
        b = b->next;
        Vector2 newCenter = {center.x + 2*radius + spacing, center.y};
        center = newCenter;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    Node * tmp = new Node(key, nullptr);
    tmp->val = key;
    tmp->next = nullptr;
    b->next = tmp;

    NewPos = GetPosition(CountNode(head));
}

void LinkedList::SearchNode(int key){
    if (!head){
        cout << "Head is NULL\n";
        return;
    }
    

}