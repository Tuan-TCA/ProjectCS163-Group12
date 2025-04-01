#pragma once
#include <vector>
#include <queue>
#include "Vertex.h"
#include "Edge.h"
#include "Page.h"
#include "Variables.h"
using namespace std;

enum class Algorithm{
    BFS,
    MST
};

class Graph : public Page{
    public:
    Algorithm currentALgorithm;
    vector<string> AlgorithmOptions = {"BFS", "MST"};
    int selectedAlgorithmIndex; 
    Button AlgorithmOptionButton; 
    Button AlgorithmPrevButton; 
    Button AlgorithmNextButton;

    bool added;
    vector<Vertex> vertex;
    vector<Edge> edge;
    vector<vector<int>> matrix;
    Button MSTbutton;
    float minDistance;
    vector<vector<Drawable*>> arrayQueue;
    vector<string> pseudocode;
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
    void reset() override;

    void startAnimation( float duration);
    void handleChoice();
    Vertex* findVertex(int value);
    Edge* findEdge(Vertex* v1, Vertex* v2);
    void addFromMatrix();

    void resetAnimation();
    void handleCollision();
    void addFromTextbox();
    void FILE_INPUT() override;
    void RANDOM_INPUT() override; 
    void HandleInput();
};
