#include "HashTB.h"
#include <raylib.h>
#include <cmath>
#include <thread>
#include <chrono>
#include <iostream>
#include "DrawUtils.h"
#include "Program.h"
using namespace std;

// HashTableChaining::HashTableChaining() {
//     for (int i = 0; i < tableSize; ++i) {
//         table[i] = nullptr;
//     }
//     isInserting = false;
//     lastInsertedKey = -1;
// }

void HashTableChaining::init(){
    Page::init();
    table.resize(tableSize, nullptr);
    isInserting = false;
    lastInsertedKey = -1;
    isCreating = false;
    isDuplicateInsert = false;
}
HashTableChaining::HashTableChaining(int size) {
    tableSize = size;
    table.resize(size, nullptr);
    isInserting = false;
    lastInsertedKey = -1;
    isCreating = false;
    isDuplicateInsert = false;
}

HashTableChaining::~HashTableChaining() {
    for (int i = 0; i < tableSize; ++i) {
        HashNode* current = table[i];
        while (current) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

int HashTableChaining::HashFunction(int key) {
    return key % tableSize;
}

void HashTableChaining::Insert(int key) {
    int index = HashFunction(key);
    HashNode* cur = table[index];

    while (cur) {
        if (cur->key == key) {
            // Trùng → không insert
            lastInsertedKey = key;
            isInserting = false;
            isDuplicateInsert = true;   // ➕ thêm biến này (bên dưới sẽ nói)
            return;
        }
        cur = cur->next;
    }

    isInserting = true;
    lastInsertedKey = key;
}

bool HashTableChaining::Search(int key) {
    int index = HashFunction(key);
    HashNode* current = table[index];
    while (current) {
        if (current->key == key) return true;
        current = current->next;
    }
    return false;
}


void HashTableChaining::DrawHashTable(Vector2 origin) {
    Rectangle bucket = {
        origin.x ,
        origin.y + 50,
        (float)bucket_width,
        (float)spacing * (tableSize)
    };
    bucket_color = MyColor6;
    DrawRectangleRec(bucket, bucket_color);
    //DrawRectangleLines(bucket.x, bucket.y, bucket.width, bucket.height, BLACK);
    for (int i = 0; i < tableSize; ++i) {
        // Vẽ ô bucket
        // Rectangle bucket = {
        //     origin.x,
        //     origin.y + i * spacing,
        //     (float)bucket_width,
        //     (float)bucket_height
        // };

        // DrawRectangleRec(bucket, bucket_color);
        // DrawRectangleLines(bucket.x, bucket.y, bucket.width, bucket.height, BLACK);

        string label = to_string(i);
        DrawText(label.c_str(), bucket.x + 8, (i+2) * spacing + 35, font_size, text_color);

        // Vẽ dãy node trong bucket[i]
        HashNode* current = table[i];
        Vector2 nodePos = {
            bucket.x + spacing,
            (i+2) * spacing + 25 + bucket_height / 2.0f
        };

        while (current) {
            // Vẽ node
            DrawNode(
                nodePos,
                current->key,
                0,  
                radius,
                font_size,
                ring,
                circle,
                choose_color,
                visit_color,
                text_color
            );
        
            if (current->next) {
                Vector2 nextPos = { nodePos.x + spacing, nodePos.y };
                DrawArrowHTB(nodePos, nextPos, radius, arrow_size, arrow_color);
                nodePos = nextPos; // Cập nhật nodePos cho node tiếp theo
            }
        
            current = current->next; 
        }        
}
}

void HashTableChaining::DrawInsertEffect(Vector2 origin) {
    if (!isInserting) return;

    int index = HashFunction(lastInsertedKey);
    float y = (index + 2) * spacing + 25 + bucket_height / 2.0f;

    // Tính vị trí node đầu tiên trong bucket
    Vector2 nodePos = { origin.x + spacing, y };

    // Duyệt từng node hiện có và highlight
    HashNode* cur = table[index];
    while (cur) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // page.draw();
        Page::draw();
        DrawHashTable(origin);
    
        // Highlight node đang duyệt
        DrawNode(nodePos, cur->key, -1, radius, font_size,
                 ring, circle, choose_color, visit_color, text_color);
    
        EndDrawing();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
        cur = cur->next;
    
        // ✅ Luôn cập nhật nodePos sau mỗi node (kể cả node cuối)
        nodePos.x += spacing;
    }
    

    // Sau khi duyệt hết, thêm node mới vào vị trí nodePos
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // page.draw();
    Page::draw();
    DrawHashTable(origin);
    // 👉 Nếu có node trước đó → vẽ mũi tên từ node cũ đến node mới
    if (table[index]) {
        Vector2 arrowStart = { nodePos.x - spacing, nodePos.y };
        Vector2 arrowEnd = nodePos;
        DrawArrowHTB(arrowStart, arrowEnd, radius, arrow_size, arrow_color);
    }

    // vẽ node mới tại cuối
    DrawNode(nodePos, lastInsertedKey, 1, radius, font_size,
             ring, circle, choose_color, visit_color, text_color);
                // Chèn node mới sau khi animation kết thúc
    HashNode* newNode = new HashNode(lastInsertedKey);
    if (!table[index]) {
        table[index] = newNode;
    } else {
        HashNode* cur = table[index];
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = newNode;
    }
    EndDrawing();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    isInserting = false;
}

void HashTableChaining::DrawSearchEffect(Vector2 origin) {
    if (!isSearching) return;

    int index = HashFunction(searchKey);
    float y = origin.y + index * spacing + bucket_height / 2.0f;
    Vector2 nodePos = { origin.x + bucket_width + spacing, y };

    HashNode* cur = table[index];
    while (cur) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // page.draw();
        Page::draw();
        DrawHashTable(origin);

        // highlight node đang kiểm tra
        DrawNode(nodePos, cur->key, -1, radius, font_size,
                 ring, circle, choose_color, visit_color, text_color);

        EndDrawing();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        if (cur->key == searchKey) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            // page.draw();
            Page::draw();
            DrawHashTable(origin);

            DrawNode(nodePos, cur->key, 1, radius, font_size,
                     ring, circle, choose_color, visit_color, text_color);

            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(600));

            isSearching = false;
            return;
        }

        nodePos.x += spacing;
        cur = cur->next;
    }

    // Nếu không tìm thấy
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // page.draw();
    Page::draw();
    DrawHashTable(origin);
    DrawText("Not Found", origin.x + 400, y - 10, font_size, RED);
    EndDrawing();
    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    isSearching = false;
}

void HashTableChaining::DrawDeleteEffect(Vector2 origin) {
    if (!isDeleting) return;

    int index = HashFunction(deleteKey);
    float y = origin.y + index * spacing + bucket_height / 2.0f;
    Vector2 nodePos = { origin.x + bucket_width + spacing, y };

    HashNode* cur = table[index];
    HashNode* prev = nullptr;

    while (cur) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // page.draw();
        Page::draw();
        DrawHashTable(origin);

        // Highlight node đang kiểm tra
        DrawNode(nodePos, cur->key, -1, radius, font_size,
                 ring, circle, choose_color, visit_color, text_color);

        EndDrawing();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        if (cur->key == deleteKey) {
            // Animation xoá: chỉ không vẽ node nữa
            for (int step = 10; step >= 0; --step) {
                float alpha = step / 10.0f;
            
                BeginDrawing();
                ClearBackground(RAYWHITE);
                // page.draw();
                Page::draw();
                DrawHashTable(origin);
            
                // Vẽ node đang mờ dần/
                DrawFadingNode(nodePos, cur->key, alpha, radius, font_size, circle, text_color);
            
                EndDrawing();
                std::this_thread::sleep_for(std::chrono::milliseconds(40));
            }
            

            // Xóa node khỏi danh sách
            if (prev == nullptr) {
                table[index] = cur->next;
            } else {
                prev->next = cur->next;
            }

            delete cur;
            break;
        }

        prev = cur;
        cur = cur->next;
        nodePos.x += spacing;
    }

    isDeleting = false;
}

void HashTableChaining::draw() {
    Page::draw();
    
    Vector2 origin = { 350, 100 };

    DrawHashTable(origin);
    DrawSearchEffect(origin);
    DrawInsertEffect(origin);
    DrawDeleteEffect(origin);
    DrawInsertDuplicateEffect(origin);

    // 👇 Add auto-create nếu đang tạo từ array
    if (isCreating && !createKeys.empty()) {
        Insert(createKeys.front());
        createKeys.erase(createKeys.begin());
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    if (createKeys.empty()) isCreating = false;
}


void HashTableChaining::DrawInsertDuplicateEffect(Vector2 origin) {
    if (!isDuplicateInsert) return;

    int index = HashFunction(lastInsertedKey);
    float y = origin.y + index * spacing + bucket_height / 2.0f;

    Vector2 nodePos = { origin.x + bucket_width + spacing, y };
    HashNode* cur = table[index];

    while (cur) {
        if (cur->key == lastInsertedKey) {
            // Là node trùng → fade đỏ
            for (int step = 0; step <= 10; ++step) {
                float alpha = step / 10.0f;

                BeginDrawing();
                ClearBackground(RAYWHITE);
                // page.draw();
                Page::draw();
                DrawHashTable(origin);

                // Overlay đỏ với alpha
                Color overlay = RED;
                overlay.a = static_cast<unsigned char>(alpha * 255);
                DrawFadingNode(nodePos, cur->key, alpha, radius, font_size, overlay, text_color);

                EndDrawing();
                std::this_thread::sleep_for(std::chrono::milliseconds(40));
            }
            break;
        }
        nodePos.x += spacing;
        cur = cur->next;
    }

    isDuplicateInsert = false;
}




void HashTableChaining::event() {
    Page::event();
    if (currentOperation == Operation:: Insert) {
        if (textbox.nums.size() > 0) {
            lastInsertedKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            textbox.inputText = {""};
            Insert(lastInsertedKey);
        }
    }

    if (currentOperation == Operation:: Search) {
        if (textbox.nums.size() > 0) {
            searchKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            textbox.inputText = {""};
            isSearching = true;
        }
    }
    if (currentOperation == Operation:: Delete) {
        if (textbox.nums.size() > 0) {
            deleteKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            textbox.inputText = {""};
            isDeleting = true;
        }
    }
    if (currentOperation == Operation:: Create) {
         if(textbox.nums.size() > 0){
            table.clear();
             tableSize = textbox.nums[0]; 
             table.resize(tableSize);
             textbox.nums.erase(textbox.nums.begin());
             textbox.inputText = {""};
        }
        if (textbox.nums.size() > 0) {
             //Insert other values
            createKeys = textbox.nums;
            textbox.nums.clear();
            textbox.inputText = {""};
            isCreating = true;
        }
        
    }    

        // Xử lý CREATE với table size nhập từ bàn phím
        //     if (currentOperation == Operation::Create && !textbox.nums.empty()) {
        //     int size = textbox.nums[0];  // Lấy table size từ input
        //     textbox.nums.erase(textbox.nums.begin());
    
        //     if (B) delete B;  // Xoá bảng cũ nếu có
        //     B = new HashTableChaining(size);  // Khởi tạo bảng mới với kích thước
        //     textbox.inputText = {""};  // Reset input
        // }
        // if (B) B->event();

        // if(B)
        // B->draw();
        // else {
        //     B = new HashTableChaining(3);
        //     B->draw();
        // }
}

void HashTableChaining::reset(){
    Page::reset();
    tableSize = 3;
    table.clear();
    isInserting = false;
    lastInsertedKey = -1;
    isCreating = false;
    isDuplicateInsert = false;
    createKeys.clear();
}