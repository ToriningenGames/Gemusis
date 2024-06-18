#ifndef OPTIONS_H
#define OPTIONS_H

#include <SDL2/SDL.h>

void optionsinit(void *(*fontinitcallback)(void *atlas));
void optionsclose();
bool optionsisme(Uint32 id);
void optionseventready();
void optionsevent(SDL_Event *event);
void optionseventend();
void optionsdraw();

#endif 
