#define NK_IMPLEMENTATION
#define NK_SDL_RENDERER_IMPLEMENTATION

#include "inc/nkwrapper.h"
#include "inc/gemusiscore.h"

#include "inc/options.h"

void tvinit();
void tvclose();
void tvloop();

//Lets other windows get fonts right
struct nk_font *fontinit(struct nk_sdl *this)
{
        struct nk_font_atlas *atlas;
        nk_sdl_font_stash_begin(this, &atlas);
        struct nk_font *font = nk_font_atlas_add_from_file(atlas, "ProggyClean.ttf", 13, 0);
        nk_sdl_font_stash_end(this);
        return font;
}

//Dispatch an SDL message to the correct window
bool sendmessage(SDL_Event *event, Uint32 winid)
{
        if (optionsisme(winid)) {
                optionsevent(event);
        } else {
                return false;
        }
        return true;
}

//This _must_ be run on the main thread!
void render(struct iohub *data)
{
        //System init
        
        //SDL init
        //TV init
        SDL_Window *tvwin = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 480, 0);
        SDL_Surface *tvsrc = SDL_CreateRGBSurface(0, 320, 480, 32, RMASK, GMASK, BMASK, 0);
        //NK init
        SDL_Window *window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
        struct nk_sdl *object = malloc(sizeof(*object));
        SDL_Event event;
        
        //NK init
        struct nk_context *nkoptions = nk_sdl_init(object, window, renderer);
        //Font init
        struct nk_font *font = fontinit(object);
        nk_style_set_font(nkoptions, &font->handle);
        optionsinit(fontinit);
        
        //Event loop
        while (data->isRunning) {
                //Load the TV screen
                SDL_LockSurface(tvsrc);
                SDL_LockMutex(data->screenLock);
                memcpy(tvsrc->pixels, data->screenData, MAXSCREENSIZE);
                SDL_UnlockMutex(data->screenLock);
                SDL_UnlockSurface(tvsrc);
                
                //Event polling
                nk_input_begin(nkoptions);
                optionseventready();
                //Make sure we send events to the right window
                while (SDL_PollEvent(&event)) {
                        switch (event.type) {
                        case SDL_QUIT :
                                data->isRunning = false;
                                break;
                        case SDL_MOUSEBUTTONDOWN :
                        case SDL_MOUSEBUTTONUP :
                        case SDL_MOUSEMOTION :
                                if (!sendmessage(&event, ((Uint32*)&event)[2])) {
                                        nk_sdl_handle_event(object, &event);
                                }
                                break;
                        default :
                                break;
                        }
                }
                optionseventend();
                nk_input_end(nkoptions);
                
                //NK windows
                if (nk_begin(nkoptions, "NKWin", nk_rect(50,50,230,250), NK_WINDOW_TITLE | NK_WINDOW_MOVABLE)) {
                        nk_layout_row_dynamic(nkoptions, 30, 1);
                        nk_label(nkoptions, "Label", NK_TEXT_LEFT);
                        if (nk_button_label(nkoptions, "Quit")) {
                                data->isRunning = false;
                        }
                }
                nk_end(nkoptions);
                
                //NK render
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                nk_sdl_render(object, NK_ANTI_ALIASING_OFF);
                SDL_RenderPresent(renderer);
                
                optionsdraw();
                
                //TV render
                SDL_Surface *tvdest = SDL_GetWindowSurface(tvwin);
                SDL_BlitSurface(tvsrc, 0, tvdest, 0);
                SDL_UpdateWindowSurface(tvwin);
        }
        optionsclose();
        nk_sdl_shutdown(object);
        nk_free(nkoptions);
        SDL_DestroyWindow(window);
        SDL_DestroyWindow(tvwin);
        SDL_FreeSurface(tvsrc);
        SDL_Quit();
        return;
}
