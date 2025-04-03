#pragma once
#include <raylib.h>
#include "Variables.h"
#include "Menu.h"
#include "Page.h"
#include "LinkedList.h"
#include "HashTB.h"
#include "Graph.h"
class Program
{
public:
    Menu menu;
    Page page;
    LinkedList LL;
    Graph graph;
    HashTableChaining hashtable;
    Program();
    void run();

    void init();
    void draw();
    void event();
};