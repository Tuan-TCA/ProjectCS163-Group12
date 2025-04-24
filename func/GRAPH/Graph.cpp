#include "Graph.h"

#include <algorithm>


float distance(Vector2 pos1, Vector2 pos2){
    return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

void Graph::init(){
    OperationOptions = {"CREATE", "ALGORITHM"};
    selectedAlgorithmIndex = 0;
    currentALgorithm = Algorithm::BFS;
    AlgorithmOptionButton = Button(screenWidth * 0.24f * 0.15f,screenHeight / 2 - screenHeight*0.63f * 0.35f + 10 , screenWidth*0.24f * 0.7f, screenHeight*0.63f * 0.15f, AlgorithmOptions[selectedAlgorithmIndex].c_str(), WHITE, LIGHTGRAY, MyColor5);
    AlgorithmPrevButton = Button(5,screenHeight / 2 - screenHeight*0.63f * 0.35f + 10 ,  screenWidth*0.24f * 0.15f - 10, screenHeight*0.63f * 0.15f, "<", WHITE, LIGHTGRAY, MyColor5);
    AlgorithmNextButton = Button(screenWidth*0.24f * 0.85f + 5, screenHeight / 2 - screenHeight*0.63f * 0.35f + 10 ,  screenWidth*0.24f * 0.15f - 10, screenHeight*0.63f * 0.15f, ">", WHITE, LIGHTGRAY, MyColor5);
    vertex_textbox = TextBox(side. x + 5, side.y + screenHeight*0.63f * 0.51f, screenWidth*0.08, screenHeight*0.63f * 0.11f, "", WHITE, WHITE, BLACK);
    edge_textbox = TextBox(side.x + screenWidth*0.08f + 10, side.y + screenHeight*0.63f * 0.51f, screenWidth*0.08, screenHeight*0.63f * 0.11f, "", WHITE, WHITE, BLACK);
    vertex_textbox.resetTextbox();
    edge_textbox.resetTextbox();
    // textbox.bounds = Rectangle{side.x + 5, side.y + screenHeight*0.63f * 0.45f + 20 , screenWidth*0.25f - 100, screenHeight*0.63f * 0.15f};
    added = false;
    minDistance = 100.0f;
    got1stV = false;
    isAnimating = false;
    clickedV = nullptr;
    textWidth = 20;
    show_weight = SwitchButton(setting_menu.x + setting_menu.width * 0.5f, setting_menu.y + setting_menu.width*0.3f * 0.61f * 2 + 10, setting_menu.width*0.3f, setting_menu.width*0.3f * 0.61f, "", MyColor1,MyColor1, WHITE);
}

void Graph::draw(){
    Page::draw();

    for(auto& e: edge){
        e.Draw();
    }
    for(auto& v: vertex){
        v.Draw();
    }

    //setting
    show_weight.Draw();
    DrawTextEx(FONT, "WEIGHT", {setting_menu.x + 15, setting_menu.y + 18 + setting_menu.width*0.3f * 0.61f * 2 + 15}, 25, 2, WHITE);
    //Algorithm
    if(currentOperation == Operation::Algorithm){
        AlgorithmOptionButton.textColor = AlgorithmNextButton.textColor = AlgorithmPrevButton.textColor = MyColor5;
        AlgorithmOptionButton.Draw(LIGHTGRAY, WHITE);
        AlgorithmPrevButton.Draw(LIGHTGRAY, WHITE);
        AlgorithmNextButton.Draw(LIGHTGRAY, WHITE);
    }

    if (currentOperation == Operation::Create && currentInput != InputType::File) {
            DrawRectangle(vertex_textbox.bounds.x - 5, vertex_textbox.bounds.y - 5 - 20, 5 + 5 + 5 + vertex_textbox.bounds.width * 2, 10 + 20 + vertex_textbox.bounds.height, MyColor3);
            DrawTextEx(FONT, "V = ", {vertex_textbox.bounds.x + vertex_textbox.bounds.width /2 - 20, vertex_textbox.bounds.y - 20}, 20, 2, WHITE);
            DrawTextEx(FONT ,"E = ", {edge_textbox.bounds.x + edge_textbox.bounds.width / 2 - 20, edge_textbox.bounds.y - 20}, 20, 2, WHITE);
              
            vertex_textbox.Draw(22); 
            edge_textbox.Draw(22);
    }
    //code state
    
    Vector2 maxWidth = {0,0};
        // Tìm dòng dài nhất để làm kích thước chuẩn
        for(const auto& line : pseudocode) {
            Vector2 lineWidth = MeasureTextEx(FONT, line.c_str(), 15, 3);
            if(lineWidth.x > maxWidth.x) maxWidth = lineWidth;
        }
        textWidth = maxWidth.x; 
    Color highlightColor = Color{255, 222, 89, 255};
     if(isAnimating || currentOperation == Operation::Algorithm){
    for (int i = 0; i < pseudocode.size(); ++i) {
        Color currentColor = highlightColor;
        if(!StepQueue.empty() && find(StepQueue[currentQueueIndex].begin(), StepQueue[currentQueueIndex].end(), i) != StepQueue[currentQueueIndex].end()){
            currentColor.a = 255;
        }
        else{
            currentColor.a = 0;
        }
        DrawRectangleRounded(Rectangle{codeDisplayPLace.x, codeDisplayPLace.y + 10 + i * lineHeight, codeDisplayPLace.width,  lineHeight}, 0, 5, currentColor);
        DrawTextEx(FONT, pseudocode[i].c_str(), {codeDisplayPLace.x + 5, codeDisplayPLace.y + 10 + i * lineHeight} , 15, 3, MyColor4);
        
    }
    }

}


void Graph::event(){
    musicVolume.value = volume;
    Page::event();
  

   if(!added){
        addFromMatrix(); 
       added = true;
   }


    if( currentOperation == Operation::Create && currentInput != InputType::File){
        addFromTextbox();
    }
    //code display event
        if(currentOperation == Operation::Algorithm ){
        
        if ( currentALgorithm == Algorithm::CC)    {
        isClosingCodePlace = true;
        isExpandingCodePlace = false;
        animatingTime = 0;

        }else{
            if(showCodeButton.IsClicked()){
            animatingTime = 0;
           
            isClosingCodePlace = !isClosingCodePlace;
            isExpandingCodePlace = !isExpandingCodePlace;
            }
             if(isClosingCodePlace) showCodeButton.label = "SHOW CODE";
            else showCodeButton.label = "HIDE CODE";
        }
    }

    //SETTING
       if(show_weight.isOpening){
        for(auto& e: edge){
            e.isWeightVisible = false;
        }
    }
    else{
        for(auto& e: edge){
            e.isWeightVisible = true;
        }
    }
    if(currentQueueIndex > arrayQueue.size()) isPlaying = false;
    //ALgorithm operation
    if (OperationPrevButton.IsClicked()) {
        selectedAlgorithmIndex = 0;
        if (OperationOptions[selectedOperationIndex] != "CREATE"){
            isClosingCodePlace = false;
            isExpandingCodePlace = true;
        
        }
    }

    if (OperationNextButton.IsClicked()) {
        selectedAlgorithmIndex = 0;
        if (OperationOptions[selectedOperationIndex] != "CREATE" ){
            isClosingCodePlace = false;
            isExpandingCodePlace = true;
        }
    }
    if(OperationOptions[selectedOperationIndex] == "ALGORITHM") currentOperation = Operation::Algorithm;

    if (AlgorithmPrevButton.IsClicked()) {
        resetAnimation();
        selectedAlgorithmIndex = (selectedAlgorithmIndex - 1 + AlgorithmOptions.size()) % AlgorithmOptions.size();
       if(AlgorithmOptions[selectedAlgorithmIndex] != "Connected\nComponents"){
            isClosingCodePlace = false;
            isExpandingCodePlace = true;
       }
    }

    if (AlgorithmNextButton.IsClicked()) {
        resetAnimation();
        selectedAlgorithmIndex = (selectedAlgorithmIndex + 1) % AlgorithmOptions.size();
        if(AlgorithmOptions[selectedAlgorithmIndex] != "Connected\nComponents"){
            isClosingCodePlace = false;
            isExpandingCodePlace = true;
       }
    
    }
     AlgorithmOptionButton.label = AlgorithmOptions[selectedAlgorithmIndex].c_str(); 
    if(AlgorithmOptions[selectedAlgorithmIndex] == "BFS") currentALgorithm = Algorithm::BFS;
    if(AlgorithmOptions[selectedAlgorithmIndex] == "DFS") currentALgorithm = Algorithm::DFS;
    if(AlgorithmOptions[selectedAlgorithmIndex] == "MST") currentALgorithm = Algorithm::MST;
    if(AlgorithmOptions[selectedAlgorithmIndex] == "Connected\nComponents") currentALgorithm = Algorithm::CC;
    
    //vertex
    for(auto& v: vertex){
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
            if(CheckCollisionPointCircle(GetMousePosition(), v.position, v.radius) || v.isPressing){
                v.position = GetMousePosition();
                v.isPressing = true;
            }
        }
        else  if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)){
            if(CheckCollisionPointCircle(GetMousePosition(), v.position, v.radius) || v.isPressing){
                Vector2 mousePos = GetMousePosition();
                Vector2 delta = mousePos - v.position;
                v.isPressing = true;
                for(auto& v_ : vertex){
                    v_.position = v_.position + delta;
                }
                
            }
        
        }
        else v.isPressing = false;
        
    }

    for(auto& e: edge){
        
        if(!e.isAnimating || (e.isAnimating && e.endEdge != e.start->position && e.endEdge != e.end->position)) e.Update(0);
        
    }
    handleCollision();
    
    if (back1.IsClicked() || back2.IsClicked() || (!textbox.active && IsKeyPressed(KEY_LEFT))) {
        
        isPlaying = false;

        if (!arrayQueue.empty() && currentQueueIndex < arrayQueue.size()) {
            vector<Drawable*> current = arrayQueue[currentQueueIndex];
            for (auto& elem : current) {
                elem->reset();
            }
            currentQueueIndex--;
            if (currentQueueIndex < 0) currentQueueIndex = 0;
            if (currentQueueIndex < arrayQueue.size()) {
                vector<Drawable*> prev = arrayQueue[currentQueueIndex];
                for (auto& elem : prev) {
                    elem->reset();
                    elem->isAnimating = true; 
                }
            }
        }

    } 
    else if (next1.IsClicked() || next2.IsClicked() || (!textbox.active && IsKeyPressed(KEY_RIGHT))) {

        isPlaying = false; 

        if (!arrayQueue.empty() && currentQueueIndex < arrayQueue.size()) {
            vector<Drawable*> current = arrayQueue[currentQueueIndex];
            for (auto& elem : current) {
                elem->SetColor();
            }
            currentQueueIndex++;
            if (currentQueueIndex > arrayQueue.size() - 1) currentQueueIndex = arrayQueue.size() - 1;
            if (currentQueueIndex < arrayQueue.size()) {
                vector<Drawable*> next = arrayQueue[currentQueueIndex];
                for (auto& elem : next) {
                    elem->SetColor();
                }
            }
        }

    }

    if(backward1.IsClicked() || backward2.IsClicked() || (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_LEFT))){
        isPlaying = false;  
        if(!arrayQueue.empty() && currentQueueIndex < arrayQueue.size()){
            for(auto& s: arrayQueue){
                for(auto& elem: s){
                    elem->reset();
                }
            }
            currentQueueIndex = 0;
            for(auto& s: arrayQueue[0]){
                s->isAnimating = true;
            }
        }
    }
    else if (forward1.IsClicked() || forward2.IsClicked() || (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_RIGHT))){
        isPlaying = false;
        if(!arrayQueue.empty() && currentQueueIndex < arrayQueue.size()){
        for(auto& s: arrayQueue){
            for(auto& elem : s){
                elem->SetColor();
            }
        }    
        currentQueueIndex = arrayQueue.size() - 1;
        }
    }

   

    if(currentOperation == Operation::Algorithm && (currentALgorithm == Algorithm::MST || currentALgorithm == Algorithm::CC)){
    Ok.label = "START";
    Ok.bounds = Rectangle{side.x * 1.2f + 5, side.y + screenHeight*0.63f * 0.3f + 15, screenWidth*0.24f - 10, screenHeight*0.63f * 0.15f};
    }
    else{
        Ok.label = "GO";
        Ok.bounds = Rectangle{ side.x + (side.x  + side.width) * 0.74f, side.y + screenHeight*0.63f * 0.3f + 15, 73, screenHeight*0.63f * 0.15f};
       
    }


   handleChoice();
   
}
void Graph::handleChoice(){
    if(currentOperation == Operation::Algorithm){
        // currentInput = InputType::Keyboard;
        switch (currentALgorithm)
        {
        case Algorithm::BFS:
            pseudocode = {
                "BFS (G, s)",
                " while !Q.empty // Q is a normal queue",
                "   for each neighbor v of u = Q.front, Q.pop",
                "       if v is unvisited, tree edge, Q.push(v)",
                "done with s"
            };
            handleBFS();
            break;
        case Algorithm::MST:
            pseudocode = {
                "Sort E edges by increasing weight", //0
                "T = {}",
                "for (i = 0; i < edgeList.length; i++)", // 2
                "  if adding e = edgelist[i] does not form a cycle", //3
                "    add e to T", // 4
                "  else ignore e", // 5
                "MST = T",
            };
            handleMST();
            break;
        case Algorithm::DFS:
           pseudocode = {
                "DFS(u):",                                     // 0
                "  mark u as visited",                         // 1
                "  for each neighbor v of u:",                // 2
                "    if v is not visited:",                    // 3          
                "      DFS(v)",                                // 4
                "      backtrack to u",
                "done with u"                        // 5
            };
            handleDFS();
            break;
            case Algorithm::CC:
            pseudocode = {};
            handleCC();
            break;
        default:
        pseudocode = {};
           break;
        }
    }
    else{
        resetAnimation();
    }
}
void Graph::startAnimation(float duration){
    this->duration = duration;
    currentQueueIndex = 0;
}

void Graph::resetAnimation(){
    StepQueue.clear();
    arrayQueue.clear();
    isAnimating  = false;
    got1stV = false;
    AlgoCalled = false;
    clickedV = nullptr;
    currentQueueIndex = 0;
    currentStep = 0;
    for(auto& v: vertex){
        v.reset();
    }
    for(auto& e: edge){
        e.reset();
    }
}




void Graph::addFromMatrix(){
     srand(static_cast<unsigned int>(time(0) + rand()));
    int n = matrix.size();
    //random vertices in workplace 
    int minX = workplace.x, maxX = workplace.x + workplace.width;  
    int minY = workplace.y, maxY = workplace.y + workplace.height;
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
        vertex[i] = vertex_;
        
    }

    edge.clear();

    for(int i = 0; i < matrix.size(); i++){
        for(int j = i; j < matrix.size(); j++){ // bat dau tu 0
            if(matrix[i][j]){
                edge.push_back(Edge(&vertex[i], &vertex[j], matrix[i][j]));
            }
        }
    }

    if(currentALgorithm == Algorithm::MST) dsu.init(vertex.size()); // init dsu with n sets
}

void Graph::addFromTextbox(){
    if(textbox.nums.size() > 0){
        
        reset();
        int n = textbox.nums[0];
        matrix.resize(n, vector<int>(n));
        int idx = 1;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                matrix[i][j] = textbox.nums[idx++];
            }
        }

        textbox.nums.clear();
        
    }
}



void Graph::RANDOM_INPUT() {
    std::mt19937 rng(std::random_device{}());

    switch (currentOperation) {
        case Operation::Create: {
            textbox.reset();
            std::uniform_int_distribution<int> vertexDist(4, 9);
            int numVertices = vertex_textbox.inputText.empty() || vertex_textbox.inputText[0].empty() ? vertexDist(rng) : stoi(vertex_textbox.inputText[0]);
            if (vertex_textbox.inputText[0].empty()) vertex_textbox.inputText[0] = to_string(numVertices);

            int maxEdges = numVertices * (numVertices - 1) / 2;
            std::uniform_int_distribution<int> edgeDist(0, maxEdges);
            int numEdges = 0;
            if (!edge_textbox.inputText.empty() && !edge_textbox.inputText[0].empty()) {
                numEdges = stoi(edge_textbox.inputText[0]);
            } else {
                numEdges = edgeDist(rng);
                edge_textbox.inputText[0] = to_string(numEdges);
            }
            std::uniform_int_distribution<int> weightDist(1, 10);

            std::vector<std::vector<int>> adjMatrix(numVertices, std::vector<int>(numVertices, 0));
            std::vector<std::string> lines;
            std::stringstream ss;

            int targetEdges = std::min(numEdges, maxEdges);
            std::vector<std::pair<int, int>> allPossibleEdges;
            for (int i = 0; i < numVertices; ++i) {
                for (int j = i + 1; j < numVertices; ++j) {
                    allPossibleEdges.push_back({i, j});
                }
            }

            std::shuffle(allPossibleEdges.begin(), allPossibleEdges.end(), rng);

            for (int k = 0; k < std::min((int)allPossibleEdges.size(), targetEdges); ++k) {
                int u = allPossibleEdges[k].first;
                int v = allPossibleEdges[k].second;
                int weight = weightDist(rng);
                adjMatrix[u][v] = weight;
                adjMatrix[v][u] = weight;
            }

            ss << numVertices;
            lines.push_back(ss.str());
            ss.str("");

            for (int i = 0; i < numVertices; ++i) {
                for (int j = 0; j < numVertices; ++j) {
                    ss << adjMatrix[i][j] << (j == numVertices - 1 ? "" : " ");
                }
                lines.push_back(ss.str());
                ss.str("");
            }

            textbox.inputText = lines;
            textbox.SubIndex.clear();
            for (const auto& line : lines) {
                textbox.SubIndex.push_back(line.length());
            }
            textbox.currentIndex = 0;
            break;
        }
        default:
            break;
    }
}
void Graph::FILE_INPUT(){
    switch (currentOperation)
    {
    case Operation::Insert:
        //Insert graph
        break;
    case Operation::Create:
        if(IsFileDropped()){        
        FilePathList droppedFiles = LoadDroppedFiles();
        TextCopy(filePath,droppedFiles.paths[0]);
        ifstream fin(filePath);
        if(!fin.is_open()) cout << "Cannot open dropped file";
        else{
            reset(); // reset graph;
            textbox.reset();
            matrix.clear();
            int n;
            fin >> n;
            matrix.resize(n, vector<int>(n));
            for(int i = 0; i < n; i ++){
                for(int j = 0; j < n; j++){
                    fin >> matrix[i][j];
                }
            }     
            fin.close();
        }
        UnloadDroppedFiles(droppedFiles); 
    }
        break;
    
    default:
    Page::handleInput();
        break;
    }
    
}

void Graph::reset(){
    Page::reset();
    added = false;
    vertex.clear();
    edge.clear();
    matrix.clear();
    arrayQueue.clear();
    StepQueue.clear();
    isAnimating  = false;
    got1stV = false;
    AlgoCalled = false;
    clickedV = nullptr;
    currentQueueIndex = 0;
    currentStep = 0;
    selectedAlgorithmIndex = 0;
}



void Graph::handleCollision(){
    for(int i = 0; i < vertex.size(); i++){
        for(int j = 0; j < vertex.size(); j++){
            float dis = distance(vertex[i].position, vertex[j].position);
            if( dis && dis  < minDistance){
                Vector2 delta = vertex[i].position - vertex[j].position;
                Vector2 rate = delta / dis;
                delta = rate * (minDistance - dis);
                if(vertex[i].isPressing){
                    vertex[j].position = vertex[j].position - delta;
                }
                else{
                    vertex[i].position = vertex[i].position + delta;
                }
            }
        }
    }

    //bound the position
    for(auto& s : vertex){
        if(s.position.x < workplace.x) s.position.x = workplace.x;
        if(s.position.y < workplace.y) s.position.y = workplace.y;
        if(s.position.x > workplace.x + workplace.width) s.position.x = workplace.x + workplace.width;
        if(s.position.y > workplace.y + workplace.height) s.position.y = workplace.y + workplace.height;
    }

}


void Graph::handleInput(){
    Page::handleInput();
    vertex_textbox.update();
    edge_textbox.update();
    if(currentOperation == Operation::Algorithm){
        textbox.HandleInput();
    }
    if(currentOperation == Operation::Create){
        if(vertex_textbox.active) vertex_textbox.HandleInput();
                if(edge_textbox.active) edge_textbox.HandleInput();
    }
    if(Ok.IsClicked()) {
        vertex_textbox.reset();
        edge_textbox.reset();
    }
}

void Graph::updateSide(){
    Page::updateSide();
    AlgorithmOptionButton.bounds =Rectangle{side.x + (side.x + side.width) * 0.15f, side.y + screenHeight*0.63f * 0.15f + 10 , screenWidth*0.24f * 0.7f, screenHeight*0.63f * 0.15f};
    AlgorithmPrevButton.bounds = Rectangle{side.x + 5,side.y + screenHeight*0.63f * 0.15f + 10 ,  screenWidth*0.24f * 0.15f - 10, screenHeight*0.63f * 0.15f}; 
    AlgorithmNextButton.bounds = Rectangle{side.x + (side.x + side.width) * 0.85f + 5, side.y + screenHeight*0.63f * 0.15f + 10,  screenWidth*0.24f * 0.15f - 10, screenHeight*0.63f * 0.15f};
    vertex_textbox.bounds = {side.x + 5, side.y + screenHeight*0.63f * 0.54f, screenWidth*0.08f, screenHeight*0.63f * 0.11f};
    edge_textbox.bounds = {side.x + screenWidth*0.08f + 10, side.y + screenHeight*0.63f * 0.54f, screenWidth*0.08f, screenHeight*0.63f * 0.11f};
    show_weight.bounds = {setting_menu.x + setting_menu.width * 0.5f, setting_menu.y + setting_menu.width*0.3f * 0.61f * 2 + 20, setting_menu.width*0.3f, setting_menu.width*0.3f * 0.61f};
}