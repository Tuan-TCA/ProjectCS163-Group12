#include <AllLibrary.h>

void insertNode(LinkedListNode* &head, int key) {
    if (!head) {
        head = new LinkedListNode;
        head->val = key;
        head->next = nullptr;
        return;
    }
    LinkedListNode * a = head;
    while (a->next) a = a->next;
    LinkedListNode * tmp = new LinkedListNode;
    tmp->val = key;
    tmp->next = nullptr;
    a->next = tmp;
}

void deleteNode(LinkedListNode* &head, int key){
    if(!head) return;
    if(head->val == key){
        LinkedListNode* tmp = head;
        head = head->next;
        delete tmp;
        return;
    }
    else{
        LinkedListNode* tmp = head;
        while(tmp && tmp->next && tmp->next->val != key){
            tmp = tmp->next;
        }
        if(!tmp->next) return;
        else{
            tmp->next = tmp->next->next;
        }
    }
}

LinkedListNode *search(LinkedListNode* head, int key){
    if(!head) return nullptr;
    if(head->val == key) return head;
    return search(head->next, key);
}


void update(LinkedListNode *&head, int first, int second){
    LinkedListNode* tmp = search(head, first);
    tmp->val = second;
    return;
}

