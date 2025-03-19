#pragma once
#include <raylib.h>
#include <bits/stdc++.h>
#include "Variables.h"
#include "Menu.h"
#include "LinkedList.h"
#include "HashTB.h"
class Program
{
public:
    Menu menu;
    Page page;
    LinkedList A;
    Program();
    void run();

    void draw();
    void event();
};