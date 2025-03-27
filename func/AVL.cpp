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

Vector2 AVL::calculateChildPos(Vector2 parentPos, bool isLeft, int level) {
    float xOffset = workplace.width / pow(2, level + 2);
    return {
        isLeft ? parentPos.x - 3.5*xOffset : parentPos.x + 3.5*xOffset,
        parentPos.y + 3.5*radius  // Khoảng cách dọc giữa các mức
    };
}

void AVL::insert(int key, TreeNode*& root, TreeNode* parent, int level) {
    if (!root) {
        Vector2 pos;
        if (!parent) {
            pos = rootPos;  // Node gốc
        } else {
            bool isLeft = key < parent->val;
            pos = calculateChildPos(parent->Pos, isLeft, level);
        }
        
        root = new TreeNode(key, nullptr, nullptr, pos);
        return;
    }
    
    if (key < root->val) {
        insert(key, root->left, root, level + 1);
    } 
    else if (key > root->val) {
        insert(key, root->right, root, level + 1);
    }
    // Bỏ qua nếu key đã tồn tại
}


void AVL::DrawTN(Vector2 center, int key, int choose){
    string s = to_string(key);

    if (choose == 1)
        DrawCircleV(center, radius, choose_color);
    if (choose == -1)
        //cout << center.x << ' ' << key << '\n';
        DrawCircleV(center, radius, visit_color);
    if (choose == 0)
        DrawCircleV(center, radius, RED);

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

    DrawTN(root->Pos, root->val, 0);
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



void AVL::draw() {
    Page::draw();

    static float elapsedTime = 0.0f; 
    const float stepDuration = 0.5f/animationSpeed;

    if (currentOperation == Operation::Insert) {
        if (isInserting) {
            animationController.Reset();         
            this->insert(lastInsertedKey,root);         
            DrawTree(root);
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


}


void AVL::init() {
    Page::init();
    root = nullptr;
    workplace = {screenWidth*0.24f,screenHeight*0.2f,(float) screenWidth *(1-0.24f),screenHeight*(1-0.095f)};
    rootPos= {workplace.x + workplace.width / 2, workplace.y};      
    int a[]={8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15, 16};
    for (int i = 0; i < 16; i++)
    {
        this->insert(a[i],root);
    }
    
    isInserting = false;
    isSearching = false;
    isDeleting = false;
    isUpdating = false;
       
}