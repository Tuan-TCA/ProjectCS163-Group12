#include "AVL.h"
#include "ControlAnimation.h"
#include <iostream>
#include <vector>

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
    // Highlight for visualization
    
    if (root->val == key) {
        root->isHighLight = 1;
        addStep(this->root,3);
        root->isHighLight = 0;
        
        
        root->isHighLight = 1;
        addStep(this->root,4);
        root->isHighLight = 0;

        if (root->left && root->right) {
            root->isHighLight = -1;
            addStep(this->root,5);
            root->isHighLight = 0;

            TreeNode* successor = root->right;
            successor->isHighLight = 2;
            addStep(this->root,6);
            successor->isHighLight = 0;

            TreeNode* successorParent = root;
            
            while (successor && successor->left) {
                successorParent = successor;
                successor = successor->left;
                successor->isHighLight = 2;
                addStep(this->root,6);
                successor->isHighLight = 0;
            }

            


            // successor->isHighLight = 1;
            // addStep(this->root,6);
            // successor->isHighLight = 0;

            
            root->val = successor->val;
            deleteAVL(root->right, root,root->val);

            // TraceLog(LOG_INFO, "Replacing with successor value %d", successor->val);
            // if (successorParent->left == successor) {
            //     successorParent->left = successor->right;
            //     if (successor->right) 
            //         successor->right->parent = successorParent;
            // } else {
            //     successorParent->right = successor->right;
            //     if (successor->right) 
            //         successor->right->parent = successorParent;

            // }
            // delete successor;
            // successor = nullptr;
            
            // TreeNode* tmpSSparent = successorParent;
            // //cout<<successorParent->right->val<<"@@@"<<endl;
            
            // while(tmpSSparent != nullptr) {
            //     tmpSSparent->isHighLight = -1;
            //     addStep(this->root, 9);
            //     tmpSSparent->isHighLight = 0;

            //     balance(tmpSSparent, tmpSSparent->parent, key);
            //     tmpSSparent = tmpSSparent->parent;

            // }

            // root->isHighLight = -1;
            // addStep(this->root,7);
            // root->isHighLight = 0;

        }
        else {

            root->isHighLight = -1;
            addStep(this->root,8);
            root->isHighLight = 0;

            TreeNode* temp = root;
            if (root->left) {
                root = root->left;

            } else {
                root = root->right;
            }
            delete temp;
        }

        if (root) {
            CalculateAllPos(root, parent, parent && root == parent->left);
            balance(root, parent, key);
            root->isHighLight = -1;
            addStep(this->root,9);
            root->isHighLight = 0;
            TraceLog(LOG_INFO, "Root value after deletion %d", root->val);
        }
        return true;
    }

    bool deleted;
    if (key < root->val) {
        
        root->isHighLight = -1;
        addStep(this->root,1);
        root->isHighLight = 0;
        deleted = deleteAVL(root->left, root, key);
            
    } else {
        
        root->isHighLight = -1;
        addStep(this->root,1);
        root->isHighLight = 0;
        deleted = deleteAVL(root->right, root, key);
            
    }

    if (deleted) {
        CalculateAllPos(root, parent, parent && root == parent->left);
        balance(root, parent, key);

        
        root->isHighLight = -1;
        addStep(this->root,9);
        root->isHighLight = 0;
    }

    return deleted;
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
                addStep(this->root,5);  
                root->isHighLight = 0;
                RightRotate(root);
            }
            else {
                root->isHighLight = -1;
                addStep(this->root,6);  
                root->isHighLight = 0;
                LeftRotate(root->left);
                RightRotate(root);
        
            }
        }
        else {
            if(key > root->right->val) {
                root->isHighLight = -1;
                addStep(this->root,7);  
                root->isHighLight = 0;
                LeftRotate(root);
            }
            else {
                root->isHighLight = -1;
                addStep(this->root,8);  
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

     pseudocodeX = codeDisplayPLace.x  + 5;
    pseudocodeY = codeDisplayPLace.y  + 10;
    
    FONT = GetFontDefault();
    
    Color highlightColor = Color{255, 222, 89, 255};
    Color textColor = MyColor4;

    Vector2 maxWidth = {0 ,0};
    if(currentOperation != Operation::Algorithm) {
        // Tìm dòng dài nhất để làm kích thước chuẩn
        
        for(const auto& line : pseudocode) {
            Vector2 lineWidth = MeasureTextEx(FONT, line.c_str(), 20, 3);
            if(lineWidth.x > maxWidth.x) maxWidth = lineWidth;
        }
        textWidth = maxWidth.x ;

        for(size_t i = 0; i < pseudocode.size(); ++i) {
            // Vẽ highlight cho toàn bộ chiều rộng
            if(a.curCode == i) {
                DrawRectangleRounded(
                    Rectangle{pseudocodeX - 10, pseudocodeY + i*lineHeight - 5, 
                             maxWidth.x + 20, lineHeight}, // Dùng maxWidth thay vì textWidth
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

    DrawTree(a.root);

}

void AVL::draw() {
    Page::draw();

    static float elapsedTime = 0.0f;
    const float stepDuration = 0.5f / animationSpeed;

    
    if(IsKeyPressed(KEY_A)) {
        Vector2 k = GetMousePosition();
        auto t = root->Pos;
        root->Pos = k;
        DrawTree(root);
        root->Pos = t;
    }

    if(currentOperation == Operation::Create) {
        if (isCreating) {
            hasCreate = true;
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dist(2,11);
            uniform_int_distribution<int> dist2(100,999);

            int t = dist(gen);
            while(t--) {
                int k = dist2(gen);
                this->insert(k, root);
            }
            steps.clear();
            isCreating = false;
            isPlaying = true;
        }
        else {
            DrawTree(root);
            isPlaying = false;
        }
    }

    if (currentOperation == Operation::Insert) {
        if (isInserting) {

            this->insert(lastInsertedKey, root); // Thêm node và lưu các bước
            addStep(this->root);
            isInserting = false;
            isPlaying = true;
            elapsedTime = 0.0f;
        } else {
            if (!steps.empty()) {

                if(cur >= 0 && cur< steps.size()) {
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
        } else {
            if (!steps.empty()) {
                
                if (!steps.empty()) {
                    if(cur >= 0 && cur< steps.size()) {
                        
                        if(cur == steps.size()-2) 
                            drawStep(steps[cur], Found);
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
}



void AVL::event() {

    Page::event();
   
    if(currentOperation == Operation::Create) {
        hasInsert = false;
        hasSearch = false;
        hasDelete = false;
        hasCreate = true;
        if(Page::Ok.IsClicked()) {
            DestroyRecursive(root);
            root = nullptr;
            isCreating = true;
        }       
    }
    if(currentOperation == Operation::Insert) {
        if(!hasInsert) {
            hasInsert = true;
            hasSearch = false;
            hasDelete = false;
            hasCreate = false;
            cur = 0;
            DrawTree(root);
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
    
     if(currentOperation != Operation::Create){
        isClosingCodePlace = false;
        isExpandingCodePlace = true;
        animatingTime = 0;
    }
    else{
        isClosingCodePlace = true;
        isExpandingCodePlace = false;
        animatingTime = 0;
    }

    static Operation lastOp = Operation::Algorithm;
    if(currentOperation != lastOp) {
        updatePseudocode(currentOperation);
        lastOp = currentOperation;
    }

    if(!isPlaying){
        if(!switchState ? play1.IsClicked() : play2.IsClicked()){
            isPlaying = true;
            TraceLog(LOG_INFO, "is playing");
        }
    }
    else{
        if(!switchState ? pause1.IsClicked() : pause2.IsClicked())
        {
            isPlaying = false;
            TraceLog(LOG_INFO, "is pausing");
        }
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
    workplace = {screenWidth*0.24f,screenHeight*0.2f,(float) screenWidth *(1-0.24f),screenHeight*(1-0.095f)};
    rootPos= {workplace.x + workplace.width / 2 + 50, workplace.y};      
    
    steps.clear();

    isInserting = false;
    isSearching = false;
    isDeleting = false;
    isUpdating = false;
    isCreating = false;

    hasInsert = false;
    hasSearch = false;
    hasDelete = false;

    cur = -1;
    curCode = -1;
    pseudocode = {};
    lineHeight = 30;
}
void AVL::reset(){
    Page::reset();
        root = nullptr;
    workplace = {screenWidth*0.24f,screenHeight*0.2f,(float) screenWidth *(1-0.24f),screenHeight*(1-0.095f)};
    rootPos= {workplace.x + workplace.width / 2, workplace.y};      
    
    steps.clear();

    isInserting = false;
    isSearching = false;
    isDeleting = false;
    isUpdating = false;
    isCreating = false;

    hasInsert = false;
    hasSearch = false;
    hasDelete = false;

    cur = -1;
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
    float xOffset = 850 / pow(2, level + 2);
    return {
        isLeft ? parentPos.x - 4.2f * xOffset : parentPos.x + 4.2f *xOffset,
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
        root->Pos = rootPos;
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
    
    int wNode =  MeasureText(s.c_str(), Fs);
    DrawText(s.c_str(), center.x - wNode / 2, center.y - Fs/2, Fs, text_color);
    
    
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
    
    if (root->left) {
        DrawArrow(root->Pos, root->left->Pos);
        DrawTree(root->left);
    }
    if (root->right) {
        DrawArrow(root->Pos, root->right->Pos);
        DrawTree(root->right);
    }
}



