#ifndef Helps_h
#define Helps_h

#include "Data.h"
enum HelpsInlineTabs
{
    H_Helps,
    H_About,
    H_Copyright
};
class HelpsAndCredit
{
    private: 
        HelpsInlineTabs inlineTab;
        Tabs direct;
        LButton helpsButton, aboutButton, copyrightButton;
    public:
        HelpsAndCredit();
        ~HelpsAndCredit();
        Tabs getDirect();
        void setUp(SDL_Renderer* renderer);
        void handleEvent(SDL_Event* e);
        void render(SDL_Renderer* renderer);
};

#endif