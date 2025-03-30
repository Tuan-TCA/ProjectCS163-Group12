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
    vector<string> pseudocode = {
        "BFS (G, s)",
        " while !Q.empty // Q is a normal queue",
        "   for each neighbor v of u = Q.front, Q.pop",
        "       if v is unvisited, tree edge, Q.push(v)",
    };
    int currentStep = 0;
    vector<vector<int>> StepQueue;
    float duration;
    bool isAnimating;
    int currentQueueIndex;


    //bfs
    bool got1stV;
    bool bfsCalled = false;
    Vertex* clickedV = nullptr;
    Vertex* getFirstVertexClicked();
    void bfs(Vertex* source);
    void handleBFS();

    void init() override;
    void draw() override;
    void event() override;
    void update();
    void handleInput() override;
    
    void startAnimation( float duration);

   
    Vertex* findVertex(int value);
    Edge* findEdge(Vertex* v1, Vertex* v2);
    void addFromMatrix();
    void reset();
    void handleCollision();
};