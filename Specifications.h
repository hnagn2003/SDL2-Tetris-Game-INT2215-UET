#ifndef Specifications_h
#define Specifications_h
#include "Tetromino.h"
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
#endif