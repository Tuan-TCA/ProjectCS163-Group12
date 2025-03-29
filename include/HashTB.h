#pragma once
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

#include <raylib.h>
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

class HashTableChaining : public Page {
private:
    // Các biến cần thiết cho việc vẽ
    // Vector2 origin = { 350, 100 };
    // Vector2 nodePos = { origin.x + bucket_width + spacing, origin.y + bucket_height / 2.0f };
    // Vector2 arrowStart = { nodePos.x - spacing, nodePos.y };
    // Vector2 arrowEnd = { nodePos.x, nodePos.y };
    // Vector2 nodePos = { origin.x + bucket_width + spacing, origin.y + bucket_height / 2.0f };
public:

    int tableSize = 10;
    vector<HashNode*> table; // Khởi tạo bảng băm với kích thước tableSize
    // HashNode* table[tableSize]; // Bảng băm

    int HashFunction(int key);

    // Cấu hình cho vẽ node

    const Color ring = BLACK;
    const Color circle = LIGHTGRAY;
    const Color choose_color = GREEN;
    const Color visit_color = RED;


    // UI settings
    const int bucket_width = 80;
    const int bucket_height = 40;
    const int spacing = 70;
    const int radius = 25;
    const int font_size = 20;

    const Color bucket_color = LIGHTGRAY;
    const Color node_color = SKYBLUE;
    const Color text_color = BLACK;
    const Color arrow_color = BLACK;
    const float arrow_size = 10.0f;

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
    void DrawHashTable(Vector2 origin);
    void DrawInsertEffect(Vector2 origin, Page &page);
    void DrawSearchEffect(Vector2 origin, Page& page);
    void DrawDeleteEffect(Vector2 origin, Page& page);
    void DrawInsertDuplicateEffect(Vector2 origin, Page& page);


    // Integration with Page
    void DrawHashTableInPage(Page page);
    void EventHashTableInPage(Page& page);
    
};
