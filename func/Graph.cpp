#include "Graph.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include "Variables.h"
#include <algorithm>
#include "ControlAnimation.h"
#include <unordered_set>
using namespace std;

float distance(Vector2 pos1, Vector2 pos2){
    return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}
void Graph::init(){
    Page::init();
    MSTbutton =  Button(5, screenHeight / 2 - screenHeight*0.63f * 0.5f + 5, screenWidth*0.24f - 10, screenHeight*0.63f * 0.15f, "MST", MyColor1, Fade(MyColor1, 0.8f), WHITE); 
    added = false;
    minDistance = 100.0f;
    got1stV = false;
    isAnimating = false;
}

void Graph::draw(){
    Page::draw();


    for(auto& e: edge){
        // cout << "edge draw" << endl;
        e.Draw();
    }
        for(auto& v: vertex){
        v.Draw();
    }

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

void Graph::event(){
    Page::event();
    handleInput();
   if(!added){
        addFromMatrix(); 
       added = true;
   }

     
    for(auto& v: vertex){
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
            if(CheckCollisionPointCircle(GetMousePosition(), v.position, v.radius) || v.isPressing){
                v.position = GetMousePosition();
                v.isPressing = true;
            }
        }else{
            v.isPressing = false;
        }
    }

    if (back1.IsClicked() || back2.IsClicked()) {
        cout << "back\n";
        isPlaying = false;
        cout << "before back " << currentIndex << endl;
        if (!arrayQueue.empty() && currentIndex < arrayQueue.size()) {
            vector<Drawable*> current = arrayQueue[currentIndex];
            for (auto& elem : current) {
                elem->reset();
            }
            currentIndex--;
            if (currentIndex < 0) currentIndex = 0;
            if (currentIndex < arrayQueue.size()) {
                vector<Drawable*> prev = arrayQueue[currentIndex];
                for (auto& elem : prev) {
                    elem->reset();
                    elem->isAnimating = true; 
                }
            }
        }
        cout << "after back " << currentIndex << endl;
    } 
    else if (next1.IsClicked() || next2.IsClicked()) {
        cout << "next\n";
        isPlaying = false; 
        cout << "before next " << currentIndex << endl;
        if (!arrayQueue.empty() && currentIndex < arrayQueue.size()) {
            vector<Drawable*> current = arrayQueue[currentIndex];
            for (auto& elem : current) {
                elem->SetColor(ORANGE);
                elem->isAnimating = false;
            }
            currentIndex++;
            if (currentIndex > arrayQueue.size() - 1) currentIndex = arrayQueue.size() - 1;
            if (currentIndex < arrayQueue.size()) {
                vector<Drawable*> next = arrayQueue[currentIndex];
                for (auto& elem : next) {
                    elem->SetColor(ORANGE);
                    elem->isAnimating = false; // ready to be animating
                }
            }
        }
        cout << "after next " << currentIndex << endl;
    }
   handleBFS();
    // cout << currentIndex << endl
   
}

void Graph::startAnimation(float duration){
    this->duration = duration;
    currentIndex = 0;
}


Edge* Graph::findEdge(Vertex* v1, Vertex* v2){
    for(auto& e: edge){
        if((e.start == v1 && e.end == v2) || (e.start == v2 && e.end == v1)) return &e;
    }
    return nullptr;
}

Vertex* Graph::findVertex(int value){
    for(auto& v: vertex){
        if(v.value == value) return &v;
    }
    return nullptr;
}


void Graph::addFromMatrix(){
     srand(static_cast<unsigned int>(time(0) + rand()));
    int n = matrix.size();
    //random vertices in workplace 
    int minX = screenWidth * 0.3f, maxX = screenWidth - 100;  
    int minY = screenHeight * 0.2f, maxY = screenHeight * 0.8f;
    vertex.clear();
    vertex.resize(n);
    for(int i = 0; i < n; i++){
        Vertex vertex_;
        vertex_.value = i;
        float newPosX, newPosY;
        bool validPosition = false;
        while(!validPosition){
        newPosX = rand() % (maxX - minX + 1) + minX;
        newPosY = rand() %  (maxY - minY + 1) + minY;
        validPosition = true;
        for(int j = 0; j <= i;j++){
            if(distance({newPosX, newPosY}, vertex[j].position) < minDistance){
                validPosition = false;
                break;
            }
        }
        }
        vertex_.position.x =  newPosX;
        vertex_.position.y =  newPosY;    
         cout << "Vertex " << i << " position: (" << vertex_.position.x << ", " << vertex_.position.y << ")" << endl;
        vertex[i] = vertex_;
        
    }

    edge.clear();

    for(int i = 0; i < matrix.size(); i++){
        for(int j = i; j < matrix.size(); j++){
            if(matrix[i][j]){
                edge.push_back(Edge(&vertex[i], &vertex[j], matrix[i][j]));
            }
        }
    }



}
void Graph::handleInput(){
    
    switch (currentInput) {
            case InputType::Random:
            if (InputOptionButton.IsClicked()) {
                 // Lấy số ngẫu nhiên
            }
            break;
            case InputType::Keyboard:
                textbox.HandleInput(); 
                break;
            case InputType::File:
                if(IsFileDropped()){
                    
                    FilePathList droppedFiles = LoadDroppedFiles();
                    TextCopy(filePath,droppedFiles.paths[0]);
                    ifstream fin(filePath);
                    if(!fin.is_open()) cout << "Cannot open dropped file";
                    else{
                        cout << "File path: " << filePath << endl;
                        reset(); // reset graph;
                        textbox.resetTextbox();
                        matrix.clear();
                        int n;
                        fin >> n;
                        matrix.resize(n, vector<int>(n));
                        for(int i = 0; i < n; i ++){
                            for(int j = 0; j < n; j++){
                                fin >> matrix[i][j];
                                cout << "matrix[" << i << "][" << j << "] = " << matrix[i][j] << endl;
                            }
                        }     
                        fin.close();
                    }
                    UnloadDroppedFiles(droppedFiles); 
                }
                break;
            default:
                break;
        }

}

void Graph::reset(){
    added = false;
    vertex.clear();
    edge.clear();
    matrix.clear();

    arrayQueue.clear();
    isAnimating  = false;
    got1stV = false;
    bfsCalled = false;
    clickedV = nullptr;
    currentIndex = 0;
}

void Graph::handleBFS(){
    float deltaTime = GetFrameTime();
     if(!got1stV){
        clickedV = getFirstVertexClicked();
    }
        
    // cout << arrayQueue.size();
    if(isAnimating && clickedV){
    
         if (!bfsCalled) {
            bfs(clickedV);
            // cout << arrayQueue.size() << endl;
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
                    // cout << "dôdo" << endl;        
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
        if(drawableVertexStorage.size() != 0)  arrayQueue.push_back(drawableEdgeStorage);
        if(drawableEdgeStorage.size() != 0) arrayQueue.push_back(drawableVertexStorage);
        
    }
    int i = 0;
    for (auto& elem : arrayQueue) {
        cout << "Index " << i++ << endl;
        for(auto& s: elem) s->print();
    }
}

void Graph::update(){
    float deltaTime = GetFrameTime();


}