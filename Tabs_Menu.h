#ifndef Menu_h
#define Menu_h
#include "Data.h"

class Tabs_Menu{
    public:
        LButton button[allButtonsOfMenu];
        LTexture keyUp[4], keyDown[4];
        Tabs direct;
    public:
        Tabs_Menu();
        ~Tabs_Menu();
        Tabs getDirect();
        void resetDirect();
        void handleEvents(SDL_Event* e);
        void setUpMenu(SDL_Renderer* renderer);
        void render(SDL_Renderer* renderer);
};
#endif