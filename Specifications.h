#ifndef Specifications_h
#define Specifications_h
#include "Tetromino.h"


#include "Structure.h"
#include <map>
#include <vector>
#include <algorithm> // void updateScoreTable
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Data.h"


extern std::vector<int> highestScore;
extern std::map<std::string, int> settingsElement;

enum Tabs {
    Menu = -1,
    InGame_SoloMode,
    InGame_BattleMode,
    Settings,
    Helps,
    ExitGame,
    allButtonsOfMenu
};
enum GameMode {
    Player1,
    SinglePlay,
    Player2
};
bool updateScoreTable(int score);
void playSoundEffects(Mix_Chunk* chunk, int loop = 0, int channel = -1);
void printScoreTable(SDL_Renderer *renderer, int x, int y);
class LButton
{
    public:
		LTexture* keyUp;
        LTexture* keyDown;
        bool inside;
        bool motionMouse;
        bool pressed;
        int xCen, yCen, width, height;
        int xPos, yPos;
	public:
		LButton(){
            keyDown = new LTexture;
            keyUp = new LTexture;
            inside = 0;
            pressed = 0;
            xPos = 0; yPos = 0; xCen = 0; yCen = 0;
        }
        LButton(LTexture* _keyUp, LTexture* _keyDown)
        {
            motionMouse = 0;
            keyUp = _keyUp;
            keyDown = _keyDown;
            width = keyUp->getWidth();
            height = keyUp->getHeight();
            xPos = 0; yPos = 0; xCen = 0; yCen = 0;
        }
        bool getPressed()
        {
            return pressed;
        }
        bool getInside()
        {
            return inside;
        }
        int getXCen(){return xCen;}
        int getYCen(){return yCen;}
        int getXPos(){return xPos;}
        int getYPos(){return yPos;}
        int getWidth(){return width;}
        int getHeight(){return height;}
        void setSize(int w, int h){width = w; height = h;}
        void setPressed(bool _pressed){pressed = _pressed;}
        void setTexture(LTexture* _keyUp, LTexture* _keyDown)
        {
            keyUp = _keyUp;
            keyDown = _keyDown;
            width = keyUp->getWidth();
            height = keyUp->getHeight();
        }
        void setPosition( int x, int y )
        {
            xPos = x; yPos = y;
        }
		void setCenterPosition( int x, int y )
        {
            xCen = x; yCen = y;
        }
        void handleEvents(SDL_Event* e, bool circleButton = 0)
        {
            if (xPos == 0 && yPos == 0)
            {
                xPos = xCen - width/2, yPos = yCen - height/2;
            }
            motionMouse = 0;
            pressed = 0;
        	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
            {
                int x, y;
		        SDL_GetMouseState( &x, &y );
                bool inside = true;
                if (!circleButton)
                {
                    if (x<xPos)
                    {
                        inside = false;
                    }
                    else if (x>xPos+width)
                    {
                        inside = false;
                    }
                    else if (y<yPos)
                    {
                        inside = false;
                    }
                    else if (y>yPos + height)
                    {
                        inside = false;
                    }
                }
                else
                {
                    if ( (x-xCen)*(x-xCen) + (y-yCen)*(y-yCen) <= width*width/4 )
                    {
                        
                        inside = true;
                    }else
                    {
                        inside = false;
                    }
                }
                if (inside)
                {
                    switch (e->type)
                    {
                        case SDL_MOUSEMOTION:
                            motionMouse = 1;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            playSoundEffects(ES_MouseClick);
                            motionMouse = 1;
                            pressed = 1;
                            break;
                        case SDL_MOUSEBUTTONUP:
                            pressed = 0;
                            break;
                        default:
                            break;
                    }
                }
            }
    
        }
		void render(SDL_Renderer* renderer, int x = 0, int y = 0)
        {
            if (x==0&&y==0)
            {
                x=xPos; y = yPos;
            }
            if (motionMouse)
            {
                keyDown->render(renderer, x, y);
            }
            else
            {
                keyUp->render(renderer, x, y);
            }
        }

};
static LButton* backButton = new LButton;
static LButton* replayButton = new LButton;

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
struct Point
{
    int x;
    int y;
    Point(int _x, int _y){
        x = _x;
        y = _y;
    }
};

// chuyển tọa độ trong grid về tọa độ thực (tọa độ render ra màn hình)
int gridSizeToRendererSize(int w);
int gridXPosToRendererPos(int x);
int gridYPosToRendererPos(int y);




#endif