#ifndef GEMUSIS_CORE_H
#define GEMUSIS_CORE_H

#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL_mutex.h>

//System defines
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

struct motoRegFile {
        uint32_t D0;
        uint32_t D1;
        uint32_t D2;
        uint32_t D3;
        uint32_t D4;
        uint32_t D5;
        uint32_t D6;
        uint32_t D7;
        uint32_t A0;
        uint32_t A1;
        uint32_t A2;
        uint32_t A3;
        uint32_t A4;
        uint32_t A5;
        uint32_t A6;
        uint32_t A7;
        uint32_t PC;
        union {
                //Notice: This is little-endian dependent
                uint16_t SSR;
                uint8_t CCR;
                //TODO: What is the behavior of the undefined bits?
                struct {
                        bool carry:1;
                        bool overflow:1;
                        bool zero:1;
                        bool negative:1;
                        bool extend:1;
                        bool b5:1;
                        bool b6:1;
                        bool b7:1;
                        uint8_t interrupt:3;
                        bool b11:1;
                        bool b12:1;
                        bool supervisor:1;      //TODO: Is this always 1, or does it merely do nothing?
                        bool b14:1;
                        bool trace:1;
                };
        } SSR;
};

//Screen defines
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
        bool vsync;                     //Whether screen drawing should respect VSync
        struct motoRegFile motoRegs;
};
void render(struct iohub *data);

//Program control defines
extern struct shortcut {
        SDL_Keymod modifiers;
        SDL_Scancode key;       //No support for multi-key shortcuts
} programShortcuts[];
enum shortcutCode {
        SC_OpenOptions,
        SC_OpenTv,
        SC_OpenVDP,
        SC_OpenSound,
        SC_OpenMotoDebug,
        SC_OpenZilogDebug,
        SC_OpenIO,
        SC_OpenInfo,
        SC_OpenMotoMemView,
        SC_OpenZilogMemView,
        SC_End
};

#endif
