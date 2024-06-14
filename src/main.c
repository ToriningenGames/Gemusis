#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>

//Nuklear defines
#define NK_MEMSET memset
#define NK_MEMCPY memcpy
#define NK_SIN sin
#define NK_COS cos
//#define NK_STRTOD strtod
//#define NK_DTOA dtoa          //There is no dtoa in the standard library that takes a char* and a double safely, returning a char*...
                                //Nuklear always gives this function a statically-allocated array
#define NK_VSNPRINTF vsnprintf

#define NK_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_STANDARD_BOOL
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#include "nuklear.h"
#define NK_SDL_RENDERER_SDL_H "dummy.h"          //Don't try to reinclude SDL
#define NK_SDL_RENDERER_IMPLEMENTATION
#include "nuklear_sdl_renderer.h"


int main(int argc, char **argv)
{
        //SDL init
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Window *window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 866, 600, 0);
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Event event;
        bool running = true;
        //NK init
        struct nk_context *nkctx = nk_sdl_init(window, renderer);
        //Font init
        struct nk_font_atlas *atlas;
        nk_sdl_font_stash_begin(&atlas);
        struct nk_font *font = nk_font_atlas_add_from_file(atlas, "ProggyClean.ttf", 13, 0);
        nk_sdl_font_stash_end();
        nk_style_set_font(nkctx, &font->handle);
        //Event loop
        while (running) {
                //Event polling
                nk_input_begin(nkctx);
                while (SDL_PollEvent(&event)) {
                        switch (event.type) {
                                case SDL_QUIT :
                                        running = false;
                                        break;
                                default :
                                        nk_sdl_handle_event(&event);
                                        break;
                        }
                }
                nk_input_end(nkctx);
                //NK init
                if (nk_begin(nkctx, "NKWin", nk_rect(50,50,230,250), NK_WINDOW_TITLE | NK_WINDOW_MOVABLE)) {
                        nk_layout_row_dynamic(nkctx, 30, 1);
                        nk_label(nkctx, "Label", NK_TEXT_LEFT);
                        nk_button_label(nkctx, "Button");
                }
                nk_end(nkctx);
                //NK render
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                //SDL_RenderClear(renderer);
                nk_sdl_render(NK_ANTI_ALIASING_OFF);
                SDL_RenderPresent(renderer);
        }
        nk_sdl_shutdown();
        nk_free(nkctx);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
}
