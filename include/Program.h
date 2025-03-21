#pragma once
#include <raylib.h>
#include "Variables.h"
#include "Menu.h"
#include "Page.h"
#include "LinkedList.h"
#include "HashTB.h"
class Program
{
public:
    Menu menu;
    Page page;
    LinkedList LL;
    Program();
    void run();

    void init();
    void draw();
    void event();
};