#ifndef Grid_h
#define Grid_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Tetromino.h"
#include "Game.h"
#include "Specifications.h"
#include <iostream>
#include <cstdlib>

// struct block;
// struct Box{
//     int x, y;
//     int width = TILE_SIZE;
//     int height = TILE_SIZE;
// };
class Grid{
    private:
        int width = COLS*TILE_SIZE;
        int height = ROWS*TILE_SIZE;
        int xPos = (SCREEN_WIDTH - width) / 2;
        int yPos = (SCREEN_HEIGHT - height) / 2;
        // Point center{xPos + width, yPos + height};
        // mỗi 1 ô trên grid define = 1 block
        block matrix[ROWS+HIDDEN_ROWS][COLS];
        
    public:
        Grid();
        ~Grid();
        block (*(getGrid)())[COLS]{
            return matrix;
        }
        void render(SDL_Renderer *renderer);
        //kiểm tra 1 hàng có filled hay ko
        bool filledRow(int i){
            for (int j = 0; j<COLS; j++){
                if (matrix[i][j].exist==0){
                    return false;
                }
            }
            return true;
        }
        void deleteRow(int indexOfDeletedRow){
            for (int i=indexOfDeletedRow; i>delimitedLine+HIDDEN_ROWS-2; i--){
                for (int j=0; j<COLS; j++){
                    matrix[i][j].exist = matrix[i-1][j].exist;
                    matrix[i][j].color = matrix[i-1][j].color; //...
                }
            }
            // for (int j=0; j<COLS; j++){
            //     matrix[0][j].exist = 0;
            //     matrix[0][j].color = backgroundColor;
            // }
            
        }
        // kiểm tra sự tạo thành 1 hàng và xóa, return số hàng bị xóa
        int update(int topRowCheck, int botRowCheck){
            int deletedRowCount = 0;
            for (int i = topRowCheck; i<=botRowCheck; i++){
                if (filledRow(i)){
                    deleteRow(i);
                    deletedRowCount++;
                }
            }
            return deletedRowCount;
        }
        int getHighestRow(int startPoint, int leftLimit, int rightLimit){
            for (int i=startPoint; i<ROWS+HIDDEN_ROWS; i++){
                for (int j=leftLimit; j<=rightLimit; j++){
                    if (matrix[i][j].exist){
                        return i;
                    }
                }
            }
            return ROWS+HIDDEN_ROWS-1;
        }
        
};

#endif