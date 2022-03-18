#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include "Game.h"
using namespace std;

int main( int argc, char* args[] ){

    Game game;
    game.init("Tetris - by me", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 500, true );

}