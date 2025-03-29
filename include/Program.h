#pragma once
#include <raylib.h>
#include <bits/stdc++.h>
#include "Variables.h"
#include "Menu.h"
#include "LinkedList.h"
#include "HashTB.h"
#include "drawutils.h"
class Program
{
public:
    Menu menu;
    Page page;
    LinkedList A;
    HashTableChaining *B = nullptr;
    Program();
    void run();

    void draw();
    void event();
};