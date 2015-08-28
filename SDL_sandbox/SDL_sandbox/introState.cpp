#include "introState.h"
#include "gameEngine.h"
#include "texture.h"
#include "playState.h"

tIntroState* tIntroState::m_pInstance;

void tIntroState::CreateInstance()
{
    assert(m_pInstance == NULL);
    m_pInstance = new tIntroState();
}

tIntroState::tIntroState() : 
m_pBackground(NULL),
m_pFader(NULL),
m_Alpha(255)
{
}

tIntroState* tIntroState::Instance() 
{
    assert(m_pInstance != NULL);
	return m_pInstance;
}

bool tIntroState::Init(tGameEngine* pGame)
{
    bool success = false;
    if(pGame->Renderer())
    {
	    m_pBackground = new tTexture();
        if(m_pBackground && m_pBackground->loadFromFile("../../images/menus/intro.bmp", pGame->Renderer()) == false)
        {
            printf("Intro state failed to load background texture!\n");
            success = false;
        }
        else
        {
            // start off opaque
	        m_Alpha = 255;

	        m_pBackground->setBlendMode(SDL_BLENDMODE_BLEND);
            m_pBackground->setAlpha(m_Alpha);
            success = true;
        }        
    }
    return success;
}

void tIntroState::Cleanup()
{
    m_pBackground->free();
    delete m_pBackground;
    m_pBackground = NULL;

    m_pInstance = NULL;
}

void tIntroState::HandleEvents(tGameEngine* pGame)
{
    // User presses a key
    if (pGame->Events()->type == SDL_KEYDOWN)
    {
        // Select surfaces based on key press
        switch (pGame->Events()->key.keysym.sym)
        {
        case SDLK_SPACE:
            pGame->ChangeState(tPlayState::Instance());
            break;
        default:
            break;
        }
    }
}

void tIntroState::Update(tGameEngine* /*pGame*/, const double /*interpolation*/) 
{
	m_Alpha--;

	if (m_Alpha < 0)
    {
		m_Alpha = 0;
    }

    //if(m_pBackground)
    //{
	   // m_pBackground->setAlpha(m_Alpha);
    //}
}

void tIntroState::Draw(tGameEngine* pGame)
{
    if(pGame->Renderer())
    {
        SDL_SetRenderDrawColor(pGame->Renderer(), 0x0, 0x0, 0x0, 0x0);
        SDL_RenderClear(pGame->Renderer());

        if(m_pBackground)
        {
            m_pBackground->render(pGame->Renderer(), 0, 0);
        }

        // Update screen
        SDL_RenderPresent(pGame->Renderer());
    }
}