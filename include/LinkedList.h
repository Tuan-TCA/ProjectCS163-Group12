#pragma once
#include <string>
#include <math.h>
#include <iostream>
using namespace std;
#include <raylib.h>

struct LinkedListNode {
    int val;
    int x, y;
    LinkedListNode* next;
};

//const
const int r = 50;  
const int font_size = 40; 
const int spacing = 50; 

const int screenWidth = 1100;
const int screenHeight = 1100;

//algorithm
void insertNode(LinkedListNode* &head, int key);
void deleteNode(LinkedListNode* &head, int key);
LinkedListNode *search(LinkedListNode* head, int key);
void update(LinkedListNode *&head, int &first, int second);
void DrawRim(Vector2 center, Color RimDark, Color RimBland);

void update1(LinkedListNode *head, int nums[], int key, int id);
//hlt
void updatePosition(LinkedListNode * head);

//animation
void DrawArrow(Vector2 start, Vector2 end, float arrowSize, Color color);
void DrawLinkedList(LinkedListNode* head);
void Choose(Vector2 center, Color RimDark, Color RimBland, LinkedListNode * head);
void DrawNewNode(Vector2 center, string value, Color RimDark, Color RimBland, LinkedListNode* head);
void AcceptNode(Vector2 start, Vector2 target, string value, LinkedListNode* head);
Vector2 GetPosition(LinkedListNode* head);
void MoveLinkedList(LinkedListNode* head, Vector2 orinalPosition, Vector2 newPosition);
void DrawNewLinkedList(LinkedListNode* head, Vector2 position);
//hlt
void DrawLinkedList1(LinkedListNode* head);

//search
void traverseSearch(LinkedListNode* head, int key);
void traverseDelete(LinkedListNode* &head, int key);