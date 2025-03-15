#include <LinkedList.h>

void insertNode(LinkedListNode* &head, int key) {
    if (!head) {
        head = new LinkedListNode;
        head->val = key;
        head->next = nullptr;
        return;
    }
    
    Vector2 center = GetPosition(head);
    Vector2 newCenter;
    
    LinkedListNode* a = head;
    // Vẽ cái tô màu đỏ
    while (a->next){
        BeginDrawing();
        Choose(center, {255, 100, 100, 150}, {255, 150, 150, 100}, head);
        EndDrawing();
        WaitTime(0.3);
        a = a->next;
        newCenter = {center.x + spacing + 2*r, center.y};
        center = newCenter;
    }

    BeginDrawing();
    Choose(center, {255, 100, 100, 150}, {255, 150, 150, 100}, head);
    EndDrawing();
    newCenter = {center.x + spacing + 2*r, center.y};
    WaitTime(0.5);
    LinkedListNode * tmp = new LinkedListNode;
    
    //VỊ TRÍ NODE MỚI XUẤT HIỆN
    Vector2 centerNewNode = {100, 100};

    BeginDrawing();
    string s = to_string(key); 
    DrawNewNode(centerNewNode, s, {255, 255, 150, 150}, {255, 255, 180, 80}, head);
    EndDrawing();

    WaitTime(0.1);
    
    // Chèn node mới vào danh sách
    
    Vector2 finalPos = newCenter;  // Vị trí cuối trong danh sách
    
    // Di chuyển node vào hàng
    BeginDrawing();
    AcceptNode(centerNewNode, finalPos, s, head);
    DrawArrow({center.x + r + 10, center.y}, {newCenter.x - r - 10, newCenter.y}, 15, BLACK);
    EndDrawing();
    
    Vector2 prev = GetPosition(head);

    tmp->val = key;
    tmp->next = nullptr;
    a->next = tmp;

    Vector2 cur = GetPosition(head);
    /*
    idea cho node di chuyển tính vị trí node ban đầu hiện tại
    đưa nó vào while đến khi vị trí ban đầu thành cân bằng thì thôi
    */
    BeginDrawing();
    MoveLinkedList(head, prev, cur);
    EndDrawing();
}

void updatePosition(LinkedListNode * head){
    Vector2 cur = GetPosition(head), next;

    while(head){
        head->x = cur.x;
        head->y = cur.y;
        next = {cur.x + 2 * r + spacing, cur.y};
        cur = next;
        head = head->next;
    }
}


void deleteNode(LinkedListNode* &head, int key){
    if(!head) return;
    // if(head->val == key){
    //     LinkedListNode* tmp = head;
    //     head = head->next;
    //     delete tmp;
    //     return;
    // }
    // else{
    //     LinkedListNode* tmp = head;
    //     while(tmp && tmp->next && tmp->next->val != key){
    //         tmp = tmp->next;
    //     }
    //     if(!tmp->next) return;
    //     else{
    //         tmp->next = tmp->next->next;
    //     }
    // }

    traverseDelete(head, key);

}

LinkedListNode *search(LinkedListNode* head, int key){
    if(!head) return nullptr;
    
    traverseSearch(head, key);
    // if(head->val == key) return head;
    // return search(head->next, key);
    return nullptr;
}


void update(LinkedListNode *&head, int &first, int second){
    LinkedListNode* tmp = search(head, first);
    if(!tmp) cout << "Not found!";
    tmp->val = second;
    return;
}

// function test update
void update1(LinkedListNode *head, int nums[], int key, int id){
    LinkedListNode *tmp = head;
    int count = 0;

    while(tmp && count < id) {
        tmp = tmp->next;
        count++;
    }

    if (tmp) {
        tmp->val = key;
        nums[id] = key; 
    }
}


