#include "stdafx.h"
#include "texture.h"
#include "globals.h"

tTexture::tTexture()
{
    // Initialize
    m_pTexture = NULL;
    m_Width = 0;
    m_Height = 0;
}

tTexture::tTexture(const tTexture& other)
{
    m_Width = other.getWidth();
    m_Height = other.getHeight();
    memcpy(m_pTexture, other.m_pTexture, sizeof(other.m_pTexture));
}


tTexture::~tTexture()
{
    // Deallocate
    free();
}

void tTexture::free()
{
    // Free texture if it exists
    if (m_pTexture != NULL)
    {
        SDL_DestroyTexture(m_pTexture);
        m_pTexture = NULL;
        m_Width = 0;
        m_Height = 0;
    }
}

bool tTexture::loadFromFile(std::string path, SDL_Renderer* pRenderer)
{
    // Get rid of preexisting texture
    free();

    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Color key image
        if (SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF)) != 0)
        {
            printf("Unable to set color key! SDL Error: %s\n", SDL_GetError());
        }

        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(pRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            // Get image dimensions
            m_Width = loadedSurface->w;
            m_Height = loadedSurface->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    // Return success
    m_pTexture = newTexture;
    return m_pTexture != NULL;
}


bool tTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* pRenderer, TTF_Font* pFont)
{
    // Get rid of preexisting texture
    free();

    // Render text surface
    SDL_Color bkColor = {0, 0, 0};
    SDL_Surface* textSurface = TTF_RenderText_Solid(pFont, textureText.c_str(), textColor);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        // Create texture from surface pixels
        m_pTexture = SDL_CreateTextureFromSurface(pRenderer, textSurface);
        if (m_pTexture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            // Get image dimensions
            m_Width = textSurface->w;
            m_Height = textSurface->h;
        }

        // Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    // Return success
    return m_pTexture != NULL;
}

bool tTexture::render(SDL_Renderer* pRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    // Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, m_Width, m_Height};

    // Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render to screen
    if (SDL_RenderCopyEx(pRenderer, m_pTexture, clip, &renderQuad, angle, center, flip) != 0)
    {
        printf("Unable to render texture! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void tTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    // Modulate texture
    SDL_SetTextureColorMod(m_pTexture, red, green, blue);
}

void tTexture::setBlendMode(SDL_BlendMode blending)
{
    // Set blending function
    SDL_SetTextureBlendMode(m_pTexture, blending);
}

void tTexture::setAlpha(Uint8 alpha)
{
    // Modulate texture alpha
    SDL_SetTextureAlphaMod(m_pTexture, alpha);
}

int tTexture::getWidth() const
{
    return m_Width;
}

int tTexture::getHeight() const
{
    return m_Height;
}