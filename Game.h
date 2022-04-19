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
        int lineCount;
        size_t score;
        int level;
        int velocity;
        int moveVel;
        Tetromino nextTetrads;
        Tetromino currentTetrads;
        Grid grid;
    public: 
        Game_State(){
            lineCount = 0;
            score = 0;
            level = 1;
            velocity = initVelocity;
            moveVel = velocity;
            nextTetrads = getRandomTetrads();
            currentTetrads = getRandomTetrads();
        }

        Grid getGrid(){
            return grid;
        }
        Tetromino* getCurTetrads(){
            return &currentTetrads;
        }
        Tetromino* getNextTetrads(){
            return &nextTetrads;
        }
        void updateGameState(short int updateLines){
            score += updateLines * level;
            level = lineCount/10+1;
            velocity = -500*(level-1) + 1000;
        }
        //
        void render (SDL_Renderer *renderer){
            grid.render(renderer);
            currentTetrads.render(renderer);

        }

        void newTetradsFalling(){
            // if (currentTetrads.getXPos() <= 0){
                currentTetrads.setFall(true);
                currentTetrads.fall(moveVel, &grid);
            // }
        }

        void handleEvent(SDL_Event& event){
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    
                    switch( event.key.keysym.sym )
                    {
                        case SDLK_UP: 
                            if ( !event.key.repeat ){
                                currentTetrads.rotate(&grid); 
                                break;
                            }
                        break;
                        case SDLK_DOWN: 
                            if (currentTetrads.getStatus()){
                                currentTetrads.moveDown(&grid); 
                            }
                            break;
                        case SDLK_LEFT: 
                            currentTetrads.moveLeft(&grid); 
                            break;
                        case SDLK_RIGHT: 
                            currentTetrads.moveRight(&grid); 
                            break;
                        case SDLK_SPACE:
                            // std::cout << "e1 "<<currentTetrads.getYPos()<<' ' << nextTetrads.getYPos() << std::endl;
                            currentTetrads.dropDown(&grid);
                            // std::cout << "e2 "<<currentTetrads.getYPos()<<' ' << nextTetrads.getYPos() << std::endl;
                            break;
                        default: break;
                    }
                    
                    break;
                case SDL_KEYUP:
                    switch( event.key.keysym.sym )
                    {
                        case SDLK_DOWN: moveVel = velocity; break;
                        // case SDLK_LEFT: 
                        //     break;
                        // case SDLK_RIGHT: 
                        //     break;
                        default: break;
                    }
                    break;
                default:
                    
                    break;
            }
        //     const Uint8* keystates = SDL_GetKeyboardState(NULL);

        //     if(keystates[SDL_SCANCODE_LEFT]) {
        //         currentTetrads.moveLeft(grid);
        //     }
        //     if(keystates[SDL_SCANCODE_RIGHT]) {
        //         currentTetrads.moveRight(grid); 
        //     }
        }
        void updateFallingTetrads(){
            // std::cout << "b2"<<currentTetrads.getYPos()<<' ' << nextTetrads.getYPos() << std::endl;
            if (!currentTetrads.getStatus()){
                if (grid.getHighestRow()<=HIDDEN_ROWS){
                    nextTetrads.setCollinYInitTetrads();
                }
                
                int filledRow = grid.update(currentTetrads.getYPos()+HIDDEN_ROWS, currentTetrads.getYPos()+currentTetrads.getHCol()+HIDDEN_ROWS);
                updateGameState(filledRow);
                std::cout << "e1"<<currentTetrads.getYPos()<<' ' << nextTetrads.getYPos() << std::endl;
                currentTetrads = nextTetrads;
                std::cout << "e2"<<currentTetrads.getYPos()<<' ' << nextTetrads.getYPos() << std::endl;
                nextTetrads = getRandomTetrads();
                
            }
                    

        }
        bool gameOver(){
            if (grid.getHighestRow()<=delimitedLine+HIDDEN_ROWS){
                return true;
            }
            return false;
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