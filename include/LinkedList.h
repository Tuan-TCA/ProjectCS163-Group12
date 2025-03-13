#pragma once
#include <raylib.h>
#include "Button.h"
#include "Variables.h"
#include <bits/stdc++.h>

struct LinkedListNode {
    int val;
    LinkedListNode* next;
};


//algorithm
void insertNode(LinkedListNode* &head, int key);
void deleteNode(LinkedListNode* &head, int key);
LinkedListNode *search(LinkedListNode* head, int key);
void update(LinkedListNode *&head, int first, int second);

//animation
void DrawArrow(Vector2 start, Vector2 end, float arrowSize, Color color);
void DrawLinkedList(LinkedListNode* head);