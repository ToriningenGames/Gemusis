#ifndef GEMUSIS_CORE_H
#define GEMUSIS_CORE_H

#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL_mutex.h>

struct sixButtonJoy {
        int a:1;
        int b:1;
        int c:1;
        int x:1;
        int y:1;
        int z:1;
        int start:1;
        int mode:1;
        int up:1;
        int down:1;
        int left:1;
        int right:1;
};

struct color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t _;
};
#define RMASK 0x000000FF
#define GMASK 0x0000FF00
#define BMASK 0x00FF0000

#define MAXSCREENSIZE (sizeof(struct color) * 320 * 480)

struct iohub {
        bool systemRunning;
        bool alive;
        struct color *screenData;       //The VDP thread is responsible for padding/scaling to the correct size
        SDL_mutex *screenLock;
};
void render(struct iohub *data);

#endif
