#ifndef Specifications_h
#define Specifications_h
#include "Tetromino.h"


#include "Structure.h"
#include <algorithm> // void updateScoreTable
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Data.h"
#include "GameState.h"
#include "Tabs_Menu.h"
#include "Tabs_Helps.h"
bool updateScoreTable(int score);
void printScoreTable(SDL_Renderer *renderer, int x, int y);
void renderText(long long text, SDL_Renderer* renderer, TTF_Font* gFont, int xCenter, int yCenter, SDL_Color textColor = WHITE_COLOR);



class GameOverAnnouncement
{
    public:
        Tabs direct;
    public:
        GameOverAnnouncement()
        {
            direct = InGame_SoloMode;
        }
        Tabs getDirect()
        {
            return direct;
        }
        void resetDirect()
        {
            direct = InGame_SoloMode;
        }

        bool handleEvents(SDL_Event* e)
        {
            bool flag = 0;
            backButton->handleEvents(e, 1);
            if (backButton->getPressed())
            {
                backButton->setPressed(0);
                direct=Menu;
                flag = 1;
                return false;
            }
            replayButton->handleEvents(e, 1);
            if (replayButton->getPressed())
            {
                replayButton->setPressed(0);
                direct=InGame_SoloMode;
                flag = 1;
                return true;
            }

            direct = InGame_SoloMode; 
            return false;
        }
        void render(SDL_Renderer* renderer)
        {
            static LTexture gameOverBg(gameOverBgPath, renderer);
            gameOverBg.render(renderer, 0, 0);
            backButton->render(renderer, backButton->getXCen()-backButton->getWidth()/2, backButton->getYCen()-backButton->getHeight()/2);
            replayButton->render(renderer, replayButton->getXCen()-replayButton->getWidth()/2, replayButton->getYCen()-replayButton->getHeight()/2);
            printScoreTable(renderer, 620, 505);
        }
};
class BattleEnded
{
    private:
        Tabs direct;
    public:
        BattleEnded()
        {
            direct = InGame_BattleMode;
        }
        Tabs getDirect()
        {
            return direct;
        }
        bool handleEvents(SDL_Event* e)
        {
            backButton->handleEvents(e, 1);
            if (backButton->getPressed())
            {
                backButton->setPressed(0);
                direct=Menu;
                return false;
            }
            replayButton->handleEvents(e, 1);
            if (replayButton->getPressed())
            {
                replayButton->setPressed(0);
                direct=InGame_BattleMode;
                return true;
            }

            direct = InGame_BattleMode; 
            return false;
        }
        void render(SDL_Renderer* renderer, int result)
        {
            static LTexture battle_endTex(battle_endedP, renderer);
            battle_endTex.render(renderer, 0, 0);
            backButton->render(renderer, backButton->getXCen()-backButton->getWidth()/2, backButton->getYCen()-backButton->getHeight()/2);
            replayButton->render(renderer, replayButton->getXCen()-replayButton->getWidth()/2, replayButton->getYCen()-replayButton->getHeight()/2);
            switch (result)
            {
            case 0:
                static LTexture drawTex(drawP, renderer);
                drawTex.render(renderer, 0, 0);
                break;
            case 1:
                static LTexture player1winTex(player1winP, renderer);
                player1winTex.render(renderer, 0, 0);
                break;
            case 2:
                static LTexture player2winTex(player2winP, renderer);
                player2winTex.render(renderer, 0, 0);
                break;
            default:
                break;
            }
        }
};


void clearSettings();
void clearRankingScore();

// chuyển tọa độ trong grid về tọa độ thực (tọa độ render ra màn hình)
int gridSizeToRendererSize(int w);
int gridXPosToRendererPos(int x);
int gridYPosToRendererPos(int y);




#endif