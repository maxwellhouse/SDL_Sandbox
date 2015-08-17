// SDL_sandbox.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "texture.h"
#include "globals.cpp"
#include "player.h"
#include "enemy.h"
#include <map>
#include <sstream>

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Loads fonts
bool loadFont();

// The images that correspond to a key press
std::map<KeyPressSurfaces, SDL_Rect*> gKeyPressImageRecs;

// Scene textures
tTexture gBackgroundTexture;

// Player texture
tTexture gPlayerTexture;

// Enemy texture
tTexture gEnemyTexture;
tTexture gEnemyExplosionTexture;

// Scene sprites
SDL_Rect gSpriteClips[5];
tTexture gSpriteSheetBullets;

// Animation sprite
const int ANIMATION_FRAMES = 16;
SDL_Rect gAnimationSpriteClips[ANIMATION_FRAMES];
tTexture gSpriteSheetAnimationTexture;

// Rendered texture
tTexture gTextTexture;

// Frees media and shuts down SDL
void close();

bool init()
{
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        // Create window
        gWindow = SDL_CreateWindow(
            "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }

                // Initialize SDL_ttf
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia()
{
    // Create the map for the bullet colors;
    CreateBulletColorMap();

    // Loading success flag
    bool success = true;

    // Load sprite sheet texture
    if (gBackgroundTexture.loadFromFile("../../images/background/space.png") == false)
    {
        printf("Failed to load background texture!\n");
        success = false;
    }

    // Load sprite sheet texture
    if (gSpriteSheetAnimationTexture.loadFromFile("../../images/animation/spritesheet.png") == false)
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }

    // Load bullet sprite sheet texture
    if (gSpriteSheetBullets.loadFromFile("../../images/ammo/lazerBullets.png") == false)
    {
        printf("Failed to load sprite sheet bullets!\n");
        success = false;
    }

    // Load enemy sprite
    if( gEnemyTexture.loadFromFile("../../images/ships/enemy_1.png") == false )
    {
        printf( "Failed to load enemy ship texture!\n");
        success = false;
    }

    //Load player sprite texture
    if( gPlayerTexture.loadFromFile("../../images/ships/player_ship.png") == false )
    {
        printf( "Failed to load player ship texture!\n");
        success = false;
    }

    //Load enemy explosion texture
    if( gEnemyExplosionTexture.loadFromFile("../../images/explosion/explosion_transparent.png") == false )
    {
        printf( "Failed to load enemy explosion texture!\n");
        success = false;
    }

    return success;
}

bool loadFont()
{
    // Loading success flag
    bool success = true;

    // Open the font
    gFont = TTF_OpenFont("../../fonts/BodoniFLF-Roman.ttf", 28);
    if (gFont == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }

    return success;
}

void close()
{
    gBackgroundTexture.free();
    gTextTexture.free();

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    TTF_CloseFont(gFont);
    gFont = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

int main(int argc, char* argv[])
{
    // Start up SDL and create window
    if (init() == false)
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Load media
        if (loadMedia() == false || loadFont() == false)
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // Main loop flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // Clip rect for sprite sheet
            SDL_Rect* pSpriteRect = gKeyPressImageRecs[KEY_PRESS_SURFACE_DEFAULT];

            // Create player
            tPlayer Player(100, 0, SCREEN_WIDTH, &gPlayerTexture);

            // Movement
            int mov_x = 0;

            // The offsets of the background
            int bgX = 0, bgY = 0;

            // The offsets to move the enemies
            int enmyX = 1;
            int enemySpeed = 1;

            // Score
            int totalScore = 0;
            std::string score = "Score: ";
            SDL_Color scoreColor = {255, 0, 255};

            // Create list of enemies
            std::vector<tEnemy*> enemyList;
            for (int i = 0; i < 1; i++)
            {
                enemyList.push_back(new tEnemy(1, SCREEN_HEIGHT / 2, 0, &gEnemyTexture, &gEnemyExplosionTexture));
            }

            // Enemy direction
            bool left = true;

            // Flip type
            SDL_RendererFlip flipType = SDL_FLIP_NONE;

            // While application is running
            while (!quit)
            {
                // Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0x0);
                SDL_RenderClear(gRenderer);

                // Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    // User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    // User presses a key
                    else if (e.type == SDL_KEYDOWN)
                    {
                        // Select surfaces based on key press
                        switch (e.key.keysym.sym)
                        {

                        case SDLK_UP:
                            Player.AddBullet(&gSpriteSheetBullets, tBullet::eBT_Super);
                            break;

                        case SDLK_DOWN:
                            break;

                        case SDLK_LEFT:
                        {
                            Player.offsetMove(-8, 0);
                        }
                        break;

                        case SDLK_RIGHT:
                        {
                            Player.offsetMove(8, 0);
                        }
                        break;

                        case SDLK_SPACE:
                            Player.AddBullet(&gSpriteSheetBullets, tBullet::eBT_Normal);
                            break;
                        default:
                            break;
                        }
                    }
                }

                // Scroll background
                ++bgY;

                // If the background has gone too far
                if (bgY > gBackgroundTexture.getHeight())
                {
                    // Reset the offset
                    bgY = 0;
                }

                // Render background texture to screen
                gBackgroundTexture.render(bgX, bgY);
                gBackgroundTexture.render(bgX, bgY - gBackgroundTexture.getHeight());

                // Render player ship
                Player.render();

                // Render enemies
                for (std::vector<tEnemy*>::iterator enemy = enemyList.begin(); enemy != enemyList.end(); ++enemy)
                {
                    if (rand() % 10 == 5)
                    {
                        (*enemy)->AddBullet(&gSpriteSheetBullets);
                    }
                    (*enemy)->offsetMove(enemySpeed, 0);
                    (*enemy)->render();

                    if(Player.Hit(*enemy) == true)
                    {
                        totalScore++;
                    }

                    if((*enemy)->Hit(&Player) == true)
                    {
                        while(0);
                    }
                }

                if (enmyX == 0 || enmyX == SCREEN_WIDTH)
                {
                    enemySpeed = -enemySpeed;
                }
                enmyX += enemySpeed;

                ////Render current frame
                // SDL_Rect* currentClip = &gAnimationSpriteClips[ frame / 4 ];
                // gSpriteSheetAnimationTexture.setColor( r, g, b );
                // gSpriteSheetAnimationTexture.setAlpha( a );
                // gSpriteSheetAnimationTexture.render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2,
                // currentClip, degrees, NULL, flipType );

                ////Go to next frame
                //++frame;

                ////Cycle animation
                // if( frame / 4 >= ANIMATION_FRAMES )
                //{
                //    frame = 0;
                //}

                // Render current text
                gTextTexture.loadFromRenderedText(score + std::to_string((long double)totalScore), scoreColor);
                gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, gTextTexture.getHeight() );

                // Update screen
                SDL_RenderPresent(gRenderer);

            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}
