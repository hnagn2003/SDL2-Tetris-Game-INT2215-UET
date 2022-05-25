#ifndef Battle_h
#define Battle_h
#include "Specifications.h"
#include <thread>
enum Result{
    NONE = -1,
    DRAW,
    Player1WIN,
    Player2WIN
};
class BattleEnded
{
    private:
        Tabs direct;
    public:
        BattleEnded();
        Tabs getDirect();
        bool handleEvents(SDL_Event* e);
        void render(SDL_Renderer* renderer, Result result, int p1Score, int p2Score);
};

class BallteProcessor{
    private:
        Game_State *gameStatePlayer1;
        Game_State *gameStatePlayer2;
        BattleEnded* battleEnded;
        Tabs direct;
        bool isOver;
        Result result;
    public:
        
        BallteProcessor();
        ~BallteProcessor();
        Game_State *getGameState1();
        void reset();
        bool getOver();
        Tabs getDirect();
        void handleEvent(SDL_Event event);
        void update();
        void render(SDL_Renderer* renderer);
        bool gameOver();
        Result checkResult();
};
#endif