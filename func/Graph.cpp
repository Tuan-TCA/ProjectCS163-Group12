#include "Graph.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include "Variables.h"
using namespace std;

float distance(Vector2 pos1, Vector2 pos2){
    return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}
void Graph::init(){
    Page::init();
    subButtonPosition.pop_back();
    MSTbutton =  Button(5, screenHeight / 2 - screenHeight*0.63f * 0.5f + 5, screenWidth*0.24f - 10, screenHeight*0.63f * 0.15f, "MST", MyColor1, Fade(MyColor1, 0.8f), WHITE); 
    added = false;
    minDistance = 100.0f;
    animateSpeed = 10.0f;
    duration = 1.0;
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

       float deltaTime = GetFrameTime();
    for(auto& v: vertex){
        if(v.isClicked()) v.isColorHighlighting = true;
        if(v.isColorHighlighting){
            v.Update(deltaTime);
        }
    }

    for(auto& e: edge){
        if(e.isClicked()){
            e.isColorHighlighting = true;
        }

        if(e.isColorHighlighting){
            e.Update(deltaTime);
        }
    }
}
void Graph::addFromMatrix(){
     srand(static_cast<unsigned int>(time(0)));
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
                    added = false;
                    FilePathList droppedFiles = LoadDroppedFiles();
                    TextCopy(filePath,droppedFiles.paths[0]);
                    ifstream fin(filePath);
                    if(!fin.is_open()) cout << "Cannot open dropped file";
                    else{
                        cout << "File path: " << filePath << endl;

                        textbox.resetTextbox();
                        // for(auto& x: matrix) x.clear();
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

