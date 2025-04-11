#pragma once
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

#include <raylib.h>
#include "LinkedList.h"
#include "Variables.h"
#include "Page.h"

// struct HashNode {
//     int key;
//     HashNode* next;
//     HashNode(int k, HashNode* nxt = nullptr) {
//         key = k;
//         next = nxt;
//     }
// };

//vector<LinkedList*> heads;
class HashTBpaint : public LLpaint{
public:
    // Origin point for drawing the hash table
    Vector2 origin = {200, 200};

    // Hash table size and heads of chains
    int tableSize = 3;
    vector<LinkedList*> heads;

    // Drawing configuration
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

    int curCode = -1;
    bool isMove = false;

    HashTBpaint() {}

    vector<LinkedList*> copy(const vector<LinkedList*>& tmp) {
        vector<LinkedList*> newLists;
        for (auto& oldList : tmp) {
            LinkedList* newList = new LinkedList();          
            newList->head = copyLL(oldList->head);
            newList->headPos = oldList->headPos;
            newLists.push_back(newList);
            
        }
        
        return newLists;
    }

};

class HashTB : public Page  {
public:
    Vector2 origin;
    int tableSize = 3;
    vector<LinkedList*> heads;
    
    vector<HashTBpaint> steps;
    int cur = -1;
    int curCode = -1;

    // Cấu hình cho vẽ node
     Color ring = BLACK;
     Color circle = {64, 210, 173, 255};
     Color choose_color = GREEN;
     Color visit_color = RED;
    Rectangle bucket = {
        origin.x ,
        origin.y + 50,
        (float)bucket_width,
        (float)spacing * (tableSize)
    };
    // UI settings
     int bucket_width = 25;
     int bucket_height = 40;
     int spacing = 70;
     int radius = 25;
     int font_size = 20;

    Color bucket_color = MyColor6;
     Color node_color = SKYBLUE;
     Color text_color = BLACK;
     Color arrow_color = BLACK;
     float arrow_size = 10.0f;

    // Logic variables
    bool isInserting = false;
    int lastInsertedKey = -1;

    bool isSearching = false;
    int SearchKey = -1;
    bool searchFound = false;  // (tuỳ chọn) để biết có tìm thấy hay không

    bool isDeleting = false;
    int DeleteKey = -1;
    bool isDuplicateInsert = false;

    void addStepH(const vector<LinkedList*>& heads, int curCode = -1, bool isMove = false) {
        HashTBpaint tmp;
        tmp.heads = tmp.copy(heads);
        updateVariables(tmp.heads);
        tmp.curCode = curCode;
        tmp.isMove = isMove;
        steps.push_back(tmp);
    }
    void drawStep(HashTBpaint &a, int Found = -1);
    void handleUI();
    int Found = -1;
    bool hasInsert;
    bool hasSearch;
    bool hasDelete;
    bool hasCreate;

    // Constructor & Destructor
    // HashTB();
    HashTB(){};
    ~HashTB();
    HashTB(int size);
    int HashFunction(int key);

       void updatePseudocode();
    void updateVariables(vector<LinkedList*>& a);
    void DrawHashTB(vector<LinkedList*>& heads);

    // Core functions
    void Insert(int key);
    bool Search(int key);
    bool Delete(int key);
    void Create();
    void Clear(); // optional reset function

    bool isCreating = false;
    vector<int> createKeys;

    // Integration with Page
    void init() override;
    void draw() override;
    void event() override;
    void reset() override;
    void RANDOM_INPUT() override;
    
};