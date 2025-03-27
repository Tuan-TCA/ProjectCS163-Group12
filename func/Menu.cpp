#include "Menu.h"
#include "Variables.h"

void Menu::init() {
    SwitchTheme = SwitchButton(screenWidth*0.9f, screenHeight*0.016f, screenWidth*0.082f, screenWidth*0.05f, "", MyColor1, MyColor1, WHITE);
    font = LoadFont("res/font/romulus.png");
    buttons1.push_back(AnimatedImageButton("res/button/Menu/1_LL.png", screenWidth * 0.1f, screenHeight * 0.4, screenWidth * 0.18, screenWidth * 0.18 / 0.844f));
    buttons1.push_back(AnimatedImageButton("res/button/Menu/1_HT.png", screenWidth * 0.3f, screenHeight * 0.4, screenWidth * 0.18, screenWidth * 0.18 / 0.844f));
    buttons1.push_back(AnimatedImageButton("res/button/Menu/1_AVL.png", screenWidth * 0.5f, screenHeight * 0.4, screenWidth * 0.18, screenWidth * 0.18 / 0.844f));
    buttons1.push_back(AnimatedImageButton("res/button/Menu/1_GRAPH.png", screenWidth * 0.7f, screenHeight * 0.4, screenWidth * 0.18, screenWidth * 0.18 / 0.844f));

    buttons2.push_back(AnimatedImageButton("res/button/Menu/2_LL.png", screenWidth * 0.1f, screenHeight * 0.4, screenWidth * 0.18, screenWidth * 0.18 / 0.844f));
    buttons2.push_back(AnimatedImageButton("res/button/Menu/2_HT.png", screenWidth * 0.3f, screenHeight * 0.4, screenWidth * 0.18, screenWidth * 0.18 / 0.844f));
    buttons2.push_back(AnimatedImageButton("res/button/Menu/2_AVL.png", screenWidth * 0.5f, screenHeight * 0.4, screenWidth * 0.18, screenWidth * 0.18 / 0.844f));
    buttons2.push_back(AnimatedImageButton("res/button/Menu/2_GRAPH.png", screenWidth * 0.7f, screenHeight * 0.4, screenWidth * 0.18, screenWidth * 0.18 / 0.844f));
}

void Menu::draw() {
    ClearBackground(MyColor1);
    string title = "Data Visualization";
    DrawRectangle(0, 0, screenWidth, screenHeight, MyColor3);
    DrawTextEx(font, title.c_str(), {screenWidth*0.2f, screenHeight*0.1f}, screenWidth * 0.0667, 5, MyColor4);
    DrawTextEx(font, "\n\nCS163 - GROUP 12", {screenWidth*0.3f, screenHeight*0.1f}, screenWidth * 0.04, 5, MyColor4);
    SwitchTheme.Draw();
    for(auto &button : !switchState ? buttons1 : buttons2) {
        button.Update();
        button.Draw();
    }
}

int Menu::modeRetrieve() {
    for(int i = 0; i < buttons1.size(); i++) {
        if(switchState ? buttons2[i].IsClicked() : buttons1[i].IsClicked()) {
            return i+1;
        }
    }
    return -1;
}
