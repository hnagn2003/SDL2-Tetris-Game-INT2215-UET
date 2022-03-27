#include "Game.h"
#include "Tetromino.h"
#include "Grid.h"
#include "Specifications.h"
#include <iostream>

Grid::Grid(){

    for (size_t i=0; i<ROWS; i++){
        for (size_t j=0; j<COLS; j++){
            matrix[i][j] = {j, i, backgroundColor};
        }
    }
}
Grid::~Grid(){

}
void Grid::render(SDL_Renderer *renderer){
    for (size_t i = 0; i <= ROWS; i++){
        SDL_SetRenderDrawColor(renderer, 100, 100, 0, 0);
        SDL_RenderDrawLine(renderer, xPos, i*TILE_SIZE + yPos, xPos + TILE_SIZE*COLS, i*TILE_SIZE + yPos);
    }
    for (size_t i = 0; i <= COLS; i++){
        SDL_SetRenderDrawColor(renderer, 100, 100, 0, 0);
        SDL_RenderDrawLine(renderer, i*TILE_SIZE + xPos, yPos, i*TILE_SIZE + xPos, yPos + TILE_SIZE*ROWS);
    }

    for (size_t i = 0; i < ROWS; i++){
        for (size_t j = 0; j < COLS; j++){
            if (matrix[i][j].exist){
                matrix[i][j].render(renderer);
            }
        }
    }

}