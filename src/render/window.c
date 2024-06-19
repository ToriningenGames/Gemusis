#include "inc/window.h"
#include "inc/nkwrapper.h"

//Lets other windows get fonts right
struct nk_font *fontinit(struct nk_sdl *this)
{
        struct nk_font_atlas *atlas;
        nk_sdl_font_stash_begin(this, &atlas);
        struct nk_font *font = nk_font_atlas_add_from_file(atlas, "ProggyClean.ttf", 13, 0);
        nk_sdl_font_stash_end(this);
        return font;
}

void windowinit(struct window *this)
{
        if (this->window) {
                //Bring the window back to fore
                SDL_RaiseWindow(this->window);
                SDL_SetWindowPosition(this->window, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
                return;
        }
        this->object = malloc(sizeof(*this->object));
        //NK init
        this->window = SDL_CreateWindow("Default", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
        this->renderer = SDL_CreateRenderer(this->window, -1, 0);
        this->windowid = SDL_GetWindowID(this->window);
        this->context = nk_sdl_init(this->object, this->window, this->renderer);
        //Font init
        struct nk_font *font = fontinit(this->object);
        nk_style_set_font(this->context, &font->handle);
}

bool windowisme(struct window *this, Uint32 id)
{
        if (!this->window)
                return false;
        return id == this->windowid;
}

void windowclose(struct window *this)
{
        if (!this->window)
                return;         //Nothing to clean
        nk_sdl_shutdown(this->object);
        nk_free(this->context);
        free(this->object);
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        this->window = NULL;
}

void windoweventready(struct window *this)
{
        if (!this->window)
                return;         //Nothing to run
        nk_input_begin(this->context);
}

void windoweventend(struct window *this)
{
        if (!this->window)
                return;         //Nothing to run
        nk_input_end(this->context);
}

void windowevent(struct window *this, SDL_Event *event)
{
        if (!this->window)
                return;         //Nothing to run
        nk_sdl_handle_event(this->object, event);
        if (event->type = SDL_WINDOWEVENT && ((struct SDL_WindowEvent*)event)->event == SDL_WINDOWEVENT_CLOSE)
                windowclose(this);
}

struct windowResult windowdraw(struct window *this, struct iohub *data)
{
        struct windowResult results = {0};
        if (!this->window)
                return results;         //Nothing to draw
        //NK windows
        if (nk_begin(this->context, "Default", nk_rect(0,0,800,600), 0)) {
                nk_layout_row_dynamic(this->context, 30, 1);
                nk_label(this->context, "Default", NK_TEXT_LEFT);
                nk_end(this->context);
        }
        
        //NK render
        SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        nk_sdl_render(this->object, NK_ANTI_ALIASING_OFF);
        SDL_RenderPresent(this->renderer);
        return results;
}
