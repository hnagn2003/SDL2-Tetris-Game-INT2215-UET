#include "Data.h"
void playSoundEffects(Mix_Chunk* chunk, int loop, int channel)
{
    if (settingsElement["Sound Effects"])
    {
        Mix_PlayChannel( channel, chunk, loop );
    }
}