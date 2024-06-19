#include "inc/nkwrapper.h"
#include "inc/gemusiscore.h"

#include "inc/options.h"
#include "inc/tv.h"

#define forAllWindows(X, Y) for (int winfor = 0; Y = X[winfor]; winfor++)

//This _must_ be run on the main thread!
void render(struct iohub *data)
{
        //System init
        struct window *windows[WINDOW_END+1];
        struct window *win;
        struct windowResult results;
        windows[WINDOW_TV] = tvGet();
        windows[WINDOW_OPTIONS] = optionsGet();
        windows[WINDOW_END] = NULL;
        SDL_Event event;
        
        forAllWindows(windows, win) {
                win->init(win);
        }
        
        //Event loop
        while (data->isRunning) {
                //Event polling
                forAllWindows(windows, win) {
                        win->eventready(win);
                }
                //Make sure we send events to the right window
                while (SDL_PollEvent(&event)) {
                        switch (event.type) {
                        case SDL_QUIT :
                                data->isRunning = false;
                                break;
                        case SDL_WINDOWEVENT :
                        case SDL_MOUSEBUTTONDOWN :
                        case SDL_MOUSEBUTTONUP :
                        case SDL_MOUSEMOTION :
                                forAllWindows(windows, win) {
                                        if (win->isme(win, ((Uint32*)&event)[2]))
                                                win->event(win, &event);
                                }
                                break;
                        default :
                                break;
                        }
                }
                forAllWindows(windows, win) {
                        win->eventend(win);
                }
                
                results.asInt = 0;
                forAllWindows(windows, win) {
                        results.asInt |= win->draw(win, data).asInt;
                }
                
                //Results processing
                if (results.showTv) {
                        windows[WINDOW_TV]->init(windows[WINDOW_TV]);
                }
                if (results.showVDP) {
                        //
                }
                if (results.showOptions) {
                        windows[WINDOW_OPTIONS]->init(windows[WINDOW_OPTIONS]);
                }
        }
        forAllWindows(windows, win) {
                win->close(win);
        }
        SDL_Quit();
        return;
}
