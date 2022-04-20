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
const std::string rFont = "MTO Grunge Sans Shadow.ttf";
const std::string menuPicturePath = "assets/Pictures/menu.png";

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
    easy = 1000,
    hard = 600,
    extremely_hard = 300,
    super_ultra_hard = 100,
    asian = 30
};

struct Point{
    int x;
    int y;
    Point(int _x, int _y){
        x = _x;
        y = _y;
    }
};

struct PointOnGrid{
    int x;
    int y;
    PointOnGrid(int _x = 0, int _y = 0){
        x = (SCREEN_WIDTH - COLS*TILE_SIZE) / 2 + _x*TILE_SIZE;
        y = (SCREEN_HEIGHT - ROWS*TILE_SIZE) / 2 + _y*TILE_SIZE;
    }
};
// chuyển tọa độ trong grid về tọa độ thực (tọa độ render ra màn hình)
int gridSizeToRendererSize(int w);
int gridXPosToRendererPos(int x);
int gridYPosToRendererPos(int y);

class block{
    public:
        int xGrid, yGrid, wGrid = 1, hGrid = 1;
        SDL_Color color;  
        bool exist;
        block(){
            exist = false;
        }
        block(int x, int y, SDL_Color _color){
            xGrid = x;
            yGrid = y;
            color = _color;
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

        void render(SDL_Renderer* renderer){
            SDL_Rect rectBlock{gridXPosToRendererPos(xGrid), gridYPosToRendererPos(yGrid), gridSizeToRendererSize(wGrid), gridSizeToRendererSize(hGrid)};
            SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, 0 );
            SDL_RenderFillRect(renderer, &rectBlock);
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
enum allButton{
    START_BUTTON,
    LEVEL_SETUP_BUTTON,
    HIGH_SCORE,
    SETTINGS_BUTTON,
    HELP_BUTTON,
    ABOUT_BUTTON
};
class LButton
{
	public:
		LButton(){
            motionMouse = 0;
        }
        LButton(LTexture* _keyUp, LTexture* _keyDown){
            motionMouse = 0;
            keyUp = _keyUp;
            keyDown = _keyDown;
        }
        void setTexture(LTexture* _keyUp, LTexture* _keyDown){
            keyUp = _keyUp;
            keyDown = _keyDown;
        }
		void setPosition(){}
		void render(SDL_Renderer* renderer, int x, int y){
            if (motionMouse){
                keyDown->render(renderer, x, y);
            }else{
                keyUp->render(renderer, x, y);
            }
        }

	private:
		LTexture* keyUp;
        LTexture* keyDown;
        bool motionMouse;
        bool isPressing;
};

class Menu{
    public:
        LTexture background;
        int level;
        
    public:
        Menu(SDL_Renderer* gRenderer){
            level = 1;
            background.loadFromFile(menuPicturePath, gRenderer);
        }
};
#endif