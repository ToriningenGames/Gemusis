#include <SDL2/SDL.h>

#define NK_IMPLEMENTATION
#include "Nuklear/nuklear.h"


int main(int argc, char **argv)
{
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Delay(3000);
        SDL_Quit();
        return 0;
}
