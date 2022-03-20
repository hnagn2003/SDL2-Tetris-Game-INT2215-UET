#ifndef Game_h
#define Game_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Tetromino.h"
#include "Grid.h"
#include "Specifications.h"

class Game_State {
    private:
        int lineCount = 0;
        size_t score = 0;
        int level = 1;
        int velocity = 1000;
        Tetromino nextTetrads = getRandomTetrads();
        Tetromino currentTetrads = getRandomTetrads();
    public: 
        int getVel(){
            return velocity;
        }
        Tetromino getCurTetrads(){
            return currentTetrads;
        }
        void updateGameState(short int updateLines){
            score += updateLines * level;
            level = score/100 + 1;
            velocity = -500*(level-1) + 1000;
        }
        void render (SDL_Renderer *renderer){
            currentTetrads.render(renderer);
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
    };
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Grid grid;
    Game_State gameState;
};


#endif