
#ifndef Grid_h
#define Grid_h

// #include <SDL.h>
// #include <stdio.h>
// #include <SDL_image.h>
// #include "Tetromino.h"
// #include "Game.h"
#include "Specifications.h"
// #include <iostream>
// #include <cstdlib>
class block
{
    public:
        int xReal, yReal;
        int xGrid, yGrid, wGrid = 1, hGrid = 1;
        int type;  
        bool exist;
        block()
        {
            exist = false;
        }
        block(int x, int y, int _type, int realCoordinates = 0)
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
        int getXGrid()
        {
            return xGrid;
        }
        int getYGrid()
        {
            return yGrid;
        }
        int getWGrid()
        {
            return wGrid;
        }
        int getHGrid()
        {
            return hGrid;
        }

        void render(SDL_Renderer* renderer, int gridXPos, int realCoordinates = 0, bool ghost = 0)
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
};  
class Grid{
    private:
        int width = COLS*TILE_SIZE;
        int height = ROWS*TILE_SIZE;
        int xPos = (SCREEN_WIDTH - width) / 2;
        int yPos = (SCREEN_HEIGHT - height) / 2;
        block matrix[ROWS+HIDDEN_ROWS][COLS];
    public:
        Grid();
        ~Grid();
        block (*(getGrid)())[COLS]
        {
            return matrix;
        }
        int getX()
        {
            return xPos;
        }
        int getY()
        {
            return yPos;
        }

        void render(SDL_Renderer *renderer, GameMode gameMode);
        //check a completed line
        bool filledRow(int i)
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
        void deleteRow(int indexOfDeletedRow)
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
        int update(int topRowCheck, int botRowCheck)
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
        int getHighestRow(int startPoint, int leftLimit, int rightLimit)
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
};

#endif