#ifndef Game_h
#define Game_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Tetromino.h"
#include "Grid.h"
#include "Specifications.h"
#include <iostream>
#include "Structure.h"


class Game_State {
    private:
        bool playing;
        int lineCount;
        long long score;
        int level;
        int velocity;
        int moveVel;
        bool switchHold;
        Tetromino* next0Tetrads;
        Tetromino* next1Tetrads;
        Tetromino* next2Tetrads;
        Tetromino* currentTetrads;
        Tetromino* holding;
        Grid* grid;

    public: 
        Game_State(){
            playing = 0;
            lineCount = 0;
            score = 0;
            level = 1;
            switchHold = 0;
            velocity = initVelocity;
            moveVel = velocity;
            next0Tetrads = new Tetromino;
            next1Tetrads = new Tetromino;
            next2Tetrads = new Tetromino;
            currentTetrads = new Tetromino;
            next0Tetrads = getRandomTetrads();
            next1Tetrads = getRandomTetrads();
            next2Tetrads = getRandomTetrads();
            currentTetrads = getRandomTetrads();
            grid = new Grid;
        }
        bool getPlaying(){
            return playing;
        }
        void setPlaying(bool _playing){
            playing = _playing;
        }
        Grid* getGrid(){
            return grid;
        }
        Tetromino* getCurTetrads(){
            return currentTetrads;
        }
        Tetromino* getNext0Tetrads(){
            return next0Tetrads;
        }
        void updateGameState(short int updateLines){
            score += updateLines * level;
            level = lineCount/10+1;
            velocity = -500*(level-1) + 1000;
        }
        //
        void render (SDL_Renderer *renderer){
            grid->render(renderer);
            currentTetrads->render(renderer);
        }

        void newTetradsFalling(){
            if (playing){
            // if (currentTetrads.getXPos() <= 0){
                currentTetrads->setFall(true);
                currentTetrads->fall(moveVel, grid);
            // }
            }
        }

        void handleEvent(SDL_Event& event){
            if (playing){
                
                switch (event.type)
                {
                    case SDL_KEYDOWN:
                        
                        switch( event.key.keysym.sym )
                        {   
                            
                            case SDLK_UP: 
                                if ( !event.key.repeat ){
                                    currentTetrads->rotate(grid); 
                                    break;
                                }
                            break;
                            case SDLK_DOWN:
                                 
                                if (currentTetrads->getStatus()){
                                    currentTetrads->moveDown(grid); 
                                }
                                
                                break;
                            case SDLK_LEFT: 
                            
                                currentTetrads->moveLeft(grid); 
                                
                                break;
                            case SDLK_RIGHT: 
                                currentTetrads->moveRight(grid); 
                                break;
                            case SDLK_SPACE:
                                
                                // std::cout << "e1 "<<currentTetrads->getYPos()<<' ' << nextTetrads->getYPos() << std::endl;
                                currentTetrads->dropDown(grid);
                                
                                // std::cout << "e2 "<<currentTetrads->getYPos()<<' ' << nextTetrads->getYPos() << std::endl;
                                break;
                            case SDLK_c:
                                // if (holding == NULL){
                                //     holding = new Tetromino;
                                //     holding = currentTetrads;
                                //     currentTetrads = next0Tetrads;
                                //     currentTetrads->setXPos(holding->getXPos());
                                //     currentTetrads->setYPos(holding->getYPos());
                                //     currentTetrads->detectCoveredRect();
                                //     next0Tetrads = next1Tetrads;
                                //     next1Tetrads = next2Tetrads;
                                //     next2Tetrads = getRandomTetrads();
                                // }else{
                                //     if (!switchHold){
                                //         Tetromino* tmp = holding;
                                //         holding = currentTetrads;
                                //         currentTetrads = tmp;
                                //         // delete tmp;
                                //         currentTetrads->setXPos(holding->getXPos());
                                //         currentTetrads->setYPos(holding->getYPos());
                                //         currentTetrads->detectCoveredRect();
                                //     }
                                // }
                                // switchHold = 1;
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
            if (playing){
                // std::cout << "b2"<<currentTetrads.getYPos()<<' ' << nextTetrads.getYPos() << std::endl;
                if (!currentTetrads->getStatus()){
                    // std::cout<<'1' << nextTetrads.getYPos() <<std::endl;
                    int highestRow = grid->getHighestRow(0, 0, COLS-1);
                    std::cout << "higest row " << highestRow << std::endl;
                    if (highestRow<=(HIDDEN_ROWS+2)){ //ch
                        next0Tetrads->setCollinYInitTetrads(highestRow);
                        std::cout << "y " << next0Tetrads->getYPos();
                    }
                    
                    // std::cout << next0Tetrads->getYPos() << ' ' << next0Tetrads->getYCol() << std::endl;
                    // std::cout<<'2' << nextTetrads.getYPos() <<std::endl;
                    int filledRow = grid->update(currentTetrads->getYPos()+HIDDEN_ROWS, currentTetrads->getYPos()+currentTetrads->getHCol()+HIDDEN_ROWS);
                    updateGameState(filledRow);
                    switchHold = 0;
                    currentTetrads = next0Tetrads;
                    next0Tetrads = next1Tetrads;
                    next1Tetrads = next2Tetrads;
                    next2Tetrads = getRandomTetrads();
                }
            }     
        }

        bool gameOver(){
            if (playing){
                if (grid->getHighestRow(0, 0, COLS-1)<=delimitedLine+HIDDEN_ROWS){
                    playing = 0;
                    return true;
                }
                return false;
            }
            return true;
        }
        
};

class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int xPos, int yPos, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen);
    void loadmedia();
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
    TTF_Font* gFont;
    FPS_Processor* gFPS_Processor;
    Game_State *gameState;
    int tabs;
    Tabs_Menu tabs_menu;
};


#endif