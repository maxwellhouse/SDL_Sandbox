#ifndef TEXTURE_H
#define TEXTURE_H

//#include "globals.h"
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

//Forward declarations
struct SDL_Texture;
struct SDL_Rect;

//Texture wrapper class
class tTexture
{
    public:
        //Initializes variables
        tTexture();

        tTexture(const tTexture& other);

        //Deallocates memory
        ~tTexture();

        //Loads image at specified path
        bool loadFromFile( std::string path );

        //Creates image from font string
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

        //Deallocates texture
        void free();

        //Renders texture at given point
        bool render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );

        //Gets image dimensions
        int getWidth() const;
        int getHeight() const;

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
};

#endif  // TEXTURE_H