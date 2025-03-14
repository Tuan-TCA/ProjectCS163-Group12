#include "Variables.h"

MODE mode; //pointer của trang 
const int screenWidth = 1200, screenHeight = 900;

//MyCorlor
//Theme 1:
Color BLUE1 = Color{17, 105, 124, 255};
Color BLUE2 = Color{27, 177, 177, 255};
Color BLUE3 = Color{65, 219, 179, 255};
Color BLUE4 = Color{30, 66, 94, 255};
Color BLUE5 = Color{33, 117, 135, 255};

Texture2D resizedImage(const char* imagePath, float width, float height) {
    Image img = LoadImage(imagePath);
    ImageResize(&img, (int)width, (int)height);  
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);  
    return texture;  
}