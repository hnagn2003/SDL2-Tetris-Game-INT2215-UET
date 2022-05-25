#include "Game.h"
#include "Tabs_Settings.h"

UserSettings::UserSettings()
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
UserSettings::~UserSettings()
{
    for (int i=0; i<settingElementsTotal; i++){
        delete[] setButton[i];
    }
    delete[] setButton;
    delete[] clearButton;
}
Tabs UserSettings::getDirect()
{
    return direct;
}
void UserSettings::resetDirect()
{
    direct = Settings;  
}
void UserSettings::initSettings(SDL_Renderer* renderer)
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
void UserSettings::handleOption(int option, int adjust)
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
void UserSettings::handleEvents(SDL_Event* e)
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
void UserSettings::update()
{
    Mix_VolumeMusic(settingsElement["Music Volume"]);
}

void UserSettings::render(SDL_Renderer* renderer)
{
    static LTexture tab_st(tabSettingsP, renderer);
    tab_st.render(renderer, 0, 0);
    int jInd = 0;
    for (auto it=settingsElement.begin(); it!=settingsElement.end(); it++)
    {
        renderText(it->first, renderer, fontVarino1, 900, 470+jInd*60, CYAN_COLOR);
        setButton[jInd][0].render(renderer, 1070, 460+jInd*60);
        setButton[jInd][1].render(renderer, 1270, 460+jInd*60);
        renderText(getSettingContents(jInd, it), renderer, fontVarino1, 1180, 475+jInd*60, CYAN_COLOR);
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
std::string UserSettings::getSettingContents(int jInd, auto it)
{
switch(jInd)
    {
        case 0:
            switch(it->second)
            {
                case 0:
                    return "off";
                    break;
                case 1:
                    return "on";
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
                return "easy";
                break;
            case hard:
                return "hard";
                break;
            case extremely_hard:
                return "super hard";
                break;
            case super_ultra_hard:
                return "ultra hard";
                break;
            case asian:
                return "asian";
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
                    return "off";
                    break;
                case 1:
                    return "on";
                    break;
                default:
                    std::cout << "Invalid Settings Value" << std::endl;
                    // exit(0);
                    break;
            }
            break;

        default:
            return std::to_string(it->second);
            break;

    }
}