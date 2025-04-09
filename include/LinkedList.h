#pragma once
#include <string>
#include <math.h>
#include <iostream>
using namespace std;
#include <raylib.h>
#include "Variables.h"
#include "Page.h"
#include "ControlAnimation.h"
#include <random>
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

        bool isCreating;
        int numbers;
    
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
        void DrawCreateNode(int n);

        void event() override;
        void init() override;
        void draw() override;
        
        int RandInt(int left, int right);
        void Create(int n);
        void InsertLL(int key);
    };