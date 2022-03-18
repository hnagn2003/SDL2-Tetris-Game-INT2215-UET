#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include "Game.h"
using namespace std;

int main( int argc, char* args[] ){

    cout << "hello";
    Game *game = new Game;
    game->render();
}