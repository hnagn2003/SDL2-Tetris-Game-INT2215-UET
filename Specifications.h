#ifndef Specifications_h
#define Specifications_h
#include "Tetromino.h"
#include <sstream>
#include <iostream>
#include "Structure.h"
#include <map>
#include <vector>
#include <algorithm> // void updateScoreTable
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL.h>
const int settingElementsTotal = 4;
const int TILE_SIZE = 40;
const int ROWS = 20;
const int HIDDEN_ROWS = 10;
const int COLS = 10;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
const int initVelocity = 1000;
const int delimitedLine = -2;
const int delayBeforeDied = 3;
const int scoreMaxMem = 5;
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color DARK_CYAN_COLOR = {0, 190, 190};
const SDL_Color GOLD_YELLOW_COLOR = {255, 204, 53};

const std::string backGroundPicture = "assets/Pictures/cyber_background.png";
const std::string menuPicturePath = "assets/Pictures/tabs_menu.png";
const std::string gameOverBgPath = "assets/Pictures/game_over_path.png";
const std::string play_again_button = "assets/Pictures/play_again_button.png";
const std::string play_again_button_ = "assets/Pictures/play_again_button_.png";

const std::string back_button = "assets/Pictures/return_button.png";
const std::string back_button_ = "assets/Pictures/return_button_.png";

const std::string menuButton[] = {"assets/Pictures/menu_button0.png","assets/Pictures/menu_button1.png","assets/Pictures/menu_button2.png","assets/Pictures/menu_button3.png"};
const std::string menuButton_[] = {"assets/Pictures/menu_button0_.png","assets/Pictures/menu_button1_.png","assets/Pictures/menu_button2_.png","assets/Pictures/menu_button3_.png"};

const std::string grid_frame = "assets/Pictures/GridFrame.png";

const std::string helpsBgP = "assets/Pictures/help_credits.png";
const std::string help_help_buttonP = "assets/Pictures/help_help_button.png";
const std::string help_help_buttonP_ = "assets/Pictures/help_help_button_.png";
const std::string help_about_buttonP = "assets/Pictures/help_about_button.png";
const std::string help_about_buttonP_ = "assets/Pictures/help_about_button_.png";

const std::string help_copyright_buttonP = "assets/Pictures/helpCB.png";

const std::string help_copyright_buttonP_ = "assets/Pictures/help_copyright_button_.png";
const std::string help_help_textP = "assets/Pictures/helps_help_tex.png";

const std::string help_about_textP = "assets/Pictures/helps_about_tex.png";
const std::string help_copyright_textP = "assets/Pictures/helps_copyright_tex.png";

const std::string winnerIconP = "assets/Pictures/winner.png";
const std::string battle_endedP = "assets/Pictures/battle_ended.png";
const std::string drawTextP = "assets/Pictures/draw.png";
const std::string victoryTextP = "assets/Pictures/victory.png";
const std::string player1winP = "assets/Pictures/player1_win.png";
const std::string player2winP = "assets/Pictures/player2_win.png";
const std::string drawP = "assets/Pictures/draw.png";
const std::string tabSettingsP = "assets/Pictures/tabs_settings.png";
const std::string right_pressP = "assets/Pictures/rightPress.png";
const std::string left_pressP = "assets/Pictures/leftPress.png";
const std::string right_pressP_ = "assets/Pictures/rightPress_.png";
const std::string left_pressP_ = "assets/Pictures/leftPress_.png";
const std::string ghostBlockP = "assets/Pictures/ghostBlocks.png";
const std::string clearHighestScoreP = "assets/Pictures/clear_highest_score.png";
const std::string clearSettingsP = "assets/Pictures/clear_settings.png";
const std::string clearHighestScoreP_ = "assets/Pictures/clear_highest_score_.png";
const std::string clearSettingsP_ = "assets/Pictures/clear_settings_.png";
const std::string fontVarino1P = "fonts/VarinonormalRegular-nRYg4.otf";

const std::string ES_MouseClickP = "assets/Sounds/MouseClick.wav";
const std::string se_moveP = "assets/Sounds/se_game_move.wav";
const std::string se_holdP = "assets/Sounds/se_game_hold.wav";
const std::string se_dropP = "assets/Sounds/se_game_harddrop.wav";
const std::string me_startP = "assets/Sounds/me_game_start1.mp3";
// const std::string se_startP = "assets/Sounds/me_game_start2.wav";
const std::string se_doubleP = "assets/Sounds/se_game_double.wav";
const std::string se_pauseP = "assets/Sounds/se_game_pause.wav";
const std::string se_rotateP = "assets/Sounds/se_game_rotate.wav";
const std::string se_countP = "assets/Sounds/se_game_count.wav";
const std::string me_gameoverP = "assets/Sounds/me_game_gameover.mp3";
const std::string se_gameoverP = "assets/Sounds/me_game_gameover.wav";
static Mix_Music* playingSoundtrack;
static Mix_Music* themeSoundtrack;
static Mix_Chunk* ES_MouseClick;
static Mix_Chunk* se_move;
static Mix_Chunk* se_hold;
static Mix_Chunk* se_drop;
static Mix_Music* me_start;
static Mix_Chunk* se_double;
static Mix_Chunk* se_pause;
static Mix_Chunk* se_rotate;
static Mix_Chunk* se_count;
static Mix_Music* me_gameover;
static Mix_Chunk* se_gameover;

extern TTF_Font* gFont1;
extern TTF_Font* fontVarino1;
extern TTF_Font* fontStar_40;
extern TTF_Font* fontStar_50;

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
        void setSize(int w, int h){
            width = w; height = h;
        }
        void setPressed(bool _pressed){
            pressed = _pressed;
        }
        void setTexture(LTexture* _keyUp, LTexture* _keyDown){
            keyUp = _keyUp;
            keyDown = _keyDown;
            width = keyUp->getWidth();
            height = keyUp->getHeight();
        }
        void setPosition( int x, int y ){
            xPos = x; yPos = y;
        }
		void setCenterPosition( int x, int y ){
            xCen = x; yCen = y;
        }
        void handleEvents(SDL_Event* e, bool circleButton = 0){
            if (xPos == 0 && yPos == 0){
                xPos = xCen - width/2, yPos = yCen - height/2;
            }
            motionMouse = 0;
            pressed = 0;
        	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
                int x, y;
		        SDL_GetMouseState( &x, &y );
                bool inside = true;
                if (!circleButton){
                    if (x<xPos){
                        inside = false;
                    }else if (x>xPos+width){
                        inside = false;
                    }else if (y<yPos){
                        inside = false;
                    }else if (y>yPos + height){
                        inside = false;
                    }
                }else{
                    if ( (x-xCen)*(x-xCen) + (y-yCen)*(y-yCen) <= width*width/4 ){
                        
                        inside = true;
                    }else{
                        inside = false;
                    }
                }
                if (inside){
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
		void render(SDL_Renderer* renderer, int x = 0, int y = 0){
            if (x==0&&y==0){
                x=xPos; y = yPos;
            }
            if (motionMouse){
                keyDown->render(renderer, x, y);
            }else{
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
        int direct;
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
        int getDirect(){
            return direct;
        }
        void resetDirect(){
            direct = Menu;
        }
        void handleEvents(SDL_Event* e){
            bool flag = 0;
            for (int i=0; i<allButtonsOfMenu; i++){
                button[i].handleEvents(e);
                if (button[i].getPressed()){
                    button[i].setPressed(0);
                    direct=i;
                    if (direct == InGame_SoloMode){
                        Mix_HaltMusic();
                    }
                    flag = 1;
                    return;
                }
            }

            direct = -1; 
        }
        void setUpMenu(SDL_Renderer* renderer){
            for (int i=0; i<4; i++){
                keyUp[i].loadFromFile(menuButton[i], renderer);
                keyDown[i].loadFromFile(menuButton_[i], renderer);
                button[i].setTexture((keyUp+i), (keyDown+i));
            }
        }
        void render(SDL_Renderer* renderer){
            static LTexture tabMenuBg(menuPicturePath, renderer);
            tabMenuBg.render(renderer, 0, 0);
            for (int i=0; i<4; i++){
                button[i].render(renderer, button[i].getXCen()-button[i].getWidth()/2, button[i].getYCen()-button[i].getHeight()/2);
            }

        }
};

class GameOverAnnouncement{
    public:
        int direct;
    public:
        GameOverAnnouncement(){
            direct = InGame_SoloMode;
        }
        int getDirect(){
            return direct;
        }
        void resetDirect(){
            direct = InGame_SoloMode;
        }

        bool handleEvents(SDL_Event* e){
            bool flag = 0;
            backButton->handleEvents(e, 1);
            if (backButton->getPressed()){
                backButton->setPressed(0);
                direct=Menu;
                flag = 1;
                return false;
            }
            replayButton->handleEvents(e, 1);
            if (replayButton->getPressed()){
                replayButton->setPressed(0);
                direct=InGame_SoloMode;
                flag = 1;
                return true;
            }

            direct = InGame_SoloMode; 
            return false;
        }
        void render(SDL_Renderer* renderer){
            static LTexture gameOverBg(gameOverBgPath, renderer);
            gameOverBg.render(renderer, 0, 0);
            backButton->render(renderer, backButton->getXCen()-backButton->getWidth()/2, backButton->getYCen()-backButton->getHeight()/2);
            replayButton->render(renderer, replayButton->getXCen()-replayButton->getWidth()/2, replayButton->getYCen()-replayButton->getHeight()/2);
            printScoreTable(renderer, 620, 505);
        }
};
class BattleEnded{
    private:
        int direct;
    public:
        BattleEnded(){
            direct = InGame_BattleMode;
        }
        int getDirect(){
            return direct;
        }
        bool handleEvents(SDL_Event* e){
            backButton->handleEvents(e, 1);
            if (backButton->getPressed()){
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
enum HelpsInlineTabs{
    H_Helps,
    H_About,
    H_Copyright
};
class HelpsAndCredit{
    private: 
        int inlineTab;
        int direct;
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

        int getDirect()
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

        void handleEvent(SDL_Event* e){
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
        void render(SDL_Renderer* renderer){
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

enum Shapes{
    I_BLOCK,
    L_BLOCK,
    J_BLOCK,
    O_BLOCK,
    S_BLOCK,
    T_BLOCK,
    Z_BLOCK,
    TOTAL_OF_TETRADS
};

const SDL_Color TetroColor[] = {
    {0, 209, 232},
    {0, 126, 229},
    {218, 147, 0},
    {232, 214, 0},
    {0, 222, 61},
    {187, 0, 222},
    {232, 0, 0}
};


enum LEVEL{
    easy = 20,
    hard = 15,
    extremely_hard = 10,
    super_ultra_hard = 5,
    asian = 1
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

// struct PointOnGrid{
//     int x;
//     int y;
//     PointOnGrid(int _x = 0, int _y = 0){
//         x = (SCREEN_WIDTH - COLS*TILE_SIZE) / 2 + _x*TILE_SIZE;
//         y = (SCREEN_HEIGHT - ROWS*TILE_SIZE) / 2 + _y*TILE_SIZE;
//     }
// };
// chuyển tọa độ trong grid về tọa độ thực (tọa độ render ra màn hình)
int gridSizeToRendererSize(int w);
int gridXPosToRendererPos(int x);
int gridYPosToRendererPos(int y);

class block{
    public:
        int xReal, yReal;
        int xGrid, yGrid, wGrid = 1, hGrid = 1;
        int type;  
        bool exist;
        block(){
            exist = false;
        }
        block(int x, int y, int _type, int realCoordinates = 0){
            if (realCoordinates){
                xReal = x;
                yReal = y;
            }else{
                xGrid = x;
                yGrid = y;
            }
            type = _type;
            exist = false;
        }
        int getXGrid(){
            return xGrid;
        }
        int getYGrid(){
            return yGrid;
        }
        int getWGrid(){
            return wGrid;
        }
        int getHGrid(){
            return hGrid;
        }

        void render(SDL_Renderer* renderer, int gridXPos, int realCoordinates = 0, bool ghost = 0){
            // SDL_Rect rectBlock{gridXPosToRendererPos(xGrid)+gridXPos, gridYPosToRendererPos(yGrid), gridSizeToRendererSize(wGrid), gridSizeToRendererSize(hGrid)};
            // SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, 0 );
            static LTexture blockTemp("assets/Pictures/7block.png", renderer);
            static LTexture ghostBlockTex(ghostBlockP, renderer);
            SDL_Rect clip{type*TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
            if (!ghost){
                if (realCoordinates){
                    blockTemp.render(renderer, xReal+gridXPos, yReal, &clip);
                }else{
                    blockTemp.render(renderer, gridXPosToRendererPos(xGrid)+gridXPos, gridYPosToRendererPos(yGrid), &clip);
                }
            }else{
                if (realCoordinates){
                    ghostBlockTex.render(renderer, xReal+gridXPos, yReal, &clip);
                }else{
                    ghostBlockTex.render(renderer, gridXPosToRendererPos(xGrid)+gridXPos, gridYPosToRendererPos(yGrid), &clip);
                }
            }
        }
};  
// xử lý fps: print, capping
class FPS_Processor{
    public:
        long long countedFrames;
        LTexture* gFPSTextTexture;
        LTimer* fpsTimer;
        LTimer* capTimer;
    public:
        FPS_Processor(){
            countedFrames = 0;
            gFPSTextTexture = new LTexture;
            fpsTimer = new LTimer;
            capTimer = new LTimer;
        }
        ~FPS_Processor(){
            gFPSTextTexture->free();
        }
        void initTimeCounting(){
            fpsTimer->start();
        }
        void cappingFrame(){
            capTimer->start();
            ++countedFrames;
            int frameTicks = capTimer->getTicks();
            if( frameTicks < SCREEN_TICK_PER_FRAME )
            {
                //Wait remaining time
                SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
            }
        }
        void printFPS(SDL_Renderer* renderer, TTF_Font* gFont){
            int avgFPS = countedFrames / ( fpsTimer->getTicks() / 1000.f );
            std::stringstream timeText;
            timeText.str( "" );
            timeText << "FPS: " << avgFPS; 
            SDL_Color textColor = { 0, 0, 0, 255 };
            if( !gFPSTextTexture->loadFromRenderedText( timeText.str().c_str(), textColor, gFont, renderer ))
            {
                printf( "Unable to render FPS texture!\n" );
	        }
            gFPSTextTexture->render( renderer,( SCREEN_WIDTH - gFPSTextTexture->getWidth() ), 0 );
        }
};



#endif