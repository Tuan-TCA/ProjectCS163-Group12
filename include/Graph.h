#pragma once
#include "Page.h"
#include "Variables.h"
#include <vector>
using namespace std;
class Graph : public Page{
    public:
    bool added;
    vector<Vertex> vertex;
    vector<Edge> edge;
    vector<vector<int>> matrix;
    Button MSTbutton;
    float minDistance;
    float animateSpeed;
    float duration;

    void init() override;
    void draw() override;
    void event() override;
    void handleInput() override;

    void addFromMatrix();
};