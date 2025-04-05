#pragma once
#include <vector>
#include <queue>
#include <unordered_set>
#include "Vertex.h"
#include "Edge.h"
#include "Page.h"
#include "Variables.h"
using namespace std;

enum class Algorithm{
    BFS,
    DFS,
    MST,
    CC
};
struct Dsu {
    vector<int> parent;

    void init(int n) {
        parent.resize(n + 5, 0);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }

    bool join(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return false;
        parent[v] = u;
        return true;
    }
};

class Graph : public Page{
    public:
    Algorithm currentALgorithm;
    vector<string> AlgorithmOptions = {"BFS", "MST", "DFS", "Connected\nComponents"};
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
    int currentStep = 0;
    vector<vector<int>> StepQueue;
    float duration;
    bool isAnimating;
    int currentQueueIndex;


    //bfs
    bool got1stV;
    bool AlgoCalled = false;
    Vertex* clickedV = nullptr;
    Vertex* getFirstVertexClicked();
    void bfs(Vertex* source);
    void handleBFS();
    //Kruskal
    Dsu dsu;
    void mst();
    void handleMST();

    //ConnectedComponents
    void bfsComponents(Vertex* source, Color CC_COLOR, unordered_set<Vertex*>& visitedVertices);
    void findConnectedComponents();
    void handleCC();


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
    void updateSide() override;
};
