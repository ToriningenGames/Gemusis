
#include "inc/nkwrapper.h"

static SDL_Window *window = NULL;
Uint32 windowid;
static SDL_Renderer *renderer;
static struct nk_context *context;
static struct nk_sdl *object;

void optionsinit(void *(*fontinitcallback)(struct nk_sdl *))
{
        if (window)
                return;         //Already exists
        object = malloc(sizeof(*object));
        //NK init
        window = SDL_CreateWindow("Options", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        windowid = SDL_GetWindowID(window);
        context = nk_sdl_init(object, window, renderer);
        //Font init
        struct nk_font *font = fontinitcallback(object);
        nk_style_set_font(context, &font->handle);
}

bool optionsisme(Uint32 id)
{
        if (!window)
                return false;
        return id == windowid;
}

void optionsclose()
{
        if (!window)
                return;         //Nothing to clean
        nk_sdl_shutdown(object);
        nk_free(context);
        free(object);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        window = NULL;
}

void optionseventready()
{
        if (!window)
                return;         //Nothing to run
        nk_input_begin(context);
}

void optionseventend()
{
        if (!window)
                return;         //Nothing to run
        nk_input_end(context);
}

void optionsevent(SDL_Event *event)
{
        if (!window)
                return;         //Nothing to run
        nk_sdl_handle_event(object, event);
}

void optionsdraw()
{
        if (!window)
                return;         //Nothing to draw
        //NK windows
        if (nk_begin(context, "OptionWin", nk_rect(50,50,230,250), NK_WINDOW_TITLE | NK_WINDOW_MOVABLE)) {
                nk_layout_row_dynamic(context, 30, 1);
                nk_label(context, "Label", NK_TEXT_LEFT);
                nk_button_label(context, "Button");
        }
        nk_end(context);

        //NK render
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        nk_sdl_render(object, NK_ANTI_ALIASING_OFF);
        SDL_RenderPresent(renderer);
}
