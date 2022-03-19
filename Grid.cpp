#include "Game.h"
#include "Grid.h"
#include <iostream>

Grid::Grid(){

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
}