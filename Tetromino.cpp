// #include <iostream>
// #include <SDL_image.h>
// #include <SDL.h>
#include "Game.h"
#include "Tetromino.h"
// #include "Grid.h"
// #include "Specifications.h"
// #include <cstdlib>
#include <set>
void Tetromino::renderGhostPiece(SDL_Renderer* renderer, Grid* grid)
{
    static Tetromino ghostTetro;
    ghostTetro = *this;
    ghostTetro.disableFromActivate();
    while(!ghostTetro.collision(grid, 1, 0)){
        ghostTetro.yPos++;
        ghostTetro.collin.y++;
    }
    ghostTetro.render(renderer, grid->getX(), 1);
}
// hàm random tetrads, làm giảm xác suất giống nhau của 2 khối liên tiếp
Tetromino* getRandomTetrads()
{ //...
    Tetromino* res = new Tetromino;
    static std::set<int> tetradsBag;
    if (tetradsBag.begin() == tetradsBag.end()){
        for (int i=0; i<7; i++){
            tetradsBag.insert(i);
        }
    }
    auto it = tetradsBag.begin();
    std::advance (it, rand()%tetradsBag.size());
    int pickRandOne = *it;
    *res = Tetrads[pickRandOne];
    tetradsBag.erase(tetradsBag.find(pickRandOne));
    
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