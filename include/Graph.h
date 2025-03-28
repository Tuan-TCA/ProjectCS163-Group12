#pragma once
#include "Page.h"
#include "Variables.h"
#include <vector>
#include <queue>
#include "Vertex.h"
#include "Edge.h"
#include "ControlAnimation.h"
using namespace std;
class Graph : public Page{
    public:
    bool added;
    vector<Vertex> vertex;
    vector<Edge> edge;
    vector<vector<int>> matrix;
    Button MSTbutton;
    float minDistance;
    vector<vector<Drawable*>> arrayQueue;
    float duration;
    bool isAnimating;
    bool got1stV;
    bool bfsCalled = false;
    Vertex* clickedV = nullptr;
    int currentIndex;

    void init() override;
    void draw() override;
    void event() override;
    void update();
    void handleInput() override;
    
    void startAnimation( float duration);
    void bfs(Vertex* source);
    void handleBFS();
    Vertex* getFirstVertexClicked();
    Vertex* findVertex(int value);
    Edge* findEdge(Vertex* v1, Vertex* v2);
    void addFromMatrix();
    void reset();
    void handleCollision();
};