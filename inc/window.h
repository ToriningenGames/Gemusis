#ifndef WINDOW_H
#define WINDOW_H

#include "inc/nkwrapper.h"
#include "inc/gemusiscore.h"


struct windowResult {
        union {
        struct {
                uint32_t showOptions:1;
                uint32_t showTv:1;
                uint32_t showVDP:1;
                uint32_t showSound:1;
                uint32_t showMotoDebugger:1;
                uint32_t showZilogDebugger:1;
                uint32_t showIO:1;
                uint32_t showInfo:1;
                uint32_t showMotoMemView:1;
                uint32_t showZilogMemView:1;
        };
        uint32_t asInt;
        };
};

struct window {
        SDL_Window *window;
        Uint32 windowid;
        SDL_Renderer *renderer;
        SDL_Surface *surface;
        struct nk_context *context;
        struct nk_sdl *object; 
        void (*init)(struct window *this, struct iohub *data);
        void (*close)(struct window *this, struct iohub *data);
        bool (*isme)(struct window *this, Uint32 id);
        void (*eventready)(struct window *this);
        struct windowResult (*event)(struct window *this, SDL_Event *event, struct iohub *data);
        void (*eventend)(struct window *this);
        struct windowResult (*draw)(struct window *this, struct iohub *data);
};

struct nk_font *fontinit(struct nk_sdl *this);
void windowinit(struct window *this, struct iohub *data);
void windowclose(struct window *this, struct iohub *data);
bool windowisme(struct window *this, Uint32 id);
void windoweventready(struct window *this);
struct windowResult windowevent(struct window *this, SDL_Event *event, struct iohub *data);
void windoweventend(struct window *this);
struct windowResult windowdraw(struct window *this, struct iohub *data);

enum windowTypes {
        WINDOW_TV,
        WINDOW_OPTIONS,
        WINDOW_MOTODEBUG,
        WINDOW_END,
};

#endif
