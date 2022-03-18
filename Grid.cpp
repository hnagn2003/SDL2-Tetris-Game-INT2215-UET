#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "Game.h"
#include "Grid.h"
using namespace std;
const int ROWS = 20;
const int COLS = 10;
Grid::Grid(){

}
Grid::~Grid(){

}
void Grid::render(SDL_Renderer *renderer, int x, int y){
    for (size_t i = 0; i <= ROWS; i++){
        SDL_SetRenderDrawColor(renderer, 100, 100, 0, 0);
        SDL_RenderDrawLine(renderer, xPos, i*TILE_SIZE, xPos + TILE_SIZE*COLS, i*TILE_SIZE);
    }
    for (size_t i = 0; i <= COLS; i++){
        SDL_SetRenderDrawColor(renderer, 100, 100, 0, 0);
        SDL_RenderDrawLine(renderer, i*TILE_SIZE, yPos, i*TILE_SIZE, yPos + TILE_SIZE*ROWS);
    }
}