#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>

// stl
#include <stdlib.h>

//Screen dimension constants
const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 256;

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

// Forward declares
//struct SDL_Window;
//struct SDL_Renderer;

//Globals
//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

//Globally used font
extern TTF_Font* gFont;

#endif  // GLOBALS_H