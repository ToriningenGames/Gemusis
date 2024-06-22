#include "inc/motodebug.h"

void motodebuginit(struct window *this, struct iohub *data)
{
        (void)data;
        if (this->window) {
                //Bring the window back to fore
                SDL_RaiseWindow(this->window);
                SDL_SetWindowPosition(this->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                return;
        }
        this->object = malloc(sizeof(*this->object));
        //NK init
        this->window = SDL_CreateWindow("68000 Debugger", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE);
        this->renderer = SDL_CreateRenderer(this->window, -1, 0);
        this->windowid = SDL_GetWindowID(this->window);
        this->context = nk_sdl_init(this->object, this->window, this->renderer);
        //Font init
        struct nk_font *font = fontinit(this->object);
        nk_style_set_font(this->context, &font->handle);
}

//How we're gonna do resizing:
//The size of all windows varies depending on the frame, of couse.
//Only the _main_ nk window is actually resizable
//Every frame, the others' sizes are dynamically recalculated to fill the space.
//So, the user can "move the median", but they're just resizing one window
struct windowResult motodebugdraw(struct window *this, struct iohub *data)
{
        (void)data;
        if (!this->window)
                return results;         //Nothing to draw
        int width, height;
        SDL_GetWindowSize(this->window, &width, &height);
}

struct window *motodebugget()
{
        static struct window Options = {
                .window = NULL,
                .init = motodebuginit,
                .close = windowclose,
                .isme = windowisme,
                .eventready = windoweventready,
                .event = windowevent,
                .eventend = windoweventend,
                .draw = motodebugdraw
        };
        return &Options;
}
