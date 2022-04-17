#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include "Game.h"
#include "Tetromino.h"
#include "Grid.h"
#include "Specifications.h"
#include <time.h>
#include <math.h>

bool fullScreen = false;

int main( int argc, char* args[] ){
    srand(time(0));
    Game *game = new Game;
    game->init("Tetris - by me", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, fullScreen );
    while (game->running())
    {
        // Uint64 start = SDL_GetPerformanceCounter();
        game->handleEvents();
        game->update();
        game->render();
        // Uint64 end = SDL_GetPerformanceCounter();
        // float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        // SDL_Delay(floor(16.666f - elapsedMS)); // 60 fps
    }
    game->clean();
}

