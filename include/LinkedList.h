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

struct Node{
    int val;
    Node * next;
    Node(int key, Node * nextNode){
        val = key;
        next = nextNode;
    };
};



class LinkedList : public Page{
    public:
        Node* head;
        Rectangle workplace;


        //public variable for linked-list
        const int radius = 30;
        const int font_size = 30;
        const int spacing = 30;
        const Color choose_color = { 0, 128, 0, 128 };//green
        const Color visit_color = RED;//red
        const Color ring = MyColor2;
        const Color circle = MyColor2;
        const Color text_color = WHITE;
        const float arrow_size = 15.0;
        const Color arrow_color = MyColor1;

        int W = 600;
        int H = 600;
        
        // Biến kiểm soát hiệu ứng chèn
        ControlAnimation animationController;
        bool isInserting;
        int lastInsertedKey;

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
        
        LinkedList* copy() const;
        //animation
        Vector2 GetPosition(int count);
        Vector2 Pos = {400,300}, NewPos, finishedPos;
        bool hasFinishedOnce = false;
        int CountNode(Node* head);
        void DrawArrow(Vector2 start, Vector2 end);
        void DrawNode(Vector2 center, int key, int choose);
        void DrawLL(Vector2 pos, bool last = true);
        void DrawInsert(int key);
        bool DrawSearchNode(int key);
        void DrawDeleteNode(int key);
        void DrawUpDateNode(int first, int second);

        void event() override;
        void init() override;
        void draw() override;

        //test show code
        static const char* INSERT_CODE[];
        static const char* DELETE_CODE[];
        static const char* SEARCH_CODE[];
        void DrawHighlightedCode(const char* code[], int start, int end);

    };