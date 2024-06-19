#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "inc/gemusiscore.h"


int main(int argc, char **argv)
{
        SDL_Init(SDL_INIT_EVERYTHING);
        struct iohub *data = malloc(sizeof(*data));
        data->isRunning = true;
        data->screenData = malloc(MAXSCREENSIZE);
        for (int i = 0; i < MAXSCREENSIZE / sizeof(*data->screenData); i++) {
                data->screenData[i].r = (i%320) / 40 % 2 ? 0 : 255;
                data->screenData[i].g = (i%320) / 80 % 2 ? 0 : 255;
                data->screenData[i].b = (i%320) / 160 % 2 ? 0 : 255;
        }
        data->screenLock = SDL_CreateMutex();
        //Begin rendering
        render(data);
        //Asked to quit; kill the children
        SDL_DestroyMutex(data->screenLock);
        free(data);
        return 0;
}
