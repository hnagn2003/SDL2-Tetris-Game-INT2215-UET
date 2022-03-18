#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include "Game.h"
#include "Tetromino.h"
#include "Grid.h"
using namespace std;
// 10 x 20

const int ROWS = 20;
const int COLS = 10;
const int SCREEN_WIDTH = 10*40;
const int SCREEN_HEIGHT = 20*40;

bool fullScreen = false;

int main( int argc, char* args[] ){

    Game *game = new Game;
    game->init("Tetris - by me", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, fullScreen );
    while (game->running())
    {
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();
}

