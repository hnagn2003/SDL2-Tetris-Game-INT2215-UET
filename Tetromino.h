#ifndef Tetromino_h
#define Tetromino_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Specifications.h"
class block{
    public:
        render(int xPos, int yPos);
    private:
        SDL_Color color;

};

class Tetromino{
    private:
        static const int size = 4;
        SDL_Color color;
        int x, y;
        bool matrix[size][size];
    public:
        Tetromino()
        {}
        Tetromino (SDL_Color _color, bool _matrix[4][4], int _x = SCREEN_WIDTH/2, int _y = 0)
        {
            color = _color;
            x = _x;
            y = _y;
            for (size_t i=0; i<size; i++){
                for (size_t j=0; j<size; j++){
                    matrix[i][j] = _matrix[i][j];
                }
            }
        }

        
};

static bool mI[4][4] = {
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

const Tetromino Tetrads =
    {
        TetroColor[I_BLOCK],
        mI
    };

#endif