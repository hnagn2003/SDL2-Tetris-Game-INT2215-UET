#include "Game.h"
#include "Specifications.h"

int gridSizeToRendererSize(int w)
{
return w*TILE_SIZE;
}

int gridXPosToRendererPos(int x) //...
{
    return (SCREEN_WIDTH - COLS*TILE_SIZE) / 2 + x*TILE_SIZE;
}

int gridYPosToRendererPos(int y)
{
    return (SCREEN_HEIGHT - ROWS*TILE_SIZE) / 2 + y*TILE_SIZE;
}

bool updateScoreTable(int score)
{
    highestScore.push_back(score);
    sort(highestScore.begin(), highestScore.end(), std::greater<int>());
    highestScore.pop_back();
    return true;
}

void printScoreTable(SDL_Renderer *renderer, int x, int y)
{
    LTexture ranking[scoreMaxMem];
    for (int i=0; i<scoreMaxMem; i++)
    {
        if (i==0){
            ranking[i].loadFromRenderedText(std::to_string(highestScore[i]), GOLD_YELLOW_COLOR, fontStar_50, renderer);
        }else{
            ranking[i].loadFromRenderedText(std::to_string(highestScore[i]), WHITE_COLOR, fontStar_40, renderer);
        }
        ranking[i].render(renderer, x, y+i*50);
    }
}

void clearSettings()
{
    settingsElement["Ghost Piece"]=1;
	settingsElement["Level"]=easy;
	settingsElement["Sound Effects"]=1;
	settingsElement["Music Volume"]=80;
}

void clearRankingScore()
{
    for (int i = 0; i<scoreMaxMem; i++)
    {
        highestScore[i] = 0;
    }
}

void renderText(std::string text, SDL_Renderer* renderer, TTF_Font* gFont, int xPos, int yPos, SDL_Color textColor){
    LTexture textTexture;
    textTexture.loadFromRenderedText(text, textColor, gFont, renderer);
    textTexture.render(renderer, xPos-textTexture.getWidth()/2, yPos-textTexture.getHeight()/2);
	textTexture.free();
}

void loadGameFonts(){
    gFont1 = TTF_OpenFont(fo_northStarP.c_str() , 24 );
	fontVarino1 = TTF_OpenFont(fo_Varino1P.c_str(), 20);
	fontStar_40 = TTF_OpenFont(fo_northStarP.c_str(), 40);
	fontStar_50 = TTF_OpenFont(fo_northStarP.c_str(), 50);
}

void loadGameButtons(SDL_Renderer* renderer){
    backButton = new LButton;
	replayButton = new LButton;
	LTexture* backButtonTex = new LTexture;
	LTexture* backButtonTex_ = new LTexture;
	backButtonTex->loadFromFile(back_button, renderer);
    backButtonTex_->loadFromFile(back_button_, renderer);
	backButton->setTexture(backButtonTex, backButtonTex_);

	LTexture* replayButtonTex = new LTexture;
    LTexture* replayButtonTex_ = new LTexture;
	replayButtonTex->loadFromFile(play_again_button, renderer);
	replayButtonTex_->loadFromFile(play_again_button_, renderer);
	replayButton->setTexture(replayButtonTex, replayButtonTex_);

}

void loadGameMusicAndSound(){
    me_playing = Mix_LoadMUS( me_playingP.c_str() );
	me_theme = Mix_LoadMUS( me_themeP.c_str() );
	se_mouseClick = Mix_LoadWAV(se_mouseClickP.c_str());
	se_move = Mix_LoadWAV(se_moveP.c_str());
	se_hold = Mix_LoadWAV(se_holdP.c_str());
	se_drop = Mix_LoadWAV(se_dropP.c_str());
	se_start = Mix_LoadWAV(se_startP.c_str());
	se_double = Mix_LoadWAV(se_doubleP.c_str());
	se_pause = Mix_LoadWAV(se_pauseP.c_str());
	se_rotate = Mix_LoadWAV(se_rotateP.c_str());
	se_count = Mix_LoadWAV(se_countP.c_str());
	me_gameover = Mix_LoadMUS(me_gameoverP.c_str());
	se_gameover = Mix_LoadWAV(se_gameoverP.c_str());
	for (int i=0; i<4; i++)
	{
		se_lineCompleted[i] = Mix_LoadWAV(se_lineCompletedP[i].c_str());
	}
}

void loadGameSettings()
{
    settingsElement.insert(std::make_pair("Ghost Piece", 1));
	settingsElement.insert(std::make_pair("Level", easy));
	settingsElement.insert(std::make_pair("Sound Effects", 1));
	settingsElement.insert(std::make_pair("Music Volume", 80));

	SDL_RWops* settingsFile = SDL_RWFromFile("settings/settings.bin", "r+b");
	if (settingsFile==NULL){
		settingsFile = SDL_RWFromFile("settings/settings.bin", "w+b");
		if (settingsFile!=NULL){
			for (auto it = settingsElement.begin(); it!=settingsElement.end(); it++){
				SDL_RWwrite(settingsFile, &(it->second), sizeof(int), 1);			
			}
			SDL_RWclose( settingsFile );
		}else{
			printf( "Error: Unable to create file! SDL Error: %s\n", SDL_GetError() );
		}

	}else{
		for (auto it = settingsElement.begin(); it!=settingsElement.end(); it++){
			SDL_RWread(settingsFile, &(it->second), sizeof(int), 1);
		}
		SDL_RWclose(settingsFile);
	}

	highestScore.insert(highestScore.end(), scoreMaxMem, 0);
	SDL_RWops* highestScoreFile = SDL_RWFromFile("settings/scoreFile.bin", "r+b");
	if (highestScoreFile==NULL){
		highestScoreFile = SDL_RWFromFile("settings/scoreFile.bin", "w+b");
		if (highestScoreFile!=NULL){
			for (int i=0; i<scoreMaxMem; i++){
				SDL_RWwrite(highestScoreFile, &(highestScore[i]), sizeof(int), 1);			
			}
			SDL_RWclose( highestScoreFile );
		}else{
			printf( "Error: Unable to create file! SDL Error: %s\n", SDL_GetError() );
		}
	}else{
		for (int i=0; i<scoreMaxMem; i++){
			SDL_RWread(highestScoreFile, &(highestScore[i]), sizeof(int), 1);
		}
		SDL_RWclose(highestScoreFile);
	}
}

GameOverAnnouncement::GameOverAnnouncement()
{
	direct = InGame_SoloMode;
}
Tabs GameOverAnnouncement::getDirect()
{
	return direct;
}
void GameOverAnnouncement::resetDirect()
{
	direct = InGame_SoloMode;
}

bool GameOverAnnouncement::handleEvents(SDL_Event* e)
{
	bool flag = 0;
	backButton->handleEvents(e, 1);
	if (backButton->getPressed())
	{
		backButton->setPressed(0);
		direct=Menu;
		flag = 1;
		return false;
	}
	replayButton->handleEvents(e, 1);
	if (replayButton->getPressed())
	{
		replayButton->setPressed(0);
		direct=InGame_SoloMode;
		flag = 1;
		return true;
	}

	direct = InGame_SoloMode; 
	return false;
}
void GameOverAnnouncement::render(SDL_Renderer* renderer)
{
	static LTexture gameOverBg(gameOverBgPath, renderer);
	gameOverBg.render(renderer, 0, 0);
	backButton->render(renderer, backButton->getXCen()-backButton->getWidth()/2, backButton->getYCen()-backButton->getHeight()/2);
	replayButton->render(renderer, replayButton->getXCen()-replayButton->getWidth()/2, replayButton->getYCen()-replayButton->getHeight()/2);
	printScoreTable(renderer, 620, 505);
}