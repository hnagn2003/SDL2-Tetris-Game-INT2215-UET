#ifndef GameState1_h
#define GameState1_h
#include "Specifications.h"
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
        Game_State()
        {
            playing = 0;
            lineCount = 0;
            score = 0;
            level = 1;
            switchHold = 0;
            pause = 0;
            countDownTime = 0;
            inCountDown = 0;
            timeC = 0;
            direct = InGame_SoloMode;
            velocity = initVelocity;
            isOver = 0;
            recordScore = 0;
            holding = NULL;
            next0Tetrads = getRandomTetrads();
            next1Tetrads = getRandomTetrads();
            next2Tetrads = getRandomTetrads();
            currentTetrads = getRandomTetrads();
            gameOverAnnouncement = new GameOverAnnouncement;
            grid = new Grid;
            difficulty = easy; //...

        }
        Tabs getDirect()
        {
            return direct;
        }
        bool getOver()
        {
            return isOver;
        }
        bool getPlaying()
        {
            return playing;
        }
        void setPlaying(bool _playing)
        {
            playing = _playing;
        }
        bool getPause()
        {
            return pause;
        }
        long long getScore()
        {
            return score;
        }

        Grid* getGrid()
        {
            return grid;
        }
        Tetromino* getCurTetrads()
        {
            return currentTetrads;
        }
        Tetromino* getNext0Tetrads()
        {
            return next0Tetrads;
        }
        void setCountDownTime(int c)
        {
            countDownTime = c;
        }
        void setInCountDown(bool iC)
        {
            inCountDown = iC;
        }
        bool isInCountDown()
        {
            return inCountDown;
        }
        void updateGameState(short int updateLines)
        {
            score += updateLines * level;
            level = lineCount/(int)difficulty+1;
            velocity = 1000/level;
        }
        void setRecord(bool set)
        {
            recordScore = set;
        }
        bool getRecord()
        {
            return recordScore;
        }
        void render (SDL_Renderer *renderer, GameMode gameMode = SinglePlay)
        {
            renderGrid(renderer, gameMode);
            if (countDownTime > 0)
            {
                renderText(countDownTime, renderer, gFont1, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, WHITE_COLOR);
            }
            
            if (gameMode!=Player1 && pause && playing)
            {
                static LTexture pressPTex;
                pressPTex.loadFromRenderedText("Press P to pause/continue the game", DARK_CYAN_COLOR, fontVarino1, renderer);
                pressPTex.render(renderer, (SCREEN_WIDTH - pressPTex.getWidth())/2, 100);
            }
            backButton->render(renderer, backButton->getXCen()-backButton->getWidth()/2, backButton->getYCen()-backButton->getHeight()/2);
            renderOver(renderer, gameMode);
        }

        void renderGrid(SDL_Renderer *renderer, GameMode gameMode = SinglePlay)
        {
            grid->render(renderer, gameMode);
            renderText(lineCount, renderer, gFont1, 693.5+grid->getX(), 628.5+grid->getY());
            renderText(score, renderer, gFont1, 693.5+grid->getX(), 736+grid->getY());
            renderText(level, renderer, gFont1, 693.5+grid->getX(), 842+grid->getY());
            if (holding!=NULL)
            {
                holding->render(renderer, grid->getX(), 663-2*TILE_SIZE, 242-2*TILE_SIZE);
            }
            next0Tetrads->render(renderer, grid->getX(), 1259-2*TILE_SIZE, 244-2*TILE_SIZE);
            next1Tetrads->render(renderer, grid->getX(), 1259-2*TILE_SIZE, 400-2*TILE_SIZE);
            next2Tetrads->render(renderer, grid->getX(), 1259-2*TILE_SIZE, 556-2*TILE_SIZE);
            if (settingsElement["Ghost Piece"] == 1)
            {
                currentTetrads->renderGhostPiece(renderer, grid);
            }
            currentTetrads->render(renderer, grid->getX());
        }
        void renderOver(SDL_Renderer *renderer, GameMode gameMode = SinglePlay)
        {
            if (isOver && gameMode==SinglePlay)
            {
                gameOverAnnouncement->render(renderer);
                LTexture printScore;
                printScore.loadFromRenderedText(std::to_string(score), BLACK_COLOR, gFont1, renderer);
                printScore.render(renderer, 914, 236);
            } 
        }

        void newTetradsFalling()
        {
            if (playing){
                currentTetrads->setFall(true);
                currentTetrads->fall(velocity, grid);
            }
        }

        void reset()
        {
            playing = 0;
            lineCount = 0;
            score = 0;
            level = 1;
            switchHold = 0;
            pause = 0;
            countDownTime = 0;
            inCountDown = 0;
            isOver = 0;
            direct = InGame_SoloMode;
            velocity = initVelocity;
            recordScore = 0;
            next0Tetrads = getRandomTetrads();
            next1Tetrads = getRandomTetrads();
            next2Tetrads = getRandomTetrads();
            currentTetrads = getRandomTetrads();
            grid = new Grid;
            difficulty = (LEVEL)settingsElement["Level"]; //...
        }
        void handleEvent(SDL_Event event, GameMode gameMode = SinglePlay)
        {
            if (isOver && gameMode == SinglePlay){
                if (gameOverAnnouncement->handleEvents(&event))
                {
                    reset();
                }
                direct = gameOverAnnouncement->getDirect();

                return;
            }
            if (gameMode != Player2){
                backButton->handleEvents(&event, 1);
                if (backButton->getPressed())
                {
                    Mix_HaltMusic();
                    reset();
                    direct=Menu;
                    return;
                }
            }
            direct = InGame_SoloMode;
            if (playing)
            {
                switch (event.type)
                {   
                    case SDL_KEYDOWN:
                        if (gameMode == SinglePlay){
                            processEventSinglePlay(event);
                        }
                        else
                        {
                            if (gameMode == Player2)
                            {
                                processEventPlayer2(event);
                            }else{
                                processEventPlayer1(event);   
                            }
                        }
                        break;
                    case SDL_KEYUP:
                        switch( event.key.keysym.sym )
                        {
                            default: break;
                        }
                        break;
                    default:
                        
                        break;
                }
            }

        }
        void processEventSinglePlay(const SDL_Event &event)
        {
            switch( event.key.keysym.sym )
            {   
                case SDLK_UP: 
                    if ( !event.key.repeat && !pause )
                    {
                        currentTetrads->rotate(grid);
                        playSoundEffects(se_rotate);
                        break;
                    }
                break;
                case SDLK_DOWN:
                    
                    if (currentTetrads->getStatus() && !pause)
                    {
                        currentTetrads->moveDown(grid);
                        playSoundEffects(se_move);
                    }
                    
                    break;
                case SDLK_LEFT: 
                    if (!pause){
                        int tmp_leftPos = currentTetrads->getXCol();
                        currentTetrads->moveLeft(grid); 
                        if (tmp_leftPos != currentTetrads->getXCol())
                        {
                            playSoundEffects(se_move);
                        }
                    }
                    break;
                case SDLK_RIGHT: 
                    if (!pause){
                        int tmp_rightPos = currentTetrads->getXCol();
                        currentTetrads->moveRight(grid); 
                        if (tmp_rightPos != currentTetrads->getXCol())
                        {
                            playSoundEffects(se_move);
                        }
                    }
                    break;
                case SDLK_SPACE:
                    if (!pause){
                        currentTetrads->dropDown(grid);
                        playSoundEffects(se_drop);
                    }
                    break;
                case SDLK_c:
                    if (!pause)
                    {
                        if (holding == NULL)
                        {
                            playSoundEffects(se_hold);
                            holding = new Tetromino;
                            *holding = Tetrads[currentTetrads->getType()];
                            currentTetrads = next0Tetrads;
                            next0Tetrads = next1Tetrads;
                            next1Tetrads = next2Tetrads;
                            next2Tetrads = getRandomTetrads();
                        }else{
                            if (!switchHold)
                            {
                                playSoundEffects(se_hold);
                                int tmp = holding->getType();
                                *holding = Tetrads[currentTetrads->getType()];
                                *currentTetrads = Tetrads[tmp];
                            }
                        }
                        switchHold = 1;
                    }
                    break;
                case SDLK_p:
                    if(!pause)
                    {
                        pauseGame();
                        playSoundEffects(se_pause);
                    }
                    else
                    {
                        startCD();
                    }
                    break;
            
                default: break;
            }    
        }
        void processEventPlayer2(SDL_Event event){
            switch( event.key.keysym.sym )
            {   
                case SDLK_w: 
                    if ( !event.key.repeat && !pause )
                    {
                        currentTetrads->rotate(grid); 
                        playSoundEffects(se_rotate);
                        break;
                    }
                break;
                case SDLK_s:
                    
                    if (currentTetrads->getStatus() && !pause)
                    {
                        currentTetrads->moveDown(grid); 
                        playSoundEffects(se_move);
                    }
                    
                    break;
                case SDLK_a: 
                    if (!pause){
                        int tmp_leftPos = currentTetrads->getXCol();
                        currentTetrads->moveLeft(grid); 
                        if (tmp_leftPos != currentTetrads->getXCol())
                        {
                            playSoundEffects(se_move);
                        }
                    }
                    break;
                case SDLK_d: 
                    if (!pause){
                        int tmp_rightPos = currentTetrads->getXCol();
                        currentTetrads->moveRight(grid); 
                        if (tmp_rightPos != currentTetrads->getXCol())
                        {
                            playSoundEffects(se_move);
                        }
                    }
                    break;
                case SDLK_SPACE:
                    if (!pause){
                        currentTetrads->dropDown(grid);
                        playSoundEffects(se_drop);
                    }
                    
                    break;
                case SDLK_c:
                    if (!pause)
                    {
                        if (holding == NULL)
                        {
                            playSoundEffects(se_hold);
                            holding = new Tetromino;
                            *holding = Tetrads[currentTetrads->getType()];
                            currentTetrads = next0Tetrads;
                            next0Tetrads = next1Tetrads;
                            next1Tetrads = next2Tetrads;
                            next2Tetrads = getRandomTetrads();
                        }
                        else
                        {
                            if (!switchHold)
                            {
                                playSoundEffects(se_hold);
                                int tmp = holding->getType();
                                *holding = Tetrads[currentTetrads->getType()];
                                *currentTetrads = Tetrads[tmp];
                            }
                        }
                        switchHold = 1;
                    }
                    break;
                case SDLK_p:
                    if(!pause)
                    {
                        pauseGame();
                        playSoundEffects(se_pause);
                    }
                    else
                    {
                        startCD();
                    }
                    break;
            
                default: break;
            }
        }

        void processEventPlayer1(SDL_Event event)
        {
        switch( event.key.keysym.sym )
            {   
                case SDLK_UP: 
                    if ( !event.key.repeat && !pause )
                    {
                        currentTetrads->rotate(grid); 
                        playSoundEffects(se_rotate);
                        break;
                    }
                break;
                case SDLK_DOWN:
                    
                    if (currentTetrads->getStatus() && !pause)
                    {
                        currentTetrads->moveDown(grid); 
                        playSoundEffects(se_move);
                    }
                    
                    break;
                case SDLK_LEFT: 
                    if (!pause){
                        int tmp_leftPos = currentTetrads->getXCol();
                        currentTetrads->moveLeft(grid); 
                        if (tmp_leftPos != currentTetrads->getXCol())
                        {
                            playSoundEffects(se_move);
                        }
                    }
                    break;

                case SDLK_RIGHT: 
                    if (!pause){
                        int tmp_rightPos = currentTetrads->getXCol();
                        currentTetrads->moveRight(grid); 
                        if (tmp_rightPos != currentTetrads->getXCol())
                        {
                            playSoundEffects(se_move);
                        }
                    }
                    break;

                case SDLK_KP_ENTER:
                    if (!pause)
                        currentTetrads->dropDown(grid);
                        playSoundEffects(se_drop);
                    
                    break;
                case SDLK_KP_PLUS:
                    if (!pause){
                        if (holding == NULL){
                            playSoundEffects(se_hold);
                            holding = new Tetromino;
                            *holding = Tetrads[currentTetrads->getType()];
                            currentTetrads = next0Tetrads;
                            next0Tetrads = next1Tetrads;
                            next1Tetrads = next2Tetrads;
                            next2Tetrads = getRandomTetrads();
                        }else{
                            if (!switchHold){
                                playSoundEffects(se_hold);
                                int tmp = holding->getType();
                                *holding = Tetrads[currentTetrads->getType()];
                                *currentTetrads = Tetrads[tmp];
                            }
                        }
                        switchHold = 1;
                    }
                    break;
                case SDLK_p:
                    if(!pause){
                        pauseGame();
                        playSoundEffects(se_pause);
                    }else{
                        startCD();
                    }
                    break;
            
                default: break;
            }            
        }
        void pauseGame(){
            currentTetrads->setPause(1);
            pause = 1;
        }
        void startCD(){
            countDownTime = 3;
            inCountDown = true;
        }
        void countDownHandle()
        {
            if (inCountDown){
                if (countDownTime > 0)
                {
                    if (timeC == 0)
                    {
                        timeC = SDL_GetTicks();
                    }
                    if (SDL_GetTicks() - timeC > 1000)
                    {
                        timeC = SDL_GetTicks();
                        countDownTime --;
                        if (countDownTime == 0){
							playSoundEffects(se_start);
                        }else{
                            playSoundEffects(se_count);
                        }
                    }
                }else{
                    currentTetrads->setPause(0);
                    pause = 0;
                    inCountDown = false;
                }
            }
        }
        void updateFallingTetrads()
        {
            if (playing)
            {
                if (!currentTetrads->getStatus())
                {
                    int highestRow = grid->getHighestRow(0, 0, COLS-1);
                    if (highestRow<=(HIDDEN_ROWS+2))
                    { 
                        next0Tetrads->setCollinYInitTetrads(highestRow);
                        if (holding!=NULL)
                        {
                            holding->setCollinYInitTetrads(highestRow);
                        }
                    }
                    int filledRow = grid->update(currentTetrads->getYPos()+HIDDEN_ROWS, currentTetrads->getYPos()+currentTetrads->getHCol()+HIDDEN_ROWS);
                    lineCount+=filledRow;
                    updateGameState(filledRow);
                    switchHold = 0;
                    currentTetrads = next0Tetrads;
                    next0Tetrads = next1Tetrads;
                    next1Tetrads = next2Tetrads;
                    next2Tetrads = getRandomTetrads();
                }
            }
        }

        bool gameOver()
        {
                if (grid->getHighestRow(0, 0, COLS-1)<=delimitedLine+HIDDEN_ROWS)
                {
                    playing = 0;
                    return true;
                }
            return false;
        }
        void update(GameMode gameMode = SinglePlay)
        {
            isOver = gameOver();
            static bool gameOver_SE = true;
            if (isOver)
            {
                backButton->setPosition(1289, 569);
                if (gameOver_SE && gameMode == SinglePlay)
                {
                    playSoundEffects(se_gameover);
                    gameOver_SE = false;
                }
                return;
            }
            gameOver_SE = true;
            if (!playing)
            {
				startCD();
				pauseGame();
			}
			countDownHandle();
			playing = 1;
			newTetradsFalling();
			updateFallingTetrads();
        }
};

#endif