#include "playState.h"
#include "gameEngine.h"
#include "texture.h"
#include "globals.h"
#include "player.h"
#include "enemy.h"

tPlayState* tPlayState::m_pInstance;

void tPlayState::CreateInstance()
{
    assert(m_pInstance == NULL);
    m_pInstance = new tPlayState();
}

tPlayState::tPlayState() :
    m_pPlayer(NULL),
    m_BackgroundXPos(0),
    m_BackgroundYPos(0),
    m_TotalScore(0),
    m_ScoreString("Score"),
    m_pBackgroundTexture(NULL),
    m_pPlayerTexture(NULL),
    m_pSpriteSheetWeapons(NULL),
    m_pEnemyTexture(NULL),
    m_pEnemyExplosionTexture(NULL),
    m_pTextTexture(NULL),
    m_pFont(NULL)
{
}

tPlayState* tPlayState::Instance() 
{
    assert(m_pInstance != NULL);
	return m_pInstance;
}

bool tPlayState::Init(tGameEngine* pGame)
{
    bool success = false;
    // Only create the game objects if the init is successful.
    if(LoadMedia(pGame) && LoadFont(pGame))
    {
        CreateGameObjects();
        success = true;
    }

    return success;
}

void tPlayState::Cleanup()
{
    m_pInstance = NULL;

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
    if(m_pSpriteSheetWeapons)
    {
        m_pSpriteSheetWeapons->free();
        delete m_pSpriteSheetWeapons;
        m_pSpriteSheetWeapons = NULL;
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

    TTF_CloseFont(m_pFont);
    m_pFont = NULL;
    TTF_Quit();
}

void tPlayState::HandleEvents(tGameEngine* pGame)
{
    // User presses a key
    if (pGame->Events()->type == SDL_KEYDOWN)
    {
        // Select surfaces based on key press
        switch (pGame->Events()->key.keysym.sym)
        {
        case SDLK_UP:
            m_pPlayer->AddBullet(m_pSpriteSheetWeapons, tWeapon::eBT_Super);
            break;

        case SDLK_DOWN:
            m_Enemies.push_back(new tEnemy(1, SCREEN_HEIGHT / 2, 0, m_pEnemyTexture, m_pEnemyExplosionTexture));
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
            m_pPlayer->AddBullet(m_pSpriteSheetWeapons, tWeapon::eBT_Normal);
            break;
        default:
            break;
        }
    }
}

void tPlayState::Update(tGameEngine* pGame, const double interpolation) 
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
    for (std::vector<tEnemy*>::iterator enemyIt = m_Enemies.begin(); enemyIt != m_Enemies.end();)
    {
        if (rand() % 10 == 5)
        {
            (*enemyIt)->AddBullet(m_pSpriteSheetWeapons);
        }
        (*enemyIt)->move(interpolation);

        if((*enemyIt)->Hit(m_pPlayer) == true)
        {
        }
        if(m_pPlayer->Hit(*enemyIt) == true)
        {
            m_TotalScore++;
            (*enemyIt)->wasHit(1);
        }
        if((*enemyIt)->isDead() == true)
        {
            enemyIt = m_Enemies.erase(enemyIt);
        }
        else
        {
            ++enemyIt;
        }
    }
}

void tPlayState::Draw(tGameEngine* pGame)
{
    if(pGame->Renderer())
    {
        // Clear screen
        SDL_SetRenderDrawColor(pGame->Renderer(), 0x0, 0x0, 0x0, 0x0);
        SDL_RenderClear(pGame->Renderer());

        // Render background texture to screen
        m_pBackgroundTexture->render(pGame->Renderer(), m_BackgroundXPos, m_BackgroundYPos);
        m_pBackgroundTexture->render(pGame->Renderer(), m_BackgroundXPos, m_BackgroundYPos - m_pBackgroundTexture->getHeight());

        // Render player ship
        m_pPlayer->render(pGame->Renderer());

        for (unsigned int enemyIndex = 0; enemyIndex < m_Enemies.size(); enemyIndex++)
        {
            m_Enemies[enemyIndex]->render(pGame->Renderer());
        }

        // Render current score
        m_pTextTexture->loadFromRenderedText(m_ScoreString + std::to_string((long double)m_TotalScore), m_ScoreColor, pGame->Renderer(), m_pFont);
        m_pTextTexture->render( pGame->Renderer(), ( SCREEN_WIDTH - m_pTextTexture->getWidth() ) / 2, m_pTextTexture->getHeight() );

        // Update screen
        SDL_RenderPresent(pGame->Renderer());
    }
}

bool tPlayState::LoadMedia(tGameEngine* pGame)
{
    // Loading success flag
    bool success = true;

    m_pBackgroundTexture = new tTexture();
    if (m_pBackgroundTexture && m_pBackgroundTexture->loadFromFile("../../images/background/space.png", pGame->Renderer()) == false)
    {
        printf("Failed to load background texture!\n");
        success = false;
    }

    m_pSpriteSheetWeapons = new tTexture();
    if (m_pSpriteSheetWeapons && m_pSpriteSheetWeapons->loadFromFile("../../images/ammo/lazerBullets.png", pGame->Renderer()) == false)
    {
        printf("Failed to load sprite sheet bullets!\n");
        success = false;
    }

    m_pEnemyTexture = new tTexture();
    if(m_pEnemyTexture && m_pEnemyTexture->loadFromFile("../../images/ships/enemy_1.png", pGame->Renderer()) == false)
    {
        printf( "Failed to load enemy ship texture!\n");
        success = false;
    }

    m_pPlayerTexture = new tTexture();
    if(m_pPlayerTexture && m_pPlayerTexture->loadFromFile("../../images/ships/player_ship.png", pGame->Renderer()) == false)
    {
        printf( "Failed to load player ship texture!\n");
        success = false;
    }

    m_pEnemyExplosionTexture = new tTexture();
    if(m_pEnemyExplosionTexture && m_pEnemyExplosionTexture->loadFromFile("../../images/explosion/explosion_transparent.png", pGame->Renderer()) == false)
    {
        printf( "Failed to load enemy explosion texture!\n");
        success = false;
    }

    return success;
}

bool tPlayState::LoadFont(tGameEngine* pGame)
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

    try
    {
        m_pTextTexture = new tTexture();
    }
    catch(const std::bad_alloc &)
    {
        printf("Failed to allocate memory for text texture.");
        success = false;
    }

    return success;
}

void tPlayState::CreateGameObjects()
{
    // Create player
    m_pPlayer = new tPlayer(100, 0, SCREEN_WIDTH, m_pPlayerTexture);

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