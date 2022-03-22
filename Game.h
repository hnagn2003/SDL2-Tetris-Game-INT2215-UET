#ifndef Game_h
#define Game_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Tetromino.h"
#include "Grid.h"
#include "Specifications.h"
#include <iostream>

class Game_State {
    private:
        int lineCount = 0;
        size_t score = 0;
        int level = 1;
        int velocity = 500;
        int moveVel = velocity;
        Tetromino nextTetrads = getRandomTetrads();
        Tetromino currentTetrads = getRandomTetrads();
        Grid grid;
    public: 

        int getOriginVel(){
            return velocity;
        }
        void setVel(int vel){
            moveVel = vel;
        }
        Grid getGrid(){
            return grid;
        }
        Tetromino* getCurTetrads(){
            return &currentTetrads;
        }
        void updateGameState(short int updateLines){
            score += updateLines * level;
            level = score/100 + 1;
            velocity = -500*(level-1) + 1000;
        }
        void render (SDL_Renderer *renderer){
            currentTetrads.render(renderer);
        }

        void newTetradsFalling(){
            currentTetrads.fall(moveVel, grid);
        }


};

class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int xPos, int yPos, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running()
    {
        return isRunning;
    }
    // void setRunning(bool running){
    //     isRunning = running;
    // }
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Game_State gameState;
};


#endif