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
        data->screenLock = SDL_CreateMutex();
        //Begin rendering
        render(data);
        //Asked to quit; kill the children
        SDL_DestroyMutex(data->screenLock);
        free(data);
        return 0;
}
