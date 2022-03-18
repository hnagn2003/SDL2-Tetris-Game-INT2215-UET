#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include "Game.h"
using namespace std;
// 10 x 20
const int TILE_SIZE = 40;
const int SCREEN_WIDTH = 10*TILE_SIZE;
const int SCREEN_HEIGHT = 20*TILE_SIZE;
bool fullScreen = false;

int main( int argc, char* args[] ){

    Game *game = new Game;
    game->init("Tetris - by me", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, fullScreen );
    while (game->running())
    {
        game->handelEvents();
        game->update();
        game->render();
    }
    game->clean();
}

