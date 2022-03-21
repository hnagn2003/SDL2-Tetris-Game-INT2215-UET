#ifndef Tetromino_h
#define Tetromino_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Specifications.h"
#include "Grid.h"
#include <iostream>
#include <algorithm>  
const int xTetradsInit = 3;
const int yTetradsInit = -1;
const int sizeOfTetradsSide = 4;

int gridSizeToRendererSize(int w);
int gridXPosToRendererPos(int x);
int gridYPosToRendererPos(int y);
void transPos(bool matrix[sizeOfTetradsSide][sizeOfTetradsSide]);


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
        int xPos, yPos;
        SDL_Rect collin;
        bool matrix[sizeOfTetradsSide][sizeOfTetradsSide];
        Uint32 startTime = SDL_GetTicks();
    public:
        Tetromino()
        {}
        Tetromino (SDL_Color _color, bool _matrix[sizeOfTetradsSide][sizeOfTetradsSide], int _w, int _h, int _x, int _y, int _xPos = xTetradsInit, int _yPos = yTetradsInit)
        {
            color = _color;
            collin.x = _x;
            collin.y = _y;
            collin.w = _w;
            collin.h = _h;
            xPos = _xPos;
            yPos = _yPos;
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
                        block aBlock{xPos+j, yPos+i, color};
                        if (aBlock.getYGrid()>=0){
                            aBlock.render(renderer);
                        }
                    }
                }
            }
        }

        bool collision(Grid grid){ // ...
            // short int rightSide = collin.x + collin.w;
            // if (rightSide > COLS){
            //     return true;
            // }

            // short int leftSide = collin.x;
            // if (leftSide < 0){
            //     return true;
            // }

            // short int bottomSide = collin.y + collin.h;
            // if (bottomSide > ROWS){
            //     return true;
            // }


            return false;
        }
        void detectCoveredRect(){
            collin.w = 0; collin.h = 0;
            for (size_t i=0; i<sizeOfTetradsSide; i++){
                for (size_t j=0; j<sizeOfTetradsSide; j++){
                    if (matrix[i][j]!=0){
                        collin.h++;
                        break;
                    }
                }
            }
            for (size_t j=0; j<sizeOfTetradsSide; j++){
                for (size_t i=0; i<sizeOfTetradsSide; i++){
                    if (matrix[i][j]!=0){
                        collin.w++;
                        break;
                    }
                }
            }

            bool xStop = false, yStop = false;
            for (size_t i=0; i<sizeOfTetradsSide && !xStop; i++){
                for (size_t j=0; j<sizeOfTetradsSide && !xStop; j++){
                    if (matrix[i][j]!=0){
                        collin.y = yPos+j;
                        xStop = true;
                    }
                }
            }
            for (size_t j=0; j<sizeOfTetradsSide && !yStop; j++){
                for (size_t i=0; i<sizeOfTetradsSide && !yStop; i++){
                    if (matrix[i][j]!=0){
                        collin.x = xPos+i;
                        yStop = true;
                    }
                }
            }
        }
        void rotate(){
            transPos(matrix);
            detectCoveredRect();
        }
        void move(int velocity, Grid grid){
            if (!collision(grid)){
                if (SDL_GetTicks() - startTime >= velocity){
                    collin.y++;
                    yPos++;
                    startTime = SDL_GetTicks();
                    rotate();
                }
            }
        }

        void fall(int velocity, Grid grid){
            move(velocity, grid);
        }

};

static bool matrixStructure_I[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
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
            4, 1,
            xTetradsInit, yTetradsInit+1
        },

        {
            TetroColor[L_BLOCK],
            matrixStructure_L,
            3, 2,
            xTetradsInit, yTetradsInit+1
        },

        {
            TetroColor[J_BLOCK],
            matrixStructure_J,
            3, 2,
            xTetradsInit, yTetradsInit+1
        },

        {
            TetroColor[O_BLOCK],
            matrixStructure_O,
            2, 2,
            xTetradsInit+1, yTetradsInit+1
        },

        {
            TetroColor[S_BLOCK],
            matrixStructure_S,
            3, 2,
            xTetradsInit, yTetradsInit+1
        },

        {
            TetroColor[T_BLOCK],
            matrixStructure_T,
            3, 2,
            xTetradsInit, yTetradsInit+1
        },

        {
            TetroColor[Z_BLOCK],
            matrixStructure_Z,
            3, 2,
            xTetradsInit, yTetradsInit+1
        }
    };


Tetromino getRandomTetrads();

#endif