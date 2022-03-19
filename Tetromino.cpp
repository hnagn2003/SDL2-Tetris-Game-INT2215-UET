#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "Game.h"
#include "Tetromino.h"


int gridSizeToRendererSize(int w){return w*TILE_SIZE;}
int gridXPosToRendererPos(int x){return (SCREEN_WIDTH - COLS*TILE_SIZE) / 2 + x*TILE_SIZE;}
int gridYPosToRendererPos(int y){return (SCREEN_HEIGHT - ROWS*TILE_SIZE) / 2 + y*TILE_SIZE;}