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
        UserSettings()
        {
            direct = Settings;
            for (int i=0; i<settingElementsTotal; i++)
            {
                    setButton[i][0].setPosition(1070, 460+60*i);
                    setButton[i][1].setPosition(1270, 460+60*i);
            }
            for (int i=0; i<totalOfClearButton; i++)
            {
                clearButton[i].setPosition(700 + 320*i, 700 ); //...
            }
        }
        ~UserSettings()
        {

        }
        Tabs getDirect()
        {
            return direct;
        }
        void resetDirect()
        {
            direct = Settings;  
        }
        void initSettings(SDL_Renderer* renderer)
        {
            static LTexture* leftPress = new LTexture(left_pressP, renderer);
            static LTexture* rightPress = new LTexture(right_pressP, renderer);
            static LTexture* leftPress_ = new LTexture(left_pressP_, renderer);
            static LTexture* rightPress_ = new LTexture(right_pressP_, renderer);
            for (int i=0; i<settingElementsTotal; i++){
                setButton[i][0].setTexture(leftPress, leftPress_);
                setButton[i][1].setTexture(rightPress, rightPress_);
            }
            static LTexture* clearButtonTex[2];
            static LTexture* clearButtonTex_[2];
            clearButtonTex[clearScore] = new LTexture(clearHighestScoreP, renderer);
            clearButtonTex[clearUserSettings] = new LTexture(clearSettingsP, renderer);
            clearButtonTex_[clearScore] = new LTexture(clearHighestScoreP_, renderer);
            clearButtonTex_[clearUserSettings] = new LTexture(clearSettingsP_, renderer);
            for (int i=0; i<totalOfClearButton; i++){
                clearButton[i].setTexture(clearButtonTex[i], clearButtonTex_[i]);
            }
        }
        void handleOption(int option, int adjust)
        {
            switch (option)
            {
            case 1:
                if (adjust == 1 && settingsElement["Level"] > asian){
                    settingsElement["Level"] -= 5;
                    if (settingsElement["Level"] <= 0)
                    {
                        settingsElement["Level"] = 1;
                    }
                }
                if (adjust == 0 && settingsElement["Level"] < easy){
                    settingsElement["Level"] += 5;
                }
                break;
            case 2:
                if (adjust == 1)
                {
                    settingsElement["Music Volume"] +=20;
                }
                if (adjust == 0)
                {
                    settingsElement["Music Volume"] -=20;
                }
                if (settingsElement["Music Volume"] > 100){
                    settingsElement["Music Volume"] = 100;
                }
                if (settingsElement["Music Volume"] < 0){
                    settingsElement["Music Volume"] = 0;
                }
                break;
            case 3:
                if (settingsElement["Sound Effects"] == 0)
                {
                    settingsElement["Sound Effects"] = 1;
                }
                else
                {
                    settingsElement["Sound Effects"] = 0;
                }
                break;
            case 0:
                if (settingsElement["Ghost Piece"] == 0)
                {
                    settingsElement["Ghost Piece"] = 1;
                }
                else
                {
                    settingsElement["Ghost Piece"] = 0;
                }
                break;
            case 4:
                clearRankingScore();
                break;
            case 5:
                clearSettings();
                break;
            default:
                break;
            }
        }
        void handleEvents(SDL_Event* e)
        {
            backButton->handleEvents(e, 1);
            if (backButton->getPressed()){
                backButton->setPressed(0);
                direct=Menu;
                return;
            }
            for (int i=0; i<settingElementsTotal; i++)
            {
                for (int j=0; j<2; j++)
                {
                    setButton[i][j].handleEvents(e);
                    if (setButton[i][j].getPressed())
                    {
                        setButton[i][j].setPressed(0);
                        handleOption(i, j);
                    }
                }
            }
            for (int i=0; i<totalOfClearButton; i++)
            {
                clearButton[i].handleEvents(e);
                if (clearButton[i].getPressed())
                {
                    handleOption(i+settingElementsTotal, 0);
                }
            }
            direct = Settings;
        }
        void update()
        {
            Mix_VolumeMusic(settingsElement["Music Volume"]);
        }

        void render(SDL_Renderer* renderer)
        {
            static LTexture tab_st(tabSettingsP, renderer);
            tab_st.render(renderer, 0, 0);
            int jInd = 0;
            for (auto it=settingsElement.begin(); it!=settingsElement.end(); it++)
            {
                LTexture tmp;
                tmp.loadFromRenderedText(it->first, CYAN_COLOR, fontVarino1, renderer);
                tmp.render(renderer, 800, 460+jInd*60);
                setButton[jInd][0].render(renderer, 1070, 460+jInd*60);
                setButton[jInd][1].render(renderer, 1270, 460+jInd*60);
                LTexture tmp2;
                std::string content;
                switch(jInd)
                {
                    case 0:
                        switch(it->second)
                        {
                            case 0:
                                content = "off";
                                break;
                            case 1:
                                content = "on";
                                break;
                            default:
                                std::cout << "Invalid Settings Value" << std::endl;
                                // exit(0);
                                break;
                        }
                        break;

                    case 1:
                        switch (it->second)
                        {
                        case easy:
                            content = "easy";
                            break;
                        case hard:
                            content = "hard";
                            break;
                        case extremely_hard:
                            content = "super hard";
                            break;
                        case super_ultra_hard:
                            content = "ultra hard";
                            break;
                        case asian:
                            content = "asian";
                            break;
                        default:
                            std::cout << "Invalid Settings Value" << std::endl;
                            // exit(0);
                            break;
                        }
                        break;

                    case 3:
                        switch(it->second)
                        {
                            case 0:
                                content = "off";
                                break;
                            case 1:
                                content = "on";
                                break;
                            default:
                                std::cout << "Invalid Settings Value" << std::endl;
                                // exit(0);
                                break;
                        }
                        break;

                    default:
                        content = std::to_string(it->second);
                        break;

                }
                tmp2.loadFromRenderedText(content, CYAN_COLOR, fontVarino1, renderer);
                tmp2.render(renderer, 1100, 460+jInd*60);
                jInd++;
            }
            for (int i=0; i<totalOfClearButton; i++)
            {
                clearButton[i].render(renderer, clearButton[i].getXPos(), clearButton[i].getYPos());
            }
            backButton->render(renderer, backButton->getXCen()-backButton->getWidth()/2, backButton->getYCen()-backButton->getHeight()/2);
            static Uint32 flag = 0;
            static LTexture clearedText("Data is cleared!", CYAN_COLOR, fontVarino1, renderer);
            if (clearButton[0].getPressed())
            {
                flag = SDL_GetTicks();
            }
            if (SDL_GetTicks() - flag <= 1000)
            {
                clearedText.render(renderer, 730, 780);
                return;
            }
            flag = 0;
        }
};
#endif

