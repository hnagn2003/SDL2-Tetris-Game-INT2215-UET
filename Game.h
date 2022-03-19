#ifndef Game_h
#define Game_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Tetromino.h"
#include "Grid.h"
#include "Specifications.h"
class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int xPos, int yPos, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running()
    {
        return isRunning;
    };
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Grid grid;
    Tetromino current;
};

#endif