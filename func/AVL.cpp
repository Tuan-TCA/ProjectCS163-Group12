#include "AVL.h"
#include "ControlAnimation.h"
#include <iostream>



void AVL::insert(int key, TreeNode*& root, TreeNode* parent) {
    // if (root) {
    //     root->isHighLight = true;
    //     addStep(this->root);  // Capture state before going down
    //     root->isHighLight = false;
    // }
    if (!root) {
        Vector2 pos;
        if (!parent) {
            pos = rootPos;
            root = new TreeNode(key, nullptr, nullptr, nullptr, 
                pos, 1, 1, 0);
            
        } else {
            bool isLeft = key < parent->val;
            pos = calculateChildPos(parent->Pos, isLeft, parent->level+1);
            root = new TreeNode(key, nullptr, nullptr,parent, 
                pos, 1, parent->level+1, 0);
        }
        // Don't add step here yet
        root->isHighLight = -1;
        addStep(this->root);  // Capture state before going down
        root->isHighLight = 0;
        return;
    }
    
    if (key < root->val) {
        insert(key, root->left, root);

    } 
    else if (key > root->val) {
        insert(key, root->right, root);
    }
    else return;

    // Update height and balance
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    root->parent = parent;
    root->level = getLevel(parent) + 1;
    int balance = getHeight(root->left) - getHeight(root->right);
    
    if(abs(balance) >= 2) {
        if(balance > 1) {
            cout<<"LL";
            if(key < root->left->val) {
                RightRotate(root);
            }
            else {
                LeftRotate(root->left);
                RightRotate(root);
                cout<<"LL";
            }
        }
        else {
            if(key > root->right->val) {
                LeftRotate(root);
            }
            else {
                RightRotate(root->right);
                LeftRotate(root);
            }
        }
        // root->isHighLight = false;
        // addStep(this->root);
    }
    //addStep(this->root);
    // Recalculate all positions after any potential rotations
    //CalculateAllPos(this->root, nullptr, true);
    
    // Only add step after everything is complete
    //addStep(this->root);  
    if (root) {
        root->isHighLight = 0;
    }

    root->isHighLight = -1;
    addStep(this->root);  // Capture state before going down
    root->isHighLight = 0;

}

int cur;
void AVL::draw() {
    Page::draw();

    static float elapsedTime = 0.0f;
    const float stepDuration = 0.5f / animationSpeed;
    if(IsKeyPressed(KEY_A)) {
        DrawTree(root);
    }
    if (currentOperation == Operation::Insert) {
        if (isInserting) {
            steps.clear(); // Xóa các bước cũ
            this->insert(lastInsertedKey, root); // Thêm node và lưu các bước
            addStep(this->root);
            isInserting = false;
            isPlaying = true;
            cur = 0; // Bắt đầu từ bước đầu tiên
            elapsedTime = 0.0f;
        } else {
            if (!steps.empty()) {
                // Đảm bảo cur nằm trong khoảng hợp lệ
                if(cur >= 0 && cur< steps.size()) {
                    DrawTree(steps[cur].root);
                }

                // Tự động chạy tiếp nếu đang ở chế độ play
                if (isPlaying) {
                    elapsedTime += GetFrameTime();
                    if (elapsedTime >= stepDuration) {
                        if (cur < steps.size() ) {
                            cur++;
                            elapsedTime = 0.0f;
                        }
                    }
                }
                
                if(cur == steps.size() && cur!=0) {
                    DrawTree(steps[cur-1].root);
                    isPlaying = false;
                }
            }
        }
    }
    // ... (Xử lý các operation khác nếu cần)
}



void AVL::event() {
    Page::event();


    //Choose Operation
    if(currentOperation == Operation::Create) {
        //CreateLL;
    }
    if(currentOperation == Operation::Insert) {
        
        if(textbox.nums.size() > 0) {
            lastInsertedKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isInserting = true;
            textbox.inputText = "";
        }   
        // Node* cur = head; while(cur) {cout<<cur->val<<" "; cur = cur->next;} cout<<endl;
    }
    if(currentOperation == Operation::Search) {
        if(textbox.nums.size() > 0) {
            SearchKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isSearching = true;
            textbox.inputText = "";
        }
    }
    if(currentOperation == Operation::Delete) {
        if(textbox.nums.size() > 0) {
            DeleteKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isDeleting = true;
            textbox.inputText = "";
        }
    }

    if(currentOperation == Operation::Update) {
        if(textbox.nums.size() > 0) {
            UpdateKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            newVal = textbox.nums[1];
            isUpdating = true;
            textbox.inputText = "";
        }
    }

    //Run step-by-step

    if(!isPlaying){
        if(!switchState ? play1.IsClicked() : play2.IsClicked()){
            animationController.isPaused = !animationController.isPaused;
            isPlaying = true;
            TraceLog(LOG_INFO, "is playing");
        }
    }
    else{
        if( isPlaying && !switchState ? pause1.IsClicked() : pause2.IsClicked())
        {
            animationController.isPaused = !animationController.isPaused;
            isPlaying = false;
            TraceLog(LOG_INFO, "is pausing");
        }
    }

    // Điều khiển step-by-step
    if (back1.IsClicked() || back2.IsClicked()) { // Nút back
        if (cur > 0) {
            cur--;
        }
        isPlaying = false; // Tạm dừng khi lùi
    } 
    else if (next1.IsClicked() || next2.IsClicked()) { // Nút next
        if (cur < steps.size() - 1) {
            cur++;
        }
        isPlaying = false; // Tạm dừng khi tiến
    }

    // Phím mũi tên trái/phải
    if (IsKeyPressed(KEY_LEFT)) {
        if (cur > 0) {
            cur--;
            isPlaying = false;
        }
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        if (cur < steps.size() - 1) {
            cur++;
            isPlaying = false;
        }
    }
}


void AVL::init() {
    Page::init();
    root = nullptr;
    workplace = {screenWidth*0.24f,screenHeight*0.2f,(float) screenWidth *(1-0.24f),screenHeight*(1-0.095f)};
    rootPos= {workplace.x + workplace.width / 2, workplace.y};      
    //int a[]={8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15, 16};  for (int i = 0; i < 16; i++) this->insert(a[i],root);
    steps.clear();

    isInserting = false;
    isSearching = false;
    isDeleting = false;
    isUpdating = false;
       
}

void AVL::DestroyRecursive(TreeNode* node)
{
    if (node)
    {
        DestroyRecursive(node->left);
        DestroyRecursive(node->right);
        delete node;
    }
}

AVL::~AVL() {
    DestroyRecursive(root);
    root = nullptr;
}

int AVL::getHeight(TreeNode *root) {
    if(root) return root->height;
    return 0;
}
int AVL::getLevel(TreeNode *root) {
    if(root) return root->level;
    return 0;
}


Vector2 AVL::calculateChildPos(Vector2 parentPos, bool isLeft, int level) {
    float xOffset = workplace.width / pow(2, level + 2);
    return {
        isLeft ? parentPos.x - 3.5*xOffset : parentPos.x + 3.5*xOffset,
        parentPos.y + 3.5*radius  // Khoảng cách dọc giữa các mức
    };
}


void AVL::CalculateAllPos(TreeNode* &root, TreeNode* parent, bool isLeft) {
    if(!root) return;

    if(parent) {
        root->Pos = calculateChildPos(parent->Pos, isLeft, parent->level + 1);
        root->level = parent->level + 1;
    }

    
    CalculateAllPos(root->left, root, true);
    CalculateAllPos(root->right, root, false);
    
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
}

void AVL::RightRotate(TreeNode* &root) {
    if (!root || !root->left) return;
    Vector2 oldPos = root->Pos;
    int oldLevel = root->level;
    
    TreeNode *tmp = root->left;
    TreeNode *tmpRight = tmp->right;

    // Cập nhật liên kết
    tmp->right = root;
    root->left = tmpRight;

    // Cập nhật parent
    if (tmpRight) tmpRight->parent = root;  // Nếu có node tmpLeft
    tmp->parent = root->parent;           // Kế thừa parent từ root cũ
    root->parent = tmp;                   // Root cũ trở thành con trái của tmp
    
    // Cập nhật root mới
    root = tmp;
    root->Pos = oldPos;
    root->level = oldLevel;


    // Cập nhật height: cập nhật node cũ (root cũ) trước, node mới (tmp) sau
    if(root->left)
    root->left->height = 1 + max(getHeight(root->left->left), getHeight(root->left->right));
    if(root->right)
    root->right->height = 1 + max(getHeight(root->right->left), getHeight(root->right->right));
    
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Tính toán lại vị trí từ node gốc mới (không cần gán thủ công Pos/level)
    if(root->parent)
        CalculateAllPos(root, root->parent, root->val < root->parent->val);  // Giả sử CalculateAllPos xử lý parent
    else 
        CalculateAllPos(root, root->parent, true);  // Giả sử CalculateAllPos xử lý parent
    
}

void AVL::LeftRotate(TreeNode* &root) {
    if (!root || !root->right) return;

    Vector2 oldPos = root->Pos;
    int oldLevel = root->level;

    TreeNode *tmp = root->right;
    TreeNode *tmpLeft = tmp->left;

    // Cập nhật liên kết
    tmp->left = root;
    root->right = tmpLeft;
    
    // Cập nhật parent
    if (tmpLeft) tmpLeft->parent = root;  // Nếu có node tmpLeft
    tmp->parent = root->parent;           // Kế thừa parent từ root cũ
    root->parent = tmp;                   // Root cũ trở thành con trái của tmp

    // Cập nhật root mới
    root = tmp;
    root->Pos = oldPos;
    root->level = oldLevel;
    
    // Cập nhật height: cập nhật node cũ (root cũ) trước, node mới (tmp) sau
    if(root->left)
    root->left->height = 1 + max(getHeight(root->left->left), getHeight(root->left->right));
    if(root->right)
    root->right->height = 1 + max(getHeight(root->right->left), getHeight(root->right->right));
   
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    
    // Tính toán lại vị trí từ node gốc mới (không cần gán thủ công Pos/level)
    if(root->parent)
        CalculateAllPos(root, root->parent, root->val < root->parent->val);  // Giả sử CalculateAllPos xử lý parent
    else 
        CalculateAllPos(root, root->parent, true);  // Giả sử CalculateAllPos xử lý parent
    
}

bool AVL::isNodeHighlighted(int key) {
    for (TreeNode* &node : hightlightNodes) {
        if (node->val == key) {
            node->isHighLight = false;
            hightlightNodes.erase(hightlightNodes.begin() + (&node - &hightlightNodes[0]));
            return true;
        }
    }
    return false;
}

//choose = 1=green -1=red, 0=white
void AVL::DrawTN(TreeNode *a){
    
    Vector2 center = a->Pos;
    int key = a->val;
    int choose = a->isHighLight;

    string s = to_string(key);
    if (choose == 1)
        DrawCircleV(center, radius, choose_color);
    if (choose ==-1)//isNodeHighlighted(key))
        //cout << center.x << ' ' << key << '\n';
        DrawCircleV(center, radius, visit_color);
    if (choose == 0)
        DrawCircleV(center, radius, WHITE);

    DrawCircleV(center, radius - 9, MyColor2);
    DrawCircleV(center, radius - 10, MyColor2);

    int Fs = max(10, static_cast<int>(font_size-s.size()*3));
    //Draw text
    int wNode =  MeasureText(s.c_str(), Fs);
    DrawText(s.c_str(), center.x - wNode / 2, center.y - Fs/2, Fs, text_color);
    
    // EndDrawing();
}

void AVL::DrawArrow(Vector2 start, Vector2 end) {
    bool isRight = start.x < end.x;

    float length = sqrtf(powf(abs(end.x - start.x), 2) + powf(abs(end.y - start.y), 2));

    
    if(isRight) {
        start = {start.x + (abs(start.x - end.x) * radius) / length, start.y + (abs(start.y - end.y) * radius) / length};
        end = {end.x - (abs(start.x - end.x) * radius) / length - 5, end.y - 3 - (abs(start.y - end.y) * radius) / length};

    }
    else {
        start = {start.x - ((start.x - end.x) * radius) / length, start.y + (abs(start.y - end.y) * radius) / length};
        end = {end.x + ((start.x - end.x) * radius) / length +5, end.y -3 - (abs(start.y - end.y) * radius) / length};
    }
    float arrowAngle = PI/6;
    float angle = atan2f(end.y - start.y, end.x - start.x);

    Vector2 arrowHead = {end.x, end.y};
    Vector2 left = {arrowHead.x - (arrow_size+2) * cos(angle + arrowAngle), 
                    arrowHead.y - (arrow_size+2) * sin(angle + arrowAngle)};
    Vector2 right = {arrowHead.x - (arrow_size+2) * cos(angle - arrowAngle), 
                     arrowHead.y - (arrow_size+2) * sin(angle - arrowAngle)};

    DrawLineEx(start, arrowHead, 5, arrow_color);
    DrawLineEx(arrowHead, left, 3, arrow_color);
    DrawLineEx(arrowHead, right, 3, arrow_color);
}

void AVL::DrawTree(TreeNode* root) {
    if (!root) return;

    DrawTN(root);
    //TraceLog(LOG_INFO, "Draw %d at (%f, %f)", root->val, root->Pos.x, root->Pos.y);
    if (root->left) {
        DrawArrow(root->Pos, root->left->Pos);
        DrawTree(root->left);
    }
    if (root->right) {
        DrawArrow(root->Pos, root->right->Pos);
        DrawTree(root->right);
    }
}



