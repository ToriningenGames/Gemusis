#include "inc/nkwrapper.h"
#include "inc/gemusiscore.h"

#include "inc/options.h"
#include "inc/tv.h"
#include "inc/motodebug.h"

#define forAllWindows(X, Y) for (int winfor = 0; (Y = X[winfor]); winfor++)

//This _must_ be run on the main thread!
void render(struct iohub *data)
{
        //System init
        struct window *windows[WINDOW_END+1];
        struct window *win;
        struct windowResult results;
        windows[WINDOW_TV] = tvGet();
        windows[WINDOW_OPTIONS] = optionsGet();
        windows[WINDOW_MOTODEBUG] = motodebugGet();
        windows[WINDOW_END] = NULL;
        SDL_Event event;
        
        forAllWindows(windows, win) {
                win->init(win, data);
        }
        
        //Event loop
        while (data->alive) {
                //Event polling
                results.asInt = 0;
                forAllWindows(windows, win) {
                        win->eventready(win);
                }
                //Make sure we send events to the right window
                while (SDL_PollEvent(&event)) {
                        switch (event.type) {
                        case SDL_QUIT :
                                data->alive = false;
                                break;
                        case SDL_KEYUP :
                        case SDL_TEXTINPUT :
                        case SDL_TEXTEDITING :
                        case SDL_TEXTEDITING_EXT :
                        case SDL_KEYDOWN :
                        case SDL_WINDOWEVENT :
                        case SDL_MOUSEBUTTONDOWN :
                        case SDL_MOUSEBUTTONUP :
                        case SDL_MOUSEMOTION :
                        case SDL_MOUSEWHEEL :
                                forAllWindows(windows, win) {
                                        if (win->isme(win, ((Uint32*)&event)[2]))
                                                results.asInt |= win->event(win, &event, data).asInt;
                                }
                                break;
                        default :
                                break;
                        }
                }
                forAllWindows(windows, win) {
                        win->eventend(win);
                }
                
                forAllWindows(windows, win) {
                        results.asInt |= win->draw(win, data).asInt;
                }
                
                //Results processing
                if (results.showTv) {
                        windows[WINDOW_TV]->init(windows[WINDOW_TV], data);
                }
                if (results.showOptions) {
                        windows[WINDOW_OPTIONS]->init(windows[WINDOW_OPTIONS], data);
                }
        }
        forAllWindows(windows, win) {
                win->close(win, data);
        }
        SDL_Quit();
        return;
}
