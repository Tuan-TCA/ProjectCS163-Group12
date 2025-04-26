#include "Variables.h"

MODE mode; //pointer của trang 
string getMODE() {
    if(mode == MODE::LL) return "Linked List";
    if(mode == MODE::HASHTB) return "Hash Table";
    if(mode == MODE::AVL) return "AVL Tree";
    if(mode == MODE::GRAPH) return "Graph";
    return "";
}
const int screenWidth = 1267, screenHeight =  950;
const float subWidth = screenHeight*0.63f * 0.15f;
const float subHeight = screenHeight*0.63f * 0.15f;

//MyCorlor
//Theme 1:
float animationSpeed = 1.0;
float volume = 0;
Sound sound;
bool pause = false;
bool switchState = false;
char filePath[50];
Font FONT = LoadFont("res/font/MouldyCheeseRegular-WyMWG.ttf");

Color MyColor1 = Color{17, 105, 124, 255};
Color MyColor2 = Color{27, 177, 177, 255};
Color MyColor3 = Color{65, 219, 179, 255};
Color MyColor4 = Color{30, 66, 94, 255};
Color MyColor5 = Color{33, 117, 135, 255};
Color MyColor6 = Color{190, 255, 214, 255};
Color MyColor7 = Color{40, 150, 150, 255};

void UpdateColorsBasedOnSwitchState() {
    if (switchState) {
        MyColor1 = Color{143, 50, 81, 255};  
        MyColor2 = Color{212, 87, 107, 255}; 
        MyColor3 = Color{255, 134, 124, 255};//ok
        MyColor4 = Color{88, 33, 64, 255};//ok
        MyColor5 = Color{163, 62, 53, 255};
        MyColor6 = Color{255, 211, 207, 255};
        MyColor7 = Color{212, 87, 107, 255};

    } else {
        MyColor1 = Color{17, 105, 124, 255};  // Xanh
        MyColor2 = Color{27, 177, 177, 255};
        MyColor3 = Color{65, 219, 179, 255};
        MyColor4 = Color{30, 66, 94, 255};
        MyColor5 = Color{33, 117, 135, 255};
        MyColor6 = Color{190, 255, 214, 255};
        MyColor7 = Color{40, 150, 150, 255};
    }
}
Texture2D resizedImage(const char* imagePath, float width, float height) {
    Image img = LoadImage(imagePath);
    ImageResize(&img, (int)width, (int)height);  
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);  
    return texture;  
}

Vector2 operator+(Vector2 a, Vector2 b){
    return {a.x + b.x, a.y + b.y};
}

Vector2 operator-(Vector2 a, Vector2 b){
    return {a.x - b.x, a.y - b.y};
}

Vector2 operator*(Vector2 a, float b){
    return {a.x * b, a.y * b};
}

Vector2 operator/(Vector2 a, float b){
    return {a.x / b, a.y / b};
}

 bool operator!=(Vector2 a, Vector2 b){
    return a.x != b.x || a.y != b.y;
 }

bool operator!=(Color a, Color b){
    return a.a != b.a || a.b != b.b || a.g != b.g || a.r != b.r;
}

Rectangle operator-(Rectangle a, Rectangle b){
    return{a.x - b.x, a.y - b.y, a.width - b.width, a.height - b.height};
}
Rectangle operator+(Rectangle a, Rectangle b){
    return{a.x + b.x, a.y + b.y, a.width + b.width, a.height + b.height};
}
Rectangle operator*(Rectangle a, float b){
    return{a.x * b, a.y * b, a.width *b, a.height * b};
}

bool operator!=(Rectangle a, Rectangle b){
    return a.x != b.x || a.y != b.y || a.width != b.width || a.height != b.height;
}
