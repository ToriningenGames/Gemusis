#ifndef WINDOW_H
#define WINDOW_H

#include "inc/nkwrapper.h"
#include "inc/gemusiscore.h"


struct windowResult {
        union {
                struct {
                int showTv:1;
                int showOptions:1;
                int showVDP:1;
                };
        int asInt:3;
        };
};

struct window {
        SDL_Window *window;
        Uint32 windowid;
        SDL_Renderer *renderer;
        SDL_Surface *surface;
        struct nk_context *context;
        struct nk_sdl *object; 
        void (*init)(struct window *this);
        void (*close)(struct window *this);
        bool (*isme)(struct window *this, Uint32 id);
        void (*eventready)(struct window *this);
        void (*event)(struct window *this, SDL_Event *event);
        void (*eventend)(struct window *this);
        struct windowResult (*draw)(struct window *this, struct iohub *data);
};

struct nk_font *fontinit(struct nk_sdl *this);
void windowinit(struct window *this);
void windowclose(struct window *this);
bool windowisme(struct window *this, Uint32 id);
void windoweventready(struct window *this);
void windowevent(struct window *this, SDL_Event *event);
void windoweventend(struct window *this);
struct windowResult windowdraw(struct window *this, struct iohub *data);

#define WINDOW_END 2
#define WINDOW_TV 0
#define WINDOW_OPTIONS 1

#endif
