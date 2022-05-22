#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include "Game.h"
#include "Tetromino.h"
#include "Grid.h"
#include "Specifications.h"
#include <time.h>
#include <math.h>
// press ESC to escape from the game
bool fullScreen = false;
int main( int argc, char* args[] )
{
    srand(time(0));
    Game *game = new Game;
    game->init("Tetris - by me", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, fullScreen );
    game->loadmedia();
    while (game->running())
    {
        game->handleEvents();
        game->playMusic();
        game->update(); 
        game->render();
    }
    game->clean();
}

