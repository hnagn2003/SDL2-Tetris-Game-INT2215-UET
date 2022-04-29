#include "Game.h"
#include "Tetromino.h"
#include "Grid.h"
#include "Specifications.h"
#include <iostream>

Grid::Grid(){
    gridFrame = new LTexture;
    for (int i=0; i<ROWS+HIDDEN_ROWS; i++){
        for (int j=0; j<COLS; j++){
            matrix[i][j] = {j, i-HIDDEN_ROWS, -1};
        }
    }
}
Grid::~Grid(){

}
void Grid::render(SDL_Renderer *renderer, int gameMode){
    if (gameMode == 0){
    //         for (int i = 0; i <= ROWS; i++){
    //     SDL_SetRenderDrawColor(renderer, 100, 100, 0, 0);
    //     SDL_RenderDrawLine(renderer, xPos, i*TILE_SIZE + yPos, xPos + TILE_SIZE*COLS, i*TILE_SIZE + yPos);
    // }
    // for (int i = 0; i <= COLS; i++){
    //     SDL_SetRenderDrawColor(renderer, 100, 100, 0, 0);
    //     SDL_RenderDrawLine(renderer, i*TILE_SIZE + xPos, yPos, i*TILE_SIZE + xPos, yPos + TILE_SIZE*ROWS);
    // }
        xPos = 0;
        yPos = 0;
        
    }else if (gameMode == 1){
        xPos = -SCREEN_WIDTH/4;
        yPos = 0;
    }else if (gameMode == -1){
        xPos = SCREEN_WIDTH/4;
        yPos = 0;
    }
    gridFrame->render(renderer, xPos, yPos);
    for (int i = -4; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            if (matrix[i+HIDDEN_ROWS][j].exist){
                matrix[i+HIDDEN_ROWS][j].render(renderer, xPos);
            }
        }
    }
}

