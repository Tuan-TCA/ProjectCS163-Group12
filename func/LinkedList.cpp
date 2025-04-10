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
    headPos = {400,300};
    // position = {workplace.x*1.1f, workplace.y*1.1f};
    isInserting = false;
    isSearching = false;
    isDeleting = false;
    isUpdating = false;


    isInserting = false;
    isSearching = false;
    isDeleting = false;
    isUpdating = false;
    //isCreating = false;

    hasInsert = false;
    hasSearch = false;
    hasDelete = false;

    cur = -1;
    curCode = -1;
    pseudocode = {};


}


void LinkedList::reset(){
    Page::reset();
     while (head){
        Node * tmp = head;
        head = head->next;
        delete tmp;
    }
    head = nullptr;
    workplace = {400,300,600,600};
    isInserting = false;
    isSearching = false;
    isDeleting = false;
    isUpdating = false;
}

void LinkedList::event() {
    Page::event();
    //Choose Operation
   
    if(currentOperation == Operation::Create) {
    //     hasInsert = false;
    //     hasSearch = false;
    //     hasDelete = false;
    //     hasCreate = true;
    //     if(Page::Ok.IsClicked()) {
    //         DestroyRecursive(head);
    //         root = nullptr;
    //         isCreating = true;
    //     }       
    // }
    }
    
    if(currentOperation == Operation::Insert) {
        if(!hasInsert) {
            hasInsert = true;
            hasSearch = false;
            hasDelete = false;
            hasCreate = false;
            cur = 0;
            DrawLL(head);
            steps.clear();
            addStep(this->head);
    
        }
        if(textbox.nums.size() > 0) {
            lastInsertedKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isInserting = true;
            textbox.inputText = {""};
        }   
        
    }
    if(currentOperation == Operation::Search) {
        if(!hasSearch) {
            hasInsert = false;
            hasSearch = true;
            hasDelete = false;
            hasCreate = false;
            cur = 0;
            steps.clear();
            addStep(this->head);
        }
        if(textbox.nums.size() > 0) {
            SearchKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isSearching = true;
            textbox.inputText = {""};
        }
    }
    if(currentOperation == Operation::Delete) {
        if(!hasDelete) {
            hasInsert = false;
            hasSearch = false;
            hasDelete = true;
            hasCreate = false;
            cur = 0;
            steps.clear();
            addStep(this->head);
        }
        if(textbox.nums.size() > 0) {
            DeleteKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isDeleting = true;
            textbox.inputText = {""};
        }
    }

    static Operation lastOp = Operation::Algorithm;
    if(currentOperation != lastOp) {
        updatePseudocode();
        lastOp = currentOperation;
    }

    if(!isPlaying){
        if(!switchState ? play1.IsClicked() : play2.IsClicked()){
            isPlaying = true;
            TraceLog(LOG_INFO, "is playing");
        }
    }
    else{
        if(!switchState ? pause1.IsClicked() : pause2.IsClicked())
        {
            isPlaying = false;
            TraceLog(LOG_INFO, "is pausing");
        }
    }

    
    if (back1.IsClicked() || back2.IsClicked()) { 
        if (cur > 0) {
            cur--;
        }
        isPlaying = false; 
    } 
    else if (next1.IsClicked() || next2.IsClicked()) { 
        if (cur < steps.size() - 1) {
            cur++;
        }
        isPlaying = false; 
    }

    
    if (IsKeyPressed(KEY_LEFT)) {
        if (cur > 0) {
            cur--;
            isPlaying = false;
        }
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        if (cur < steps.size() - 1) {
            cur++;
            isPlaying = false;
        }
    }
    //...Lưu ý: Cần chỉnh sửa hiển thị nút play, pause cho phù hợp
}


void LinkedList::draw() {
    Page::draw();

    static float elapsedTime = 0.0f;
    const float stepDuration = 0.5f / animationSpeed;

    
    if(IsKeyPressed(KEY_A)) {
        Vector2 k = GetMousePosition();
        auto t = head->Pos;
        head->Pos = k;
        DrawLL(head);
        head->Pos = t;
    }

    // if(currentOperation == Operation::Create) {
    //     if (isCreating) {
    //         hasCreate = true;
    //         random_device rd;
    //         mt19937 gen(rd());
    //         uniform_int_distribution<int> dist(2,11);
    //         uniform_int_distribution<int> dist2(100,999);

    //         int t = dist(gen);
    //         while(t--) {
    //             int k = dist2(gen);
    //             this->insert(k, head);
    //         }
    //         steps.clear();
    //         isCreating = false;
    //         isPlaying = true;
    //     }
    //     else {
    //         DrawLL(head);
    //         isPlaying = false;
    //     }
    // }
    if (currentOperation == Operation::Insert) {
        if (isInserting) {
            cout<<"Insert";
            this->Insert(lastInsertedKey);
      
            addStep(this->head);
            isInserting = false;
            isPlaying = true;
            elapsedTime = 0.0f;
            
            //rotationStartTime = GetTime();
            //isRotating = false;
        } else if (!steps.empty()) {
            if (cur >= 0 && cur < steps.size()) {
                // Xử lý animation xoay - chỉ khi đang phát (isPlaying)
                // if (steps[cur].isRotating && isPlaying) {
                //     if (!isRotating) {
                //         // Bắt đầu animation xoay
                //         isRotating = true;
                //         rotationStartTime = GetTime();
                //     }
    
                //     float rotationProgress = (GetTime() - rotationStartTime) / stepDuration;
                    
                //     if (rotationProgress < 1.0f) {
                //         // Đang trong quá trình xoay
                //         AVLpaint tmp;
                //         tmp.copy(steps[cur].head);
                //         tmp.isRotating = true;
                        
                //         updateNodePositions(tmp.head, steps[cur+1].head, rotationProgress);
                        
                //         drawStep(tmp);
                //     } else {
                //         // Kết thúc xoay, chuyển sang bước tiếp theo
                //         isRotating = false;
                //         cur++;
                //         drawStep(steps[cur]);
                //     }
                // } 

                // else {
                    // Vẽ bước hiện tại (không xoay hoặc không phải đang phát)
                    
                    drawStep(steps[cur]);
                    
                    
                    // Tự động chuyển bước nếu đang phát
                    if (isPlaying) {
                        elapsedTime += GetFrameTime();
                        if (elapsedTime >= stepDuration) {
                            if (cur < steps.size() - 1) {
                                cur++;
                                elapsedTime = 0.0f;
                            } else {
                                isPlaying = false;
                            }
                        }
                    
                    }

                    if(cur == steps.size() && cur!=0) {  
                        drawStep(steps[cur-1]);   
                        cout<<"ok";      
                        isPlaying = false;
                    }
            }
        }
    }

    // if (currentOperation == Operation::Search) {
    //     if (isSearching) {
    //         animationController.Reset();         
    //         DrawSearchNode(SearchKey);           
    //         isSearching = false;                 
    //         elapsedTime = 0.0f;                  
    //         hasFinishedOnce = false;             
    //     } else {
    //         if (!animationController.steps.empty()) {
    //             if (animationController.currentStep < animationController.steps.size()) {
    //                 animationController.steps[animationController.currentStep](); 
    //             }

    //             if (!animationController.IsPaused()) {
    //                 elapsedTime += GetFrameTime(); 
    //                 if (elapsedTime >= stepDuration && !animationController.IsFinished()) {
    //                     animationController.NextStep(); 
    //                     elapsedTime = 0.0f;             
    //                     // cout << animationController.currentStep << endl; 
    //                 }
    //             }
    //         }

    //         if (animationController.IsFinished()) {
    //             DrawLL(Pos); 
    //             if (!hasFinishedOnce) {
    //                 finishedPos = Pos;    
    //                 hasFinishedOnce = true; 
    //             }
    //             if (Pos.x > NewPos.x) {
    //                 Pos = {Pos.x - 5, Pos.y}; 
    //             } else {
    //                 Pos = NewPos; 
    //             }
    //         }
    //     }
    // }

    // if (currentOperation == Operation::Delete) {
    //     if (isDeleting) {
    //         animationController.Reset(); 
    //         DrawDeleteNode(DeleteKey);           
    //         isDeleting = false;                  
    //         elapsedTime = 0.0f;              
    //         hasFinishedOnce = false;             
    //     } else {
    //         if (!animationController.steps.empty()) {
    //             if (animationController.currentStep < animationController.steps.size()) {
    //                 animationController.steps[animationController.currentStep](); 
    //             }

    //             if (!animationController.IsPaused()) {
    //                 elapsedTime += GetFrameTime(); 
    //                 if (elapsedTime >= stepDuration && !animationController.IsFinished()) {
    //                     animationController.NextStep(); 
    //                     elapsedTime = 0.0f;             
    //                     // cout << animationController.currentStep << endl; 
    //                 }
    //             }
    //         }

    //         if (animationController.IsFinished()) {
    //             DrawLL(Pos); 
    //             if (!hasFinishedOnce) {
    //                 finishedPos = Pos;    
    //                 hasFinishedOnce = true; 
    //             }
    //             if (Pos.x < NewPos.x) {
    //                 Pos = {Pos.x + 5, Pos.y}; 
    //             } else {
    //                 Pos = NewPos; 
    //             }
    //         }
    //     }
    // }

    // if (currentOperation == Operation::Update) {
    //     if (isUpdating) {
    //         animationController.Reset();         
    //         DrawUpDateNode(UpdateKey, newVal);   
    //         isUpdating = false;                  
    //         elapsedTime = 0.0f;                  
    //         hasFinishedOnce = false;             
    //     } else {
    //         if (!animationController.steps.empty()) {
    //             if (animationController.currentStep < animationController.steps.size()) {
    //                 animationController.steps[animationController.currentStep](); 
    //             }

    //             if (!animationController.IsPaused()) {
    //                 elapsedTime += GetFrameTime(); 
    //                 if (elapsedTime >= stepDuration && !animationController.IsFinished()) {
    //                     animationController.NextStep(); 
    //                     elapsedTime = 0.0f;             
    //                     // cout << animationController.currentStep << endl; 
    //                 }
    //             }
    //         }

    //         if (animationController.IsFinished()) {
    //             DrawLL(Pos); 
    //             if (!hasFinishedOnce) {
    //                 finishedPos = Pos;    
    //                 hasFinishedOnce = true; 
    //             }
    //             if (Pos.x > NewPos.x) {
    //                 Pos = {Pos.x - 5, Pos.y}; 
    //             } else {
    //                 Pos = NewPos; 
    //             }
    //         }
    //     }
    // }
}

void LinkedList::updatePseudocode(){
    switch (currentOperation){
        case Operation::Insert:
        pseudocode = {
            "if empty, head = new Node(value)",//0
            "Node* cur = head;", //1
            "while(cur && cur->next)", //2
            "   cur = cur->next", // 3
            "cur->next = new Node(value)" // 4    
        };
            break;
            default:
            break;
    }

}

// LinkedList* LinkedList::copy() const {
//     LinkedList* newList = new LinkedList(); // Tạo đối tượng mới

//     // Sao chép các thuộc tính
//     newList->Pos = this->Pos;
//     newList->NewPos = this->NewPos;
//     newList->finishedPos = this->finishedPos;
//     newList->hasFinishedOnce = this->hasFinishedOnce;
//     newList->workplace = this->workplace;
//     newList->W = this->W;
//     newList->H = this->H;
//     newList->isInserting = this->isInserting;
//     newList->lastInsertedKey = this->lastInsertedKey;
//     newList->isSearching = this->isSearching;
//     newList->SearchKey = this->SearchKey;
//     newList->isDeleting = this->isDeleting;
//     newList->DeleteKey = this->DeleteKey;
//     newList->isUpdating = this->isUpdating;
//     newList->UpdateKey = this->UpdateKey;
//     newList->newVal = this->newVal;

//     // Sao chép danh sách liên kết
//     if (!this->head) return newList; // Nếu danh sách rỗng, trả về bản sao rỗng

//     Node* current = this->head;
//     Node* newHead = new Node(current->val, nullptr); // Sao chép node đầu tiên
//     newList->head = newHead;
//     Node* newCurrent = newHead;

//     current = current->next;
//     while (current) {
//         newCurrent->next = new Node(current->val, nullptr); // Sao chép node tiếp theo
//         newCurrent = newCurrent->next;
//         current = current->next;
//     }

//     return newList;
// }

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

void LinkedList::DrawArrow(Node* start, Node* end) {
    
    // start->Pos = {start.Pos.x + radius, start->Pos.y};
    // end = {end.x - radius, end.y};
    float arrowAngle = PI/6;
    float angle = atan2f(end->Pos.y - start->Pos.y, end->Pos.x - start->Pos.x);
    Vector2 arrowHead = {end->Pos.x, end->Pos.y};

    Vector2 left = {arrowHead.x - arrow_size * cos(angle + arrowAngle), 
                    arrowHead.y - arrow_size * sin(angle + arrowAngle)};
    Vector2 right = {arrowHead.x - arrow_size * cos(angle - arrowAngle), 
                     arrowHead.y - arrow_size * sin(angle - arrowAngle)};
    Color arrow_color = MyColor1;
    DrawLineEx(start->Pos, arrowHead, 5, arrow_color);
    DrawLineEx(arrowHead, left, 3, arrow_color);
    DrawLineEx(arrowHead, right, 3, arrow_color);
}

//moi
void LinkedList::DrawNode(Node* node) {
    if (node == nullptr) return;

    string s = to_string(node->val);
    Vector2 center = node->Pos;
    int choose = node->isHighLight;

    // Vẽ vòng ngoài theo trạng thái highlight
    if (choose == 1) {
        DrawCircleV(center, radius, choose_color); // màu xanh
    } else if (choose == -1) {
        DrawCircleV(center, radius, visit_color);  // màu đỏ
    } else if (choose == 2) {
        DrawCircleV(center, radius, YELLOW);       // màu vàng (nếu cần thêm)
    } else {
        DrawCircleV(center, radius, WHITE);        // mặc định
    }

    // Vẽ vòng trong
    DrawCircleV(center, radius - 9, MyColor2);
    DrawCircleV(center, radius - 10, MyColor2);

    // Cỡ chữ tùy theo độ dài key
    int Fs = max(10, static_cast<int>(font_size - s.size() * 3));
    int wNode = MeasureText(s.c_str(), Fs);
    // Vẽ giá trị node
    DrawText(s.c_str(), center.x - wNode / 2, center.y - Fs / 2, Fs, text_color);
}


void LinkedList::DrawLL(Node* head) {
    if (!head){
        // cout << "Head is null\n";
        return;
    }
    Node * cur = head;
    int num = CountNode(head);

    Vector2 center = head->Pos;
    // cout << center.x;
    while (cur){
        
        // Vector2 newCenter = {center.x + 2 * radius + spacing, center.y};
        // if(cur->next && cur->next->next == nullptr) return;
        if (cur->next){
            DrawArrow(cur, cur->next);
        }
        DrawNode(cur);
        cur = cur->next;
        // center = newCenter;
    }
}




void LinkedList::drawStep(LLpaint a, int Found) {

    pseudocodeX = 20;
    pseudocodeY = 500;
    lineHeight = 30;
    FONT = GetFontDefault();
    
    Color highlightColor = Color{255, 222, 89, 255};
    Color textColor = MyColor4;
    
    Vector2 maxWidth = {0,0};
    if(currentOperation != Operation::Algorithm) {
        // Tìm dòng dài nhất để làm kích thước chuẩn
        
        for(const auto& line : pseudocode) {
            Vector2 lineWidth = MeasureTextEx(FONT, line.c_str(), 20, 3);
            if(lineWidth.x > maxWidth.x) maxWidth = lineWidth;
        }

        for(size_t i = 0; i < pseudocode.size(); ++i) {
            // Vẽ highlight cho toàn bộ chiều rộng
            if(a.curCode == i) {
                DrawRectangleRounded(
                    Rectangle{pseudocodeX - 10, pseudocodeY + i*lineHeight - 5, 
                             maxWidth.x + 20, lineHeight}, // Dùng maxWidth thay vì textWidth
                    0.3f, 5, highlightColor);
            }
            
            // Vẽ chữ
            DrawTextEx(FONT, pseudocode[i].c_str(), 
                      {pseudocodeX, pseudocodeY + i*lineHeight}, 
                      20, 3, textColor);
        }
    }

    if(Found == 0) {
        a.noti();
    }

    DrawLL(a.head);

}


void LinkedList::Insert(int key) {
    if (!head) {
        head = new Node(key, nullptr, headPos, 0);
        head->isHighLight = -1;
        addStep(this->head,0);  
        head->isHighLight = 0;
        return;
    }
    cout << "head not null" << endl;
    Node * a = head;
   
    a->isHighLight = -1;
    addStep(this->head,2);  
    a->isHighLight = 0;
    
    while (a && a->next) {
        a = a->next;
        cout<<"3";
        a->isHighLight = -1;
        addStep(this->head,3);  
        a->isHighLight = 0;
    }
    Vector2 curPos = a->Pos;
    Vector2 newPos = {curPos.x  + 2 * radius + spacing, curPos.y};
    cout << "before next\n";
    a->next = new Node(key, nullptr, newPos, 0);
    a = a->next;

    a->isHighLight = 2;
    addStep(this->head,4);  
    a->isHighLight = 0;
}

// bool LinkedList::DrawSearchNode(int key){
//     if (!head){
//         cout << "Head is NULL\n";
//         return false;
//     }
//     bool found = false;

//     Pos = GetPosition(CountNode(head));
//     Vector2 center = Pos;
//     //DrawLL(center);

//     Node * a = head;
//     while (a){

//         cout << "SEARCH: " << a->val << ' ' << key << '\n';

//         if(a->val == key){
//             animationController.AddStep([this, a,center]() {
//             DrawLL(Pos);
//             DrawNode(center, a->val, 1);
//             });
//             found = true;
//             //std::this_thread::sleep_for(std::chrono::milliseconds(700));
//             return true;
//         }
//         animationController.AddStep([this, a,center]() {
//         DrawLL(Pos);
//         DrawNode(center, a->val, -1);
//         });
//         a = a->next;
//         Vector2 newCenter = {center.x + 2*radius + spacing, center.y};
//         center = newCenter;
//         //std::this_thread::sleep_for(std::chrono::milliseconds((int)(500.0f / animationSpeed)));
//     }
//     if (!found) {
//         animationController.AddStep([this, a,center]() {
//         DrawLL(Pos);  
         
//         int textW = MeasureText("NOT FOUND", font_size); 
//         int listWidth = max(CountNode(head), 1) * (2 * radius + spacing); 
//         int posX = Pos.x + (listWidth - textW) / 2 - radius;
//         int posY = Pos.y + font_size + 100;  
    
//         DrawText("NOT FOUND", posX, posY, font_size, RED);
//         });
//         //EndDrawing(); 
//         //std::this_thread::sleep_for(std::chrono::milliseconds(1000));  
//     }

//     return found;
// }

// void LinkedList::DrawDeleteNode(int key) {
//     if (!head) {
//         animationController.AddStep([this]() {
//             DrawLL(this->Pos);
//             DrawText("List is empty", Pos.x, Pos.y - 50, font_size, RED);
//         });
//         return;
//     }

//     Pos = GetPosition(CountNode(head));
//     Vector2 center = Pos;

//     // Tạo bản sao

//     Node *a = head, *prev = nullptr;
//     bool found = false;

    
//     LinkedList* tmp = this->copy();
//     while (a) {
//         Vector2 currentCenter = center;
//         int val = a->val;
//         animationController.AddStep([tmp, currentCenter, val]() {
//             tmp->DrawLL(tmp);
//             tmp->DrawNode(currentCenter, val, -1);
//         });

//         if (a->val == key && !found) {
//             found = true;
//             animationController.AddStep([tmp, currentCenter, val]() {
//                 tmp->DrawLL(tmp->Pos);
//                 tmp->DrawNode(currentCenter, val, 1);
//             });
//             break;
//         }

//         prev = a;
//         a = a->next;
//         center = {center.x + 2 * radius + spacing, center.y};
//     }

//     if (found) {
//         NewPos = GetPosition(CountNode(head) - 1);
//         tmp = this->copy();
//         animationController.AddStep([this, tmp, key]() {
//             Node *a = head, *prev = nullptr;
//             while (a && a->val != key) {
//                 prev = a;
//                 a = a->next;
//             }
//             if (a) {
//                 if (prev) {
//                     prev->next = a->next;
//                 } else {
//                     head = a->next;
//                 }
//                 delete a;
//             }
//             DrawLL(Pos); // Redraw after deletion (dùng this)
//         });
//     } 

//     else {
//         animationController.AddStep([tmp]() {
//             tmp->DrawLL(tmp->Pos);
//             int textW = MeasureText("NOT FOUND", tmp->font_size);
//             int listWidth = max(tmp->CountNode(tmp->head), 1) * (2 * tmp->radius + tmp->spacing);
//             int posX = tmp->Pos.x + (listWidth - textW) / 2 - tmp->radius;
//             int posY = tmp->Pos.y + tmp->font_size + 100;
//             DrawText("NOT FOUND", posX, posY, tmp->font_size, RED);
//         });
//     }

//     delete tmp;     // Giải phóng bản sao
// }



// void LinkedList::DrawUpDateNode(int first, int second){
//     if(!head){
//         cout << "Head is empty\n";
//         return;
//     }
//     Pos = GetPosition(CountNode(head));

//     Vector2 center = Pos;
//     DrawLL(center);

//     Node * a = head;
//     while(a){
//         if(a->val == first){
//             BeginDrawing();
//             DrawNode(center, a->val, 1);
//             EndDrawing();
//             std::this_thread::sleep_for(std::chrono::milliseconds((int)(500.0f / animationSpeed)));
//             BeginDrawing();
//             DrawNode(center, second, 1);
//             EndDrawing();
//             std::this_thread::sleep_for(std::chrono::milliseconds((int)(500.0f / animationSpeed)));
//             a->val = second;
//             return;
//         }
//         BeginDrawing();
//         DrawLL(Pos);
//         DrawNode(center, a->val, -1);
//         EndDrawing();
//         a = a->next;
//         Vector2 newCenter = {center.x + 2*radius + spacing, center.y};
//         center = newCenter;
//         std::this_thread::sleep_for(std::chrono::milliseconds((int)(500.0f / animationSpeed)));
//     }
// }
