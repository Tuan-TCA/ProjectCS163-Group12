#include <raylib.h>

struct LinkedListNode {
    int val;
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

//animation
void DrawArrow(Vector2 start, Vector2 end, float arrowSize, Color color);
void DrawLinkedList(LinkedListNode* head);
void Choose(Vector2 center, Color RimDark, Color RimBland, LinkedListNode * head);
void DrawNewNode(Vector2 center, string value, Color RimDark, Color RimBland, LinkedListNode* head);
void AcceptNode(Vector2 start, Vector2 target, string value, LinkedListNode* head);
Vector2 GetPosition(LinkedListNode* head);

void MoveLinkedList(LinkedListNode* head, Vector2 orinalPosition, Vector2 newPosition);
void DrawNewLinkedList(LinkedListNode* head, Vector2 position);