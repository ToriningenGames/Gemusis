#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "inc/gemusiscore.h"

struct shortcut programShortcuts[SC_End];

int main(int argc, char **argv)
{
        (void)argc; (void)argv;
        SDL_Init(SDL_INIT_EVERYTHING);
        struct iohub *data = calloc(1, sizeof(*data));
        data->alive = true;
        data->systemRunning = false;
        data->screenLock = SDL_CreateMutex();
        //Test data
        data->screenData = malloc(MAXSCREENSIZE);
        for (unsigned long i = 0; i < MAXSCREENSIZE / sizeof(*data->screenData); i++) {
                data->screenData[i].r = (i%320) / 40 % 2 ? 0 : 255;
                data->screenData[i].g = (i%320) / 80 % 2 ? 0 : 255;
                data->screenData[i].b = (i%320) / 160 % 2 ? 0 : 255;
        }
        data->motoRegs.D1 = 0xAA55;
        //Threads go here
        //Begin rendering
        render(data);
        //Asked to quit; kill the children
        SDL_DestroyMutex(data->screenLock);
        free(data->screenData);
        free(data);
        return 0;
}
