#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "Game.h"
#include "Tetromino.h"
#include "Grid.h"
#include "Specifications.h"
#include <cstdlib>
#include <SDL_ttf.h>

int gridSizeToRendererSize(int w)
    {
    return w*TILE_SIZE;
    }
int gridXPosToRendererPos(int x) //...
    {
        return (SCREEN_WIDTH - COLS*TILE_SIZE) / 2 + x*TILE_SIZE;
    }
int gridYPosToRendererPos(int y)
    {return (SCREEN_HEIGHT - ROWS*TILE_SIZE) / 2 + y*TILE_SIZE;
    }
void updateScoreTable(int score){
    highestScore.push_back(score);
    sort(highestScore.begin(), highestScore.end(), std::greater<int>());
    highestScore.pop_back();
}

void printScoreTable(SDL_Renderer *renderer, int x, int y){
    // LTexture ranking[scoreMaxMem];
    // for (int i=0; i<scoreMaxMem; i++){
    //     if (i==0){
    //         ranking[i].loadFromRenderedText(std::to_string(highestScore[i]), GOLD_YELLOW_COLOR, fontStar_50, renderer);
    //     }else{
    //         ranking[i].loadFromRenderedText(std::to_string(highestScore[i]), WHITE_COLOR, fontStar_40, renderer);
    //     }
    //     ranking[i].render(renderer, x, y+i*50);
    // }
}
