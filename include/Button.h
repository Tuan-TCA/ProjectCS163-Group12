#pragma once
#include "Variables.h"

using namespace std;

class MyRec {
private:
    
    Color color;
    Color textColor;
    string label;

public:
    Rectangle bounds;
    MyRec() {};
    MyRec(float x, float y, float width, float height, string labelText, Color color, Color textCol) {
        bounds = {x, y, width, height};
        label = labelText;
        color = color;
        textColor = textCol;
    }

    void Draw() {
        DrawRectangleRec(bounds, color);
        int textWidth = MeasureText(label.c_str(), 40);
        DrawText(label.c_str(), bounds.x + (bounds.width - textWidth) / 2, bounds.y + (bounds.height - 40) / 2, 40, textColor);
    }

    void DrawRounded(){
        DrawRectangleRounded(bounds, 20, 0, color);
        DrawText(label.c_str(), bounds.x + (bounds.width - MeasureText(label.c_str(), 40)) / 2, bounds.y + (bounds.height - 40) / 2, 40, textColor);
    }
    void DrawRounded(Color color){
        DrawRectangleRounded(bounds, 20, 0, color);
        DrawText(label.c_str(), bounds.x + (bounds.width - MeasureText(label.c_str(), 40)) / 2, bounds.y + (bounds.height - 40) / 2, 40, textColor);
    }

    void Draw(Color color, string Mode){
        DrawRectangleRec(bounds, color);
        int textWidth = MeasureText(Mode.c_str(), 40);
        DrawText(Mode.c_str(), bounds.x + (bounds.width - textWidth) / 2, bounds.y + (bounds.height - 40) / 2, 40, textColor);
    }
};

class Button {
public:
    Rectangle bounds;
    Color color;
    Color hoverColor;
    Color textColor;
    const char* label;
    bool isHovered;
    Texture2D image;

    Button() {
        bounds = {0,0,0,0};
        label = "";
        color = WHITE;
        hoverColor = WHITE;
        textColor = WHITE;
        isHovered = false;
    }

    Button(float x, float y, float width, float height, const char* labelText, Color buttonColor, Color hoverCol, Color textCol) {
        bounds = {x, y, width, height};
        label = labelText;
        color = buttonColor;
        hoverColor = hoverCol;
        textColor = textCol;
        isHovered = false;
    }

    virtual void Update() {
        Vector2 mousePoint = GetMousePosition();
        isHovered = CheckCollisionPointRec(mousePoint, bounds);
    }

    virtual void Draw() {
        Update();
        DrawRectangleRec(bounds, isHovered ? hoverColor : color);
        int textWidth = MeasureText(label, 20);
        // DrawText(label, bounds.x + (bounds.width - textWidth) / 2, bounds.y + (bounds.height - 20) / 2, 20, textColor);
        DrawTextEx(FONT, label, {bounds.x + (bounds.width - textWidth) / 2, bounds.y + (bounds.height - 20) / 2}, 20, 3, textColor );
    }

    virtual void Draw(Color HoverColor, Color color){
        Update();
        DrawRectangleRec(bounds, isHovered ? HoverColor : color);
        int textWidth = MeasureText(label, 20);
                DrawTextEx(FONT, label, {bounds.x + (bounds.width - textWidth) / 2, bounds.y + (bounds.height - 20) / 2}, 20, 3, textColor );

    }
    void DrawRounded(){
        Update();
        DrawRectangleRounded(bounds, 20, 0,isHovered ? hoverColor : color);
        int textWidth = MeasureText(label, 20);
        DrawTextEx(FONT, label, {bounds.x + (bounds.width - textWidth) / 2, bounds.y + (bounds.height - 20) / 2}, 20, 3, textColor );
    }

    void DrawText2D () {
        Update();
        Rectangle sourceRec = {0,0, (float) image.width, (float) image.height};
        Vector2 origin = {0,0};
        DrawTexturePro(image, sourceRec, bounds, origin, 0.0f, isHovered ? LIGHTGRAY : YELLOW);
    }

    Rectangle getBound(){
        return bounds;
    }
    bool isOver(){
        return isHovered;
    }
    bool IsClicked() {
        Update();
        if (isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(volume) PlaySound(sound);
            return true;
        }
        return false;
    }
};

class TextBox: public Button {
public:
    vector<string> inputText;
    int currentIndex;
    int startRowIndex;
    int startColumnIndex;
    int maxVisibleLength;
    bool active;
    vector<int> SubIndex;
    vector<int> nums;

    TextBox() : Button() {
        inputText = {""};
        active = false;
        SubIndex = {0};
        nums.clear();
        maxVisibleLength = 15; 
        startColumnIndex = 0;
    }

    TextBox(float x, float y, float width, float height, const char* labelText, 
            Color buttonColor, Color hoverCol, Color textCol)
        : Button(x, y, width, height, labelText, buttonColor, hoverCol, textCol) { 
        inputText = {""};  
        SubIndex = {0};
        active = false;  
        nums.clear();  
        currentIndex = 0; 
        maxVisibleLength = 15; 
        startColumnIndex = 0;
    }
    void update(){
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        active = (mousePos.x >= bounds.x && mousePos.x <=  bounds.x + bounds.width && mousePos.y >= bounds.y && mousePos.y <= bounds.y + bounds.height);
        }

        if(active){
            if(IsKeyPressed(KEY_DOWN)){

                currentIndex++;
                if(currentIndex >= inputText.size()) currentIndex = inputText.size() - 1;
                if(currentIndex - startRowIndex > 2) startRowIndex++;
                startColumnIndex = 0;
            }

            if(IsKeyPressed(KEY_UP)){
                currentIndex--;
                if(currentIndex < 0) currentIndex = 0;
                if(currentIndex - startRowIndex < 0) startRowIndex--;
                startColumnIndex = 0;
            }

            if (!SubIndex.empty() && currentIndex >= 0 && currentIndex < SubIndex.size()) { 
                if(IsKeyPressed(KEY_LEFT)){
                    SubIndex[currentIndex]--;
                    if(SubIndex[currentIndex] < 0) {
                        SubIndex[currentIndex] = 0;
                        if(startColumnIndex > 0 && SubIndex[currentIndex] < startColumnIndex) startColumnIndex--;
                    } else if (SubIndex[currentIndex] < startColumnIndex) {
                        startColumnIndex = SubIndex[currentIndex];
                    }
                }

                if (!inputText.empty() && currentIndex >= 0 && currentIndex < inputText.size()) { 
                    if(IsKeyPressed(KEY_RIGHT)){
                        SubIndex[currentIndex]++;
                         if(SubIndex[currentIndex] > inputText[currentIndex].size()) {
                            SubIndex[currentIndex] = inputText[currentIndex].size();
                        } 
                        else if (SubIndex[currentIndex] >= startColumnIndex + maxVisibleLength) {
                            startColumnIndex++;
                        }
                    }
                }
            }

        }
    }
    void Draw() override {  
        Button::Draw();
        int cnt = 0;
        for(int i = startRowIndex; i < inputText.size() && i < startRowIndex + 3; i++){
            string currentText = inputText[i];
            int subIndex = (i == currentIndex && !SubIndex.empty() && i < SubIndex.size()) ? SubIndex[i] : currentText.size();

            string visibleText = "";
            int cursorPositionInVisibleText = -1;

            if (!currentText.empty()) {
                int endIndex = min((int)currentText.size(), startColumnIndex + maxVisibleLength);
                int length = endIndex - startColumnIndex;
                if (length > 0) {
                    visibleText = currentText.substr(startColumnIndex, length);
                } else {
                    visibleText = "";
                }
     
                if (i == currentIndex) {
                    cursorPositionInVisibleText = subIndex - startColumnIndex;
                    if (cursorPositionInVisibleText < 0 || cursorPositionInVisibleText > visibleText.size()) {
                        cursorPositionInVisibleText = visibleText.size(); 
                    }
                }
            } else if (i == currentIndex) {
                    cursorPositionInVisibleText = 0;
            }
            string displayText = visibleText;
            if (active && i == currentIndex && ((int)(GetTime() * 2) % 2 == 0) && cursorPositionInVisibleText >= 0 && cursorPositionInVisibleText <= displayText.size()) {
            displayText.insert(displayText.begin() + cursorPositionInVisibleText, '|');
            }

            float lineHeight = 25;
            // Vector2 textHeight = MeasureTextEx(FONT, displayText.c_str(), 25, 1);
            DrawTextEx(FONT, displayText.c_str(), {bounds.x + 5 , bounds.y + 5  + cnt * lineHeight}, 25, 2, textColor);
            cnt++;
            
        }
    }

    void Draw(int fontSize)  {
        Button::Draw();
        for(int i = startRowIndex; i < inputText.size() && i < startRowIndex + 3; i++){
            string displayText = inputText[i];
            if (active && i == currentIndex && ((int)(GetTime() * 2) % 2 == 0) ) {
                displayText.insert(displayText.begin() + SubIndex[currentIndex], '|');
            }
            DrawText(displayText.c_str(), bounds.x + 5, bounds.y + bounds.height / 3 - MeasureTextEx(FONT, displayText.c_str(), fontSize, 1).y / 2, fontSize, textColor);
        }
    }   

    void HandleInput() {
    if (active) {
        int key = GetCharPressed();
        if (!inputText.empty() && currentIndex >= 0 && currentIndex < inputText.size() &&
            !SubIndex.empty() && currentIndex >= 0 && currentIndex < SubIndex.size()) { 
            while (key > 0 ) {
                if (key >= '0' && key <= '9' || key == ' ') {
                    int idx = SubIndex[currentIndex];
                    inputText[currentIndex].insert(inputText[currentIndex].begin() + idx,(char)key);
                    SubIndex[currentIndex]++;
                    if (SubIndex[currentIndex] >= startColumnIndex + maxVisibleLength) {
                        startColumnIndex++;
                    }
                }
                key = GetCharPressed();
            }
        }

        if(IsKeyPressed(KEY_ENTER)){
            inputText.push_back("");
            SubIndex.push_back(0);
            currentIndex++;
             if(currentIndex - startRowIndex > 2) startRowIndex++;
             startColumnIndex = 0;
        }

        if (!inputText.empty() && currentIndex >= 0 && currentIndex < inputText.size() &&
            !SubIndex.empty() && currentIndex >= 0 && currentIndex < SubIndex.size()) { 
            if(IsKeyPressed(KEY_BACKSPACE)){
                if (SubIndex[currentIndex] > 0) {
                    SubIndex[currentIndex]--;
                    int idx = SubIndex[currentIndex];
                    inputText[currentIndex].erase(inputText[currentIndex].begin() + idx);
                    if (SubIndex[currentIndex] < startColumnIndex) {
                        startColumnIndex--;
                        if (startColumnIndex < 0) startColumnIndex = 0;
                    }
                } else if (inputText.size() > 1) { 
                    inputText.erase(inputText.begin() + currentIndex);
                    SubIndex.erase(SubIndex.begin() + currentIndex);
                    currentIndex--;
                    if (currentIndex < 0) currentIndex = 0;
                    if (!SubIndex.empty() && currentIndex >= 0 && currentIndex < SubIndex.size()) {
                        SubIndex[currentIndex] = inputText[currentIndex].size();
                        startColumnIndex = max(0, (int)inputText[currentIndex].size() - maxVisibleLength); 
                    }
                    if(currentIndex - startRowIndex < 0) startRowIndex--;
                }
                else startColumnIndex = 0;
            }

        }
    }
}

    

  
    void reset(){
        active = false;
        inputText.clear();
        inputText = {""};
        currentIndex = 0;
        SubIndex.clear();
        SubIndex.push_back(0);
        startRowIndex = 0;
        startColumnIndex = 0;
        active = false;
        nums.clear();
    }

    void resetTextbox(){
        active = false;
        inputText.clear();
        inputText = {""};
        currentIndex = 0;
        SubIndex.clear();
        SubIndex.push_back(0);
        startRowIndex = 0;
        startColumnIndex = 0;
        active = false;
        // nums.clear();
    }

    

    
};

class ButtonFromImage : public Button {
private:
    Texture2D texture;
    Texture2D textureOver;
public:
    ButtonFromImage() : Button(0, 0, 0, 0, "", RAYWHITE, RAYWHITE, RAYWHITE), texture({ 0 }), textureOver({ 0 }) {}
    ButtonFromImage(const char* imagePath, const char* imageOverPath, float x, float y, float width, float height)
        : Button(x, y, width, height, "", RAYWHITE, RAYWHITE, RAYWHITE) {
        texture = resizedImage(imagePath, width, height);
        textureOver = resizedImage(imageOverPath, width, height);
    }

    void Draw() override {
        Update();
        DrawTexture(!isOver() ? texture : textureOver, bounds.x, bounds.y, WHITE);
    }
};

class AnimatedButton : public Button {
public:
    bool isScaling;
    float scaleFactor;
    float scaleSpeed;
    float colorAlpha;
    float colorAlphaSpeed;

    AnimatedButton(){}
    AnimatedButton(float x, float y, float width, float height, const char* labelText, Color buttonColor, Color hoverCol, Color textCol)
        : Button(x, y, width, height, labelText, buttonColor, hoverCol, textCol) {
        isScaling = false;
        scaleFactor = 1.0f;
        scaleSpeed = 1.0f;
        colorAlpha = 1.0f;
        colorAlphaSpeed = 1.0f;
    }

    void Update() override {
        Button::Update(); 

        float deltaTime = GetFrameTime();
        if (isHovered && !isScaling) {
            isScaling = true;
        } else if (!isHovered && isScaling) {
            isScaling = true;
        }

        if (isScaling) {
            if (isHovered) {
                scaleFactor += scaleSpeed * deltaTime;
                colorAlpha -= colorAlphaSpeed * deltaTime;
                if (scaleFactor > 1.2f) scaleFactor = 1.2f;
                if (colorAlpha < 0.5f) colorAlpha = 0.5f;
            } else {
                scaleFactor -= scaleSpeed * deltaTime;
                colorAlpha += colorAlphaSpeed * deltaTime;
                if (scaleFactor < 1.0f) {
                    scaleFactor = 1.0f;
                    isScaling = false;
                }
                if (colorAlpha > 1.0f) {
                    colorAlpha = 1.0f;
                    isScaling = false;
                }
            }
        }
    }

    void Draw() override {
        Rectangle scaledBounds = {
            bounds.x - (bounds.width * (scaleFactor - 1.0f) / 2.0f),
            bounds.y - (bounds.height * (scaleFactor - 1.0f) / 2.0f),
            bounds.width * scaleFactor,
            bounds.height * scaleFactor
        };

        Color drawColor = color;
        drawColor.a = static_cast<unsigned char>(colorAlpha * 255);

        DrawRectangleRounded(scaledBounds, 17, 2, drawColor);
        int textWidth = MeasureText(label, 20);
        DrawText(label, bounds.x - (bounds.width * (scaleFactor - 1.0f) / 2.0f) + (bounds.width * scaleFactor - textWidth ) / 2, bounds.y  - (bounds.height * (scaleFactor - 1.0f) / 2.0f) + (bounds.height * scaleFactor - 20) / 2, 20 * scaleFactor, textColor);
    }

    void Draw(Color color) {
        Rectangle scaledBounds = {
            bounds.x - (bounds.width * (scaleFactor - 1.0f) / 2.0f),
            bounds.y - (bounds.height * (scaleFactor - 1.0f) / 2.0f),
            bounds.width * scaleFactor,
            bounds.height * scaleFactor
        };

        Color drawColor = color;
        drawColor.a = static_cast<unsigned char>(colorAlpha * 255);

        DrawRectangleRounded(scaledBounds, 17, 2, drawColor);
        int textWidth = MeasureText(label, 20);
        DrawText(label, bounds.x - (bounds.width * (scaleFactor - 1.0f) / 2.0f) + (bounds.width * scaleFactor - textWidth ) / 2, bounds.y  - (bounds.height * (scaleFactor - 1.0f) / 2.0f) + (bounds.height * scaleFactor - 20) / 2, 20 * scaleFactor, textColor);
    }
};

class AnimatedImageButton : public AnimatedButton{
    public:

    Texture2D texture;

    AnimatedImageButton(){
    }
        AnimatedImageButton(const char* path, float x, float y, float width, float height) : 
        AnimatedButton( x,  y,  width,  height,  "",  WHITE,  WHITE,  WHITE){
            texture = resizedImage(path, width, height);
        }
    float Lerp(float start, float end, float amount) {
        return start + (end - start) * amount;
    }
        void Update() override {
        Button::Update();
        float deltaTime = GetFrameTime();
        float targetScale = isHovered ? 1.2f : 1.0f;
        float targetAlpha = isHovered ? 0.5f : 1.0f;
        float lerpSpeed = 5.0f; // Tốc độ nội suy

        scaleFactor = Lerp(scaleFactor, targetScale, lerpSpeed * deltaTime);
        colorAlpha = Lerp(colorAlpha, targetAlpha, lerpSpeed * deltaTime);

        // Có thể thêm một ngưỡng nhỏ để xác định khi hiệu ứng kết thúc
        if (abs(scaleFactor - targetScale) < 0.01f && abs(colorAlpha - targetAlpha) < 0.01f) {
            isScaling = false; // Hoặc bạn có thể bỏ biến isScaling nếu không cần thiết nữa
        } else {
            isScaling = true;
        }
    }
    void Draw() override{
        Rectangle scaledBounds = {
            bounds.x - (bounds.width * (scaleFactor - 1.0f) / 2.0f),
            bounds.y - (bounds.height * (scaleFactor - 1.0f) / 2.0f),
            bounds.width * scaleFactor,
            bounds.height * scaleFactor
        };

        
        DrawTexture(texture, bounds.x, bounds. y, WHITE);
      
    }

};

class SwitchThemeButton : public Button {
public:
    float switchPos;  
    bool isSwitching; 
    float switchSpeed; 
    
    SwitchThemeButton(){}
    SwitchThemeButton(float x, float y, float width, float height, const char* labelText, Color buttonColor, Color hoverCol, Color textCol)
        : Button(x, y, width, height, labelText, buttonColor, hoverCol, textCol) {
        switchPos = 0.0f; 
        switchState = false; // is turning off
        isSwitching = false; 
        switchSpeed = 0.05f;
    }


    void UpdateSwitch() {
        Vector2 mousePos = GetMousePosition();
       
        if (IsClicked()) {
            switchState = !switchState; 
            UpdateColorsBasedOnSwitchState();
            isSwitching = true;  
        }

        if (isSwitching) {
            if (switchState && switchPos < 1.0f) {
                switchPos += switchSpeed;
                if (switchPos >= 1.0f) {
                    switchPos = 1.0f;
                    isSwitching = false; 
                }
            }
            else if (!switchState && switchPos > 0.0f) {
                switchPos -= switchSpeed;
                if (switchPos <= 0.0f) {
                    switchPos = 0.0f;
                    isSwitching = false;  
                }
            }
        }
    }

    void Draw() override {
        UpdateSwitch();
        
        DrawRectangleRounded(bounds, bounds.height / 2, 10, MyColor4);
        DrawCircle(bounds.x + bounds.width * 0.3f +switchPos * (bounds.width - bounds.height), bounds.y + bounds.height / 2, bounds.height / 2 - 5, WHITE);
    }
};

class SwitchButton : public Button {
public:
    float switchPos;  
    bool isSwitching; 
    float switchSpeed; 
    bool isOpening = false;
    SwitchButton(){}
    SwitchButton(float x, float y, float width, float height, const char* labelText, Color buttonColor, Color hoverCol, Color textCol)
        : Button(x, y, width, height, labelText, buttonColor, hoverCol, textCol) {
        switchPos = 0.0f; 
        isSwitching = false; 
        switchSpeed = 0.05f;
    }


    void UpdateSwitch() {
        Vector2 mousePos = GetMousePosition();
       
        if (IsClicked()) {
            isOpening = !isOpening; 
            isSwitching = true;  
        }

        if (isSwitching) {
            if (isOpening && switchPos < 1.0f) {
                switchPos += switchSpeed;
                if (switchPos >= 1.0f) {
                    switchPos = 1.0f;
                    isSwitching = false; 
                }
            }
            else if (!isOpening && switchPos > 0.0f) {
                switchPos -= switchSpeed;
                if (switchPos <= 0.0f) {
                    switchPos = 0.0f;
                    isSwitching = false;  
                }
            }
        }
    }

    void Draw() override {
        UpdateSwitch();
        
        DrawRectangleRounded(bounds, bounds.height / 2, 10, MyColor4);
        DrawCircle(bounds.x + bounds.width * 0.3f +switchPos * (bounds.width - bounds.height), bounds.y + bounds.height / 2, bounds.height / 2 - 5, WHITE);
    }
};

class Slider {
public:
    Rectangle bounds;
    float value;
    float minValue;
    float maxValue;
    bool isDragging;

    Slider() : isDragging(false), value(0.3), minValue(0), maxValue(1) {}

    Slider(Rectangle bounds, float value,float minValue, float maxValue)
        : bounds(bounds), minValue(minValue), maxValue(maxValue), value(value), isDragging(false) {}

    void Update() {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, bounds) || isDragging) {
                float ratio = (mouse.x - bounds.x) / bounds.width;
                ratio = std::clamp(ratio, 0.0f, 1.0f);
                value = minValue + (maxValue - minValue) * ratio;
                isDragging = true;
            }
        } else {
            isDragging = false;
        }
    }

    void Draw() {
   
        DrawRectangleRounded(bounds, 0.1f, 8, WHITE);

        float filledWidth = (value - minValue) / (maxValue - minValue) * bounds.width;
        DrawRectangleRounded({bounds.x, bounds.y, filledWidth, bounds.height}, 0.1f, 8, Fade(MyColor7, 0.4f));

        float knobX = bounds.x + filledWidth - 10;
        float knobY = bounds.y ;
        DrawRectangleRounded({knobX, knobY, bounds.width * 0.1f, bounds.height}, 0.5f, 20, MyColor7);

    }
};
