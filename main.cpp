#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include "Game.h"
using namespace std;
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1030;
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