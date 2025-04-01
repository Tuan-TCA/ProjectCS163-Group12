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
        if(v.isClicked()) { //We can click on specific vertex to start animating
            got1stV = true;
            isAnimating = true;
            isPlaying = true;
            return &v;
        } 
        if(textbox.nums.size() > 0){ // Or get from textbox
            int value = textbox.nums[0];
            cout << value << endl;
            textbox.nums.erase(textbox.nums.begin());
            if(v.value == value){
                got1stV = true;
                isAnimating = true;
                isPlaying = true;
                return &v;
            }
        }
        if (AlgorithmOptionButton.IsClicked()){ //or click directly on the button(randomly pick any vertex)
            int value = rand()% (vertex.size() - 1);
            if(v.value == value){
                got1stV = true;
                isAnimating = true;
                isPlaying = true;
                return &v;
            }
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



// BREADTH FIRST SEARCH
void Graph::bfs(Vertex* source) {
    // cout << "bfs\n";
    int n = matrix.size();
    if (n == 0) return;
    arrayQueue.clear();
    
    
    queue<Vertex*> q;
  
    unordered_set<Edge*> visitedEdge;
    unordered_set<Vertex*> visitedVertices; 

    q.push(source);  // Start with the source vertex which one we've just clicked on
    arrayQueue.push_back({source});
    StepQueue.push_back({1, 2});
    //Mark as visited nhe
    visitedVertices.insert(source);

    

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
            StepQueue.push_back({2});
        }
        if (!drawableVertexStorage.empty()) {
            arrayQueue.push_back(drawableVertexStorage);
            StepQueue.push_back({3});
        }

        
    }
    int i = 0;
    for (auto& elem : arrayQueue) {
        cout << "Index " << i++ << endl;
        for(auto& s: elem) s->print();
    }
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
            arrayQueue[currentQueueIndex][0]->startAnimation(ORANGE, 1);
            bfsCalled = true;
        }
            if (!arrayQueue.empty() && currentQueueIndex < arrayQueue.size()) {
            
            vector<Drawable*> current = arrayQueue[currentQueueIndex];
 
            int checkDoneAnimating = 0;
            for(int i = 0; i < current.size(); i++){
                if (!current[i]->isAnimating) { // done or hasn't started yet
                checkDoneAnimating++;      
                }
               
                if(isPlaying) current[i]->Update(deltaTime);
            }
            if(checkDoneAnimating == current.size()) {
                if(!arrayQueue.empty() && currentQueueIndex + 1 < arrayQueue.size()){
                        
                        current = arrayQueue[++currentQueueIndex];
                        for(auto& elem: current){
                            elem->startAnimation(ORANGE, 1);
                        }

                    }
                else if(currentQueueIndex >= arrayQueue.size()){
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



