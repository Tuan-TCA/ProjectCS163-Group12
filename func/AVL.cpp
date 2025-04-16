#include "AVL.h"
#include <iostream>
#include<stack>
#include <vector>
#include <sstream>


void updateRotation(float stepDuration, AVLpaint& tmp, AVLpaint& tar) {
    if (!tmp.root || !tmp.isRotating) return;
    
    // Tỷ lệ tiến trình (0.0 -> 1.0)
    float t = GetFrameTime() / stepDuration;
    if (t > 1.0f) t = 1.0f; 

    vector<TreeNode*> stack;
    stack.push_back(tmp.root);

    while (!stack.empty()) {
        TreeNode* current = stack.back();
        stack.pop_back();

        if (!current) continue;

        // Tìm node tương ứng trong cây đích (tar) dựa trên val
        TreeNode* target = tar.root;
        while (target && target->val != current->val) {
            if (current->val < target->val) {
                target = target->left;
            } else {
                target = target->right;
            }
        }

        // Nếu tìm thấy node tương ứng, cập nhật targetPos
        if (target) {
            current->targetPos = target->Pos;
        }

        // Kiểm tra nếu targetPos khác {0, 0} thì nội suy Pos
        if (current->targetPos.x != 0.0f || current->targetPos.y != 0.0f) {
            current->Pos.x = current->Pos.x + t * (current->targetPos.x - current->Pos.x);
            current->Pos.y = current->Pos.y + t * (current->targetPos.y - current->Pos.y);
        }

        if (current->right) stack.push_back(current->right);
        if (current->left) stack.push_back(current->left);
    }
}

void AVL::reset(){
    Page::reset();
     root = nullptr;
    rootPos= {screenWidth*0.6f, screenHeight*0.2f};        
    camera.target = rootPos;
    camera.offset = rootPos;
    steps.clear();

    isInserting = false;
    isSearching = false;
    isDeleting = false;
    isUpdating = false;
    isCreating = false;

    hasInsert = false;
    hasSearch = false;
    hasDelete = false;
    hasCreate = false;
    hasUpdate = false;
    cur = -1;
    curCode = -1;
     lineHeight = 30;
     createKeys.clear();
}

void AVL::balance(TreeNode * &root, TreeNode *& parent, int key) {
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    root->parent = parent;
    root->level = getLevel(parent) + 1;
    Vector2 oldPos = root->Pos;
    int balance = getHeight(root->left) - getHeight(root->right);
    
    if(abs(balance) >= 2) {
        if(balance > 1) {
    
            if(key < root->left->val) {
                RightRotate(root);
            }
            else {
                LeftRotate(root->left);
                RightRotate(root);
        
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
    }
    else 
        return;
    
    
    if (root) {
        root->isHighLight = 0;
    }



    root->Pos = oldPos;
    TraceLog(LOG_INFO, "root val %d", root->val);
    if (root->parent) {
        CalculateAllPos(root, root->parent, root == root->parent->left);
    } else {
        CalculateAllPos(root, nullptr, true);
    }

    root->isHighLight = -1;
    addStep(this->root);  
    root->isHighLight = 0;
}

bool AVL::deleteAVL(TreeNode*& root, TreeNode*& parent, int key) {
    if (!root) return false;

    // Bước 1: Tìm node cần xóa
    if (key < root->val) {
        root->isHighLight = -1;
        addStep(this->root, 1);
        root->isHighLight = 0;
        if (!deleteAVL(root->left, root, key))
            return false;
    } 
    else if (key > root->val) {
        root->isHighLight = -1;
        addStep(this->root, 1);
        root->isHighLight = 0;
        if (!deleteAVL(root->right, root, key))
            return false;
    } 
    else {
        // Tìm thấy node cần xóa
        root->isHighLight = 1;
        addStep(this->root, 3);
        root->isHighLight = 0;

        // Node có 0 hoặc 1 con
        if (!root->left || !root->right) {
            TreeNode* child = (root->left) ? root->left : root->right;
            root->isHighLight = -1;
            addStep(this->root, 8);
            root->isHighLight = 0;

            // Cập nhật lại con trỏ ở node cha (nếu có)
            if (child) {
                child->parent = parent;
            }

            TreeNode* nodeToDelete = root;
            root = child;
            // Nếu có cha, cập nhật lại con của nó
            if (parent) {
                if (parent->left == nodeToDelete)
                    parent->left = root;
                else if (parent->right == nodeToDelete)
                    parent->right = root;
            } else {
                this->root = root;
            }
            delete nodeToDelete;
        } 
        else {
            // Node có 2 con: Tìm successor (node nhỏ nhất bên phải)
            root->isHighLight = -1;
            addStep(this->root, 5);
            root->isHighLight = 0;
            TreeNode* successor = root->right;
            while (successor->left)
                successor = successor->left;
            root->val = successor->val;
            // Xóa successor trong cây con phải
            deleteAVL(root->right, root, successor->val);
        }
    }

    // Nếu cây con rỗng, tính lại vị trí từ rootPos rồi thoát.
    if (!root) {
        // Cập nhật lại vị trí của toàn cây từ gốc
        if(this->root)
            CalculateAllPos(this->root, nullptr, true);
        return true;
    }

    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

    int balance = getHeight(root->left) - getHeight(root->right);

    if (balance > 1) {
        if (getHeight(root->left->left) >= getHeight(root->left->right)) {
            root->isHighLight = -1;
            addStep(this->root, 5, 1);
            root->isHighLight = 0;
            TreeNode* old = root;
            RightRotate(root); 
            if (root->parent == nullptr) {
                this->root = root;
                root->Pos = rootPos;
                root->level = 1;
            }
        } else {
            root->isHighLight = -1;
            addStep(this->root, 6, 1);
            root->isHighLight = 0;
            LeftRotate(root->left);
            TreeNode* old = root;
            RightRotate(root);
            if (root->parent == nullptr) {
                this->root = root;
                root->Pos = rootPos;
                root->level = 1;
            }
        }
    }
    else if (balance < -1) {
        if (getHeight(root->right->right) >= getHeight(root->right->left)) {
            root->isHighLight = -1;
            addStep(this->root, 7, 1);
            root->isHighLight = 0;
            TreeNode* old = root;
            LeftRotate(root);
            if (root->parent == nullptr) {
                this->root = root;
                root->Pos = rootPos;
                root->level = 1;
            }
        } else {
            root->isHighLight = -1;
            addStep(this->root, 8, 1);
            root->isHighLight = 0;
            RightRotate(root->right);
            TreeNode* old = root;
            LeftRotate(root);
            if (root->parent == nullptr) {
                this->root = root;
                root->Pos = rootPos;
                root->level = 1;
            }
        }
    }

    // Sau khi cân bằng, nếu node hiện tại là gốc của toàn cây,
    // cập nhật lại
    if (root->parent == nullptr) {
        this->root = root;
        root->Pos = rootPos;
        root->level = 1;
    }

    CalculateAllPos(this->root, nullptr, true);

    root->isHighLight = -1;
    addStep(this->root, 9);
    root->isHighLight = 0;
    return true;
}

bool AVL::Update(int oldKey, int newKey) {
    bool t = deleteAVL(this->root, this->root->parent, oldKey);
    if(t) {
        insert(newKey, this->root);
    }
    return t;
}

bool AVL::search(int key, TreeNode*& root, TreeNode* parent) {   
    if (!root) {
        return false;
    }

    root->isHighLight = -1;
    addStep(this->root,1);  
    root->isHighLight = 0;


    if(root->val == key) {
        root->isHighLight = 1;
        addStep(this->root,2);
        root->isHighLight = 0;
        return true;
    }

    if (key < root->val) {
        
        root->isHighLight = -1;
        addStep(this->root,3);
        root->isHighLight = 0;
        return search(key, root->left, root);
    } 
    else {
        
        root->isHighLight = -1;
        addStep(this->root,4);
        root->isHighLight = 0;
        return search(key, root->right, root);
    }
    
}


void AVL::insert(int key, TreeNode*& root, TreeNode* parent) {   
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
        
        root->isHighLight = -1;
        addStep(this->root,1);  
        root->isHighLight = 0;
        return;
    }

    root->isHighLight = -1;
    addStep(this->root,1);  
    root->isHighLight = 0;
    
    if (key < root->val) {
        insert(key, root->left, root);

    } 
    else if (key > root->val) {
        insert(key, root->right, root);
    }
    else return;

    
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    root->parent = parent;
    root->level = getLevel(parent) + 1;
    int balance = getHeight(root->left) - getHeight(root->right);
    
    root->isHighLight = -1;
    addStep(this->root,2);  
    root->isHighLight = 0;

    if(abs(balance) >= 2) {
        root->isHighLight = -1;
        addStep(this->root,4);  
        root->isHighLight = 0;
        if(balance > 1) {
    
            if(key < root->left->val) {
                root->isHighLight = -1;
                addStep(this->root,5,1);  
                root->isHighLight = 0;
                RightRotate(root);
            }
            else {
                root->isHighLight = -1;
                addStep(this->root,6,1);  
                root->isHighLight = 0;
                LeftRotate(root->left);
                RightRotate(root);
        
            }
        }
        else {
            if(key > root->right->val) {
                root->isHighLight = -1;
                addStep(this->root,7,1);  
                root->isHighLight = 0;
                LeftRotate(root);
            }
            else {
                root->isHighLight = -1;
                addStep(this->root,8,1);  
                root->isHighLight = 0;
                RightRotate(root->right);
                LeftRotate(root);
            }
        } 
    }
    else {
        root->isHighLight = -1;
        addStep(this->root,3);  
        root->isHighLight = 0;
        return;
    }
    
    root->isHighLight = -1;
    addStep(this->root,9);  
    root->isHighLight = 0;

}

void AVL::drawStep(AVLpaint a, int Found) {

    lineHeight = 30;
    
    Color highlightColor = Color{255, 222, 89, 255};
    Color textColor = MyColor4;
    
    Vector2 maxWidth = {0,0};
    if(currentOperation != Operation::Algorithm) {
        
        for(const auto& line : pseudocode) {
            Vector2 lineWidth = MeasureTextEx(FONT, line.c_str(), 20, 3);
            if(lineWidth.x > maxWidth.x) maxWidth = lineWidth;
        }
        textWidth = maxWidth.x;
        for(size_t i = 0; i < pseudocode.size(); ++i) {
            // Vẽ highlight cho toàn bộ chiều rộng
            if(a.curCode == i) {
                DrawRectangleRounded(
                    Rectangle{pseudocodeX - 10, pseudocodeY + i*lineHeight - 5, 
                             maxWidth.x + 20, lineHeight},
                    0.3f, 5, highlightColor);
            }
            
            // Vẽ chữ
            DrawTextEx(FONT, pseudocode[i].c_str(), 
                      {pseudocodeX, pseudocodeY + i*lineHeight}, 
                      20, 3, textColor);
        }
    }

    if(Found == 0) {
        a.noti();
    }

    BeginMode2D(camera);  
        DrawTree(a.root);
        EndMode2D();

}

void AVL::draw() {
    Page::draw();

    static float elapsedTime = 0.0f;
    const float stepDuration = 0.5f / animationSpeed;

    
    // if(IsKeyPressed(KEY_A)) {
    //     Vector2 k = GetMousePosition();
    //     auto t = root->Pos;
    //     root->Pos = k;
    //     BeginMode2D(camera);  
    //     DrawTree(root);
    //     EndMode2D();
        
    //     root->Pos = t;
    // }

    if(currentOperation == Operation::Create) {
        if (isCreating) {
            hasCreate = true;
            Create();
            
        }
        else {
            BeginMode2D(camera);  
            DrawTree(root);
            EndMode2D();
            isPlaying = false;
        }
    }
    else{
        if(hasCreate && isCreating == false){
            BeginMode2D(camera);  
            DrawTree(root);  
            EndMode2D();
            // isPlaying = false;
        }
    }
    if (currentOperation == Operation::Insert) {
        if (isInserting) {
            this->insert(lastInsertedKey, root);
            addStep(this->root);
            isInserting = false;
            isPlaying = true;
            elapsedTime = 0.0f;
            rotationStartTime = GetTime();
            isRotating = false;
        } else if (!steps.empty()) {
            if (cur >= 0 && cur < steps.size()) {
                // Xử lý animation xoay - chỉ khi đang playing (isPlaying)
                if (steps[cur].isRotating && isPlaying) {
                    if (!isRotating) {
                        // Bắt đầu animation xoay
                        isRotating = true;
                        rotationStartTime = GetTime();
                    }
    
                    float rotationProgress = (GetTime() - rotationStartTime) / stepDuration;
                    
                    if (rotationProgress < 1.0f) {
                        // Đang trong quá trình xoay
                        AVLpaint tmp;
                        tmp.copy(steps[cur].root);
                        tmp.isRotating = true;
                        
                        updateNodePositions(tmp.root, steps[cur+1].root, rotationProgress);
                        
                        drawStep(tmp);
                    } else {
                        // Kết thúc xoay, chuyển sang bước tiếp theo
                        isRotating = false;
                        cur++;
                        drawStep(steps[cur]);
                    }
                } 
                else {
                    // Vẽ bước hiện tại (không xoay hoặc không phải đang playing)
                    drawStep(steps[cur]);
                    
                    // Tự động chuyển bước nếu đang playing
                    if (isPlaying) {
                        elapsedTime += GetFrameTime();
                        if (elapsedTime >= stepDuration) {
                            if (cur < steps.size() - 1) {
                                cur++;
                                elapsedTime = 0.0f;
                            } else {
                                isPlaying = false;
                            }
                        }
                    }
                }
            }
        }
    }

    
    if (currentOperation == Operation::Update) {
        if (isUpdating) {
            Found = (this->Update(UpdateKey,newKey)) ? 1 : 0;
            if(!Found) {
                addStep(this->root, 2);
            }
            addStep(this->root);
            isUpdating = false;
            isPlaying = true;
            elapsedTime = 0.0f;
            rotationStartTime = GetTime();
            isRotating = false;
        } else if (!steps.empty()) {
            if (cur >= 0 && cur < steps.size()) {
                // Xử lý animation xoay - chỉ khi đang playing (isPlaying)
                if (steps[cur].isRotating && isPlaying) {
                    if (!isRotating) {
                        // Bắt đầu animation xoay
                        isRotating = true;
                        rotationStartTime = GetTime();
                    }
    
                    //Chia để tính tỷ lệ đến khi GetTime - rotationStart = stepDuration thì là 1 bước
                    float rotationProgress = (GetTime() - rotationStartTime) / stepDuration;
                    
                    if (rotationProgress < 1.0f) {
                        // Đang trong quá trình xoay
                        AVLpaint tmp;
                        tmp.copy(steps[cur].root);
                        tmp.isRotating = true;
                        
                        updateNodePositions(tmp.root, steps[cur+1].root, rotationProgress);
                        
                        // Xử lý riêng cho trường hợp delete
                        if (cur == steps.size()-2) {
                            drawStep(tmp, Found);
                        } else {
                            drawStep(tmp);
                        }
                    } else {
                        // Kết thúc xoay, chuyển sang bước tiếp theo
                        isRotating = false;
                        cur++;
                        if (cur == steps.size()-1) {
                            drawStep(steps[cur], Found);
                        } else {
                            drawStep(steps[cur]);
                        }
                    }
                } 
                else {
                    // Vẽ bước hiện tại (không xoay hoặc không phải đang playing)
                    if (cur == steps.size()-2) {
                        drawStep(steps[cur], Found);
                    } else {
                        drawStep(steps[cur]);
                    }
                    
                    // Tự động chuyển bước nếu đang playing
                    if (isPlaying) {
                        elapsedTime += GetFrameTime();
                        if (elapsedTime >= stepDuration) {
                            if (cur < steps.size() - 1) {
                                cur++;
                                elapsedTime = 0.0f;
                            } else {
                                isPlaying = false;
                            }
                        }
                    }
                }
            }
        }
    }

    
    if (currentOperation == Operation::Delete) {
        if (isDeleting) {
            Found = (this->deleteAVL(root, root->parent, DeleteKey)) ? 1 : 0;
            if(!Found) {
                addStep(this->root, 2);
            }
            addStep(this->root);
            isDeleting = false;
            isPlaying = true;
            elapsedTime = 0.0f;
            rotationStartTime = GetTime();
            isRotating = false;
        } else if (!steps.empty()) {
            if (cur >= 0 && cur < steps.size()) {
                // Xử lý animation xoay - chỉ khi đang playing (isPlaying)
                if (steps[cur].isRotating && isPlaying) {
                    if (!isRotating) {
                        // Bắt đầu animation xoay
                        isRotating = true;
                        rotationStartTime = GetTime();
                    }
    
                    //Chia để tính tỷ lệ đến khi GetTime - rotationStart = stepDuration thì là 1 bước
                    float rotationProgress = (GetTime() - rotationStartTime) / stepDuration;
                    
                    if (rotationProgress < 1.0f) {
                        // Đang trong quá trình xoay
                        AVLpaint tmp;
                        tmp.copy(steps[cur].root);
                        tmp.isRotating = true;
                        
                        updateNodePositions(tmp.root, steps[cur+1].root, rotationProgress);
                        
                        // Xử lý riêng cho trường hợp delete
                        if (cur == steps.size()-2) {
                            drawStep(tmp, Found);
                        } else {
                            drawStep(tmp);
                        }
                    } else {
                        // Kết thúc xoay, chuyển sang bước tiếp theo
                        isRotating = false;
                        cur++;
                        if (cur == steps.size()-1) {
                            drawStep(steps[cur], Found);
                        } else {
                            drawStep(steps[cur]);
                        }
                    }
                } 
                else {
                    // Vẽ bước hiện tại (không xoay hoặc không phải đang playing)
                    if (cur == steps.size()-2) {
                        drawStep(steps[cur], Found);
                    } else {
                        drawStep(steps[cur]);
                    }
                    
                    // Tự động chuyển bước nếu đang playing
                    if (isPlaying) {
                        elapsedTime += GetFrameTime();
                        if (elapsedTime >= stepDuration) {
                            if (cur < steps.size() - 1) {
                                cur++;
                                elapsedTime = 0.0f;
                            } else {
                                isPlaying = false;
                            }
                        }
                    }
                }
            }
        }
    }

    if (currentOperation == Operation::Search) {
        
        if (isSearching) {
            Found = (this->search(SearchKey, root)) ? 1 : 0;
            if(!Found) {
                addStep(this->root, 5);
            }
            addStep(this->root);
            isPlaying = true;
            isSearching = false;                 
            elapsedTime = 0.0f;      
            
        } else {
        
                if (!steps.empty()) {
                    if(cur >= 0 && cur< steps.size()) {
                        
                        if(cur == steps.size()-2) {
                            drawStep(steps[cur], Found);
                        }
                        else 
                            drawStep(steps[cur]);
                    }

    
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
                        drawStep(steps[cur-1]);         
                        isPlaying = false;
                    }
                }
        }
    }

    //RUN AT ONCE
    if(forward1.IsClicked() || forward2.IsClicked()){
        cur = steps.size() - 1;
        isPlaying = false;
    }
    if(backward1.IsClicked() || backward2.IsClicked()){
         cur = 0;
         isPlaying = false;
    }
}


void AVL::updateNodePositions(TreeNode* src, TreeNode* target, float progress) {
    if (!src || !target) return;
    stack<TreeNode*> nodeStack;
    nodeStack.push(src);
    
    while (!nodeStack.empty()) {
        TreeNode* current = nodeStack.top();
        nodeStack.pop();

        TreeNode* targetNode = findNode(target, current->val);
        if (targetNode) {
            current->Pos.x = current->Pos.x + progress * (targetNode->Pos.x - current->Pos.x);
            current->Pos.y = current->Pos.y + progress * (targetNode->Pos.y - current->Pos.y);
        }
        
        if (current->right) nodeStack.push(current->right);
        if (current->left) nodeStack.push(current->left);
    }
}


TreeNode* AVL::findNode(TreeNode* root, int val) {
    if (!root) return nullptr;
    if (root->val == val) return root;
    if (val < root->val) return findNode(root->left, val);
    return findNode(root->right, val);
}

void AVL::event() {

    Page::event();
   
    if(currentOperation == Operation::Create) {
        hasInsert = false;
        hasSearch = false;
        hasDelete = false;
        hasCreate = true;
        hasUpdate = false;
        cur = 0;
        BeginMode2D(camera);  
            DrawTree(root);  
            EndMode2D();
        steps.clear();
        
        addStep(root);
        if (textbox.nums.size() > 0) {
            textbox.nums.erase(textbox.nums.begin());
            DestroyRecursive(root);
            root = nullptr;
            createKeys = textbox.nums;
            textbox.nums.clear();
            textbox.inputText = {""};
            isCreating = true;
        }    
    }
    
    if(currentOperation == Operation::Insert) {
        if(!hasInsert) {
            hasInsert = true;
            hasSearch = false;
            hasDelete = false;
            hasUpdate = false;
            hasCreate = false;
            cur = 0;
            BeginMode2D(camera);  
            DrawTree(root);
            EndMode2D();
            steps.clear();
            addStep(this->root);
    
        }
        if(textbox.nums.size() > 0) {
            lastInsertedKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isInserting = true;
            textbox.inputText = {""};
        }   
        
    }
    if(currentOperation == Operation::Search) {
        if(!hasSearch) {
            hasInsert = false;
            hasSearch = true;
            hasDelete = false;
            hasUpdate = false;
            hasCreate = false;
            cur = 0;
            steps.clear();
            addStep(this->root);
        }
        if(textbox.nums.size() > 0) {
            SearchKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isSearching = true;
            textbox.inputText = {""};
        }
    }
    if(currentOperation == Operation::Delete) {
        if(!hasDelete) {
            hasInsert = false;
            hasSearch = false;
            hasDelete = true;
            hasCreate = false;
            hasUpdate = false;
            cur = 0;
            steps.clear();
            addStep(this->root);
        }
        if(textbox.nums.size() > 0) {
            DeleteKey = textbox.nums[0];
            textbox.nums.erase(textbox.nums.begin());
            isDeleting = true;
            textbox.inputText = {""};
        }
    }

    
    if(currentOperation == Operation::Update) {
        if(!hasUpdate) {
            hasInsert = false;
            hasSearch = false;
            hasDelete = false;
            hasCreate = false;
            hasUpdate = true;
            cur = 0;
            steps.clear();
            addStep(this->root);
        }
        if(textbox.nums.size() > 0) {
            UpdateKey = textbox.nums[0];
            newKey = textbox.nums[1];
            textbox.nums.clear();
            isUpdating = true;
            textbox.inputText = {""};
        }
    }

    static Operation lastOp = Operation::Algorithm;
    if(currentOperation != lastOp) {
        updatePseudocode(currentOperation);
        lastOp = currentOperation;
    }


    
    if (back1.IsClicked() || back2.IsClicked()) { 
        if (cur > 0) {
            cur--;
        }
        isPlaying = false; 
    } 
    else if (next1.IsClicked() || next2.IsClicked()) { 
        if (cur < steps.size() - 1) {
            cur++;
        }
        isPlaying = false; 
    }

    
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



void AVL::updatePseudocode(Operation op) {
    switch(op) {
        case Operation::Insert:
            pseudocode = {
                "AVL Insert(key):",
                "1. Perform standard BST insert",
                "3. Get balance factor (left - right)",
                "3. If balanced: Done",
                "4. If unbalanced:",
                "   a. Left-Left case: Right Rotate",
                "   b. Left-Right case: Left then Right",
                "   c. Right-Right case: Left Rotate",
                "   d. Right-Left case: Right then Left",
                "5. Balance the tree",
            };
            break;
            
        case Operation::Delete:
            pseudocode = {
                "AVL Delete(key):",
                "1. Search for the node to delete",
                "   a. If not found: return",
                "   b. If found: Go to step 2",
                "2. Delete the node",
                "   a. If node has two children:",
                "     i. Find successor (min in right)",
                "     ii. Replace and delete successor",
                "   b. Else: Delete node",
                "5. Rebalance the tree",
            };
            break;
            
        case Operation::Search:
            pseudocode = {
                "AVL Search: ",
                "1. While current node exists:",
                "   a. If key == current: found",
                "   b. If key < current: go left",
                "   c. Else: go right",
                "2. Return not found"
            };
            break;
            
        case Operation::Create:
            pseudocode = {
                "AVL Create:",
                "1. Initialize empty tree",
                "2. Generate random nodes",
                "3. For each node:",
                "   a. Insert with balancing",
                "4. Calculate positions for display"
            };
            break;
            
        default:
            pseudocode = {
                "AVL Tree Operations",
                "Select operation to view pseudocode"
            };
    }
}



void AVL::init() {
    Page::init();
    root = nullptr;
    
    rootPos= {screenWidth*0.6f, screenHeight*0.2f};           
     camera.target = rootPos;
    camera.offset = rootPos;
    steps.clear();

    isInserting = false;
    isSearching = false;
    isDeleting = false;
    isUpdating = false;
    isCreating = false;

    hasInsert = false;
    hasSearch = false;
    hasDelete = false;
    hasUpdate = false;
    hasCreate = false;
    cur = -1;
    curCode = -1;
    pseudocode = {};
     lineHeight = 30;
       
}

void AVL::DestroyRecursive(TreeNode* node)
{
    if(!node) return;
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
    float xOffset = (screenWidth*0.65) / pow(2, level + 1.75);
    float mul = 4.3;
    if(level > 3) {
        xOffset = (screenWidth*0.7) / pow(2, level + 1.75);
        mul = 4.7;
    }
    return {
        
        isLeft ? parentPos.x - mul * xOffset : parentPos.x + mul *xOffset,
        parentPos.y + 3.5f *radius  
    };
}


void AVL::CalculateAllPos(TreeNode* &root, TreeNode* parent, bool isLeft) {
    if(!root) return;

    if(parent) {
        root->Pos = calculateChildPos(parent->Pos, isLeft, parent->level + 1);
        root->level = parent->level + 1;
    }
    else {
        root->Pos = this->rootPos;
        root->level = 1;
    }

    
    CalculateAllPos(root->left, root, true);
    CalculateAllPos(root->right, root, false);
    
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
}

void AVL::RightRotate(TreeNode* &root) {
    if (!root || !root->left) return;
    Vector2 oldPos = root->Pos;
    int oldLevel = root->level;
    
    TreeNode* oldParent = root->parent;
    TreeNode *tmp = root->left;
    TreeNode *tmpRight = tmp->right;

    
    tmp->right = root;
    root->left = tmpRight;

    
    if (tmpRight) tmpRight->parent = root;  
    tmp->parent = oldParent;           
    root->parent = tmp;                   
    
    if (oldParent) {
        if (oldParent->left == root)
            oldParent->left = tmp;
        else if (oldParent->right == root)
            oldParent->right = tmp;
    }
    
    
    root = tmp;
    root->Pos = oldPos;
    root->level = oldLevel;

    
    
    if(root->left)
    root->left->height = 1 + max(getHeight(root->left->left), getHeight(root->left->right));
    if(root->right)
    root->right->height = 1 + max(getHeight(root->right->left), getHeight(root->right->right));
    
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    
    if(root->parent)
        CalculateAllPos(root, root->parent, root->val < root->parent->val);  
    else 
        CalculateAllPos(root, root->parent, true);  
    
}

void AVL::LeftRotate(TreeNode* &root) {
    if (!root || !root->right) return;

    Vector2 oldPos = root->Pos;
    int oldLevel = root->level;
    TreeNode* oldParent = root->parent;
    TreeNode *tmp = root->right;
    TreeNode *tmpLeft = tmp->left;

    
    tmp->left = root;
    root->right = tmpLeft;
    
    
    if (tmpLeft) tmpLeft->parent = root;  
    tmp->parent = oldParent;           
    root->parent = tmp;                   

    if (oldParent) {
        if (oldParent->left == root)
            oldParent->left = tmp;
        else if (oldParent->right == root)
            oldParent->right = tmp;
    }
    

    root = tmp;
    root->Pos = oldPos;
    root->level = oldLevel;
    
    
    if(root->left)
    root->left->height = 1 + max(getHeight(root->left->left), getHeight(root->left->right));
    if(root->right)
    root->right->height = 1 + max(getHeight(root->right->left), getHeight(root->right->right));
   
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    
    
    if(root->parent)
        CalculateAllPos(root, root->parent, root->val < root->parent->val);  
    else 
        CalculateAllPos(root, root->parent, true);  
    
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


void AVL::DrawTN(TreeNode *a){
    
    Vector2 center = a->Pos;
    int key = a->val;
    int choose = a->isHighLight;

    string s = to_string(key);
    if (choose == 1)
        DrawCircleV(center, radius, choose_color);
    if (choose ==-1)
        
        DrawCircleV(center, radius, visit_color);
    if (choose == 0)
        DrawCircleV(center, radius, WHITE);

    if (choose == 2)
        DrawCircleV(center, radius, YELLOW);

    DrawCircleV(center, radius - 9, MyColor2);
    DrawCircleV(center, radius - 10, MyColor2);

    int Fs = max(10, static_cast<int>(font_size-s.size()*3));
    
    int wNode =  MeasureTextEx(FONT, s.c_str(), Fs, 2).x;
    DrawTextEx(FONT, s.c_str(), {center.x - wNode / 2, center.y - Fs/2}, Fs, 2, text_color);
    
    
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

    arrow_color = MyColor1;
    DrawLineEx(start, arrowHead, 5, arrow_color);
    DrawLineEx(arrowHead, left, 3, arrow_color);
    DrawLineEx(arrowHead, right, 3, arrow_color);
}

void AVL::DrawTree(TreeNode* root) {
    if (!root) return;

    DrawTN(root);
    
    if (root->left) {
        DrawArrow(root->Pos, root->left->Pos);
        DrawTree(root->left);
    }
    if (root->right) {
        DrawArrow(root->Pos, root->right->Pos);
        DrawTree(root->right);
    }
}
void AVL::RANDOM_INPUT(){
   std::mt19937 rng(std::random_device{}());
    
    if(currentOperation == Operation::Create){
            textbox.reset();
        
            std::uniform_int_distribution<int> value(0, 999);
            std::uniform_int_distribution<int> valueSize(2, 11);
            int size = valueSize(rng);
            std::vector<int> Values;
            std::vector<std::string> lines;
            std::ostringstream ss;

            for (int i = 0; i < size; ++i) {
                int num = value(rng);
        
                while (find(Values.begin(), Values.end(), num) != Values.end()) {
                    num = value(rng);
                }
                Values.push_back(num);  
            }

         
            ss << size;
            lines.push_back(ss.str());
            ss.str("");  

          
            for (int i = 0; i < Values.size(); ++i) {
                ss << Values[i] << " ";
            }
            lines.push_back(ss.str());
            ss.str("");  
            
            textbox.inputText = lines;
            
    }
    else{
        Page::RANDOM_INPUT();
    }
}
void AVL::Create(){
     if (!createKeys.empty()) {
         this->insert(createKeys.front(), root);
        createKeys.erase(createKeys.begin());
    }
    if (createKeys.empty()) {
        isCreating = false;
            isPlaying = true;
    }
}

