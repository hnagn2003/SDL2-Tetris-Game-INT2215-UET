#ifndef Grid_h
#define Grid_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Game.h"

const int TILE_SIZE = 40;
// const int ROWS = 20;
// const int COLS = 10;
// const int SCREEN_WIDTH = COLS*TILE_SIZE;
// const int SCREEN_HEIGHT = ROWS*TILE_SIZE;

struct Box{
    int x, y;
    int width = TILE_SIZE;
    int height = TILE_SIZE;
};
class Grid{
    private:
        int xPos = 0, yPos = 0;

    public:
        Grid();
        ~Grid();
        void render(SDL_Renderer *renderer, int xPos, int yPos);
    
};

#endif