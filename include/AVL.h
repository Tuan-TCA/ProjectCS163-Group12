#pragma once
#include <string>
#include <math.h>
#include <iostream>
using namespace std;
#include <raylib.h>
#include "Variables.h"
#include "Page.h"
#include "ControlAnimation.h"

class TreeNode {
public:
    int val;
    TreeNode *left, *right;
    int height;
    int level;
    int isHighLight;
    Vector2 Pos;

    TreeNode(int key, TreeNode *leftNode, TreeNode *rightNode, Vector2 pos, int lev ) {
        val = key;
        left = leftNode;
        right = rightNode;
        height = 1;
        level = lev;
        Pos = pos;
    }

    TreeNode(int key) {
        val = key;
        left = right = nullptr;
        height = 1;
        level = 1;
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
    void RightRotate(TreeNode* &root);
    void LeftRotate(TreeNode* &root);
    void CalculateAllPos(TreeNode* &root, TreeNode* parent, bool isLeft);
    
    //Animation
    vector<AVL> steps;
    void addStep(AVL a);
    vector<TreeNode* > hightlightNodes;
    bool isNodeHighlighted(int key);

    //Draw
    void DrawTN(Vector2 center, int key, int choose);
    void DrawArrow(Vector2 start, Vector2 end);
    void DrawTree(TreeNode* root);


    //Page control
    ControlAnimation animationController;
    bool isInserting;
    int lastInsertedKey;

    bool isSearching;
    int SearchKey;

    bool isDeleting;
    int DeleteKey;

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


    AVL& operator=(const AVL& other) {
        if (this == &other) return *this; // Kiểm tra tự gán
    
        // Xóa cây hiện tại để tránh rò rỉ bộ nhớ
        DestroyRecursive(root);
    
        // Sao chép dữ liệu cơ bản
        root = copyTree(other.root);
        workplace = other.workplace;
        rootPos = other.rootPos;
        hasFinishedOnce = other.hasFinishedOnce;
        steps = other.steps;
        hightlightNodes = other.hightlightNodes;
        isInserting = other.isInserting;
        lastInsertedKey = other.lastInsertedKey;
        isSearching = other.isSearching;
        SearchKey = other.SearchKey;
        isDeleting = other.isDeleting;
        DeleteKey = other.DeleteKey;
        isUpdating = other.isUpdating;
        UpdateKey = other.UpdateKey;
        newVal = other.newVal;
    
        return *this;
    }
    
    TreeNode* copyTree(TreeNode* root) {
        if (!root) return nullptr;
        TreeNode* newNode = new TreeNode(root->val, nullptr, nullptr, root->Pos, root->level);
        newNode->left = copyTree(root->left);
        newNode->right = copyTree(root->right);
        newNode->height = root->height;
        return newNode;
    }
    
};
