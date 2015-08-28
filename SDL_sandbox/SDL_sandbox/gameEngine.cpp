#include "gameEngine.h"
#include "gameStateBase.h"
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
    m_pEvent(NULL)
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
    // Create event handler
    m_pEvent = new SDL_Event();
    if(m_pEvent == NULL)
    {
        printf("SDL_Event could not initialize! SDL_Event Error: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}
//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
void tGameEngine::ChangeState(tGameState* pState)
{
	// cleanup the current state
	if ( m_GameStates.empty() == false) 
    {
		m_GameStates.back()->Cleanup();
		m_GameStates.pop_back();
	}

	// store and init the new state
	m_GameStates.push_back(pState);
	m_GameStates.back()->Init(this);
}
//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
void tGameEngine::PushState(tGameState* pState)
{
	// pause current state
	if ( m_GameStates.empty() == false) 
    {
		m_GameStates.back()->Pause();
	}

	// store and init the new state
	m_GameStates.push_back(pState);
	m_GameStates.back()->Init(this);
}
//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
void tGameEngine::PopState()
{
	// cleanup the current state
	if ( m_GameStates.empty() == false) 
    {
		m_GameStates.back()->Cleanup();
		m_GameStates.pop_back();
	}

	// resume previous state
	if ( m_GameStates.empty() == false) 
    {
		m_GameStates.back()->Resume();
	}
}
//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
void tGameEngine::Update(const double interpolation)
{
    if(m_Running)
    {
        m_GameStates.back()->Update(this, interpolation);
    }
}
//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
void tGameEngine::Draw()
{
    if(m_Running)
    {
        m_GameStates.back()->Draw(this);
    }
}
//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
bool tGameEngine::HandleEvents()
{
    // Handle events on queue
    while (SDL_PollEvent(m_pEvent) != 0)
    {
        // User requests quit
        if (m_pEvent->type == SDL_QUIT)
        {
            Quit();
            return false;
        }
        m_GameStates.back()->HandleEvents(this);
    }
    return true;
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

    if(m_pEvent)
    {
        delete m_pEvent;
        m_pEvent = NULL;
    }

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
void tGameEngine::Quit()
{
    m_Running = false;
    Cleanup();
}
