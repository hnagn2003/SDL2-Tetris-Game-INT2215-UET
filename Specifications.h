#ifndef Specifications_h
#define Specifications_h
#include "Tetromino.h"


#include "Structure.h"
#include <algorithm> // void updateScoreTable
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Data.h"
#include "Tabs_Menu.h"

bool updateScoreTable(int score);
void printScoreTable(SDL_Renderer *renderer, int x, int y);



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
        HelpsAndCredit()
        {
            inlineTab = H_Helps;
            direct = Helps;
            helpsButton.setPosition(411, 473);
            aboutButton.setPosition(411, 557);
            copyrightButton.setPosition(411, 642);
        }

        Tabs getDirect()
        {
            return direct;
        }

        void setUp(SDL_Renderer* renderer)
        {
            LTexture* helpButtonTex = new LTexture(help_help_buttonP, renderer);
            LTexture* aboutButtonTex = new LTexture(help_about_buttonP, renderer);
            LTexture* copyrightButtonTex = new LTexture(help_copyright_buttonP, renderer);
            LTexture* helpButtonTex_ = new LTexture(help_help_buttonP_, renderer);
            LTexture* aboutButtonTex_ = new LTexture(help_about_buttonP_, renderer);
            LTexture* copyrightButtonTex_ = new LTexture(help_copyright_buttonP_, renderer);
            helpsButton.setTexture(helpButtonTex, helpButtonTex_);
            aboutButton.setTexture(aboutButtonTex, aboutButtonTex_);
            copyrightButton.setTexture(copyrightButtonTex, copyrightButtonTex_);
        }

        void handleEvent(SDL_Event* e)
        {
            bool flag = 0;
            backButton->handleEvents(e, 1);
            if (backButton->getPressed())
            {
                backButton->setPressed(0);
                direct=Menu;
                flag = 1;
                return;
            }
            direct = Helps;
            helpsButton.handleEvents(e);
            if (helpsButton.getPressed())
            {
                helpsButton.setPressed(0);
                inlineTab = H_Helps;
            }
            aboutButton.handleEvents(e);
            if (aboutButton.getPressed())
            {
                aboutButton.setPressed(0);
                inlineTab = H_About;
            }

            copyrightButton.handleEvents(e);
            if (copyrightButton.getPressed())
            {
                copyrightButton.setPressed(0);
                inlineTab = H_Copyright;
            }
        }
        void render(SDL_Renderer* renderer)
        {
            static LTexture helpsBg (helpsBgP, renderer);
            helpsBg.render(renderer, 0, 0);
            backButton->render(renderer, backButton->getXCen()-backButton->getWidth()/2, backButton->getYCen()-backButton->getHeight()/2);
            helpsButton.render(renderer);
            aboutButton.render(renderer);
            copyrightButton.render(renderer);
            static LTexture helpTextTex(help_help_textP, renderer);
            static LTexture aboutTextTex(help_about_textP, renderer);
            static LTexture cpyrightTextTex(help_copyright_textP, renderer);
            switch (inlineTab)
            {
                case H_Helps:
                    helpTextTex.render(renderer, 0, 0);
                    break;
                case H_About:
                    aboutTextTex.render(renderer, 0, 0);
                    break;
                case H_Copyright:
                    cpyrightTextTex.render(renderer, 0, 0);
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