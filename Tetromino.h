#ifndef Tetromino_h
#define Tetromino_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Specifications.h"
#include <iostream>
int gridSizeToRendererSize(int w);
int gridXPosToRendererPos(int x);
int gridYPosToRendererPos(int y);
class block{
    public:
        int xGrid, yGrid, wGrid = 1, hGrid = 1;
        SDL_Color color;
        
    public:
        block(int x, int y, SDL_Color _color){
            xGrid = x;
            yGrid = y;
            color = _color;
        }
        
        void render(SDL_Renderer* renderer){
            SDL_Rect rectBlock{gridXPosToRendererPos(xGrid), gridYPosToRendererPos(yGrid), gridSizeToRendererSize(wGrid), gridSizeToRendererSize(hGrid)};
            SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, 0 );
            SDL_RenderDrawRect(renderer, &rectBlock);
        }
};  

class Tetromino{
    private:
        static const int size = 4;
        SDL_Color color;
        SDL_Rect collin;
        bool matrix[size][size];
        Uint32 startTime = SDL_GetTicks();
    public:
        Tetromino()
        {}
        Tetromino (SDL_Color _color, bool _matrix[size][size], int _w, int _h, int _x = 5, int _y = 0)
        {
            color = _color;
            collin.x = _x;
            collin.y = _y;
            collin.w = _w;
            collin.h = _h;
            for (size_t i=0; i<size; i++){
                for (size_t j=0; j<size; j++){
                    matrix[i][j] = _matrix[i][j];
                }
            }
        }
        void render(SDL_Renderer* renderer){
            for (size_t i=0; i<size; i++){
                for (size_t j=0; j<size; j++){
                    if (matrix[i][j] == 1){
                        block aBlock{collin.x+i, collin.y+j, color};
                        aBlock.render(renderer);
                    }
                }
            }
        }

        void fall(size_t cusVEL = 1000){
            std::cout << SDL_GetTicks() << " " << startTime << " " << collin.y << std::endl; //fb
            if (SDL_GetTicks() - startTime >= 1000){
                collin.y++;
                startTime = SDL_GetTicks();
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
        mI,
        4, 1
    };

#endif