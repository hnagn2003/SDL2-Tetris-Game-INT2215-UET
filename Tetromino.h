#ifndef Tetromino_h
#define Tetromino_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Specifications.h"
int gridToRenderer(int x){return x*TILE_SIZE}
class block{
    public:
        int x, y, w = TILE_SIZE, h = TILE_SIZE;
        SDL_Color color;
        
    public:
        block(int _x, int _y){
            x = _x;
            y = _y;
        }
        
        void render(SDL_Renderer* renderer){
            SDL_Rect rectBlock{x, y, w, h};
            SDL_SetRenderDrawColor( renderer, 100, 100, 100, 0 );
            SDL_RenderDrawRect(renderer, &rectBlock);
        }
};  

class Tetromino{
    private:
        static const int size = 4;
        SDL_Color color;
        SDL_Rect collin;
        bool matrix[size][size];
    public:
        Tetromino()
        {}
        Tetromino (SDL_Color _color, bool _matrix[size][size], int _w, int _h, int _x = SCREEN_WIDTH/2, int _y = 0)
        {
            color = _color;
            collin.x = _x;
            collin.y = _y;
            collin.w = gridToRenderer(_w);
            collin.h = gridToRenderer(_h);
            for (size_t i=0; i<size; i++){
                for (size_t j=0; j<size; j++){
                    matrix[i][j] = _matrix[i][j];
                }
            }
        }
        void render(){
            
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
        mI,
        4, 1
    };

#endif