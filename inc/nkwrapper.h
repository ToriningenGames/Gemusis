 
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

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_STANDARD_BOOL
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#include "nuklear.h"

#include "nuklear_sdl_renderer.h"
