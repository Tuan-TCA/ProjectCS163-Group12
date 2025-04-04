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
    isCreating = false;
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
    isCreating = false;
}

void LinkedList::event() {
    Page::event();

    //Choose Operation
    if(currentOperation == Operation::Create) {
        if(textbox.nums.size() > 0) {
            numbers = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isCreating = true;
            textbox.inputText = {""};
        }
    }
    if(currentOperation == Operation::Insert) {
        
        if(textbox.nums.size() > 0) {
            lastInsertedKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isInserting = true;
            textbox.inputText = {""};
        }   
        // Node* cur = head; while(cur) {cout<<cur->val<<" "; cur = cur->next;} cout<<endl;
    }
    if(currentOperation == Operation::Search) {
        if(textbox.nums.size() > 0) {
            SearchKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isSearching = true;
            textbox.inputText = {""};
        }
    }
    if(currentOperation == Operation::Delete) {
        if(textbox.nums.size() > 0) {
            DeleteKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isDeleting = true;
            textbox.inputText = {""};
        }
    }

    if(currentOperation == Operation::Update) {
        if(textbox.nums.size() > 0) {
            UpdateKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            newVal = textbox.nums[1];
            isUpdating = true;
            textbox.inputText = {""};
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

    if (back1.IsClicked() || back2.IsClicked()) {
        if (animationController.IsFinished()) {
            Pos = finishedPos;
            hasFinishedOnce = false;
            isPlaying = false;
        }
        if (animationController.currentStep > 0) {
            animationController.isPaused = true;
            animationController.currentStep--; 
            if (!animationController.steps.empty()) {
                animationController.steps[animationController.currentStep]();
            }
        }
    } else if ((next1.IsClicked() || next2.IsClicked()) && animationController.currentStep < animationController.steps.size() - 1) {
        animationController.isPaused = true;
        animationController.currentStep++;
    }


    //...Lưu ý: Cần chỉnh sửa hiển thị nút play, pause cho phù hợp
}


void LinkedList::draw() {
    Page::draw();

    static float elapsedTime = 0.0f; 
    const float stepDuration = 0.5f/animationSpeed;
    if (currentOperation == Operation::Create) {
        if (isCreating) {
            animationController.Reset();         
            // DrawInsert(lastInsertedKey);         
            isCreating = false;                 
            elapsedTime = 0.0f;                  
            hasFinishedOnce = false;        
        } else {
            if (!animationController.steps.empty()) {
                if (animationController.currentStep < animationController.steps.size()) {
                    animationController.steps[animationController.currentStep](); 
                }

                if (!animationController.IsPaused()) {
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
                    finishedPos = Pos;    
                    hasFinishedOnce = true; 
                }
                if (Pos.x > NewPos.x) {
                    Pos = {Pos.x - 5, Pos.y}; 
                } else {
                    Pos = NewPos; 
                }
            }
        }
    }

    if (currentOperation == Operation::Insert) {
        if (isInserting) {
            animationController.Reset();         
            DrawInsert(lastInsertedKey);         
            isInserting = false;                 
            elapsedTime = 0.0f;                  
            hasFinishedOnce = false;        
        } else {
            if (!animationController.steps.empty()) {
                if (animationController.currentStep < animationController.steps.size()) {
                    animationController.steps[animationController.currentStep](); 
                }

                if (!animationController.IsPaused()) {
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
                    finishedPos = Pos;    
                    hasFinishedOnce = true; 
                }
                if (Pos.x > NewPos.x) {
                    Pos = {Pos.x - 5, Pos.y}; 
                } else {
                    Pos = NewPos; 
                }
            }
        }
    }

    if (currentOperation == Operation::Search) {
        if (isSearching) {
            animationController.Reset();         
            DrawSearchNode(SearchKey);           
            isSearching = false;                 
            elapsedTime = 0.0f;                  
            hasFinishedOnce = false;             
        } else {
            if (!animationController.steps.empty()) {
                if (animationController.currentStep < animationController.steps.size()) {
                    animationController.steps[animationController.currentStep](); 
                }

                if (!animationController.IsPaused()) {
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
                    finishedPos = Pos;    
                    hasFinishedOnce = true; 
                }
                if (Pos.x > NewPos.x) {
                    Pos = {Pos.x - 5, Pos.y}; 
                } else {
                    Pos = NewPos; 
                }
            }
        }
    }

    if (currentOperation == Operation::Delete) {
        if (isDeleting) {
            animationController.Reset(); 
            DrawDeleteNode(DeleteKey);           
            isDeleting = false;                  
            elapsedTime = 0.0f;              
            hasFinishedOnce = false;             
        } else {
            if (!animationController.steps.empty()) {
                if (animationController.currentStep < animationController.steps.size()) {
                    animationController.steps[animationController.currentStep](); 
                }

                if (!animationController.IsPaused()) {
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
                    finishedPos = Pos;    
                    hasFinishedOnce = true; 
                }
                if (Pos.x < NewPos.x) {
                    Pos = {Pos.x + 5, Pos.y}; 
                } else {
                    Pos = NewPos; 
                }
            }
        }
    }

    if (currentOperation == Operation::Update) {
        if (isUpdating) {
            animationController.Reset();         
            DrawUpDateNode(UpdateKey, newVal);   
            isUpdating = false;                  
            elapsedTime = 0.0f;                  
            hasFinishedOnce = false;             
        } else {
            if (!animationController.steps.empty()) {
                if (animationController.currentStep < animationController.steps.size()) {
                    animationController.steps[animationController.currentStep](); 
                }

                if (!animationController.IsPaused()) {
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
                    finishedPos = Pos;    
                    hasFinishedOnce = true; 
                }
                if (Pos.x > NewPos.x) {
                    Pos = {Pos.x - 5, Pos.y}; 
                } else {
                    Pos = NewPos; 
                }
            }
        }
    }
}

LinkedList* LinkedList::copy() const {
    LinkedList* newList = new LinkedList(); // Tạo đối tượng mới

    // Sao chép các thuộc tính
    newList->Pos = this->Pos;
    newList->NewPos = this->NewPos;
    newList->finishedPos = this->finishedPos;
    newList->hasFinishedOnce = this->hasFinishedOnce;
    newList->workplace = this->workplace;
    newList->W = this->W;
    newList->H = this->H;
    newList->isInserting = this->isInserting;
    newList->lastInsertedKey = this->lastInsertedKey;
    newList->isSearching = this->isSearching;
    newList->SearchKey = this->SearchKey;
    newList->isDeleting = this->isDeleting;
    newList->DeleteKey = this->DeleteKey;
    newList->isUpdating = this->isUpdating;
    newList->UpdateKey = this->UpdateKey;
    newList->newVal = this->newVal;

    // Sao chép danh sách liên kết
    if (!this->head) return newList; // Nếu danh sách rỗng, trả về bản sao rỗng

    Node* current = this->head;
    Node* newHead = new Node(current->val, nullptr); // Sao chép node đầu tiên
    newList->head = newHead;
    Node* newCurrent = newHead;

    current = current->next;
    while (current) {
        newCurrent->next = new Node(current->val, nullptr); // Sao chép node tiếp theo
        newCurrent = newCurrent->next;
        current = current->next;
    }

    return newList;
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
    Color arrow_color = MyColor1;
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
    DrawCircleV(center, radius - 9, MyColor2);
    DrawCircleV(center, radius - 10, MyColor2);

    int Fs = max(10, static_cast<int>(font_size-s.size()*3));
    //Draw text
    int wNode =  MeasureText(s.c_str(), Fs);
    DrawText(s.c_str(), center.x - wNode / 2, center.y - Fs/2, Fs, text_color);

    // EndDrawing();
}


void LinkedList::DrawLL(Vector2 pos, bool last) {

    if (!head){
        // cout << "Head is null\n";
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
        animationController.AddStep([this, a,center] () {
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
    //DrawLL(center);

    Node * a = head;
    while (a){

        cout << "SEARCH: " << a->val << ' ' << key << '\n';

        if(a->val == key){
            animationController.AddStep([this, a,center]() {
            DrawLL(Pos);
            DrawNode(center, a->val, 1);
            });
            found = true;
            //std::this_thread::sleep_for(std::chrono::milliseconds(700));
            return true;
        }
        animationController.AddStep([this, a,center]() {
        DrawLL(Pos);
        DrawNode(center, a->val, -1);
        });
        a = a->next;
        Vector2 newCenter = {center.x + 2*radius + spacing, center.y};
        center = newCenter;
        //std::this_thread::sleep_for(std::chrono::milliseconds((int)(500.0f / animationSpeed)));
    }
    if (!found) {
        animationController.AddStep([this, a,center]() {
        DrawLL(Pos);  
         
        int textW = MeasureText("NOT FOUND", font_size); 
        int listWidth = max(CountNode(head), 1) * (2 * radius + spacing); 
        int posX = Pos.x + (listWidth - textW) / 2 - radius;
        int posY = Pos.y + font_size + 100;  
    
        DrawText("NOT FOUND", posX, posY, font_size, RED);
        });
        //EndDrawing(); 
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));  
    }

    return found;
}

void LinkedList::DrawDeleteNode(int key) {
    if (!head) {
        animationController.AddStep([this]() {
            DrawLL(this->Pos);
            DrawText("List is empty", Pos.x, Pos.y - 50, font_size, RED);
        });
        return;
    }

    Pos = GetPosition(CountNode(head));
    Vector2 center = Pos;

    // Tạo bản sao

    Node *a = head, *prev = nullptr;
    bool found = false;

    
    LinkedList* tmp = this->copy();
    while (a) {
        Vector2 currentCenter = center;
        int val = a->val;
        animationController.AddStep([tmp, currentCenter, val]() {
            tmp->DrawLL(tmp->Pos);
            tmp->DrawNode(currentCenter, val, -1);
        });

        if (a->val == key && !found) {
            found = true;
            animationController.AddStep([tmp, currentCenter, val]() {
                tmp->DrawLL(tmp->Pos);
                tmp->DrawNode(currentCenter, val, 1);
            });
            break;
        }

        prev = a;
        a = a->next;
        center = {center.x + 2 * radius + spacing, center.y};
    }

    if (found) {
        NewPos = GetPosition(CountNode(head) - 1);
        tmp = this->copy();
        animationController.AddStep([this, tmp, key]() {
            Node *a = head, *prev = nullptr;
            while (a && a->val != key) {
                prev = a;
                a = a->next;
            }
            if (a) {
                if (prev) {
                    prev->next = a->next;
                } else {
                    head = a->next;
                }
                delete a;
            }
            DrawLL(Pos); // Redraw after deletion (dùng this)
        });
    } 

    else {
        animationController.AddStep([tmp]() {
            tmp->DrawLL(tmp->Pos);
            int textW = MeasureText("NOT FOUND", tmp->font_size);
            int listWidth = max(tmp->CountNode(tmp->head), 1) * (2 * tmp->radius + tmp->spacing);
            int posX = tmp->Pos.x + (listWidth - textW) / 2 - tmp->radius;
            int posY = tmp->Pos.y + tmp->font_size + 100;
            DrawText("NOT FOUND", posX, posY, tmp->font_size, RED);
        });
    }

    delete tmp;     // Giải phóng bản sao
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

void LinkedList::DrawCreateNode(int numbers) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }

    // 2. Tạo danh sách mới với số lượng phần tử `numbers` (random phần tử)
    for (int i = 0; i < numbers; ++i) {
        int newKey = GetRandomValue(1, 100); // Tạo số ngẫu nhiên từ 1 đến 100
        Node* newNode = new Node(newKey, nullptr);

        // Nếu danh sách rỗng, node này sẽ là head
        if (!head) {
            head = newNode;
        } else {
            // Nếu danh sách không rỗng, thêm node vào cuối danh sách
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // 3. Cập nhật lại vị trí và vẽ lại danh sách liên kết
    Pos = GetPosition(CountNode(head)); // Cập nhật vị trí để vẽ
    NewPos = Pos;
    Vector2 center = Pos;

    // 4. Vẽ lại danh sách liên kết
    animationController.Reset();  // Reset lại animation controller
    animationController.AddStep([this, center]() {
        DrawLL(Pos, true); // Vẽ lại danh sách liên kết mới
    });

    // Thực hiện vẽ node cho từng phần tử trong danh sách
    Node* temp = head;
    while (temp) {
        animationController.AddStep([this, temp, center]() {
            DrawNode(center, temp->val, 0); // Vẽ node với giá trị
        });
        temp = temp->next;
        center.x += (2 * radius + spacing); // Cập nhật vị trí vẽ cho node tiếp theo
    }

    // Chạy animation
    animationController.NextStep();
}
