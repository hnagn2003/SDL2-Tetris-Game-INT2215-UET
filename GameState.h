#ifndef GameState1_h
#define GameState1_h
#include "Specifications.h"
#include <string>
class Game_State 
{
    private:
        bool playing;
        int lineCount;
        long long score;
        int level;
        int velocity;
        LEVEL difficulty;
        bool switchHold;
        bool pause;
        int countDownTime;
        bool inCountDown;
        Tabs direct;
        Uint32 timeC;
        Tetromino* next0Tetrads;
        Tetromino* next1Tetrads;
        Tetromino* next2Tetrads;
        Tetromino* currentTetrads;
        Tetromino* holding;
        Grid* grid;
        GameOverAnnouncement* gameOverAnnouncement;
        bool isOver;
        bool recordScore;
    public: 
        Game_State();
        ~Game_State();
        Tabs getDirect();
        bool getOver();
        bool getPlaying();
        void setPlaying(bool _playing);
        bool getPause();
        long long getScore();

        Grid* getGrid();
        Tetromino* getCurTetrads();
        Tetromino* getNext0Tetrads();
        

        void setCountDownTime(int c);
        void setInCountDown(bool iC);
        bool isInCountDown();
        void updateGameState(short int updateLines);
        void setRecord(bool set);
        bool getRecord();
        void render (SDL_Renderer *renderer, GameMode gameMode = SinglePlay);

        void renderGrid(SDL_Renderer *renderer, GameMode gameMode = SinglePlay);
        void renderOver(SDL_Renderer *renderer, GameMode gameMode = SinglePlay);
        void newTetradsFalling();

        void reset();
        void handleEvent(SDL_Event event, GameMode gameMode = SinglePlay);
        void processEventSinglePlay(const SDL_Event &event);
        void processEventPlayer2(SDL_Event event);

        void processEventPlayer1(SDL_Event event);
        void pauseGame();
        void startCD();
        void countDownHandle();
        void updateFallingTetrads();

        bool gameOver();
        void update(GameMode gameMode = SinglePlay);

        void holdCurrentTetrads();

        void swapHoldingWithCurrent();
};

#endif