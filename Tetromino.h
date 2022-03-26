#ifndef Tetromino_h
#define Tetromino_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Specifications.h"
#include "Grid.h"
#include "Game.h"
#include <iostream>
#include <algorithm>  
const int xTetradsInit = 3;
const int yTetradsInit = -2;
const int sizeOfTetradsSide = 4;


void transPos(bool matrix[sizeOfTetradsSide][sizeOfTetradsSide]);




class Tetromino{
    private:
        SDL_Color color;
        int xPos, yPos;
        SDL_Rect collin;
        bool matrix[sizeOfTetradsSide][sizeOfTetradsSide];
        bool active;
        bool falling;
    public:
        Tetromino()
        {
            active = true;
            falling = false;
        }
        Tetromino (SDL_Color _color, bool _matrix[sizeOfTetradsSide][sizeOfTetradsSide], int _w, int _h, int _x, int _y, int _xPos = xTetradsInit, int _yPos = yTetradsInit)
        {
            active = true;
            falling = false;
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
        bool getStatus(){
            return active;
        }
        void setActice(bool _active){
            active = _active;
        }
        bool getFall(){
            return falling;
        }
        void setFall(bool fall){
            falling = fall;
        }
        int getXPos(){
            return xPos;
        }
        int getYPos(){
            return yPos;
        }
        int getXCol(){
            return collin.x;
        }
        int getYCol(){
            return collin.y;
        }
        int getWCol(){
            return collin.w;
        }
        int getHCol(){
            return collin.h;
        }
        void render(SDL_Renderer* renderer){
            if (collin.y >=0 && active){
                for (size_t i=0; i<sizeOfTetradsSide; i++){
                    for (size_t j=0; j<sizeOfTetradsSide; j++){
                        if (matrix[i][j] == true){
                            block aBlock{xPos+j, yPos+i, color};
                            aBlock.render(renderer);
                        }
                    }
                }
            }
        }
        void disableFromActivate(){
            falling = false;
            active = false;
        }

        void mergeToGrid(Grid *grid){
            for (size_t i=0; i<4; i++){
                for (size_t j=0; j<4; j++){
                    if (matrix[i][j] == true){
                        grid->getGrid()[i+yPos][j+xPos].color = color;
                    }
                }
            }
        }
        bool collision(Grid *grid){ // ...
            
            if (active){
                std::cout << "still active" << std::endl;
                int bottomSide = collin.y + collin.h;
                if (bottomSide >= ROWS){
                    // nhap nhay
                    disableFromActivate();
                    mergeToGrid(grid);
                    std::cout << "disable successful" << std::endl;
                    return true;
                }
                return false;
            }
            return true;
        }

        bool leftCollision(Grid grid){ // ...
            int leftSide = collin.x;
            if (leftSide <= 0){
                return true;
            }
            return false;
        }
        bool rightCollision(Grid grid){ // ...
            int rightSide = collin.x+collin.w;
            if (rightSide >= COLS){
                return true;
            }
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
                        collin.y = yPos+i;
                        xStop = true;
                    }
                }
            }
            for (size_t j=0; j<sizeOfTetradsSide && !yStop; j++){
                for (size_t i=0; i<sizeOfTetradsSide && !yStop; i++){
                    if (matrix[i][j]!=0){
                        collin.x = xPos+j;
                        yStop = true;
                    }
                }
            }
        }
        void rotate(){
            if (active){
                transPos(matrix);
                detectCoveredRect();
            }
        }
        void fall(int velocity, Grid grid){
            if (active && falling){
                static Uint32 startTime = SDL_GetTicks();
                if (SDL_GetTicks() - startTime >= velocity){
                    moveDown(&grid);
                    startTime = SDL_GetTicks();
                }
           }
        }

        void moveDown(Grid *grid){

            if (!collision(grid) && active){
                collin.y++;
                yPos++;
            }
        }
        void moveRight(Grid grid){
            if (!rightCollision(grid) && active){
                collin.x++;
                xPos++;
            }
        }

        void moveLeft(Grid grid){

            if (!leftCollision(grid) && active){
                collin.x--;
                xPos--;
            }
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