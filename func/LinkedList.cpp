
#include "LinkedList.h"

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
    head = nullptr;
    workplace = {400,300,600,600};
    headPos = {400,300};
    camera.target = headPos;
    camera.offset = headPos;
    // position = {workplace.x*1.1f, workplace.y*1.1f};
    isInserting = false;
    isSearching = false;
    isDeleting = false;
    isUpdating = false;
    isCreating = false;

    hasInsert = false;
    hasSearch = false;
    hasDelete = false;
    hasCreate = false;
    hasUpdate = false;

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
    headPos = {400,300};
    camera.target = headPos;
    camera.offset = headPos;
    isClosingCodePlace = false;
    isExpandingCodePlace = true;
    isInserting = false;
    isSearching = false;
    isDeleting = false;
    isUpdating = false;
    isCreating = false;

    hasInsert = false;
    hasSearch = false;
    hasDelete = false;
    hasCreate = false;
    hasUpdate = false;

    cur = -1;
    curCode = -1;
    lineHeight = 30;
}


void LinkedList::event() {
    musicVolume.value = volume;
    Page::event();
    //Choose Operation
   
    if(currentOperation == Operation::Create) {
        hasInsert = false;
        hasSearch = false;
        hasDelete = false;
        hasCreate = true;
        hasUpdate = false;
        cur = 0;
       BeginMode2D(camera);  
        DrawLL(this->head);   
        EndMode2D();
        steps.clear();

        addStep(this->head);
        if (textbox.nums.size() > 0) {
            //reset head
            while (head){
                Node * tmp = head;
                head = head->next;
                delete tmp;
            }
            head = nullptr;
            std::mt19937 rng(std::random_device{}());
            int num = textbox.nums[0];
             std::uniform_int_distribution<int> dist(0, 999);
             while(num--){
                createKeys.push_back(dist(rng));
             }
            
            textbox.nums.clear();
            textbox.inputText = {""};
            isCreating = true;
        }
    }
    
    if(currentOperation == Operation::Insert) {
        if(!hasInsert) {
            hasInsert = true;
            hasSearch = false;
            hasDelete = false;
            hasCreate = false;
            hasUpdate = false;
            cur = 0;
             BeginMode2D(camera);  
        DrawLL(this->head);   
        EndMode2D();
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
            hasUpdate = false;
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

    
    if(currentOperation == Operation::Update) {
        if(!hasUpdate) {
            hasInsert = false;
            hasSearch = false;
            hasDelete = false;
            hasCreate = false;
            hasUpdate = true;
            cur = 0;
            steps.clear();
            addStep(this->head);
        }
        if(textbox.nums.size() > 0) {
            UpdateKey = textbox.nums[0];
            newKey = textbox.nums[1];
    
            textbox.nums.erase(textbox.nums.begin());
            textbox.nums.erase(textbox.nums.begin());
            isUpdating = true;
            textbox.inputText = {""};
        }
    }

    if(currentOperation == Operation::Delete) {
        if(!hasDelete) {
            hasInsert = false;
            hasSearch = false;
            hasDelete = true;
            hasCreate = false;
            hasUpdate = false;
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
    

    handleUI();
    //...Lưu ý: Cần chỉnh sửa hiển thị nút play, pause cho phù hợp
}


void LinkedList::draw() {


    Page::draw();

    static float elapsedTime = 0.0f;
    const float stepDuration = 0.5f / animationSpeed;

    if(currentOperation == Operation::Create) {
        if (isCreating) {
            hasCreate = true;
            this->Create();
            
        }
        else {

       BeginMode2D(camera);  
        DrawLL(this->head);   
        EndMode2D(); 
  
            // isPlaying = false;
        }
    }
    else{
        if(hasCreate && !isCreating){
           
        BeginMode2D(camera);  
        DrawLL(this->head);   
        EndMode2D(); 
  
            // isPlaying = false;
        }
    }
    
    if (currentOperation == Operation::Insert) {
        if (isInserting) {
 
            this->Insert(lastInsertedKey);
      
            addStep(this->head);
            isInserting = false;
            isPlaying = true;
            elapsedTime = 0.0f;
            
            //rotationStartTime = GetTime();
            //isMove = false;
        } else if (!steps.empty()) {
            if (cur >= 0 && cur < steps.size()) {
                    drawStep(steps[cur]);
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
            }
        }
    }

    if (currentOperation == Operation::Update) {
        if (isUpdating) {
            Found = (this->Update(UpdateKey, newKey)) ? 1 : 0;
        
            if(!Found) {
                addStep(this->head, 6);
            }
            addStep(this->head);
            isPlaying = true;
            isUpdating = false;                 
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
    
    if (currentOperation == Operation::Delete) {
        if (isDeleting) {
            Found = (this->DeleteNode(DeleteKey)) ? 1 : 0;
            if(!Found) {
                addStep(this->head, 2);
            }
            CalculatePos(headPos);
            addStep(this->head);
            isDeleting = false;
            
            isPlaying = true;
            elapsedTime = 0.0f;
            rotationStartTime = GetTime();
            isMove = false;
        } else if (!steps.empty()) {
            if (cur >= 0 && cur < steps.size()) {
                // Xử lý animation xoay - chỉ khi đang phát (isPlaying)
                if (steps[cur].isMove && isPlaying) {
                    if (!isMove) {
                        // Bắt đầu animation xoay
                        isMove = true;
                        rotationStartTime = GetTime();
                    }
    
                    float rotationProgress = (GetTime() - rotationStartTime) / stepDuration;
                    
                    if (rotationProgress < 1.0f) {
                        // Đang trong quá trình xoay
                        LLpaint tmp;
                        tmp.copy(steps[cur].head);
                        tmp.isMove = true;
                        
                        updateLLNodePositions(tmp.head, steps[cur+1].head, rotationProgress);
                        // Xử lý riêng cho trường hợp delete
                        if (cur == steps.size()-2) {
                            drawStep(tmp, Found);
                        } else {
                            drawStep(tmp);
                            //WaitTime(1);
                        }
                    } else {
                        // Kết thúc xoay, chuyển sang bước tiếp theo
                        isMove = false;
                        cur++;
                        if (cur == steps.size()-1) {
                            drawStep(steps[cur], Found);
                        } else {
                            drawStep(steps[cur]);
                        }
                    }
                } 
                else {
                    //Vẽ bước hiện tại (không xoay hoặc không phải đang phát)
                    if (cur == steps.size()-2) {
                        drawStep(steps[cur], Found);
                    } else {
                        drawStep(steps[cur]);
                    }
                    
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
                }
            }
        }
    }


    if (currentOperation == Operation::Search) {
        
        if (isSearching) {
            Found = (this->Search(SearchKey)) ? 1 : 0;
            if(!Found) {
                addStep(this->head, 6);
            }
            addStep(this->head);
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
void LinkedList::Create(){
    if (!createKeys.empty()) {
        Insert(createKeys.front());
        createKeys.erase(createKeys.begin());
        // std::this_thread::sleep_for(std::chrono::milliseconds((int) (300 / animationSpeed)));
    }
    if (createKeys.empty()) {
        isCreating = false;
            isPlaying = true;
    }
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
        case Operation::Create:
        pseudocode ={};
        break;
        case Operation::Search:
        pseudocode = {
            "if empty, return NOT_FOUND",   //0
            "Node* cur = head",             //1
            "while (cur != nullptr)",       //2
            "   if cur->val == value",       //3
            "       return FOUND",          //4
            "   cur = cur->next",            //5
            "return NOT_FOUND",             //6
               //6
        };
        break;
        case Operation::Delete:
        pseudocode = {
            "if empty, return NOT_FOUND",           //0
            "Node* cur = head, * prev = nullptr",   //1
            "while cur is not null",                //2
            "   if(cur->val == key)",                   //3
            "       prev->next = cur->next",            //4
            "       delete cur",                        //5
            "   else prev = cur, cur = cur->next",       //6                   //4
            "   return NOT_FOUND",    //6
        };
            default:
            break;
    }

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

void LinkedList::CalculatePos(Vector2 PosHead) {
    if(!head) return; 
    head->Pos = PosHead;

    Node* pre = head;
    Node* a = head->next; 
    while(a) {
        Vector2 curPos = pre->Pos;
        a->Pos = {curPos.x  + 2 * radius + spacing, curPos.y};
        pre = a;
        a = a->next;
    }

}

Node* LinkedList::findNode(Node* ahead, int key) {
    if(!head) return nullptr;
    Node * a = head;
    while(a) {
        if(a->val ==key) {
            return a;
        }
        a = a->next;
    }
    return nullptr;
}

void LinkedList::updateLLNodePositions(Node* &a, Node* b, float &tmp) {
    if (!a || !b) return;

    Node* acur = a;
    while (acur) {
        Node* targetNode = findNode(b, acur->val);

        if (targetNode) {
            acur->Pos.x = acur->Pos.x + tmp * (targetNode->Pos.x - acur->Pos.x);
        }

        acur = acur->next;
    }

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
    DrawLineEx(start, arrowHead, radius / 10, arrow_color);
    DrawLineEx(arrowHead, left, radius / 10, arrow_color);
    DrawLineEx(arrowHead, right, radius / 10, arrow_color);
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

    DrawCircleV(center, radius * 0.82f, MyColor2);
    DrawCircleV(center, radius * 0.8f, MyColor2);

    // Cỡ chữ tùy theo độ dài key
    int Fs = max(10, static_cast<int>(font_size - s.size() * 3));
    int wNode = MeasureTextEx(FONT,s.c_str(), Fs, 2).x;
    // Vẽ giá trị node
    DrawTextEx(FONT, s.c_str(), {center.x - wNode / 2, center.y - Fs / 2}, Fs, 2, text_color);
}


void LinkedList::DrawLL(Node* head) {
    if (!head){

        return;
    }
    Node * cur = head;
    int num = CountNode(head);

    Vector2 center = head->Pos;

    while (cur){
        
        // Vector2 newCenter = {center.x + 2 * radius + spacing, center.y};
        // if(cur->next && cur->next->next == nullptr) return;
        if (cur->next){
            DrawArrow(cur->Pos, cur->next->Pos);
        }
        DrawNode(cur);
        cur = cur->next;
        // center = newCenter;
    }
}




void LinkedList::drawStep(LLpaint a, int Found) {

 
    lineHeight = 30;

    
    Color highlightColor = Color{255, 222, 89, 255};
    Color textColor = MyColor4;
    
    Vector2 maxWidth = {0,0};
    if(currentOperation != Operation::Algorithm) {
        // Tìm dòng dài nhất để làm kích thước chuẩn
        
        for(const auto& line : pseudocode) {
            Vector2 lineWidth = MeasureTextEx(FONT, line.c_str(), 20, 3);
            if(lineWidth.x > maxWidth.x) maxWidth = lineWidth;
        }
        textWidth = maxWidth.x;
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

    BeginMode2D(camera);  
        DrawLL(a.head);   
        EndMode2D();

}

void LinkedList::updatePos(){
    if(!head) return;

    Vector2 curPos = head->Pos;
    Vector2 newPos = {curPos.x  + 2 * radius + spacing, curPos.y};
    Node* cur = head->next;
    while(cur){
        cur->Pos = newPos;
        curPos = cur->Pos;
        newPos = {curPos.x  + 2 * radius + spacing, curPos.y};
        cur = cur->next;
    }
}

void LinkedList::Insert(int key) {
    if (!head) {
        head = new Node(key, nullptr, headPos, 0);
        head->isHighLight = -1;
        addStep(this->head,0);  
        head->isHighLight = 0;
        return;
    }

    Node * a = head;
   
    a->isHighLight = -1;
    addStep(this->head,1);  
    a->isHighLight = 0;
    
    while (a && a->next) {
        addStep(this->head, 2);
        a = a->next;

        a->isHighLight = -1;
        addStep(this->head,3);  
        a->isHighLight = 0;
    }
    Vector2 curPos = a->Pos;
    Vector2 newPos = {curPos.x  + 2 * radius + spacing, curPos.y};
    a->next = new Node(key, nullptr, newPos, 0);
    a = a->next;

    a->isHighLight = 2;
    addStep(this->head,4);  
    a->isHighLight = 0;
}



bool LinkedList::Search(int key) {
    if(!head) {
        addStep(this->head,0);  
        return false;
    }

    Node* a = head;
    a->isHighLight = -1;
    addStep(this->head,1);  
    a->isHighLight = 0;
    a = a->next;
    while(a) {
        addStep(this->head,2); 
        if(a->val == key) {
            addStep(this->head, 3);
            a->isHighLight = 1;
            addStep(this->head,4);  
            a->isHighLight = 0;
            return true;
        }

        a->isHighLight = -1;
        addStep(this->head,5);  
        a->isHighLight = 0;

        a = a->next;
    }
    addStep(this->head, 6);
    return false;
}

bool LinkedList::Update(int oldKey, int newKey) {
    if(!head) {
        return false;
    }

    Node* a = head;
    while(a) {
        addStep(this->head); 
        if(a->val == oldKey) {
            
            a->isHighLight = 1;
            addStep(this->head);  
            a->isHighLight = 0;

            a->val = newKey;
            a->isHighLight = 1;
            addStep(this->head);  
            a->isHighLight = 0;
            return true;
        }

        a->isHighLight = -1;
        addStep(this->head);  
        a->isHighLight = 0;

        a = a->next;
    }
    addStep(this->head);
    return false;
}

bool LinkedList::DeleteNode(int key) {
    if(!head) {
        addStep(this->head, 0);
        return false;
    }

    Node* pre = nullptr;
    Node* a = head;
    
    // a->isHighLight = -1;
    // addStep(this->head,1);  
    // a->isHighLight = 0;

    while(a) {
        addStep(this->head,2); 
        if(a->val == key) {
            if(a == head) {
                
                a->isHighLight = 1;
                addStep(this->head,3);  
                a->isHighLight = 0;
                
                Node* tmp = this->head;
                this->head = head->next;

                delete tmp; 

                addStep(this->head,5,1);  
                return true;
                
            }
            
            a->isHighLight = 1;
            addStep(this->head,3);  
            a->isHighLight = 0;

            pre->next = a->next;
            addStep(this->head,4); 
            delete a;
            a = nullptr;                  
            
            addStep(this->head,5,1);  

            return true;

        }

        a->isHighLight = -1;
        addStep(this->head,6);  
        a->isHighLight = 0;

        pre = a;
        a = a->next;
        
    }
    addStep(this->head,7); 
    return false;
}

void LinkedList::handleUI(){
    updatePos();
        static Operation lastOp = Operation::Algorithm;
    if(currentOperation != lastOp) {
        updatePseudocode();
        lastOp = currentOperation;
    }
    //RUN AT ONCE
    if(forward1.IsClicked() || forward2.IsClicked()){
        cur = steps.size() - 1;
        isPlaying = false;
    }
    if(backward1.IsClicked() || backward2.IsClicked()){
         cur = 0;
         isPlaying = false;
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

void LinkedList::RANDOM_INPUT(){
     std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(2, 8);
    if(currentOperation == Operation::Create){
        textbox.inputText = {to_string(dist(rng))};
    }
    else{
        Page::RANDOM_INPUT();
    }
}
