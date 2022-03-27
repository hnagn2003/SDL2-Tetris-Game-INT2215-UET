#ifndef Grid_h
#define Grid_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Tetromino.h"
#include "Game.h"
#include "Specifications.h"
#include <iostream>
#include <cstdlib>

// struct block;
// struct Box{
//     int x, y;
//     int width = TILE_SIZE;
//     int height = TILE_SIZE;
// };

class Grid{
    private:
        int width = COLS*TILE_SIZE;
        int height = ROWS*TILE_SIZE;
        int xPos = (SCREEN_WIDTH - width) / 2;
        int yPos = (SCREEN_HEIGHT - height) / 2;
        // Point center{xPos + width, yPos + height};
        block matrix[ROWS+HIDDEN_ROWS][COLS];
        
    public:
        Grid();
        ~Grid();
        block (*(getGrid)())[COLS]{
            return matrix;
        }
        void render(SDL_Renderer *renderer);

};

#endif