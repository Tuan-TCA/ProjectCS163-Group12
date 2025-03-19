#pragma once
#include <string>
#include <math.h>
#include <iostream>
using namespace std;
#include <raylib.h>
#include "Variables.h"
#include "Page.h"
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
        const int radius = 50;
        const int font_size = 40;
        const int spacing = 50;
        const Color choose_color = GREEN;
        const Color visit_color = RED;
        const Color ring = BLACK;
        const Color circle = LIGHTGRAY;
        const Color text_color = BLACK;
        const float arrow_size = 15.0;
        const Color arrow_color = BLACK;

        int W = 600;
        int H = 600;
        
        // Biến kiểm soát hiệu ứng chèn
        bool isInserting;
        int lastInsertedKey;
    
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
    
        void DrawLL();
        void DrawInsert(int key);
        void SearchNode(int key);
        
        void PrintLL();

        //animation
        Vector2 GetPosition(int count);
        int CountNode(Node* head);
        void DrawArrow(Vector2 start, Vector2 end);
        void DrawNode(Vector2 center, int key, int choose);

        void EventLLinPage(Page &page) {
            if(page.textbox.nums.size() > 0) {
                lastInsertedKey = page.textbox.nums[0];
                isInserting = true;  // Kích hoạt hiệu ứng vẽ Insert
                page.textbox.nums.pop_back();
            }   
            Node* cur = head; while(cur) {cout<<cur->val<<" "; cur = cur->next;} cout<<endl;
        }

        void DrawLLinPage() {
            //BeginDrawing();
            if (isInserting) {
                DrawInsert(lastInsertedKey);
                isInserting = false;
            }
            else{
                DrawLL();
            }
            //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            //EndDrawing();   
        }
    };