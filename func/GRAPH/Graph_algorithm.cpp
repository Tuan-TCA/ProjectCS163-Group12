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
        if(!textbox.nums.empty()){ // Or get from textbox
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
       v->targetColor = ORANGE;
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
                        e->targetColor = ORANGE; // set edge's color
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
         if (!AlgoCalled) {
            bfs(clickedV);
            startAnimation(1);
            arrayQueue[currentQueueIndex][0]->startAnimation(ORANGE, 1);
            AlgoCalled = true;
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
        AlgoCalled = false;
        
    } 
    
}

//Kruskal's
void Graph::mst(){

    //sort lai edge inorder
    int n = vertex.size();
    dsu.parent.clear();
    dsu.init(n + 1);
    sort(edge.begin(), edge.end(), [](Edge & x, Edge & y) {
        return x.w < y.w;
    });
    
    StepQueue.push_back({0});
    arrayQueue.push_back({});
    
    vector<bool> AnimatedVertex(n + 1, false);
    for(auto& e: edge){
        int v1 = e.start->value, v2 = e.end->value;
        Vertex* v1Ptr = findVertex(v1);
        Vertex* v2Ptr = findVertex(v2);
        v1Ptr->targetColor = ORANGE;
        v2Ptr->targetColor = ORANGE;
        if (v1Ptr == nullptr || v2Ptr == nullptr) {
            continue;
        }

         if (!dsu.join(v1, v2)){ // cannot be unioned
            // e.targetColor = GRAY;
            e.targetColor = Color{176, 232, 197, 0};
            e.kind_ani = 1;
            StepQueue.push_back({5});
            arrayQueue.push_back({&e});
             continue;
         }
            e.targetColor = ORANGE;
        if(!AnimatedVertex[v1] && !AnimatedVertex[v2]){
            AnimatedVertex[v1] = true;
            AnimatedVertex[v2] = true;
            StepQueue.push_back({3});
            arrayQueue.push_back({v1Ptr});

            StepQueue.push_back({3});
            StepQueue.push_back({4});
            arrayQueue.push_back({&e});
            arrayQueue.push_back({v2Ptr});
            
        }
        else if(AnimatedVertex[v1] && AnimatedVertex[v2]){
            StepQueue.push_back({4});
            arrayQueue.push_back({&e});
        }
        else {
            if(!AnimatedVertex[v1] && AnimatedVertex[v2]){ // dam bao animation luon start tu v1
            swap(e.start, e.end);
            swap(v1Ptr, v2Ptr);
            swap(v1, v2);
            
            }
            
            StepQueue.push_back({3});
            StepQueue.push_back({4});
            arrayQueue.push_back({&e});
            arrayQueue.push_back({v2Ptr});
            AnimatedVertex[v2] = true;
        }
            
    }
    StepQueue.push_back({6});
    arrayQueue.push_back({});
}

void Graph::handleMST(){
    float deltaTime = GetFrameTime();
    if(AlgorithmOptionButton.IsClicked() || Ok.IsClicked()){
        isAnimating = true;
        isPlaying = true;
    }

    if( isAnimating){
        if (!AlgoCalled) {
            mst();
            startAnimation(1);
            if (!arrayQueue.empty() && !arrayQueue[0].empty()) {
                arrayQueue[currentQueueIndex][0]->startAnimation(ORANGE, 1);
            }
            AlgoCalled = true;
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
                else if(currentQueueIndex >= arrayQueue.size() - 1){ 
                    isPlaying = false;
                    
                }
            }
        }
        else isAnimating = false;
    }
    else{
        AlgoCalled = false;
    }
}

//Connected Components

void Graph::bfsComponents(Vertex* source, Color CC_COLOR, unordered_set<Vertex*>& visitedVertices){
    int n = matrix.size();
    if (n == 0) return;
    
    
    queue<Vertex*> q;
  
    unordered_set<Edge*> visitedEdge;
    source->targetColor = CC_COLOR;
    q.push(source);  // Start with the source vertex 
    arrayQueue.push_back({source});
    //Mark as visited nhe
    visitedVertices.insert(source);

    

    while (!q.empty()) {
       
        Vertex* v = q.front();
       v->targetColor = CC_COLOR;
        // v->print();
        q.pop();
        vector<Vertex*> vertexStorage;
        vector<Edge*> edgeStorage;
        
        for (int i = 0; i < n; i++) {
            if (matrix[v->value][i] != 0) {
                Vertex* nextVertex = findVertex(i);
                if(nextVertex == nullptr) continue;
                if ( visitedVertices.find(nextVertex) == visitedVertices.end()) { 
                    Edge* e = findEdge(nextVertex, v);
                    if (e != nullptr && visitedEdge.find(e) == visitedEdge.end()){
                        edgeStorage.push_back(e);
                        e->targetColor = CC_COLOR; // set edge's color
                        visitedEdge.insert(e);
                    }
                    q.push(nextVertex);
                
                    vertexStorage.push_back(nextVertex);
                    visitedVertices.insert(nextVertex);
                }
                else{
                    //neu vertex da visited
                    Edge* e = findEdge(nextVertex, v);
                    if(e && visitedEdge.find(e) == visitedEdge.end()){
                        edgeStorage.push_back(e);
                        e->targetColor = CC_COLOR;
                        
                        visitedEdge.insert(e);
                    }
                    
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
}

void Graph::findConnectedComponents(){
    unordered_set<Vertex*> visited;
    vector<Color> colors = {ORANGE, RED, GREEN, BLUE, YELLOW, PURPLE, PINK, SKYBLUE, LIME, MAGENTA, RAYWHITE, DARKGREEN, DARKPURPLE, DARKBROWN}; // Nhiều màu hơn
    int colorIndex = 0;

    for (auto& v : vertex) {
        if (!visited.count(&v)) {
            bfsComponents(&v, colors[colorIndex % colors.size()], visited);
            colorIndex++;
        }
    }
}

void Graph::handleCC(){
     float deltaTime = GetFrameTime();
     if(AlgorithmOptionButton.IsClicked() || Ok.IsClicked()){
        isAnimating = true;
        isPlaying = true;
    }
    
    if( isAnimating){
         if (!AlgoCalled) {
            findConnectedComponents();
            startAnimation(1);
            arrayQueue[currentQueueIndex][0]->startAnimation(ORANGE, 1);
            AlgoCalled = true;
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
        AlgoCalled = false;   
    } 
}