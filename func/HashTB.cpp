#include "HashTB.h"
#include <raylib.h>
#include <cmath>
#include <thread>
#include <chrono>
#include <iostream>
#include <random>
#include <sstream>
#include "DrawUtils.h"
#include "Program.h"
using namespace std;

void HashTB::init(){
    Page::init();
    origin = { 350, 100 };
    heads.resize(tableSize, nullptr);
    

  
    // nullptr
    for(int i=0; i< tableSize; i++){
        if(!heads[i]) heads[i] = new LinkedList();
        heads[i]->headPos = {origin.x , origin.y+ (spacing+radius)*i};
        heads[i]->head = new Node(i, nullptr, heads[i]->headPos, 0);
    }

  
    // isInserting = false;
    // lastInsertedKey = -1;
    // isCreating = false;
    // isDuplicateInsert = false;

    isInserting = false;
    isSearching = false;
    isDeleting = false;
    isCreating = false;

    hasInsert = false;
    hasSearch = false;
    hasDelete = false;
    hasCreate = false;

    cur = -1;
    curCode = -1;
    pseudocode = {};
}


HashTB::HashTB(int size) {
    tableSize = size;
    heads.resize(size, nullptr);
    isInserting = false;
    lastInsertedKey = -1;
    isCreating = false;
    isDuplicateInsert = false;
}

HashTB::~HashTB() {
    for (int i = 0; i < tableSize; ++i) {
        Node* current = heads[i]->head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

int HashTB::HashFunction(int key) {
    return key % tableSize;
}

void HashTB::updateVariables(vector<LinkedList*>& a){
    for(auto& elem: a){
        if(elem){
        elem->radius = radius;
        elem->spacing = 30;
        elem->font_size = font_size;
        elem->arrow_size = arrow_size;
        }
    }
}

bool HashTB::Search(int key) {
    int index = HashFunction(key);
    
    Node* &head = heads[index]->head->next;

    if(!head) {
        addStepH(this->heads,0);  
        return false;
    }

    Node* a = head;

    a->isHighLight = -1;
    addStepH(this->heads,1);  
    a->isHighLight = 0;
    
    while(a) {
        addStepH(this->heads,2); 
        if(a->val == key) {
            addStepH(this->heads, 3);
            a->isHighLight = 1;
            addStepH(this->heads,4);  
            a->isHighLight = 0;
            return true;
        }

        a->isHighLight = -1;
        addStepH(this->heads,5);  
        a->isHighLight = 0;

        a = a->next;
    }
    addStepH(this->heads, 6);
    return false;


}

void HashTB::Insert(int key) {
    int index = HashFunction(key);
    
    Node* cur = heads[index]->head->next;

    while (cur) {
        if (cur->val == key) {
            return;
        }
        cur = cur->next;
    }

    // heads[index]->Insert(key);
    // Đã có pos chưa

    Node* &head = heads[index]->head;
    

    if (!head) {
        head = new Node(key, nullptr, heads[index]->headPos , 0);
        head->isHighLight = -1;
        addStepH(this->heads,0); //hastB head, heads[i] ->head->ishigh ??
        head->isHighLight = 0;
        return;
    }

    Node * a = head;
   
    a->isHighLight = -1;
    addStepH(this->heads,1);  
    a->isHighLight = 0;
    
    while (a && a->next) {
        addStepH(this->heads, 2);
        a = a->next;
        cout<<"3";
        a->isHighLight = -1;
        addStepH(this->heads,3);  
        a->isHighLight = 0;
    }
    Vector2 curPos = a->Pos;
    Vector2 newPos = {curPos.x  + 2 * radius + spacing, curPos.y};
    a->next = new Node(key, nullptr, newPos, 0);
    a = a->next;

    a->isHighLight = 2;
    addStepH(this->heads,4);  
    a->isHighLight = 0;


    isInserting = true;
    lastInsertedKey = key;
}



void HashTB::DrawHashTB(vector<LinkedList*>& heads) {
    for(auto& x : heads){
        x->DrawLL(x->head);
    }
}


void HashTB::drawStep(HashTBpaint& a, int Found) {

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
    DrawRectangle(600,600,400,400, RED);
    if(Found == 0) {
        a.noti();
    }
    DrawHashTB(a.heads);

}


void HashTB::draw() {
    Page::draw();


    static float elapsedTime = 0.0f;
    const float stepDuration = 0.5f / animationSpeed;

    // if(IsKeyPressed(KEY_A)) {
    //     Vector2 k = GetMousePosition();
    //     auto t = head->Pos;
    //     head->Pos = k;
    //     DrawLL(head);
    //     head->Pos = t;
    // }

    if(currentOperation == Operation::Create) {
        if (isCreating) {
            hasCreate = true;
            this->Create();
            isCreating = false;
            isPlaying = true;
        }
        else {
            DrawHashTB(this->heads);
            isPlaying = false;
        }
    }

    if (currentOperation == Operation::Insert) {
        if (isInserting) {
            cout<<"Insert";
            this->Insert(lastInsertedKey);
      
            addStepH(this->heads);
            isInserting = false;
            isPlaying = true;
            elapsedTime = 0.0f;
            
            //rotationStartTime = GetTime();
            //isMove = false;
        } else if (!steps.empty()) {
            if (cur >= 0 && cur < steps.size()) {
                // Xử lý animation xoay - chỉ khi đang phát (isPlaying)
                // if (steps[cur].isMove && isPlaying) {
                //     if (!isMove) {
                //         // Bắt đầu animation xoay
                //         isMove = true;
                //         rotationStartTime = GetTime();
                //     }
    
                //     float rotationProgress = (GetTime() - rotationStartTime) / stepDuration;
                    
                //     if (rotationProgress < 1.0f) {
                //         // Đang trong quá trình xoay
                //         AVLpaint tmp;
                //         tmp.copy(steps[cur].heads);
                //         tmp.isMove = true;
                        
                //         updateNodePositions(tmp.heads, steps[cur+1].heads, rotationProgress);
                        
                //         drawStep(tmp);
                //     } else {
                //         // Kết thúc xoay, chuyển sang bước tiếp theo
                //         isMove = false;
                //         cur++;
                //         drawStep(steps[cur]);
                //     }
                // } 

                // else {
                    // Vẽ bước hiện tại (không xoay hoặc không phải đang phát)
                    
                    drawStep(steps[cur]);
                    //cout<<"@";
                    
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

    
    // if (currentOperation == Operation::Delete) {
    //     if (isDeleting) {
    //         Found = (this->DeleteNode(DeleteKey)) ? 1 : 0;
    //         if(!Found) {
    //             addStepH(this->heads, 2);
    //         }
    //         CalculatePos(headsPos);
    //         addStepH(this->heads);
    //         isDeleting = false;
            
    //         isPlaying = true;
    //         elapsedTime = 0.0f;
    //         rotationStartTime = GetTime();
    //         isMove = false;
    //     } else if (!steps.empty()) {
    //         if (cur >= 0 && cur < steps.size()) {
    //             // Xử lý animation xoay - chỉ khi đang phát (isPlaying)
    //             if (steps[cur].isMove && isPlaying) {
    //                 //cout<<steps[cur].heads->val<<" ";
    //                 if (!isMove) {
    //                     // Bắt đầu animation xoay
    //                     isMove = true;
    //                     rotationStartTime = GetTime();
    //                 }
    
    //                 float rotationProgress = (GetTime() - rotationStartTime) / stepDuration;
                    
    //                 if (rotationProgress < 1.0f) {
    //                     // Đang trong quá trình xoay
    //                     LLpaint tmp;
    //                     tmp.copy(steps[cur].heads);
    //                     tmp.isMove = true;
                        
    //                     updateLLNodePositions(tmp.heads, steps[cur+1].head, rotationProgress);
    //                     //cout<<endl<<"why";
    //                     // Xử lý riêng cho trường hợp delete
    //                     if (cur == steps.size()-2) {
    //                         drawStep(tmp, Found);
    //                     } else {
    //                         drawStep(tmp);
    //                         //WaitTime(1);
    //                     }
    //                 } else {
    //                     // Kết thúc xoay, chuyển sang bước tiếp theo
    //                     isMove = false;
    //                     cur++;
    //                     if (cur == steps.size()-1) {
    //                         drawStep(steps[cur], Found);
    //                     } else {
    //                         drawStep(steps[cur]);
    //                     }
    //                 }
    //             } 
    //             else {
    //                 //Vẽ bước hiện tại (không xoay hoặc không phải đang phát)
    //                 if (cur == steps.size()-2) {
    //                     drawStep(steps[cur], Found);
    //                 } else {
    //                     drawStep(steps[cur]);
    //                 }
                    
    //                 // Tự động chuyển bước nếu đang phát
    //                 if (isPlaying) {
    //                     elapsedTime += GetFrameTime();
    //                     if (elapsedTime >= stepDuration) {
    //                         if (cur < steps.size() - 1) {
    //                             cur++;
    //                             elapsedTime = 0.0f;
    //                         } else {
    //                             isPlaying = false;
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }


    if (currentOperation == Operation::Search) {
        
        if (isSearching) {
            Found = (this->Search(SearchKey)) ? 1 : 0;
            if(!Found) {
                addStepH(this->heads, 6);
            }
            addStepH(this->heads);
            isPlaying = true;
            isSearching = false;                 
            elapsedTime = 0.0f;      
            
        } else {
        
                if (!steps.empty()) {
                    if(cur >= 0 && cur< steps.size()) {
                        
                        if(cur == steps.size()-2) {
                            drawStep(steps[cur], Found);
                        }
                        else 
                            drawStep(steps[cur]);
                    }

    
                    if (isPlaying) {
                        elapsedTime += GetFrameTime();
                        if (elapsedTime >= stepDuration) {
                            if (cur < steps.size() ) {
                                cur++;
                                elapsedTime = 0.0f;
                            }
                        }
                    }
                    
                    if(cur == steps.size() && cur!=0) {  
                        drawStep(steps[cur-1]);         
                        isPlaying = false;
                    }
                }
        }
    }

}

// void HashTB::draw() {
//     Page::draw();
  
//     DrawHashTable();
//     DrawSearchEffect();
//     DrawInsertEffect();
//     DrawDeleteEffect();
//     // for(auto& a: heads){
//     //     a->draw();
//     // }
//     head.Draw(MyColor2, getMODE());
//     switchState ? home2.Draw() : home.Draw();
//     if (isCreating && !createKeys.empty()) {
//         Insert(createKeys.front());
//         createKeys.erase(createKeys.begin());

//     }
//     if (createKeys.empty()) isCreating = false;
// }



void HashTB::event() {
    Page::event();
    
    //Choose Operation
   bucket = {
        origin.x ,
        origin.y + 50,
        (float)bucket_width,
        (float)spacing * (tableSize)
    };

    
    if(currentOperation == Operation::Create) {
        
    }
    
    if(currentOperation == Operation::Insert) {
        if(!hasInsert) {
            hasInsert = true;
            hasSearch = false;
            hasDelete = false;
            hasCreate = false;
            cur = 0;
            DrawHashTB(heads);
            steps.clear();
            addStepH(this->heads);
    
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
            addStepH(this->heads);
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
            addStepH(this->heads);
        }
        if(textbox.nums.size() > 0) {
            DeleteKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isDeleting = true;
            textbox.inputText = {""};
        }
    }

    handleUI();
    //auto create taking numbers from textbox
     if (isCreating && !createKeys.empty()) {
        Insert(createKeys.front());
        createKeys.erase(createKeys.begin());
        // std::this_thread::sleep_for(std::chrono::milliseconds((int) (300 / animationSpeed)));
    }
    if (createKeys.empty()) isCreating = false;
    //...Lưu ý: Cần chỉnh sửa hiển thị nút play, pause cho phù hợp
}


void HashTB::handleUI(){
    //updatePos();
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
}


// void HashTB::event() {
//     Page::event();

//     updateVariables();  
//     // for e->event();
//     if (currentOperation == Operation:: Insert) {
//         if (textbox.nums.size() > 0) {
//             cout << "mimi\n";
//             lastInsertedKey = textbox.nums[0];
//             textbox.nums.erase(textbox.nums.begin());
//             textbox.inputText = {""};
//             Insert(lastInsertedKey);
//             cout << "mama\n";
//         }
//     }

//     if (currentOperation == Operation:: Search) {
//         if (textbox.nums.size() > 0) {
//             SearchKey = textbox.nums[0];
//             textbox.nums.erase(textbox.nums.begin());
//             textbox.inputText = {""};
//             isSearching = true;
//         }
//     }
//     if (currentOperation == Operation:: Delete) {
//         if (textbox.nums.size() > 0) {
//             DeleteKey = textbox.nums[0];
//             textbox.nums.erase(textbox.nums.begin());
//             textbox.inputText = {""};
//             isDeleting = true;
//         }
//     }
//     if (currentOperation == Operation:: Create) {
         
        
//     }    
//        for (int i = 0; i < heads.size(); ++i) {
//     if (heads[i]) {
       
//         heads[i]->handleUI();
//     } else {
//         cout << "null at index " << i << "\n";
//     }
//     }
// }

void HashTB::updatePseudocode() {
    switch(currentOperation) {
        case Operation::Insert:
            pseudocode = {
                "index = key%HT.length;",
                "cur = table[index]",
                "if empty, cur = new Node(key)"
                "while cur && cur->next is not null",
                "   cur = cur->next",
                "cur->next = new Node(key)"
            };
            break;
        case Operation::Delete:
            pseudocode = {
                "index = key%HT.length;",
                "cur = table[index], prev = null",
                "while cur not null & cur->value != key",
                "  prev = cur, cur = cur->next"
                "if cur is null",
                "  return NOT_FOUND",
                "prev->next = cur->next, delete cur",
            };
            break;
        case Operation::Search:
            pseudocode = {
                "index = key%HT.length",
                "cur = table[index]",
                "while cur && cur->val != key",
                "   cur = cur->next",
                "if cur is null",
                "   return NOT_FOUND",
                "return FOUND"
            };
            break;
        default:
            // pseudocode = {};
            break;
    }
}


void HashTB::reset(){
    Page::reset();
    origin = { 350, 100 };
    tableSize = 3;
    heads.clear();
    heads.resize(tableSize, nullptr);
     isInserting = false;
     lastInsertedKey = -1;

     isSearching = false;
     SearchKey = -1;
     searchFound = false; 

     isDeleting = false;
     DeleteKey = -1;
     isDuplicateInsert = false;
     createKeys.clear();
}

void HashTB::RANDOM_INPUT(){
    std::mt19937 rng(std::random_device{}());
    
    if(currentOperation == Operation::Create){
            textbox.reset();
            std::uniform_int_distribution<int> bucket(2, 25); 
            int numBucket = bucket(rng);
            std::uniform_int_distribution<int> value(0, 1999);
            std::uniform_int_distribution<int> valueSize(0, 30);
            int size = valueSize(rng);
            std::vector<int> Values;
            std::vector<std::string> lines;
            std::ostringstream ss;

            for (int i = 0; i < size; ++i) {
                int num = value(rng);
        
                while (find(Values.begin(), Values.end(), num) != Values.end()) {
                    num = value(rng);
                }
                Values.push_back(num);  
            }

         
            ss << numBucket;
            lines.push_back(ss.str());
            ss.str("");  

          
            for (int i = 0; i < Values.size(); ++i) {
                ss << Values[i] << " ";
            }
            lines.push_back(ss.str());
            ss.str("");  
            
            textbox.inputText = lines;
            
    }
    else{
        Page::RANDOM_INPUT();
    }
}

void HashTB::Create(){
    if(textbox.nums.size() > 0){
                heads.clear();
                tableSize = textbox.nums[0]; 
                heads.resize(tableSize, nullptr);
                for(int i=0; i< tableSize; i++){
                    if(!heads[i]) heads[i] = new LinkedList();
                    heads[i]->headPos = {origin.x , origin.y+ (spacing+radius)*i};
                    heads[i]->head = new Node(i, nullptr, heads[i]->headPos, 0);
                }

                textbox.nums.erase(textbox.nums.begin());
                textbox.inputText = {""};
            }
        if (textbox.nums.size() > 0) {
        
            createKeys = textbox.nums;
            textbox.nums.clear();
            textbox.inputText = {""};
            isCreating = true;
        }
}