#ifndef Settings_h
#define Settings_h
#include "Specifications.h"

enum clear_button
{
    clearScore,
    clearUserSettings,
    totalOfClearButton
};
class UserSettings
{
    private:
        LButton setButton[settingElementsTotal][2];
        LButton clearButton[2];
        Tabs direct;
    public:
        UserSettings();
        ~UserSettings();
        Tabs getDirect();
        void resetDirect();
        void initSettings(SDL_Renderer* renderer);
        void handleOption(int option, int adjust);
        void handleEvents(SDL_Event* e);
        void update();

        void render(SDL_Renderer* renderer);
        std::string getSettingContents(int jInd, auto it);
};
#endif

