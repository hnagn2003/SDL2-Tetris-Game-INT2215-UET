#ifndef Tetromino_h
#define Tetromino_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Specifications.h"
#include "Grid.h"
#include "Game.h"
#include <iostream>
#include <algorithm>  
const int xTetradsInit = 3;
const int yTetradsInit = -1;
const int sizeOfTetradsSide = 4;

void transPos(bool matrix[sizeOfTetradsSide][sizeOfTetradsSide]);

class Tetromino{
    private:
        int type;
        SDL_Color color;
        // xPos, yPos tọa độ x, y chiếu trong bảng grid
        int xPos, yPos;
        // hình chữ nhật bao quanh khối tetrads
        SDL_Rect collin;
        // mảng 2 chiều đại diện cho khối tetrads
        bool matrix[sizeOfTetradsSide][sizeOfTetradsSide];
        bool active;
        bool falling;
        bool pause;
        Uint32 startTime;
    public:
        Tetromino()
        {
            active = true;
            falling = false;
            pause = 0;
            startTime = 0;

        }
        Tetromino (int _type, SDL_Color _color, bool _matrix[sizeOfTetradsSide][sizeOfTetradsSide], int _w, int _h, int _x, int _y, int _xPos = xTetradsInit, int _yPos = yTetradsInit)
        {
            type = _type;
            active = true;
            falling = false;
            pause = 0;
            color = _color;
            collin.x = _x;
            collin.y = _y;
            collin.w = _w;
            collin.h = _h;
            xPos = _xPos;
            yPos = _yPos;
            for (int i=0; i<sizeOfTetradsSide; i++){
                for (int j=0; j<sizeOfTetradsSide; j++){
                    matrix[i][j] = _matrix[i][j];
                }
            }
        }
        void setCollinYInitTetrads(int landingPoint){
            // int tmp = collin.y - yPos;
            yPos=landingPoint-HIDDEN_ROWS-4;
            // collin.y=yPos+tmp;
            
            if (yPos+HIDDEN_ROWS<=0){
                std::cout << "out of range" << std::endl;
                exit(1);
            }
            detectCoveredRect();
        }
        int getType(){
            return type;
        }
        bool getStatus(){
            return active;
        }
        void setActice(bool _active){
            active = _active;
        }
        bool getFall(){
            return falling;
        }
        void setFall(bool fall){
            falling = fall;
        }
        int getXPos(){
            return xPos;
        }
        int getYPos(){
            return yPos;
        }
        void setXPos(int x){
            xPos = x;
        }
        void setYPos(int y){
            yPos = y;
        }
        int getXCol(){
            return collin.x;
        }
        int getYCol(){
            return collin.y;
        }
        int getWCol(){
            return collin.w;
        }
        int getHCol(){
            return collin.h;
        }
        void setPause(bool p){
            pause = p;
        }
        void render(SDL_Renderer* renderer, int gridXPos){
            if (active){
                for (int i=0; i<sizeOfTetradsSide; i++){
                    for (int j=0; j<sizeOfTetradsSide; j++){
                        if (matrix[i][j] == true){
                            block aBlock{xPos+j, yPos+i, type};
                            aBlock.render(renderer, gridXPos);
                        }
                    }
                }
            }
        }
        void render(SDL_Renderer* renderer, int gridXPos, int x, int y){ 
            for (int i=0; i<sizeOfTetradsSide; i++){
                    for (int j=0; j<sizeOfTetradsSide; j++){
                        if (matrix[i][j] == true){
                            block aBlock{x+j*TILE_SIZE, y+i*TILE_SIZE, type, 1};
                            aBlock.render(renderer, gridXPos, 1);
                        }
                    }
                }
        }
        // tắt active
        void disableFromActivate(){
            falling = false;
            active = false;
        }
        // kết nạp khối tetrads vào grid của game
        void mergeToGrid(Grid *grid){
            for (int i=0; i<sizeOfTetradsSide; i++){
                for (int j=0; j<sizeOfTetradsSide; j++){
                    if (matrix[i][j] == true){
                        grid->getGrid()[i+yPos+HIDDEN_ROWS][j+xPos].type = type;
                        grid->getGrid()[i+yPos+HIDDEN_ROWS][j+xPos].exist = true;

                    }
                }
            }
        }
        // kiểm tra va chạm dưới

        bool collision(Grid *grid, bool disabled = 1){ // ...

            if (active){
                // std::cout << "begin" << std::endl;
                int bottomSide = collin.y + collin.h;
                // static int moribundFrames = 0;
                if ((bottomSide >= ROWS  || collisionWithOtherTetrads(grid)) && disabled){
                    // std::cout << "begin" << std::endl;
                    // std::cout << "b3" << std::endl;
                    // moribundFrames++;
                    // if (moribundFrames>=delayBeforeDied){ //...
                        
                        // moribundFrames = 0;
                        disableFromActivate();
                        // fixTheSuperimposed(grid);
                        mergeToGrid(grid);
                    // std::cout << "end1" << std::endl;
                    // }
                    return true;
                }
                // std::cout << "end2" << std::endl;
                return false;
                // std::cout << "end" << std::endl;
            }
            // std::cout << "end3" << std::endl;
            return true;
        
        }
        //kiểm tra chồng chéo giữa các khối tetrads và tetrads với grid
        bool checkSuperimposed(Grid *grid){
            for (int i=0; i<sizeOfTetradsSide; i++){
                for (int j=0; j<sizeOfTetradsSide; j++){
                    if (matrix[i][j]){
                        if (grid->getGrid()[i+yPos+HIDDEN_ROWS][j+xPos].exist || collin.x < 0|| collin.y < HIDDEN_ROWS*-1  || collin.x + collin.w > COLS || collin.y + collin.h > ROWS){
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        // kiểm tra va chạm với các khối tetrads khác
        bool collisionWithOtherTetrads(Grid *grid){ //bug
        // std::cout <<
        // std::cout<< "ye" <<yyyyyyystd::endl;
            for (int i=0; i<sizeOfTetradsSide; i++){
                for (int j=0; j<sizeOfTetradsSide; j++){
                    if (matrix[i][j]){
                        // std::cout << i+yPos+HIDDEN_ROWS+1 << ' ' << j+xPos <<std::endl;
                        if (grid->getGrid()[i+yPos+HIDDEN_ROWS+1][j+xPos].exist){
                            return true;
                        }
                    }
                }
            }

            // for (int i=collin.x; i<collin.x+collin.w; i++){
            //     // std::cout << collin.y+collin.h+HIDDEN_ROWS << ' ' << i << std::endl;
            //     if (grid->getGrid()[collin.y+collin.h+HIDDEN_ROWS][i].exist){
            //         return true;
            //     }
            // }
            return false;
        }

        // va chạm phải, trái
        bool collisionWithRightTetrads(Grid *grid){
            for (int i=0; i<sizeOfTetradsSide; i++){
                for (int j=0; j<sizeOfTetradsSide; j++){
                    if (matrix[i][j]){
                        if (grid->getGrid()[i+yPos+HIDDEN_ROWS][j+xPos+1].exist){

                            return true;
                        }
                    }
                }
            }
            return false;
        }
        bool collisionWithLeftTetrads(Grid *grid){
            for (int i=0; i<sizeOfTetradsSide; i++){
                for (int j=0; j<sizeOfTetradsSide; j++){
                    if (matrix[i][j]){
                        if (grid->getGrid()[i+yPos+HIDDEN_ROWS][j+xPos-1].exist){
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        bool leftCollision(Grid grid){ // ...
            int leftSide = collin.x;
            if (leftSide <= 0 || collisionWithLeftTetrads(&grid)){
                
                return true;
            }
            return false;
        }
        bool rightCollision(Grid grid){ // ...
            int rightSide = collin.x+collin.w;
            if (rightSide >= COLS || collisionWithRightTetrads(&grid)){
                
                return true;
            }
            return false;
        }
        // xác định hình chữ nhật bao quanh khối tetrads
        void detectCoveredRect(){ //bug
            collin.w = 0; collin.h = 0;
            for (int i=0; i<sizeOfTetradsSide; i++){
                for (int j=0; j<sizeOfTetradsSide; j++){
                    if (matrix[i][j]!=0){
                        collin.h++;
                        break;
                    }
                }
            }
            for (int j=0; j<sizeOfTetradsSide; j++){
                for (int i=0; i<sizeOfTetradsSide; i++){
                    if (matrix[i][j]!=0){
                        collin.w++;
                        break;
                    }
                }
            }

            bool xStop = false, yStop = false;
            for (int i=0; i<sizeOfTetradsSide && !xStop; i++){
                for (int j=0; j<sizeOfTetradsSide && !xStop; j++){
                    if (matrix[i][j]!=0){
                        collin.y = yPos+i;
                        xStop = true;
                    }
                }
            }
            for (int j=0; j<sizeOfTetradsSide && !yStop; j++){
                for (int i=0; i<sizeOfTetradsSide && !yStop; i++){
                    if (matrix[i][j]!=0){
                        collin.x = xPos+j;
                        yStop = true;
                    }
                }
            }
        }

       // hàm thực hiện hành động xoay khối ngược lại
        void rotateBack(){
            if (active){
                transPos(matrix);
                transPos(matrix);
                transPos(matrix);
                detectCoveredRect();
            }

        }
        // rơi khối tetrads
        void fall(int velocity, Grid *grid){
            if (active && falling && !pause){
                if (startTime == 0){
                    startTime = SDL_GetTicks();
                }
                if (SDL_GetTicks() - startTime >= velocity){ // cứ mỗi velocity/1000 giây khối tetrads sẽ rơi xuống
                    moveDown(grid);
                    startTime = SDL_GetTicks();
                }
           }
        }
        // di chuyển
        void moveUp(Grid *grid){
                collin.y--;
                yPos--;
        }
        void moveDown(Grid *grid, bool disable = 1){
                                                // std::cout << collin.x << ' ' << collin.y<<' ' << collin.w << ' ' <<collin.h<<std::endl;

            if (!collision(grid, disable)){
                collin.y++;
                yPos++;
            }
                                   
                                                // std::cout << collin.x << ' ' << collin.y<<' ' << collin.w << ' ' <<collin.h<<std::endl;

        }
        void moveRight(Grid *grid){
            if (!rightCollision(*grid) ){
                collin.x++;
                xPos++;
            }
        }

        void moveLeft(Grid *grid){

            if (!leftCollision(*grid) ){
                collin.x--;
                xPos--;
            }
        }
        // rơi thẳng xuống nếu phím enter is pressed
        void dropDown(Grid *grid){
            
            if (active && ((collin.y + collin.h - 1) < grid->getHighestRow(0, collin.x, collin.x+collin.w-1))){
                while(!collision(grid)){ //bughere
                    moveDown(grid);
                }
            }
            disableFromActivate();
            
        }
        void fixTheSuperimposed(Grid *grid){
            if (checkSuperimposed(grid)){
                moveLeft(grid);
                detectCoveredRect();
                if(checkSuperimposed(grid)){
                    moveLeft(grid);
                    detectCoveredRect();
                    if (checkSuperimposed(grid)){
                        moveRight(grid);
                        detectCoveredRect();
                        moveRight(grid);
                        detectCoveredRect();
                        moveRight(grid);
                        detectCoveredRect();
                        if (checkSuperimposed(grid)){
                            moveRight(grid);
                            detectCoveredRect();
                            if (checkSuperimposed(grid)){
                                moveLeft(grid);
                                detectCoveredRect();
                                moveLeft(grid);
                                detectCoveredRect();
                                moveUp(grid);
                                detectCoveredRect();
                                if (checkSuperimposed(grid)){
                                    moveUp(grid);
                                    detectCoveredRect();
                                    if (checkSuperimposed(grid)){
                                        moveDown(grid, 0);
                                        detectCoveredRect();
                                        moveDown(grid, 0);
                                        detectCoveredRect();
                                        moveDown(grid, 0);
                                        detectCoveredRect();
                                        if (checkSuperimposed(grid)){
                                            moveUp(grid);
                                            detectCoveredRect();
                                            rotateBack();
                                            detectCoveredRect();
                                        }
                                    }
                                }
                            }    
                        }
                    }
                }
            }
        }
        // hàm xoay (fix lỗi va chạm, lỗi chồng chéo khi xoay, có thể refac để code đẹp hơn nhưng em chưa kịp làm)
        void rotate(Grid *grid){
            if (active){
                transPos(matrix);
                detectCoveredRect();
                fixTheSuperimposed(grid);
                detectCoveredRect();
                // std::cout <<collin.y + collin.h << std::endl;
            }
        }
        void swapWithHolding(Tetromino &holding){

        }
};
// define matrix của 7 loại tetrads
static bool matrixStructure_I[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_L[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_J[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {0, 0, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_O[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_S[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_T[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
};

static bool matrixStructure_Z[sizeOfTetradsSide][sizeOfTetradsSide] = {
    {0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};
// khởi tạo 7 loại tetrads
const Tetromino Tetrads[TOTAL_OF_TETRADS] =
    {
        {
            I_BLOCK,
            TetroColor[I_BLOCK],
            matrixStructure_I,
            4, 1,
            xTetradsInit, yTetradsInit+1
        },

        {
            L_BLOCK,
            TetroColor[L_BLOCK],
            matrixStructure_L,
            3, 2,
            xTetradsInit, yTetradsInit+1
        },

        {
            J_BLOCK,
            TetroColor[J_BLOCK],
            matrixStructure_J,
            3, 2,
            xTetradsInit, yTetradsInit+1
        },

        {
            O_BLOCK,
            TetroColor[O_BLOCK],
            matrixStructure_O,
            2, 2,
            xTetradsInit+1, yTetradsInit+1
        },

        {
            S_BLOCK,
            TetroColor[S_BLOCK],
            matrixStructure_S,
            3, 2,
            xTetradsInit, yTetradsInit+1
        },

        {
            T_BLOCK,
            TetroColor[T_BLOCK],
            matrixStructure_T,
            3, 2,
            xTetradsInit, yTetradsInit+1
        },

        {
            Z_BLOCK,
            TetroColor[Z_BLOCK],
            matrixStructure_Z,
            3, 2,
            xTetradsInit, yTetradsInit+1
        }
    };

Tetromino* getRandomTetrads();


#endif