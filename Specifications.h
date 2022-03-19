#ifndef Specifications_h
#define Specifications_h

const int TILE_SIZE = 40;
const int ROWS = 20;
const int COLS = 10;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1030;

struct Point{
    int x;
    int y;
    Point(int _x, int _y){
        x = _x;
        y = _y;
    }
};

#endif