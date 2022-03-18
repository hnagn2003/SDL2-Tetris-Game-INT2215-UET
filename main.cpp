#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include "Game.h"
using namespace std;
const int SCREEN_WIDTH = 1900;
const int SCREEN_HEIGHT = 1080;
bool fullScreen = true;

int main( int argc, char* args[] ){

    Game game;
    game.init("Tetris - by me", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, fullScreen );

}