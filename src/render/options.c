#include "inc/options.h"

void optionsinit(struct window *this)
{
        if (this->window) {
                //Bring the window back to fore
                SDL_RaiseWindow(this->window);
                SDL_SetWindowPosition(this->window, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
                return;
        }
        this->object = malloc(sizeof(*this->object));
        //NK init
        this->window = SDL_CreateWindow("Options", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
        this->renderer = SDL_CreateRenderer(this->window, -1, 0);
        this->windowid = SDL_GetWindowID(this->window);
        this->context = nk_sdl_init(this->object, this->window, this->renderer);
        //Font init
        struct nk_font *font = fontinit(this->object);
        nk_style_set_font(this->context, &font->handle);
}

struct windowResult optionsdraw(struct window *this, struct iohub *data)
{
        struct windowResult results = {0};
        if (!this->window)
                return results;         //Nothing to draw
        //NK windows
        if (nk_begin(this->context, "OptionWin", nk_rect(0,0,800,600), 0)) {
                nk_layout_row_dynamic(this->context, 30, 1);
                nk_label(this->context, "Summon Windows", NK_TEXT_LEFT);
                if (nk_button_label(this->context, "TV")) {
                        results.showTv = 1;
                }
                if (nk_button_label(this->context, "VDP")) {
                        results.showVDP = 1;
                }
        }
        nk_end(this->context);

        //NK render
        SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        nk_sdl_render(this->object, NK_ANTI_ALIASING_OFF);
        SDL_RenderPresent(this->renderer);
        return results;
}

struct window *optionsGet()
{
        static struct window Options = {
                .window = NULL,
                .init = optionsinit,
                .close = windowclose,
                .isme = windowisme,
                .eventready = windoweventready,
                .event = windowevent,
                .eventend = windoweventend,
                .draw = optionsdraw
        };
        return &Options;
}
