#include "gameEngine.h"
#include "globals.h"
#include "texture.h"
#include "player.h"
#include "enemy.h"

tGameEngine* tGameEngine::m_pInstance;

//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
void tGameEngine::CreateInstance()
{
    assert(m_pInstance == NULL);
    m_pInstance = new tGameEngine();
}
//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
tGameEngine::tGameEngine() :
    m_Running(true),
    m_pWindow(NULL),
    m_pRenderer(NULL),
    m_pEvent(NULL),
    m_pFont(NULL),
    m_pPlayer(NULL),
    m_EnemyXPos(1),
    m_CurrentEnemySpeed(1),
    m_BackgroundXPos(0),
    m_BackgroundYPos(0),
    m_TotalScore(0),
    m_ScoreString("Score"),
    m_pBackgroundTexture(NULL),
    m_pPlayerTexture(NULL),
    m_pSpriteSheetBullets(NULL),
    m_pEnemyTexture(NULL),
    m_pEnemyExplosionTexture(NULL),
    m_pTextTexture(NULL)
{

}
//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
tGameEngine* tGameEngine::Instance()
{
    assert(m_pInstance != NULL);
    return m_pInstance;
}
//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
tGameEngine::~tGameEngine()
{
    m_pInstance->Cleanup();
    m_pInstance = NULL;
}
//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
bool tGameEngine::Init(const std::string& title)
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
        m_pWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (m_pWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer for window
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (m_pRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(m_pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

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

    success = LoadFont();
    success = LoadMedia();

    // Only create the game objects if the init is successful.
    if(success)
    {
        CreateGameObjects();
    }

    return success;
}
//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
void tGameEngine::CreateGameObjects()
{
    // Create player
    m_pPlayer = new tPlayer(100, 0, SCREEN_WIDTH, m_pPlayerTexture);
    // Create event handler
    m_pEvent = new SDL_Event();

    // Create list of enemies
    for (int i = 0; i < 1; i++)
    {
        m_Enemies.push_back(new tEnemy(1, SCREEN_HEIGHT / 2, 0, m_pEnemyTexture, m_pEnemyExplosionTexture));
    }

    // Score stuff
    m_ScoreColor.r = 255;
    m_ScoreColor.g = 0;
    m_ScoreColor.b = 255;
}
//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
void tGameEngine::Update()
{
    if(m_Running)
    {
        // Scroll background
        ++m_BackgroundYPos;

        // If the background has gone too far
        if (m_BackgroundYPos > m_pBackgroundTexture->getHeight())
        {
            // Reset the offset
            m_BackgroundYPos = 0;
        }

        // Render enemies
        for (unsigned int enemyIndex = 0; enemyIndex < m_Enemies.size(); enemyIndex++)
        {
            if (rand() % 10 == 5)
            {
                m_Enemies[enemyIndex]->AddBullet(m_pSpriteSheetBullets);
            }
            m_Enemies[enemyIndex]->offsetMove(m_CurrentEnemySpeed, 0);

            if(m_Enemies[enemyIndex]->Hit(m_pPlayer) == true)
            {
            }
            if(m_pPlayer->Hit(m_Enemies[enemyIndex]) == true)
            {
                m_TotalScore++;
                m_Enemies[enemyIndex]->wasHit(1);
                if(m_Enemies[enemyIndex]->isDead() == true)
                {
                    //std::pair<int,int> pos = m_Enemies[enemyIndex]->GetPos();
                    //gEnemyExplosionTexture.render(pos.first, pos.second, &enemyList[enemyIndex]->GetDeathClip(frame / 4));
                }
            }
        }

        if (m_EnemyXPos == 0 || m_EnemyXPos == SCREEN_WIDTH)
        {
            m_CurrentEnemySpeed = -m_CurrentEnemySpeed;
        }
        m_EnemyXPos += m_CurrentEnemySpeed;
    }
}
//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
void tGameEngine::Draw(const float /*interpolation*/)
{
    if(m_Running)
    {
        // Clear screen
        SDL_SetRenderDrawColor(m_pRenderer, 0x0, 0x0, 0x0, 0x0);
        SDL_RenderClear(m_pRenderer);

        // Render background texture to screen
        m_pBackgroundTexture->render(m_pRenderer, m_BackgroundXPos, m_BackgroundYPos);
        m_pBackgroundTexture->render(m_pRenderer, m_BackgroundXPos, m_BackgroundYPos - m_pBackgroundTexture->getHeight());

        // Render player ship
        m_pPlayer->render(m_pRenderer);

        for (unsigned int enemyIndex = 0; enemyIndex < m_Enemies.size(); enemyIndex++)
        {
            m_Enemies[enemyIndex]->render(m_pRenderer);
        }

        // Render current score
        m_pTextTexture->loadFromRenderedText(m_ScoreString + std::to_string((long double)m_TotalScore), m_ScoreColor, m_pRenderer, m_pFont);
        m_pTextTexture->render( m_pRenderer, ( SCREEN_WIDTH - m_pTextTexture->getWidth() ) / 2, m_pTextTexture->getHeight() );

        // Update screen
        SDL_RenderPresent(m_pRenderer);
    }
}
//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
void tGameEngine::HandleEvents()
{
    // Handle events on queue
    while (SDL_PollEvent(m_pEvent) != 0)
    {
        // User requests quit
        if (m_pEvent->type == SDL_QUIT)
        {
            Quit();
        }
        // User presses a key
        else if (m_pEvent->type == SDL_KEYDOWN)
        {
            // Select surfaces based on key press
            switch (m_pEvent->key.keysym.sym)
            {
            case SDLK_UP:
                m_pPlayer->AddBullet(m_pSpriteSheetBullets, tBullet::eBT_Super);
                break;

            case SDLK_DOWN:
                break;

            case SDLK_LEFT:
                {
                    m_pPlayer->offsetMove(-PLAYER_SPEED, 0);
                }
                break;

            case SDLK_RIGHT:
                {
                    m_pPlayer->offsetMove(PLAYER_SPEED, 0);
                }
                break;

            case SDLK_SPACE:
                m_pPlayer->AddBullet(m_pSpriteSheetBullets, tBullet::eBT_Normal);
                break;
            default:
                break;
            }
        }
    }
}

//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
void tGameEngine::Cleanup()
{
    // Destroy window
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    m_pWindow = NULL;
    m_pRenderer = NULL;
    TTF_CloseFont(m_pFont);
    m_pFont = NULL;

    if(m_pBackgroundTexture)
    {
        m_pBackgroundTexture->free();
        delete m_pBackgroundTexture;
        m_pBackgroundTexture = NULL;
    }
    if(m_pPlayerTexture)
    {
        m_pPlayerTexture->free();
        delete m_pPlayerTexture;
        m_pPlayerTexture = NULL;
    }
    if(m_pSpriteSheetBullets)
    {
        m_pSpriteSheetBullets->free();
        delete m_pSpriteSheetBullets;
        m_pSpriteSheetBullets = NULL;
    }
    if(m_pEnemyTexture)
    {
        m_pEnemyTexture->free();
        delete m_pEnemyTexture;
        m_pEnemyTexture = NULL;
    }
    if(m_pEnemyExplosionTexture)
    {
        m_pEnemyExplosionTexture->free();
        delete m_pEnemyExplosionTexture;
        m_pEnemyExplosionTexture = NULL;
    }
    if(m_pTextTexture)
    {
        m_pTextTexture->free();
        delete m_pTextTexture;
        m_pTextTexture = NULL;
    }
    if(m_pPlayer)
    {
        delete m_pPlayer;
        m_pPlayer = NULL;
    }
    if(m_pEvent)
    {
        delete m_pEvent;
        m_pEvent = NULL;
    }

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
bool tGameEngine::LoadFont()
{
    // Loading success flag
    bool success = true;

    // Open the font
    m_pFont = TTF_OpenFont("../../fonts/BodoniFLF-Roman.ttf", 28);
    if (m_pFont == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }

    m_pTextTexture = new tTexture();
    if(m_pTextTexture == NULL)
    {
        success = false;
    }

    return success;
}

//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
bool tGameEngine::LoadMedia()
{
    // Loading success flag
    bool success = true;

    m_pBackgroundTexture = new tTexture();
    if (m_pBackgroundTexture && m_pBackgroundTexture->loadFromFile("../../images/background/space.png", m_pRenderer) == false)
    {
        printf("Failed to load background texture!\n");
        success = false;
    }

    m_pSpriteSheetBullets = new tTexture();
    if (m_pSpriteSheetBullets && m_pSpriteSheetBullets->loadFromFile("../../images/ammo/lazerBullets.png", m_pRenderer) == false)
    {
        printf("Failed to load sprite sheet bullets!\n");
        success = false;
    }

    m_pEnemyTexture = new tTexture();
    if(m_pEnemyTexture && m_pEnemyTexture->loadFromFile("../../images/ships/enemy_1.png", m_pRenderer) == false)
    {
        printf( "Failed to load enemy ship texture!\n");
        success = false;
    }

    m_pPlayerTexture = new tTexture();
    if(m_pPlayerTexture && m_pPlayerTexture->loadFromFile("../../images/ships/player_ship.png", m_pRenderer) == false)
    {
        printf( "Failed to load player ship texture!\n");
        success = false;
    }

    m_pEnemyExplosionTexture = new tTexture();
    if(m_pEnemyExplosionTexture && m_pEnemyExplosionTexture->loadFromFile("../../images/explosion/explosion_transparent.png", m_pRenderer) == false)
    {
        printf( "Failed to load enemy explosion texture!\n");
        success = false;
    }

    return success;
}

//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
void tGameEngine::Quit()
{
    m_Running = false;
    Cleanup();
}
