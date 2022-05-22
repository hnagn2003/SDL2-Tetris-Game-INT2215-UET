#ifndef Game_h
#define Game_h

// #include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
// #include <SDL_ttf.h>

#include "Tetromino.h"
#include "Grid.h"
#include "Specifications.h"
// #include <iostream>
// #include "Structure.h"
#include <thread>
#include <cstdint>
#include <functional>
#include <string>
#include "GameState.h"


class BallteProcessor{
    private:
        Game_State *gameStatePlayer1;
        Game_State *gameStatePlayer2;
        BattleEnded* battleEnded;
        Tabs direct;
        bool isOver;
        int result;
    public:
        
        BallteProcessor()
        {
            direct = InGame_BattleMode;
            gameStatePlayer1 = new Game_State;
            gameStatePlayer2 = new Game_State;
            battleEnded = new BattleEnded;
            isOver = 0;
            result = -1;
        }
        Game_State *getGameState1()
        {
            return gameStatePlayer1;
        }
        void reset()
        {
            gameStatePlayer1->reset();
            gameStatePlayer2->reset();
            isOver = 0;
            result = -1;
        }
        bool getOver()
        {
            return isOver;
        }
        Tabs getDirect()
        {
            return direct;
        }
        void handleEvent(SDL_Event event)
        {
            if (isOver){
                gameStatePlayer1->pauseGame();
                gameStatePlayer2->pauseGame();
                if (battleEnded->handleEvents(&event))
                {
                    reset();
                }
                direct = battleEnded->getDirect();
                return;
            }
            switch (event.type)
            {   
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym )
                    { 
                        case SDLK_p: 
                            if(!gameStatePlayer1->getPause() && !gameStatePlayer2->getPause())
                            {
                                gameStatePlayer1->pauseGame();
                                gameStatePlayer2->pauseGame();
                            }
                            else
                            {
                                gameStatePlayer1->startCD();
                                gameStatePlayer2->startCD();
                            }
                            return;
                    
                        default: break;
                            
                    }
                default: break;
            }
            std::thread x(&Game_State::handleEvent, gameStatePlayer1, event, Player1);
            std::thread y(&Game_State::handleEvent, gameStatePlayer2, event, Player2);
            x.join();
            y.join();
            direct = gameStatePlayer1->getDirect();
            if (direct == InGame_SoloMode)
            {
                direct = InGame_BattleMode;
            }else
            {
                *gameStatePlayer1 = Game_State();
                *gameStatePlayer2 = Game_State();
            }
        }
        void update()
        {
            isOver = gameOver();
            // std::thread x(&Game_State::update, gameStatePlayer1, 0);
            // std::thread y(&Game_State::update, gameStatePlayer2, 1);
            // x.join();
            // y.join();
            gameStatePlayer1->update(Player1);
            gameStatePlayer2->update(Player2);
            static bool battleOver_SE = true;
            if (isOver)
            {
                if (battleOver_SE){
                    playSoundEffects(se_gameover);
                    battleOver_SE = false;
                }
                return;
            }
            battleOver_SE = true;
        }
        void render(SDL_Renderer* renderer)
        {
            gameStatePlayer1->render(renderer, Player1);
            gameStatePlayer2->render(renderer, Player2);
            if (isOver){
                battleEnded->render(renderer, result);
            }
        }
        bool gameOver()
        {
            bool P1Over = gameStatePlayer1->gameOver(), P2Over = gameStatePlayer2->gameOver();
            long long P1Score = gameStatePlayer1->getScore(), P2Score = gameStatePlayer2->getScore();
            if (P1Over && P2Over)
            {
                if (P1Score > P2Score)
                {
                    result = 1;
                }
                else if (P1Score < P2Score)
                {
                    result = 2;
                }
                else
                {
                    result = 0;
                }
            }
            if (P1Over && !P2Over)
            {
                result = 2;
            }
            if (!P1Over && P2Over)
            {
                result = 1;
            }
            return (result != -1);
        }
};
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
class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int xPos, int yPos, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen);
    void loadmedia();
    void handleEvents();
    void playMusic();
    void update();
    void render();
    void clean();
    bool running()
    {
        return isRunning;
    }
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    FPS_Processor* gFPS_Processor;
    Game_State *gameState;
    BallteProcessor* battleProcessor;
    int tabs;
    Tabs_Menu tabs_menu;
    HelpsAndCredit* helpsAndCredit;
    UserSettings* userSettings;
};


#endif