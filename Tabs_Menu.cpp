#include "Game.h"
#include "Tabs_Menu.h"

Tabs_Menu::Tabs_Menu(){
    direct = Menu;
    button[InGame_SoloMode].setCenterPosition(703, 549);//...
    button[InGame_BattleMode].setCenterPosition(1208, 549);
    button[Settings].setCenterPosition(703, 736);
    button[Helps].setCenterPosition(1208, 736);
}
Tabs_Menu::~Tabs_Menu(){

}
Tabs Tabs_Menu::getDirect(){return direct;}
void Tabs_Menu::resetDirect(){direct = Menu;}
void Tabs_Menu::handleEvents(SDL_Event* e)
{
    bool flag = 0;
    for (int i=0; i<allButtonsOfMenu; i++)
    {
        button[i].handleEvents(e);
        if (button[i].getPressed())
        {
            button[i].setPressed(0);
            direct=(Tabs)i;
            if (direct == InGame_SoloMode)
            {
                Mix_HaltMusic();
            }
            flag = 1;
            return;
        }
    }

    direct = Menu; 
}
void Tabs_Menu::setUpMenu(SDL_Renderer* renderer)
{
    for (int i=0; i<4; i++)
    {
        keyUp[i].loadFromFile(menuButton[i], renderer);
        keyDown[i].loadFromFile(menuButton_[i], renderer);
        button[i].setTexture((keyUp+i), (keyDown+i));
    }
}
void Tabs_Menu::render(SDL_Renderer* renderer)
{
    static LTexture tabMenuBg(menuPicturePath, renderer);
    tabMenuBg.render(renderer, 0, 0);
    for (int i=0; i<4; i++)
    {
        button[i].render(renderer, button[i].getXCen()-button[i].getWidth()/2, button[i].getYCen()-button[i].getHeight()/2);
    }
    static LTexture logoTex(logoP, renderer);
    logoTex.render(renderer, 0 ,0);
}