
#include "Game.h"
#include "Tetromino.h"
#include "Grid.h"
#include "Specifications.h"
#include <iostream>
block::block(){
    exist = false;
}
block::~block(){}
block::block(int x, int y, int _type, int realCoordinates)
{
    if (realCoordinates)
    {
        xReal = x;
        yReal = y;
    }
    else
    {
        xGrid = x;
        yGrid = y;
    }
    type = _type;
    exist = false;
}
int block::getXGrid()
{
    return xGrid;
}
int block::getYGrid()
{
    return yGrid;
}
int block::getWGrid()
{
    return wGrid;
}
int block::getHGrid()
{
    return hGrid;
}

void block::render(SDL_Renderer* renderer, int gridXPos, int realCoordinates, bool ghost)
{
    static LTexture blockTemp(tetroTempP, renderer);
    static LTexture ghostBlockTex(ghostBlockP, renderer);
    SDL_Rect clip{type*TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
    if (!ghost)
    {
        if (realCoordinates)
        {
            blockTemp.render(renderer, xReal+gridXPos, yReal, &clip);
        }
        else
        {
            blockTemp.render(renderer, gridXPosToRendererPos(xGrid)+gridXPos, gridYPosToRendererPos(yGrid), &clip);
        }
    }else{
        if (realCoordinates)
        {
            ghostBlockTex.render(renderer, xReal+gridXPos, yReal, &clip);
        }
        else
        {
            ghostBlockTex.render(renderer, gridXPosToRendererPos(xGrid)+gridXPos, gridYPosToRendererPos(yGrid), &clip);
        }
    }
}
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

block (*(Grid::getGrid)())[COLS]
        {
            return matrix;
        }
        int Grid::getX()
        {
            return xPos;
        }
        int Grid::getY()
        {
            return yPos;
        }

        void Grid::render(SDL_Renderer *renderer, GameMode gameMode);
        //check a completed line
        bool Grid::filledRow(int i)
        {
            for (int j = 0; j<COLS; j++)
            {
                if (matrix[i][j].exist==0)
                {
                    return false;
                }
            }
            return true;
        }
        void Grid::deleteRow(int indexOfDeletedRow)
        {
            for (int i=indexOfDeletedRow; i>delimitedLine+HIDDEN_ROWS-2; i--)
            {
                for (int j=0; j<COLS; j++)
                {
                    matrix[i][j].exist = matrix[i-1][j].exist;
                    matrix[i][j].type = matrix[i-1][j].type; //...
                }
            }
        }
        // check completed lines and delete, return số hàng bị xóa
        int Grid::update(int topRowCheck, int botRowCheck)
        {
            int deletedRowCount = 0;
            for (int i = topRowCheck; i<=botRowCheck; i++)
            {
                if (filledRow(i))
                {
                    deleteRow(i);
                    deletedRowCount++;
                }
            }
            playSoundEffects(se_lineCompleted[deletedRowCount-1]);
            return deletedRowCount;
        }
        int Grid::getHighestRow(int startPoint, int leftLimit, int rightLimit)
        {
            for (int i=startPoint; i<ROWS+HIDDEN_ROWS; i++)
            {
                for (int j=leftLimit; j<=rightLimit; j++)
                {
                    if (matrix[i][j].exist)
                    {
                        return i;
                    }
                }
            }
            return ROWS+HIDDEN_ROWS;
        }