#include "Menu.h"


void Menu::init() {
    setting_menu = Rectangle{screenWidth * 0.8f, screenHeight * 0.2f, screenWidth * 0.19f, screenHeight * 0.12f};
    Slider musicVolume  = Slider({setting_menu.x + setting_menu.width * 0.5f, setting_menu.y + setting_menu.width*0.3f * 0.61f + 10, setting_menu.width*0.45f, setting_menu.width*0.3f * 0.61f}, 0.3f, 0, 1);
    SwitchTheme = SwitchThemeButton(setting_menu.x + 5, setting_menu.y + 5, setting_menu.width*0.43f, 50, "", MyColor1, MyColor1, WHITE);
    font = LoadFont("res/font/romulus.png");
    MyRec head = MyRec(0, 10, (float) screenWidth, screenHeight*0.08f, getMODE().c_str(), MyColor2, WHITE);
    setting_button1 = ButtonFromImage("res/button/1_setting.png", "res/button/1_setting.png", head.bounds.width * 0.935f, head.bounds.y + head.bounds.height / 2 - screenWidth * 0.025f, screenWidth * 0.05f, screenWidth * 0.05f);
    setting_button2 = ButtonFromImage("res/button/2_setting.png", "res/button/2_setting.png", head.bounds.width * 0.935f, head.bounds.y + head.bounds.height / 2 - screenWidth * 0.025f, screenWidth * 0.05f, screenWidth * 0.05f);

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
   event();
    ClearBackground(MyColor1);
    string title = "Data Visualization";
    DrawRectangle(0, 0, screenWidth, screenHeight, MyColor3);
    DrawTextEx(font, title.c_str(), {screenWidth*0.2f, screenHeight*0.1f}, screenWidth * 0.0667, 5, MyColor4);
    DrawTextEx(font, "\n\nCS163 - GROUP 12", {screenWidth*0.3f, screenHeight*0.1f}, screenWidth * 0.04, 5, MyColor4);
    for(auto &button : !switchState ? buttons1 : buttons2) {
        button.Update();
        button.Draw();
    }
    switchState ? setting_button2.Draw() : setting_button1.Draw();

    //setting
    DrawRectangleRounded(setting_menu, 0.42f, 30, MyColor1);
    musicVolume.Draw();
    SwitchTheme.Draw();
    DrawTextEx(FONT, "THEME", {setting_menu.x + 15, setting_menu.y + 18}, 25, 2, WHITE);
    DrawTextEx(FONT, "VOLUME", {setting_menu.x + 15, musicVolume.bounds.y + musicVolume.bounds.height / 3}, 23, 2, WHITE);
}
void Menu::event(){
    SwitchTheme.bounds = {setting_menu.x + setting_menu.width * 0.5f, setting_menu.y + 5, setting_menu.width*0.3f, setting_menu.width*0.3f * 0.61f};
     musicVolume.bounds = {setting_menu.x + setting_menu.width * 0.5f, setting_menu.y + setting_menu.width*0.3f * 0.61f + 10, setting_menu.width*0.45f, setting_menu.width*0.3f * 0.61f};
    float deltaTime = GetFrameTime();
    Vector2 mousePos = GetMousePosition();
    Rectangle targetPlace = Rectangle{screenWidth * 0.8f, screenHeight * 0.2f, screenWidth * 0.19f, screenHeight * 0.12f};
    Rectangle closedPlace = Rectangle{(float) screenWidth * 0.99f, screenHeight * 0.2f, screenWidth * 0.19f, screenHeight * 0.12f};
  
    musicVolume.Update();
    float wheel1 = GetMouseWheelMove();
    if(wheel1 && CheckCollisionPointRec(mousePos, targetPlace)) {
        musicVolume.value += wheel1 * 0.1f;
        if(musicVolume.value > 1) musicVolume.value = 1;
        else if(musicVolume.value < 0) musicVolume.value = 0;
    }

    volume = musicVolume.value;
      if (!switchState ? setting_button1.IsClicked() : setting_button2.IsClicked()) {
    if (!setting_IsClosing && !setting_IsOpening) {
        if (hasOpened) {
            setting_IsOpening = false;
            setting_IsClosing = true;
            hasOpened = false;
            hasClosed = false;
            animatingTime = 0.0f; 
        }
        else if (hasClosed) {
            
            setting_IsOpening = true;
            setting_IsClosing = false;
            hasClosed = false;
            animatingTime = 0.0f;  
        }
    }
    }

    if (setting_IsOpening && !hasOpened) {

        animatingTime += deltaTime;  
        float t = animatingTime / 0.1f; 
    
        if (t > 1.0f) {
            t = 1.0f;
            animatingTime = 0.0f; 
            setting_IsOpening = false;
            hasOpened = true;  
        }

        setting_menu = Lerp(setting_menu, targetPlace, t); 
    }
    else if (setting_IsClosing && !hasClosed) {
        animatingTime += deltaTime; 
        float t = animatingTime / 0.1f; 

        if (t > 1.0f) {
            t = 1.0f;
            animatingTime = 0.0f;  
            setting_IsClosing = false;
            hasClosed = true; 
        }

        setting_menu = Lerp(setting_menu, closedPlace, t);
    }

}
float Menu::Lerp(float start, float end, float amount) {
    return start + amount * (end - start);
}
Rectangle Menu::Lerp(Rectangle a, Rectangle b, float amount) {
    Rectangle result;
    result.x = Lerp(a.x, b.x, amount);
    result.y = Lerp(a.y, b.y, amount);
    result.width = Lerp(a.width, b.width, amount);
    result.height = Lerp(a.height, b.height, amount);
    
    return result;
}
int Menu::modeRetrieve() {
    for(int i = 0; i < buttons1.size(); i++) {
        if(switchState ? buttons2[i].IsClicked() : buttons1[i].IsClicked()) {
            return i+1;
        }
    }
    return -1;
}
