#include "Graph.h"
#include <unordered_set>

Edge* Graph::findEdge(Vertex* v1, Vertex* v2){
    for(auto& e: edge){
        if((e.start == v1 && e.end == v2) ) return &e;
         else if (e.start == v2 && e.end == v1) {
            swap(e.start, e.end);
             return &e;
        }
    }
    return nullptr;
}
Vertex* Graph::getFirstVertexClicked(){
    for(auto& v: vertex){
        if(v.isClicked()) {
            got1stV = true;
            isAnimating = true;
            isPlaying = true;
            return &v;
        } 
    }
    return nullptr;
}

Vertex* Graph::findVertex(int value){
    for(auto& v: vertex){
        if(v.value == value) return &v;
    }
    return nullptr;
}
void Graph::handleBFS(){
    float deltaTime = GetFrameTime();
     if(!got1stV){
        clickedV = getFirstVertexClicked();
    }
    
    if( isAnimating && clickedV){
         if (!bfsCalled) {
            bfs(clickedV);
            startAnimation(1);
            arrayQueue[currentIndex][0]->startAnimation(ORANGE, 1);
            bfsCalled = true;
        }
            if (!arrayQueue.empty() && currentIndex < arrayQueue.size()) {
            
            vector<Drawable*> current = arrayQueue[currentIndex];
 
            int checkDoneAnimating = 0;
            for(int i = 0; i < current.size(); i++){
                if (!current[i]->isAnimating) { // done or hasn't started yet
                checkDoneAnimating++;      
                }
               
                   if(isPlaying) current[i]->Update(deltaTime);
            }
            if(checkDoneAnimating == current.size()) {
                if(!arrayQueue.empty() && currentIndex + 1 < arrayQueue.size()){
                        current = arrayQueue[++currentIndex];
                        for(auto& elem: current){
                            elem->startAnimation(ORANGE, 1);
                        }

                    }
                    else if(currentIndex >= arrayQueue.size()){
                        isPlaying = false;
                    }
            }
        }
        else{
            isAnimating = false;
        }
    }
    else {
        bfsCalled = false;
        
    } 
    
}


void Graph::bfs(Vertex* source) {
    // cout << "bfs\n";
    int n = matrix.size();
    if (n == 0) return;
    arrayQueue.clear();
    
    
    queue<Vertex*> q;
    unordered_set<Edge*> visitedEdge;
    unordered_set<Vertex*> visitedVertices; 

    q.push(source);  // Start with the source vertex which one we've just clicked on
    visitedVertices.insert(source);
    arrayQueue.push_back({source});
    
    while (!q.empty()) {
        Vertex* v = q.front();
        
        // v->print();
        q.pop();
        vector<Vertex*> vertexStorage;
        vector<Edge*> edgeStorage;
        for (int i = 0; i < n; i++) {
            if (matrix[v->value][i] != 0) {
                Vertex* nextVertex = findVertex(i);
                if (nextVertex != nullptr && visitedVertices.find(nextVertex) == visitedVertices.end()) { 
                    Edge* e = findEdge(v, nextVertex);
                    if (e != nullptr && visitedEdge.find(e) == visitedEdge.end()){
                        edgeStorage.push_back(e);
                        visitedEdge.insert(e);
                        // e->print();
                        // cout << "yes\n"; 
                    }
                    q.push(nextVertex);
                    vertexStorage.push_back(nextVertex);
                    visitedVertices.insert(nextVertex);
                }
            }
        }
        vector<Drawable*> drawableVertexStorage;
            for (auto& v : vertexStorage) {
                drawableVertexStorage.push_back(static_cast<Drawable*>(v)); // ép kiểu Vertex* thành Drawable*
            }
        vector<Drawable*> drawableEdgeStorage;
            for (auto& e : edgeStorage) {
                drawableEdgeStorage.push_back(static_cast<Drawable*>(e)); 
            }
        if (!drawableEdgeStorage.empty()) {
            arrayQueue.push_back(drawableEdgeStorage);
        }
        if (!drawableVertexStorage.empty()) {
            arrayQueue.push_back(drawableVertexStorage);
        }
        
    }
    int i = 0;
    for (auto& elem : arrayQueue) {
        cout << "Index " << i++ << endl;
        for(auto& s: elem) s->print();
    }
}


