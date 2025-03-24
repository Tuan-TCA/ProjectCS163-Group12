#include "LinkedList.h"
#include <raylib.h>
#include <thread>
#include "ControlAnimation.h"
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
    Page::init();
        while (head){
        Node * tmp = head;
        head = head->next;
        delete tmp;
    }
    head = nullptr;
    workplace = {400,300,600,600};
    // position = {workplace.x*1.1f, workplace.y*1.1f};
    isInserting = false;
    isSearching = false;
    isDeleting = false;
    isUpdating = false;
}

void LinkedList::event() {
    Page::event();


    //Choose Operation
    if(currentOperation == Operation::Create) {
        //CreateLL;
    }
    if(currentOperation == Operation::Insert) {
        
        if(textbox.nums.size() > 0) {
            lastInsertedKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isInserting = true;
            textbox.inputText = "";
        }   
        // Node* cur = head; while(cur) {cout<<cur->val<<" "; cur = cur->next;} cout<<endl;
    }
    if(currentOperation == Operation::Search) {
        if(textbox.nums.size() > 0) {
            SearchKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isSearching = true;
            textbox.inputText = "";
        }
    }
    if(currentOperation == Operation::Delete) {
        if(textbox.nums.size() > 0) {
            DeleteKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isDeleting = true;
            textbox.inputText = "";
        }
    }

    if(currentOperation == Operation::Update) {
        if(textbox.nums.size() > 0) {
            UpdateKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            newVal = textbox.nums[1];
            isUpdating = true;
            textbox.inputText = "";
        }
    }

    //Run step-by-step

    if(!isPlaying){
        if(!switchState ? play1.IsClicked() : play2.IsClicked()){
            animationController.isPaused = !animationController.isPaused;
            isPlaying = true;
            TraceLog(LOG_INFO, "is playing");
        }
    }
    else{
        if( isPlaying && !switchState ? pause1.IsClicked() : pause2.IsClicked())
        {
            animationController.isPaused = !animationController.isPaused;
            isPlaying = false;
            TraceLog(LOG_INFO, "is pausing");
        }
    }


    // Kiểm tra phím mũi tên trái và phải
    if (back1.IsClicked() || back2.IsClicked()) {
        if (animationController.IsFinished()) {
            // Khi animation đã hoàn tất, khôi phục Pos và trạng thái animation
            Pos = finishedPos;
            hasFinishedOnce = false;
            isPlaying = false;
            //animationController.isFinished = false; // Đặt lại để animation chưa kết thúc
        }
        if (animationController.currentStep > 0) {
            animationController.isPaused = true;
            animationController.currentStep--; // Quay lại bước trước đó
            if (!animationController.steps.empty()) {
                animationController.steps[animationController.currentStep](); // Vẽ bước trước đó
            }
        }
    } else if ((next1.IsClicked() || next2.IsClicked()) && animationController.currentStep < animationController.steps.size() - 1) {
        animationController.isPaused = true; // Tạm dừng animation
        animationController.currentStep++;
    }


    //...Lưu ý: Cần chỉnh sửa hiển thị nút play, pause cho phù hợp
}


void LinkedList::draw() {
    Page::draw();

    // Toggle pause/resume khi nhấn SPACE
    

    static float elapsedTime = 0.0f; // Thời gian trôi qua cho mỗi step
    const float stepDuration = 0.5f; // Thời gian chờ giữa các step (0.5 giây)

    // Operation: Insert
    if (currentOperation == Operation::Insert) {
        if (isInserting) {
            animationController.Reset(); 
            DrawInsert(lastInsertedKey); 
            isInserting = false;         
            elapsedTime = 0.0f;          
            hasFinishedOnce = false;     
        }
        else {
            if (!animationController.steps.empty()) { // Kiểm tra xem có bước nào không
                // Luôn vẽ step hiện tại nếu currentStep hợp lệ
                if (animationController.currentStep < animationController.steps.size()) {
                    animationController.steps[animationController.currentStep]();
                }
    
                if (animationController.IsPaused()) {
                    // Khi pause, hiển thị thông tin step hiện tại
                    DrawText(("Current Step: " + std::to_string(animationController.currentStep)).c_str(),
                             10, 10, 20, WHITE);
                } else {
                    // Cập nhật thời gian và chuyển bước nếu đủ thời gian
                    elapsedTime += GetFrameTime();
                    if (elapsedTime >= stepDuration && !animationController.IsFinished()) {
                        animationController.NextStep();
                        elapsedTime = 0.0f;
                        cout << animationController.currentStep << endl;
                    }
                }
            }
    
            if (animationController.IsFinished()) {
                DrawLL(Pos);
                if (!hasFinishedOnce) {
                    finishedPos = Pos;    // Cập nhật finishedPos trong lần đầu tiên
                    hasFinishedOnce = true; // Đánh dấu đã hoàn tất lần đầu
                }
                if (Pos.x > NewPos.x) {
                    Pos = {Pos.x - 5, Pos.y}; // Tiếp tục di chuyển Pos về NewPos
                } else {
                    Pos = NewPos; // Pos đã đến vị trí đích

                }
            }
        }
    }

    // Operation: Search
    if (currentOperation == Operation::Search) {
        if (isSearching) {
            animationController.Reset();
            DrawSearchNode(SearchKey);
            isSearching = false;
            elapsedTime = 0.0f;
        } else {
            // Kiểm tra phím mũi tên trái và phải
            if (IsKeyPressed(KEY_LEFT) && animationController.currentStep > 0) {
                animationController.isPaused = true;
                animationController.currentStep--;
            } else if (IsKeyPressed(KEY_RIGHT) && animationController.currentStep < animationController.steps.size() - 1) {
                animationController.isPaused = true;
                animationController.currentStep++;
            }

            if (!animationController.steps.empty()) {
                if (animationController.currentStep < animationController.steps.size()) {
                    animationController.steps[animationController.currentStep]();
                }

                if (animationController.IsPaused()) {
                    DrawText(("Current Step: " + std::to_string(animationController.currentStep)).c_str(),
                             10, 10, 20, WHITE);
                } else {
                    elapsedTime += GetFrameTime();
                    if (elapsedTime >= stepDuration && !animationController.IsFinished()) {
                        animationController.NextStep();
                        elapsedTime = 0.0f;
                        cout << animationController.currentStep << endl;
                    }
                }
            }

            if (animationController.IsFinished()) {
                DrawLL(Pos);
            }
        }
    }

    // Operation: Delete
    if (currentOperation == Operation::Delete) {
        if (isDeleting) {
            animationController.Reset();
            DrawDeleteNode(DeleteKey);
            isDeleting = false;
            elapsedTime = 0.0f;
        } else {
            // Kiểm tra phím mũi tên trái và phải
            if (IsKeyPressed(KEY_LEFT) && animationController.currentStep > 0) {
                animationController.isPaused = true;
                animationController.currentStep--;
            } else if (IsKeyPressed(KEY_RIGHT) && animationController.currentStep < animationController.steps.size() - 1) {
                animationController.isPaused = true;
                animationController.currentStep++;
            }

            if (!animationController.steps.empty()) {
                if (animationController.currentStep < animationController.steps.size()) {
                    animationController.steps[animationController.currentStep]();
                }

                if (animationController.IsPaused()) {
                    DrawText(("Current Step: " + std::to_string(animationController.currentStep)).c_str(),
                             10, 10, 20, WHITE);
                } else {
                    elapsedTime += GetFrameTime();
                    if (elapsedTime >= stepDuration && !animationController.IsFinished()) {
                        animationController.NextStep();
                        elapsedTime = 0.0f;
                        cout << animationController.currentStep << endl;
                    }
                }
            }

            if (animationController.IsFinished()) {
                DrawLL(Pos);
            }
        }
    }

    // Operation: Update
    if (currentOperation == Operation::Update) {
        if (isUpdating) {
            animationController.Reset();
            DrawUpDateNode(UpdateKey, newVal);
            isUpdating = false;
            elapsedTime = 0.0f;
        } else {
            // Kiểm tra phím mũi tên trái và phải
            if (IsKeyPressed(KEY_LEFT) && animationController.currentStep > 0) {
                animationController.isPaused = true;
                animationController.currentStep--;
            } else if (IsKeyPressed(KEY_RIGHT) && animationController.currentStep < animationController.steps.size() - 1) {
                animationController.isPaused = true;
                animationController.currentStep++;
            }

            if (!animationController.steps.empty()) {
                if (animationController.currentStep < animationController.steps.size()) {
                    animationController.steps[animationController.currentStep]();
                }

                if (animationController.IsPaused()) {
                    DrawText(("Current Step: " + std::to_string(animationController.currentStep)).c_str(),
                             10, 10, 20, WHITE);
                } else {
                    elapsedTime += GetFrameTime();
                    if (elapsedTime >= stepDuration && !animationController.IsFinished()) {
                        animationController.NextStep();
                        elapsedTime = 0.0f;
                        cout << animationController.currentStep << endl;
                    }
                }
            }

            if (animationController.IsFinished()) {
                DrawLL(Pos);
            }
        }
    }
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


void LinkedList::DrawLL(Vector2 pos, bool last) {

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
        if(!last && cur->next && cur->next->next == nullptr) return;
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
    //DrawLL(center);

    Node * a = head;
    Node * b = new Node(0, a);
    while (a) {
        animationController.AddStep([this, a,center]() {
            //BeginDrawing();
            DrawLL(this->Pos, false);
            DrawNode(center, a->val, -1);
            //EndDrawing();
        });

        a = a->next;
        b = b->next;
        Vector2 newCenter = {center.x + 2*radius + spacing, center.y};
        center = newCenter;
        
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
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(500.0f / animationSpeed)));
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
        Pos = GetPosition(CountNode(head) - 1);
        NewPos = Pos;
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
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(500.0f / animationSpeed)));
            BeginDrawing();
            DrawNode(center, second, 1);
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(500.0f / animationSpeed)));
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
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(500.0f / animationSpeed)));
    }
}
