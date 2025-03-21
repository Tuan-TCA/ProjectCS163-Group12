#include "LinkedList.h"
#include <raylib.h>
#include <thread>
using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
    workplace = {400,300,600,600};
    // position = {workplace.x*1.1f, workplace.y*1.1f};
    isInserting = false;
    isSearching = false;
    isDeleting = false;
    isUpdating = false;
}

void LinkedList::init(){
    while (head){
        Node * tmp = head;
        head = head->next;
        delete tmp;
    }
}

void LinkedList::EventLLinPage(Page &page) {
    if(page.currentOperation == Operation::Create) {
        //CreateLL;
    }
    if(page.currentOperation == Operation::Insert) {
        
        if(page.textbox.nums.size() > 0) {
            lastInsertedKey = page.textbox.nums[0];
            page.textbox.nums.erase(page.textbox.nums.begin());
            isInserting = true;
            page.textbox.inputText = "";
        }   
        // Node* cur = head; while(cur) {cout<<cur->val<<" "; cur = cur->next;} cout<<endl;
    }
    if(page.currentOperation == Operation::Search) {
        if(page.textbox.nums.size() > 0) {
            SearchKey = page.textbox.nums[0];
            page.textbox.nums.erase(page.textbox.nums.begin());
            isSearching = true;
            page.textbox.inputText = "";
        }
    }
    if(page.currentOperation == Operation::Delete) {
        if(page.textbox.nums.size() > 0) {
            DeleteKey = page.textbox.nums[0];
            page.textbox.nums.erase(page.textbox.nums.begin());
            isDeleting = true;
            page.textbox.inputText = "";
        }
    }

    if(page.currentOperation == Operation::Update) {
        if(page.textbox.nums.size() > 0) {
            UpdateKey = page.textbox.nums[0];
            page.textbox.nums.erase(page.textbox.nums.begin());
            newVal = page.textbox.nums[1];
            isUpdating = true;
            page.textbox.inputText = "";
        }
    }

    if (Pos.x > NewPos.x){
        Pos = {Pos.x - 5, Pos.y};
    }
    else{
        Pos = NewPos;
    }
}

void LinkedList::DrawLLinPage(Page &page) {
    if(page.currentOperation == Operation::Create) {
        //DrawLL();
    }
    if(page.currentOperation == Operation::Insert) {
        if (isInserting) {
            DrawInsert(lastInsertedKey);
            isInserting = false;
        }
        else{
            DrawLL(Pos);
        }
    }
    if(page.currentOperation == Operation::Search) {
        if (isSearching) {
            DrawSearchNode(SearchKey);
            isSearching = false;
        }
        else{
            DrawLL(Pos);
        }
    }
    if(page.currentOperation == Operation::Delete) {
        if (isDeleting) {
            DrawDeleteNode(DeleteKey);
            isDeleting = false;
        }
        else{
            DrawLL(Pos);
        }

    }

    if(page.currentOperation == Operation::Update) {
        if (isUpdating) {
            DrawUpDateNode(UpdateKey, newVal);
            isUpdating = false;
        }
        else{
            DrawLL(Pos);
        }

    }
    
    //BeginDrawing();
    if (isInserting) {
        DrawInsert(lastInsertedKey);
        isInserting = false;
    }

    if (isSearching) {
        DrawSearchNode(SearchKey);
        isSearching = false;
    }

    if (isDeleting) {
        DrawDeleteNode(DeleteKey);
        isDeleting = false;
    }

    if (isUpdating) {
        DrawDeleteNode(UpdateKey);
        isUpdating = false;
    }

    else{
        DrawLL(Pos);
    }
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //EndDrawing();   
}


Vector2 LinkedList::GetPosition(int count){
    int d = 2 * radius * count + (count - 1)*spacing;
    int X = max((W/2 - d/2) + radius, 0) + 400;
    int Y = H/2;
    Vector2 center = {(float)X, (float)Y};
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
        //cout << center.x << ' ' << key << '\n';
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

bool LinkedList::DrawSearchNode(int key){
    if (!head){
        cout << "Head is NULL\n";
        return false;
    }
    bool found = false;

    Pos = GetPosition(CountNode(head));
    Vector2 center = Pos;
    DrawLL(center);

    Node * a = head;
    while (a){

        cout << "SEARCH: " << a->val << ' ' << key << '\n';

        if(a->val == key){
            BeginDrawing();
            DrawLL(Pos);
            DrawNode(center, a->val, 1);
            EndDrawing();
            found = true;
            std::this_thread::sleep_for(std::chrono::milliseconds(700));
            return true;
        }
        BeginDrawing();
        DrawLL(Pos);
        DrawNode(center, a->val, -1);
        EndDrawing();
        a = a->next;
        Vector2 newCenter = {center.x + 2*radius + spacing, center.y};
        center = newCenter;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    if (!found) {
        BeginDrawing();  
        DrawLL(Pos);  
         
        int textW = MeasureText("NOT FOUND", font_size); 
        int listWidth = max(CountNode(head), 1) * (2 * radius + spacing); 
        int posX = Pos.x + (listWidth - textW) / 2 - radius;
        int posY = Pos.y + font_size + 100;  
    
        DrawText("NOT FOUND", posX, posY, font_size, RED);
        
        EndDrawing(); 
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  
    }

    return found;
}


void LinkedList::DrawDeleteNode(int key){
    if (!head){
        cout << "Head is NULL\n";
        return;
    }

    bool ok = DrawSearchNode(key);

    if (ok){
        Node *a = head, *prev = nullptr;
        if (head->val == key){
            head = head->next;
            delete a;
            return;
        }
        while (a){
            if (a->val == key){
                prev->next = a->next;
                delete a;
                return;
            } 
            prev = a;
            a = a->next;
        }
    }

    return;
    
    Pos = GetPosition(CountNode(head));
    Vector2 center = Pos;
    DrawLL(center);

    Node * a = head;
    Node * pre = nullptr;
    while (a){
        cout << a->val << ": " << key << '\n';
        if(a->val == key){
            BeginDrawing();
            DrawNode(center, a->val, 1);
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            if(!pre){
                head = a->next;
            }
            else{
                pre->next = a->next;
            }
            delete a;

            NewPos = GetPosition(CountNode(head));
            Pos = NewPos;

            BeginDrawing();
            DrawLL(Pos);
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            return;
        }
        BeginDrawing();
        DrawLL(Pos);
        DrawNode(center, a->val, -1);
        EndDrawing();
        pre = a;
        a = a->next;
        Vector2 newCenter = {center.x + 2*radius + spacing, center.y};
        center = newCenter;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void LinkedList::DrawUpDateNode(int first, int second){
    if(!head){
        cout << "Head is empty\n";
        return;
    }
    Pos = GetPosition(CountNode(head));
    Vector2 center = Pos;
    DrawLL(center);

    Node * a = head;
    while(a){
        if(a->val == first){
            BeginDrawing();
            DrawNode(center, a->val, 1);
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            BeginDrawing();
            DrawNode(center, second, 1);
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            a->val = second;
            return;
        }
        BeginDrawing();
        DrawLL(Pos);
        DrawNode(center, a->val, -1);
        EndDrawing();
        a = a->next;
        Vector2 newCenter = {center.x + 2*radius + spacing, center.y};
        center = newCenter;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
