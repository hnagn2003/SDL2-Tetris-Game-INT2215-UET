#ifndef Tetromino_h
#define Tetromino_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>

class block{
    public:
        render(int xPos, int yPos);
    private:
        SDL_Color color;

};

class Tetromino{
    public:

    private:
        SDL_Color color;
        int size;
        bool matrix[4][4];
        double x, y;
        
};

#endif