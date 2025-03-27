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
    Vector2 Pos;

    TreeNode(int key, TreeNode *leftNode, TreeNode *rightNode, Vector2 pos) {
        val = key;
        left = leftNode;
        right = rightNode;
        height = 1;
        Pos = pos;
    }

    TreeNode(int key) {
        val = key;
        left = right = nullptr;
        height = 1;
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
   
        // Biến kiểm soát hiệu ứng chèn
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


    void DestroyRecursive(TreeNode* node);
    int getHeight(TreeNode *root);
    Vector2 calculateChildPos(Vector2 parentPos, bool isLeft, int level);
    void insert(int key, TreeNode*& root, TreeNode* parent = nullptr, int level = 1);
    void DrawTN(Vector2 center, int key, int choose);
    void DrawArrow(Vector2 start, Vector2 end);
    void DrawTree(TreeNode* root);
    void event() override;
    void init() override;
    void draw() override;


};
