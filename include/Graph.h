#pragma once
#include "Page.h"
class GraphPage : public Page{
    public:


    void init() override;
    void draw() override;
    void event() override;
};