#ifndef Specifications_h
#define Specifications_h

const int TILE_SIZE = 40;
const int ROWS = 20;
const int COLS = 10;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1030;

const SDL_Color I_cBLOCK = {0, 209, 232};
const SDL_Color L_cBLOCK = {0, 126, 229};
const SDL_Color J_cBLOCK = {218, 147, 0};
const SDL_Color O_cBLOCK = {232, 214, 0};
const SDL_Color S_cBLOCK = {0, 222, 61};
const SDL_Color T_cBLOCK = {187, 0, 222};
const SDL_Color Z_cBLOCK = {232, 0, 0};

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
        x = _x;
        y = _y;
    }
    int xPosOnGrid(){
        return (SCREEN_WIDTH - COLS*TILE_SIZE) / 2 + x*TILE_SIZE;
    } 
    int yPosOnGrid(){
        return (SCREEN_HEIGHT - ROWS*TILE_SIZE) / 2 + y*TILE_SIZE;
    }
};
#endif