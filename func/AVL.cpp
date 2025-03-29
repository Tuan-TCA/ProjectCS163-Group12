#include "AVL.h"
#include "ControlAnimation.h"
#include <iostream>


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

void AVL::addStep(AVL a) {
    steps.push_back(a);
}
void AVL::insert(int key, TreeNode*& root, TreeNode* parent) {
    if (!root) {
        Vector2 pos;
        if (!parent) {
            pos = rootPos;
            root = new TreeNode(key, nullptr, nullptr, pos, 1);
        } else {
            bool isLeft = key < parent->val;
            pos = calculateChildPos(parent->Pos, isLeft, parent->level+1);
            root = new TreeNode(key, nullptr, nullptr, pos, parent->level + 1);
        }
        // Don't add step here yet
        cout<<"ok";
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
    
    // Recalculate all positions after any potential rotations
    //CalculateAllPos(this->root, nullptr, true);
    
    // Only add step after everything is complete
    //addStep(*this);
}


void AVL::RightRotate(TreeNode* &root) {
    if (!root || !root->left) return;  

    Vector2 oldPost = root->Pos;
    int oldLevel = root->level;
    TreeNode* tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    root = tmp;

    root->Pos = oldPost;
    root->level = oldLevel;

    // Cập nhật chiều cao
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    tmp->height = 1 + max(getHeight(tmp->left), getHeight(tmp->right));
    CalculateAllPos(root, nullptr, true);
}

void AVL::LeftRotate(TreeNode* &root) {
    if (!root || !root->right) return;  

    Vector2 oldPost = root->Pos;
    int oldLevel = root->level;

    TreeNode* tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    root = tmp;
    
    root->Pos = oldPost;
    root->level = oldLevel;

    // Cập nhật chiều cao
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    tmp->height = 1 + max(getHeight(tmp->left), getHeight(tmp->right));
    CalculateAllPos(root, nullptr, true);
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

//choose = 1 -> xanh, -1 -> do, 0 -> trang
void AVL::DrawTN(Vector2 center, int key, int choose){
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

        DrawTN(root->Pos, root->val,0);
    TraceLog(LOG_INFO, "Draw %d at (%f, %f)", root->val, root->Pos.x, root->Pos.y);
    if (root->left) {
        DrawArrow(root->Pos, root->left->Pos);
        DrawTree(root->left);
    }
    if (root->right) {
        DrawArrow(root->Pos, root->right->Pos);
        DrawTree(root->right);
    }
}



void AVL::draw() {
    Page::draw();

    static float elapsedTime = 0.0f; 
    const float stepDuration = 0.5f/animationSpeed;

    if (currentOperation == Operation::Insert) {
        if (isInserting) {
            //animationController.Reset();         
            this->insert(lastInsertedKey,root);         
            //DrawTree(root);
            isInserting = false;                 
            elapsedTime = 0.0f;                  
            hasFinishedOnce = false;        
        } else {
            // if (!animationController.steps.empty()) {
            //     if (animationController.currentStep < animationController.steps.size()) {
            //         animationController.steps[animationController.currentStep](); 
            //     }

            //     if (!animationController.IsPaused()) {
            //         elapsedTime += GetFrameTime(); 
            //         if (elapsedTime >= stepDuration && !animationController.IsFinished()) {
            //             animationController.NextStep();
            //             elapsedTime = 0.0f;            
            //             cout << animationController.currentStep << endl; 
            //         }
            //     }
            // }

            // if (animationController.IsFinished()) {
            //     DrawTree(root); 
            // }
            //cout<<steps.size()<<endl;
            DrawTree(root);
        }
    }
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

    if (back1.IsClicked() || back2.IsClicked()) {
        if (animationController.IsFinished()) {
            //Pos = finishedPos;
            hasFinishedOnce = false;
            isPlaying = false;
        }
        if (animationController.currentStep > 0) {
            animationController.isPaused = true;
            animationController.currentStep--; 
            if (!animationController.steps.empty()) {
                animationController.steps[animationController.currentStep]();
            }
        }
    } else if ((next1.IsClicked() || next2.IsClicked()) && animationController.currentStep < animationController.steps.size() - 1) {
        animationController.isPaused = true;
        animationController.currentStep++;
    }


    if (back1.IsClicked() || back2.IsClicked()) {
        if (!steps.empty() && animationController.currentStep > 0) {
            animationController.currentStep--;
            *this = steps[animationController.currentStep];  // Quay về trạng thái trước đó
        }
    }
    
    if (next1.IsClicked() || next2.IsClicked()) {
        if (animationController.currentStep < steps.size() - 1) {
            animationController.currentStep++;
            *this = steps[animationController.currentStep];  // Tiến lên trạng thái tiếp theo
        }
    }
    

}


void AVL::init() {
    Page::init();
    root = nullptr;
    workplace = {screenWidth*0.24f,screenHeight*0.2f,(float) screenWidth *(1-0.24f),screenHeight*(1-0.095f)};
    rootPos= {workplace.x + workplace.width / 2, workplace.y};      
    //int a[]={8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15, 16};  for (int i = 0; i < 16; i++) this->insert(a[i],root);
    
    isInserting = false;
    isSearching = false;
    isDeleting = false;
    isUpdating = false;
       
}