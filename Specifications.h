#ifndef Specifications_h
#define Specifications_h
#include "Tetromino.h"


#include "Structure.h"
#include <algorithm> // void updateScoreTable
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Data.h"
#include "Tabs_Menu.h"
#include "Tabs_Helps.h"
bool updateScoreTable(int score);
void printScoreTable(SDL_Renderer *renderer, int x, int y);
void renderText(std::string text, SDL_Renderer* renderer, TTF_Font* gFont, int xCenter, int yCenter, SDL_Color textColor = WHITE_COLOR);


void clearSettings();
void clearRankingScore();

// chuyển tọa độ trong grid về tọa độ thực (tọa độ render ra màn hình)
int gridSizeToRendererSize(int w);
int gridXPosToRendererPos(int x);
int gridYPosToRendererPos(int y);

void loadGameFonts();
void loadGameButtons(SDL_Renderer* renderer);
void loadGameMusicAndSound();
class GameOverAnnouncement
{
    public:
        Tabs direct;
    public:
        GameOverAnnouncement();
        Tabs getDirect();
        void resetDirect();
        bool handleEvents(SDL_Event* e);
        void render(SDL_Renderer* renderer);
};

void loadGameSettings();
#endif