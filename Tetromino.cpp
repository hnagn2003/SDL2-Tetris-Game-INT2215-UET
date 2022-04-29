#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "Game.h"
#include "Tetromino.h"
#include "Grid.h"
#include "Specifications.h"
#include <cstdlib>

// hàm random tetrads, làm giảm xác suất giống nhau của 2 khối liên tiếp
Tetromino* getRandomTetrads(){ //...
    Tetromino* res = new Tetromino;
    *res = Tetrads[rand() % TOTAL_OF_TETRADS];
    return res;
}
// hàm chuyển vị ma trận (xoay khối tetrads)
void transPos(bool matrix[sizeOfTetradsSide][sizeOfTetradsSide]){
    bool backUp[sizeOfTetradsSide][sizeOfTetradsSide];
    for (int i=0; i<sizeOfTetradsSide; i++){
        for (int j=0; j<sizeOfTetradsSide; j++){
            backUp[i][j] = matrix[i][j];
        }
    }
    for (int i=0; i<sizeOfTetradsSide; i++){
        for (int j=0; j<sizeOfTetradsSide; j++){
            matrix[j][sizeOfTetradsSide-1-i] = backUp[i][j];
        }
    }
}
