#pragma once
#include <string>
#include <math.h>
#include <iostream>
#include <random>
using namespace std;
#include <raylib.h>
#include "Variables.h"
#include "Page.h"
#include "ControlAnimation.h"

class TreeNode {
public:
    int val;
    TreeNode *left, *right, *parent;
    int height;
    int level;
    // 1=green, -1=red, 0=White
    int isHighLight = 0;
    Vector2 Pos;

    TreeNode(int key, TreeNode *leftNode, TreeNode *rightNode, TreeNode* par, 
        Vector2 pos, int heig, int lev, int isHigh ) {
        val = key;
        left = leftNode;
        right = rightNode;
        height = heig;
        level = lev;
        Pos = pos;
        isHighLight = isHigh;
        parent = par;
    }

    TreeNode(int key) {
        val = key;
        left = right = nullptr;
        height = 1;
        level = 1;
        Pos = {600,600};
        parent = nullptr;
    }

    void absorb(TreeNode* tmp) {
        if(!tmp) return;
        this->val = tmp->val;
        tmp->level = this->level;
        tmp->Pos = this->Pos;
        
    }

};


class AVLpaint {
    public:
    TreeNode *root;
    Rectangle workplace = {screenWidth*0.24f,screenHeight*0.2f,(float) screenWidth *(1-0.24f),screenHeight*(1-0.095f)};
    Vector2 rootPos= {workplace.x + workplace.width / 2, workplace.y};      
    const int radius = 40;
    const int font_size = 30;
    const int spacing = 50;
    const Color choose_color = { 0, 128, 0, 128 };//green
    const Color visit_color = RED;//red
    const Color ring = MyColor2;
    const Color circle = MyColor2;
    const Color text_color = WHITE;
    const float arrow_size = 15.0;
    const Color arrow_color = MyColor1;
    AVLpaint() {
        root = nullptr;
        rootPos = {600,500};
    }
                      
    int textW = MeasureText("NOT FOUND", font_size*2); 
    int posX = 800;
    int posY = 800;
    void noti() {
        DrawText("NOT FOUND", posX, posY, font_size*2, RED);
    }

    
    
    TreeNode* copyTree(TreeNode* root) {
        if (!root) return nullptr;
        TreeNode* newNode = new TreeNode(root->val, root->left, root->right, root->parent,root->Pos, root->height, root->level, root->isHighLight);
        newNode->left = copyTree(root->left);

        newNode->right = copyTree(root->right);
        newNode->parent = root->parent;
        newNode->height = root->height;
        newNode->level = root->level;
        newNode->isHighLight = root->isHighLight;
        return newNode;
    }

    void copy(TreeNode *a) {
        this->root = copyTree(a);
    }

};


class AVL : public Page{
public:
    TreeNode *root;
    Rectangle workplace;
    Vector2 rootPos;
    

    bool hasFinishedOnce = false;
    const int radius = 40;
    const int font_size = 30;
    const int spacing = 50;
    const Color choose_color = { 0, 128, 0, 128 };//green
    const Color visit_color = RED;//red
    const Color ring = MyColor2;
    const Color circle = MyColor2;
    const Color text_color = WHITE;
    const float arrow_size = 15.0;
    const Color arrow_color = MyColor1;

    ~AVL();
   
    //Model
    void insert(int key, TreeNode*& root, TreeNode* parent = nullptr);
    bool search(int key, TreeNode*& root, TreeNode* parent = nullptr);
    bool deleteAVL(TreeNode* &root, TreeNode* &parent, int key);
    void balance(TreeNode * &root, TreeNode *& parent, int key);

    void RightRotate(TreeNode* &root);
    void LeftRotate(TreeNode* &root);
    void CalculateAllPos(TreeNode* &root, TreeNode* parent, bool isLeft);
    
    //Animation
    vector<AVLpaint> steps;
    void addStep(TreeNode*  root) {
        AVLpaint tmp;
        tmp.copy(root);
        steps.push_back(tmp);
    }
    int cur = -1; //Current Step

    void drawAnimation();
    void drawStep(AVLpaint a, int Found = -1);

    vector<TreeNode* > hightlightNodes;
    bool isNodeHighlighted(int key);

    //Draw
    void DrawTN(TreeNode *root);
    void DrawArrow(Vector2 start, Vector2 end);
    void DrawTree(TreeNode* root);


    //Page control
    ControlAnimation animationController;
    bool isInserting;
    bool hasInsert = false;
    int lastInsertedKey;

    bool isSearching;
    bool hasSearch = false;
    int SearchKey;
    int Found = -1;

    bool isDeleting;
    bool hasDelete = false;
    int DeleteKey;

    bool isCreating;
    bool hasCreate = false;


    bool isUpdating;
    int UpdateKey;
    int newVal;


    //Else
    void DestroyRecursive(TreeNode* node);
    int getHeight(TreeNode *root);
    int getLevel(TreeNode *root);
    Vector2 calculateChildPos(Vector2 parentPos, bool isLeft, int level);
    void swapPos(TreeNode *&a, TreeNode* &other);

    void event() override;
    void init() override;
    void draw() override;

    

};
