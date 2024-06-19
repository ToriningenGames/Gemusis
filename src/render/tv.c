#include "inc/tv.h"
#include "inc/nkwrapper.h"

void tvinit(struct window *this, struct iohub *data)
{
        if (this->window) {
                //Bring the window back to fore
                SDL_RaiseWindow(this->window);
                SDL_SetWindowPosition(this->window, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
                return;
        }
        //SDL init
        this->window = SDL_CreateWindow("Game window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, SDL_WINDOW_RESIZABLE);
        this->surface = SDL_CreateRGBSurface(0, 320, 480, 32, RMASK, GMASK, BMASK, 0);
        this->windowid = SDL_GetWindowID(this->window);
        data->systemRunning = true;
}

void tvclose(struct window *this, struct iohub *data)
{
        if (!this->window)
                return;         //Nothing to clean
        SDL_DestroyWindow(this->window);
        SDL_FreeSurface(this->surface);
        this->window = NULL;
        data->systemRunning = false;
}

bool tvisme(struct window *this, Uint32 id)
{
        if (!this->window)
                return false;
        return id == this->windowid;
}

void tveventready(struct window *this)
{
        (void)this;
}

struct windowResult tvevent(struct window *this, SDL_Event *event, struct iohub *data)
{
        struct windowResult result = {0};
        if (!this->window)
                return result;
        if (event->type == SDL_WINDOWEVENT && ((struct SDL_WindowEvent*)event)->event == SDL_WINDOWEVENT_CLOSE)
                this->close(this, data);
        if (event->type == SDL_KEYDOWN && ((struct SDL_KeyboardEvent*)event)->keysym.scancode == SDL_SCANCODE_F1)
                result.showOptions = true;
        return result;
}

void tveventend(struct window *this)
{
        (void)this;
}

struct windowResult tvdraw(struct window *this, struct iohub *data)
{
        struct windowResult results = {0};
        if (!this->window)
                return results;         //Nothing to draw
        //Load the TV screen
        SDL_LockSurface(this->surface);
        SDL_LockMutex(data->screenLock);
        memcpy(this->surface->pixels, data->screenData, MAXSCREENSIZE);
        SDL_UnlockMutex(data->screenLock);
        SDL_UnlockSurface(this->surface);
        //TV render
        SDL_Surface *tvdest = SDL_GetWindowSurface(this->window);
        SDL_BlitScaled(this->surface, 0, tvdest, 0);
        SDL_UpdateWindowSurface(this->window);
        return results;
}

struct window *tvGet()
{
        static struct window TV = {
                .window = NULL,
                .init = tvinit,
                .close = tvclose,
                .isme = tvisme,
                .eventready = tveventready,
                .event = tvevent,
                .eventend = tveventend,
                .draw = tvdraw
        };
        return &TV;
}
