#pragma once
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

#include <raylib.h>
#include "LinkedList.h"
#include "Variables.h"
#include "Page.h"

struct HashNode {
    int key;
    HashNode* next;

    HashNode(int k, HashNode* nxt = nullptr) {
        key = k;
        next = nxt;
    }
};

//vector<LinkedList*> heads;


class HashTableChaining : public Page {
public:
    Vector2 origin;
    int tableSize = 3;
    vector<LinkedList*> heads;
    // vector<HashNode*> table; // Khởi tạo bảng băm với kích thước tableSize
    // HashNode* table[tableSize]; // Bảng băm

    int HashFunction(int key);

    // Cấu hình cho vẽ node

     Color ring = BLACK;
     Color circle = {64, 210, 173, 255};
     Color choose_color = GREEN;
     Color visit_color = RED;


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
    int searchKey = -1;
    bool searchFound = false;  // (tuỳ chọn) để biết có tìm thấy hay không

    bool isDeleting = false;
    int deleteKey = -1;
    bool isDuplicateInsert = false;


    // Constructor & Destructor
    // HashTableChaining();
    HashTableChaining(){};
    ~HashTableChaining();
    HashTableChaining(int size);

    // Core functions
    void Insert(int key);
    bool Search(int key);
    void Clear(); // optional reset function

    bool isCreating = false;
    vector<int> createKeys;


    // Drawing functions
    void DrawArrow(Vector2 start, Vector2 end);
    void DrawHashTable();
    void DrawInsertEffect();
    void DrawSearchEffect();
    void DrawDeleteEffect();
    // void DrawInsertDuplicateEffect();


    // Integration with Page
    void init() override;
    void draw() override;
    void event() override;
    void reset() override;
    void updateVariables();

    void RANDOM_INPUT() override;
    
};