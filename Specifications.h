#ifndef Specifications_h
#define Specifications_h
#include "Tetromino.h"
#include <sstream>
#include <iostream>
#include "Structure.h"
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
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const std::string rFont = "MTO Grunge Sans Shadow.ttf";
const std::string menuPicturePath = "assets/Pictures/tabs_menu.png";
const std::string menuButton[] = {"assets/Pictures/menu_button0.png","assets/Pictures/menu_button1.png","assets/Pictures/menu_button2.png","assets/Pictures/menu_button3.png"};
const std::string grid_frame = "assets/Pictures/GridFrame.png";
static TTF_Font* gFont1;
enum Tabs {
    Menu = -1,
    InGame_SoloMode,
    HighestScoreTable,
    InGame_BattleMode,
    Settings,
    ExitGame,
    Helps,
    About,
    allButtonsOfMenu
};
class LButton
{
    public:
		LTexture keyUp;
        LTexture keyDown;
        bool inside;
        bool motionMouse;
        bool pressed;
        int xPos, yPos, width, height;
        
	public:
		LButton(){
            inside = 0;
            pressed = 0;
        }
        LButton(LTexture _keyUp, LTexture _keyDown){
            motionMouse = 0;
            keyUp = _keyUp;
            keyDown = _keyDown;
            width = keyUp.getWidth();
            height = keyUp.getHeight();
        }
        bool getPressed(){
            return pressed;
        }
        bool getInside(){
            return inside;
        }
        int getXPos(){return xPos;}
        int getYPos(){return yPos;}
        void setPressed(bool _pressed){
            pressed = _pressed;
        }
        void setTexture(const LTexture& _keyUp, const LTexture& _keyDown){
            keyUp = _keyUp;
            keyDown = _keyDown;
            width = keyUp.getWidth();
            height = keyUp.getHeight();
        }
		void setPosition( int x, int y ){
            xPos = x; yPos = y;
        }
        void handleEvents(SDL_Event* e){
            motionMouse = 0;
            pressed = 0;
        	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
                int x, y;
		        SDL_GetMouseState( &x, &y );
                bool inside = true;
                if (x<xPos){
                    inside = false;
                }else if (x>xPos+width){
                    inside = false;
                }else if (y<yPos){
                    inside = false;
                }else if (y>yPos + height){
                    inside = false;
                }

                if (inside){
                    switch (e->type)
                    {
                        case SDL_MOUSEMOTION:
                            motionMouse = 1;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
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
                keyDown.render(renderer, x, y);
            }else{
                keyUp.render(renderer, x, y);
            }
        }

};

class Tabs_Menu{
    public:
        LButton button[allButtonsOfMenu];
        LTexture keyUp[4], keyDown[4];
        int direct;
    public:
        Tabs_Menu(){
            direct = -1;
            button[InGame_SoloMode].setPosition(560, 439);//...
            button[HighestScoreTable].setPosition(986, 439);
            button[InGame_BattleMode].setPosition(560, 557);
            button[Settings].setPosition(986, 557);
        }
        ~Tabs_Menu(){

        }
        int getDirect(){
            return direct;
        }
        void resetDirect(){
            direct = -1;
        }
        void handleEvents(SDL_Event* e){
            bool flag = 0;
            for (int i=0; i<allButtonsOfMenu; i++){
                button[i].handleEvents(e);
                if (button[i].getPressed()){
                    button[i].setPressed(0);
                    direct=i;
                    flag = 1;
                    break;
                }
            }
            if (flag){
                return;
            }
            direct = -1; 
        }
        void setUpMenu(SDL_Renderer* renderer){
            for (int i=0; i<4; i++){
                keyUp[i].loadFromFile(menuButton[i], renderer);
                button[i].setTexture(keyUp[i], keyDown[i]);
            }
        }
        void render(SDL_Renderer* renderer){
            for (int i=0; i<4; i++){
                button[i].render(renderer, button[i].getXPos(), button[i].getYPos());
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
const SDL_Color backgroundColor = {0, 0, 0};

enum LEVEL{
    easy = 20,
    hard = 13,
    extremely_hard = 9,
    super_ultra_hard = 5,
    asian = 1
};

struct Point{
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
        int xGrid, yGrid, wGrid = 1, hGrid = 1;
        int type;  
        bool exist;
        block(){
            exist = false;
        }
        block(int x, int y, int _type){
            xGrid = x;
            yGrid = y;
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

        void render(SDL_Renderer* renderer, int gridXPos){
            // SDL_Rect rectBlock{gridXPosToRendererPos(xGrid)+gridXPos, gridYPosToRendererPos(yGrid), gridSizeToRendererSize(wGrid), gridSizeToRendererSize(hGrid)};
            // SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, 0 );
            static LTexture blockTemp("assets/Pictures/7block.png", renderer);
            SDL_Rect clip{type*TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
            blockTemp.render(renderer, gridXPosToRendererPos(xGrid)+gridXPos, gridYPosToRendererPos(yGrid), &clip);
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