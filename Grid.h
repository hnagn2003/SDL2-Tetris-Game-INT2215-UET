
#ifndef Grid_h
#define Grid_h

#include "Specifications.h"

class block
{
    public:
        int xReal, yReal;
        int xGrid, yGrid, wGrid = 1, hGrid = 1;
        int type;  
        bool exist;
        block();
        ~block();
        block(int x, int y, int _type, int realCoordinates = 0);
        int getXGrid();
        int getYGrid();
        int getWGrid();
        int getHGrid();
        void render(SDL_Renderer* renderer, int gridXPos, int realCoordinates = 0, bool ghost = 0);
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
        block (*(getGrid)())[COLS];
        int getX();
        int getY();

        void render(SDL_Renderer *renderer, GameMode gameMode);
        //check a completed line
        bool filledRow(int i);
        void deleteRow(int indexOfDeletedRow);
        // check completed lines and delete, return số hàng bị xóa
        int update(int topRowCheck, int botRowCheck);
        int getHighestRow(int startPoint, int leftLimit, int rightLimit);
};

#endif