#ifndef Tetromino_h
#define Tetromino_h

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Specifications.h"
class block{
    public:
        render(int xPos, int yPos);
    private:
        SDL_Color color;

};

class Tetromino{
    private:
        SDL_Color color;
        int size;
        bool matrix[4][4];
    public:
        Tetromino(){};
        // Tetromino(SDL_Color _color, int _size, bool _matrix[4][4])
        // {
        //     color = _color;
        //     size = _size;
        //     matrix[4][4] = _matrix[4][4];
        // };
};

// enum Tetrominos{
//     I_BLOCK,
//     L_BLOCK,
//     J_BLOCK,
//     O_BLOCK,
//     S_BLOCK,
//     T_BLOCK,
//     Z_BLOCK,
//     total_of_Tetrominos
// };
// Tetromino Tetrads[7];

const Tetromino I_BLOCK = {I_cBLOCK, 4, {{0,0,1,0} // L BLOCK
,{1,1,1,0}
,{0,0,0,0}
,{0,0,0,0}}};


#endif