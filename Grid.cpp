
#include "Game.h"
#include "Tetromino.h"
#include "Grid.h"
#include "Specifications.h"
#include <iostream>

Grid::Grid(){
    for (int i=0; i<ROWS+HIDDEN_ROWS; i++)
    {
        for (int j=0; j<COLS; j++)
        {
            matrix[i][j] = {j, i-HIDDEN_ROWS, -1};
        }
    }
}
Grid::~Grid()
{

}
void Grid::render(SDL_Renderer *renderer, GameMode gameMode)
{
    if (gameMode == SinglePlay)
    {
        xPos = 0;
        yPos = 0;
        
    }
    else if (gameMode == Player2)
    {
        xPos = -SCREEN_WIDTH/4;
        yPos = 0;
    }
    else if (gameMode == Player1)
    {
        xPos = SCREEN_WIDTH/4;
        yPos = 0;
    }
    static LTexture gridFrame(grid_frame, renderer);
    gridFrame.render(renderer, xPos, yPos);
    for (int i = -4; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (matrix[i+HIDDEN_ROWS][j].exist)
            {
                matrix[i+HIDDEN_ROWS][j].render(renderer, xPos);
            }
        }
    }
}