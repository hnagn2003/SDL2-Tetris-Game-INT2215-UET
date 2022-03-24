#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "Game.h"
#include "Tetromino.h"
#include "Grid.h"
#include "Specifications.h"
#include <cstdlib>


Tetromino getRandomTetrads(){
    return Tetrads[rand() % TOTAL_OF_TETRADS];
}

void transPos(bool matrix[sizeOfTetradsSide][sizeOfTetradsSide]){
    bool backUp[sizeOfTetradsSide][sizeOfTetradsSide];
    for (size_t i=0; i<sizeOfTetradsSide; i++){
        for (size_t j=0; j<sizeOfTetradsSide; j++){
            backUp[i][j] = matrix[i][j];
        }
    }
    for (size_t i=0; i<sizeOfTetradsSide; i++){
        for (size_t j=0; j<sizeOfTetradsSide; j++){
            matrix[j][sizeOfTetradsSide-1-i] = backUp[i][j];
        }
    }
}