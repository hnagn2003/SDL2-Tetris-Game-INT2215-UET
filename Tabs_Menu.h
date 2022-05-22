#ifndef Menu_h
#define Menu_h
#include "Data.h"

class Tabs_Menu{
    public:
        LButton button[allButtonsOfMenu];
        LTexture keyUp[4], keyDown[4];
        Tabs direct;
    public:
        Tabs_Menu(){
            direct = Menu;
            button[InGame_SoloMode].setCenterPosition(703, 549);//...
            button[InGame_BattleMode].setCenterPosition(1208, 549);
            button[Settings].setCenterPosition(703, 736);
            button[Helps].setCenterPosition(1208, 736);
        }
        ~Tabs_Menu(){

        }
        Tabs getDirect(){return direct;}
        void resetDirect(){direct = Menu;}
        void handleEvents(SDL_Event* e)
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
        void setUpMenu(SDL_Renderer* renderer)
        {
            for (int i=0; i<4; i++)
            {
                keyUp[i].loadFromFile(menuButton[i], renderer);
                keyDown[i].loadFromFile(menuButton_[i], renderer);
                button[i].setTexture((keyUp+i), (keyDown+i));
            }
        }
        void render(SDL_Renderer* renderer)
        {
            static LTexture tabMenuBg(menuPicturePath, renderer);
            tabMenuBg.render(renderer, 0, 0);
            for (int i=0; i<4; i++)
            {
                button[i].render(renderer, button[i].getXCen()-button[i].getWidth()/2, button[i].getYCen()-button[i].getHeight()/2);
            }

        }
};
#endif