#ifndef Tetromino_h
#define Tetromino_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Specifications.h"
#include "Grid.h"
#include <iostream>
const int xTetradsInit = 4;
const int YTetradsInit = -1;
const int sizeOfTetradsSide = 4;

int gridSizeToRendererSize(int w);
int gridXPosToRendererPos(int x);
int gridYPosToRendererPos(int y);

enum LEVEL{
    easy = 1000,
    hard = 600,
    extremely_hard = 300,
    super_ultra_hard = 100,
    asian = 30
};

class block{
    private:
        int xGrid, yGrid, wGrid = 1, hGrid = 1;
        SDL_Color color;
        
    public:
        block(int x, int y, SDL_Color _color){
            xGrid = x;
            yGrid = y;
            color = _color;
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
            SDL_RenderDrawRect(renderer, &rectBlock);
        }
};  

class Tetromino{
    private:
        SDL_Color color;
        SDL_Rect collin;
        bool matrix[sizeOfTetradsSide][sizeOfTetradsSide];
        Uint32 startTime = SDL_GetTicks();
    public:
        Tetromino()
        {}
        Tetromino (SDL_Color _color, bool _matrix[sizeOfTetradsSide][sizeOfTetradsSide], int _w, int _h, int _x = xTetradsInit, int _y = YTetradsInit)
        {
            color = _color;
            collin.x = _x;
            collin.y = _y;
            collin.w = _w;
            collin.h = _h;
            for (size_t i=0; i<sizeOfTetradsSide; i++){
                for (size_t j=0; j<sizeOfTetradsSide; j++){
                    matrix[i][j] = _matrix[i][j];
                }
            }
        }

        void render(SDL_Renderer* renderer){
            for (size_t i=0; i<sizeOfTetradsSide; i++){
                for (size_t j=0; j<sizeOfTetradsSide; j++){
                    if (matrix[i][j] == 1){
                        block aBlock{collin.x+j, collin.y+i, color};
                        if (aBlock.getYGrid()>=0){
                            aBlock.render(renderer);
                        }
                    }
                }
            }
        }

        bool collision(Grid grid){ // nhan vao grid
            short int rightSide = collin.x + collin.w;
            if (rightSide >= COLS){
                return true;
            }

            short int leftSide = collin.x;
            if (leftSide <= 0){
                return true;
            }

            short int bottomSide = collin.y + collin.h;
            if (bottomSide >= ROWS){
                return true;
            }


            return false;
        }

        void move(int velocity, Grid grid){
            if (!collision(grid)){
                if (SDL_GetTicks() - startTime >= velocity){
                    collin.y++;
                    startTime = SDL_GetTicks();
                }
            }
        }

        void fall(int velocity, Grid grid){
            move(velocity, grid);
        }

        void rotate(){
            
        }
};

static bool matrixStructure_I[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0}
};

static bool matrixStructure_L[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_J[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {0, 0, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_O[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_S[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_T[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_Z[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};
const Tetromino Tetrads[TOTAL_OF_TETRADS] =
    {
        {
            TetroColor[I_BLOCK],
            matrixStructure_I,
            4, 1
        },

        {
            TetroColor[L_BLOCK],
            matrixStructure_L,
            3, 2
        },

        {
            TetroColor[J_BLOCK],
            matrixStructure_J,
            3, 2
        },

        {
            TetroColor[O_BLOCK],
            matrixStructure_O,
            2, 2
        },

        {
            TetroColor[S_BLOCK],
            matrixStructure_S,
            3, 2
        },

        {
            TetroColor[T_BLOCK],
            matrixStructure_T,
            3, 2
        },

        {
            TetroColor[Z_BLOCK],
            matrixStructure_Z,
            3, 2
        }
    };


Tetromino getRandomTetrads();

#endif