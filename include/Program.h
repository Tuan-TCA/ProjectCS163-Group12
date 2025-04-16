#pragma once
#include "Variables.h"
#include "Menu.h"
#include "Page.h"
#include "LinkedList.h"
#include "HashTB.h"
#include "Graph.h"
#include "AVL.h"
class Program
{
public:
    Menu menu;
    Page page;
    LinkedList LL;
    Graph graph;
    HashTB hashtable;
    AVL avl;
    Program();
    void run();

    void init();
    void draw();
    void event();
};