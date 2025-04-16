#pragma once

#include <string>
#include <cmath>
#include <iostream>
#include <vector>

#include <raylib.h>
#include "LinkedList.h"
#include "Variables.h"
#include "Page.h"

using namespace std;

// ========================= CLASS HashTBpaint ========================= //
class HashTBpaint : public LLpaint {
public:
    // Position
    Vector2 origin = {200, 200};

    // Hash table
    int tableSize = 3;
    vector<LinkedList*> heads;

    // Drawing settings
    const int bucket_width = 100;
    const int bucket_height = 60;
    const int spacing = 100;
    const int radius = 30;
    const int font_size = 30;

    const Color bucket_color = MyColor6;
    const Color node_color = SKYBLUE;
    const Color text_color = BLACK;
    const Color arrow_color = BLACK;
    const float arrow_size = 10.0f;

    const Color ring = BLACK;
    const Color circle = {64, 210, 173, 255};
    const Color choose_color = GREEN;
    const Color visit_color = RED;

    // Animation
    int curCode = -1;
    bool isMove = false;

    // Constructor
    HashTBpaint() {}

    // Copy linked lists
    void copy(const vector<LinkedList*>& tmp) {
        vector<LinkedList*> newLists;
        for (auto& oldList : tmp) {
            LinkedList* newList = new LinkedList();
            newList->head = copyLL(oldList->head);
            newList->headPos = oldList->headPos;
            newLists.push_back(newList);
        }
        this->heads = newLists;
    }

    void copy(Node* a) {
        this->head = copyLL(a);
    }
};

// =========================== CLASS HashTB ============================ //
class HashTB : public Page {
public:
    // Core data
    Vector2 origin;
    int tableSize = 3;
    vector<LinkedList*> heads;

    // Animation states
    vector<HashTBpaint> steps;
    int cur = -1;
    int curCode = -1;

    // Drawing settings
    int bucket_width = 25;
    int bucket_height = 40;
    int spacing = 40;
    int radius = 30;
    int font_size = 25;

    Color bucket_color = MyColor6;
    Color node_color = SKYBLUE;
    Color text_color = BLACK;
    Color arrow_color = BLACK;
    float arrow_size = 9.0f;

    Color ring = BLACK;
    Color circle = {64, 210, 173, 255};
    Color choose_color = GREEN;
    Color visit_color = RED;

    // Logic flags
    bool isUpdating = false;
    int UpdateKey = -1;
    int newKey = -1;

    bool isInserting = false;
    int lastInsertedKey = -1;

    bool isSearching = false;
    int SearchKey = -1;
    bool searchFound = false;

    bool isDeleting = false;
    int DeleteKey = -1;

    bool isDuplicateInsert = false;

    // Status flags
    bool hasInsert;
    bool hasSearch;
    bool hasDelete;
    bool hasCreate;
    bool hasUpdate;

    bool isCreating = false;
    vector<int> createKeys;
    float rotationStartTime;
    bool isMove = false;
    int index = -1;
    int Found = -1;

    // Constructor & Destructor
    HashTB() {}
    ~HashTB();
    HashTB(int size);

    // Hash Table core
    int HashFunction(int key);
    void Insert(int key);
    bool Search(int key);
    bool DeleteNode(int key);
    bool Update(int oldKey, int newKey);
    void Create();
    void Clear();  // Reset table

    // Drawing & animation
    void addStepH(const vector<LinkedList*>& heads, int curCode = -1, bool isMove = false);
    void drawStep(HashTBpaint &a, int Found = -1);
    void DrawHashTB(vector<LinkedList*>& heads);
    void CalculatePos(int index, Vector2 PosHead);
    void updateHTBNodePositions(Node* &a, Node* b, float &tmp);
    Node* findNode(Node* head, int key);

    // Page override
    void init() override;
    void draw() override;
    void event() override;
    void reset() override;
    void RANDOM_INPUT() override;

    // Pseudocode support
    void updatePseudocode();
    void updateVariables(vector<LinkedList*>& a);
};
