#pragma once
#include <string>
#include <math.h>
#include <iostream>
using namespace std;
#include <raylib.h>
#include "Variables.h"
#include "Page.h"
#include "ControlAnimation.h"
// class Node {
// public:
//     int val;
//     Node* next;
//     Node(int key, Node* nextnode);
// };
class Node {
public:
    int val;
    Node* next;
    
    // 1=green, -1=red, 0=White, 2=Yellow
    int isHighLight = 0;
    Vector2 Pos;
    Vector2 targetPos;

    // Constructor đầy đủ thông tin
    Node(int key, Node* nextNode, Vector2 pos,int isHigh = 0) {
        val = key;
        next = nextNode;
        Pos = pos;
        isHighLight = isHigh;
        targetPos = {0, 0};
    }

    // Constructor đơn giản
    Node(int key) {
        val = key;
        next = nullptr;
        Pos = {600, 600};
        isHighLight = 0;
        targetPos = {0, 0};
    }

    void absorb(Node* tmp) {
        if (!tmp) return;
        this->val = tmp->val;
        tmp->Pos = this->Pos;
    }
};


class LLpaint {
public:
    Node* head;
    Rectangle workplace = { screenWidth * 0.24f, screenHeight * 0.2f, (float)screenWidth * (1 - 0.24f), screenHeight * (1 - 0.095f) };
    Vector2 headPos = { 600, 600 };

    // public constants for linked-list visualization
    const int radius = 50;
    const int font_size = 40;
    const int spacing = 50;
    const Color choose_color = { 0, 128, 0, 128 }; // green
    const Color visit_color = RED; // red
    const Color ring = MyColor2;
    const Color circle = MyColor2;
    const Color text_color = WHITE;
    const float arrow_size = 15.0;
    const Color arrow_color = MyColor1;

    int curCode = -1; // current pseudocode line
    int posX = 800;
    int posY = 800;
    int textW = MeasureText("NOT FOUND", font_size * 2);
    bool isMove = 0;

    LLpaint() {
        head = nullptr;
        headPos = { 600, 600 };
    }

    void noti() {
        DrawText("NOT FOUND", posX, posY, font_size * 2, RED);
    }

    // Copy linked list (deep copy)
    Node* copyLL(Node* node) {
        if (!node) return nullptr;
        Node* newHead = new Node(node->val, nullptr, node->Pos, node->isHighLight);
        Node* curNew = newHead;
        Node* curOld = node->next;
        while (curOld) {
            curNew->next = new Node(curOld->val, nullptr, curOld->Pos, curOld->isHighLight);
            curNew = curNew->next;
            curOld = curOld->next;
        }
        return newHead;
    }

    void copy(Node* a) {
        this->head = copyLL(a);
    }

    // Tìm node theo giá trị
    Node* findNodeByValue(Node* node, int value) {
        while (node) {
            if (node->val == value) return node;
            node = node->next;
        }
        return nullptr;
    }

};
    

class LinkedList : public Page{
public:
    Node* head;
    Rectangle workplace;
    Vector2 headPos;

    //public variable for linked-list
     int radius = 50;
     int font_size = 40;
     int spacing = 50;
     Color choose_color = { 0, 128, 0, 128 };//green
     Color visit_color = RED;//red
     Color ring = MyColor2;
     Color circle = MyColor2;
     Color text_color = WHITE;
     float arrow_size = 15.0;
     Color arrow_color = MyColor1;

    int W = 600;
    int H = 600;
    
    // Biến kiểm soát hiệu ứng chèn
    ControlAnimation animationController;
    bool isInserting;
    int lastInsertedKey;

    bool isCreating;
    vector<int> createKeys;
    
    bool isSearching;
    int SearchKey;

    bool isDeleting;
    int DeleteKey;

    bool isUpdating;
    int UpdateKey;
    int newVal;

    LinkedList();

    ~LinkedList() {
        Node* current = head;
        head = nullptr;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    int Found = -1;
    int cur = -1;
    int curCode = -1;
    Node* findNode(Node* ahead, int key);
    void updateLLNodePositions(Node* &a, Node* b, float &tmp);
    LinkedList* copy() const;
    //animation
    vector<LLpaint> steps;
    Vector2 GetPosition(int count);
    Vector2 Pos = {400,300}, NewPos, finishedPos;
    bool hasFinishedOnce = false;
    void addStep(Node*  head, int curCode = -1, bool isMove = 0) {
        LLpaint tmp; 
        tmp.copy(head);
        tmp.curCode = curCode;
        tmp.isMove = isMove;
        steps.push_back(tmp);
    }
    float rotationStartTime = 0;
    void drawStep(LLpaint a, int Found = -1);
    
    int CountNode(Node* head); //ok
    void DrawArrow(Node* start, Node* end); //ok
    void DrawNode(Node * node); // ok
    void DrawLL(Node* head); // ok

    bool isMove;

    void Insert(int key);
    bool Search(int key);
    bool DeleteNode(int key);
    void Create();
    
    //void DrawUpDateNode(int first, int second);
    void updatePseudocode();
    void CalculatePos(Vector2 PosHead);
    void handleUI();
    void updatePos();
    void drawAnimation();
    bool hasInsert;
    bool hasSearch;
    bool hasDelete;
    bool hasCreate;
    
    
    void event() override;
    void init() override;
    void draw() override;
    void reset() override;
    void RANDOM_INPUT() override;
};