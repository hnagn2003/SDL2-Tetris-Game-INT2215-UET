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
        BattleEnded()
        {
            direct = InGame_BattleMode;
        }
        Tabs getDirect()
        {
            return direct;
        }
        bool handleEvents(SDL_Event* e)
        {
            backButton->handleEvents(e, 1);
            if (backButton->getPressed())
            {
                backButton->setPressed(0);
                direct=Menu;
                return false;
            }
            replayButton->handleEvents(e, 1);
            if (replayButton->getPressed())
            {
                replayButton->setPressed(0);
                direct=InGame_BattleMode;
                return true;
            }

            direct = InGame_BattleMode; 
            return false;
        }
        void render(SDL_Renderer* renderer, Result result, int p1Score, int p2Score)
        {
            static LTexture battle_endTex(battle_endedP, renderer);
            battle_endTex.render(renderer, 0, 0);
            backButton->render(renderer, backButton->getXCen()-backButton->getWidth()/2, backButton->getYCen()-backButton->getHeight()/2);
            replayButton->render(renderer, replayButton->getXCen()-replayButton->getWidth()/2, replayButton->getYCen()-replayButton->getHeight()/2);
            switch (result)
            {
            case DRAW:
                static LTexture drawTex(drawP, renderer);
                drawTex.render(renderer, 0, 0);
                break;
            case Player2WIN:
                static LTexture player1winTex(player1winP, renderer);
                player1winTex.render(renderer, 0, 0);
                break;
            case Player1WIN:
                static LTexture player2winTex(player2winP, renderer);
                player2winTex.render(renderer, 0, 0);
                break;
            default:
                break;
            }
            //render score
            renderText(std::to_string(p2Score), renderer, fontStar_40, 425, 780, WHITE_COLOR);
            renderText(std::to_string(p1Score), renderer, fontStar_50, 1543, 780, WHITE_COLOR);
        }
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
        
        BallteProcessor()
        {
            direct = InGame_BattleMode;
            gameStatePlayer1 = new Game_State;
            gameStatePlayer2 = new Game_State;
            battleEnded = new BattleEnded;
            isOver = 0;
            result = NONE;
        }
        Game_State *getGameState1()
        {
            return gameStatePlayer1;
        }
        void reset()
        {
            gameStatePlayer1->reset();
            gameStatePlayer2->reset();
            isOver = 0;
            result = NONE;
        }
        bool getOver()
        {
            return isOver;
        }
        Tabs getDirect()
        {
            return direct;
        }
        void handleEvent(SDL_Event event)
        {
            if (isOver){
                gameStatePlayer1->pauseGame();
                gameStatePlayer2->pauseGame();
                if (battleEnded->handleEvents(&event))
                {
                    reset();
                }
                direct = battleEnded->getDirect();
                return;
            }
            switch (event.type)
            {   
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym )
                    { 
                        case SDLK_p: 
                            if(!gameStatePlayer1->getPause() && !gameStatePlayer2->getPause())
                            {
                                gameStatePlayer1->pauseGame();
                                gameStatePlayer2->pauseGame();
                            }
                            else
                            {
                                gameStatePlayer1->startCD();
                                gameStatePlayer2->startCD();
                            }
                            return;
                    
                        default: break;
                            
                    }
                default: break;
            }
            std::thread x(&Game_State::handleEvent, gameStatePlayer1, event, Player1);
            std::thread y(&Game_State::handleEvent, gameStatePlayer2, event, Player2);
            x.join();
            y.join();
            direct = gameStatePlayer1->getDirect();
            if (direct == InGame_SoloMode)
            {
                direct = InGame_BattleMode;
            }else
            {
                *gameStatePlayer1 = Game_State();
                *gameStatePlayer2 = Game_State();
            }
        }
        void update()
        {
            isOver = gameOver();
            std::thread x(&Game_State::update, gameStatePlayer1, Player1);
            std::thread y(&Game_State::update, gameStatePlayer2, Player2);
            x.join();
            y.join();
            // gameStatePlayer1->update(Player1);
            // gameStatePlayer2->update(Player2);
            static bool battleOver_SE = true;
            if (isOver)
            {
                if (battleOver_SE){
                    playSoundEffects(se_gameover);
                    battleOver_SE = false;
                }
                return;
            }
            battleOver_SE = true;
        }
        void render(SDL_Renderer* renderer)
        {
            gameStatePlayer1->render(renderer, Player1);
            gameStatePlayer2->render(renderer, Player2);
            long long P1Score = gameStatePlayer1->getScore(), P2Score = gameStatePlayer2->getScore();
            if (isOver){
                battleEnded->render(renderer, result, P1Score, P2Score);
            }
        }
        bool gameOver()
        {
            result = checkResult();
            return (result != NONE);
        }
        Result checkResult(){
            bool P1Over = gameStatePlayer1->gameOver(), P2Over = gameStatePlayer2->gameOver();
            long long P1Score = gameStatePlayer1->getScore(), P2Score = gameStatePlayer2->getScore();
            if (P1Over && !P2Over)
            {
                return Player2WIN;
            }
            if (!P1Over && P2Over)
            {
                return Player1WIN;
            }
            if (P1Over && P2Over)
            {
                if (P1Score > P2Score)
                {
                    return Player1WIN;
                }
                else if (P1Score < P2Score)
                {
                    return Player2WIN;
                }
                else
                {
                    return DRAW;
                }
            }
            return NONE;
        }
};
#endif