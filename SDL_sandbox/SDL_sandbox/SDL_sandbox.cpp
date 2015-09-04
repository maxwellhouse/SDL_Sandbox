// SDL_sandbox.cpp : Defines the entry point for the console application.
//
#include "gameEngine.h"
#include "introState.h"
#include "stdafx.h"
#include "playState.h"

// windows
#ifdef WIN32
#include<Windows.h>
#endif

int main(int argc, char* argv[])
{
    // Create engine singleton.
    tGameEngine::CreateInstance();
    static tGameEngine* pGameEngine = tGameEngine::Instance();
    
    if (pGameEngine == NULL || pGameEngine->Init("Alien blah.") == false)
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Create intro state
        tIntroState::CreateInstance();
        static tIntroState* pIntroState = tIntroState::Instance();
        pIntroState->Init(pGameEngine);
        pGameEngine->ChangeState(pIntroState);
        //Create play state
        tPlayState::CreateInstance();

        const int MAX_FRAMESKIP = 10;
        unsigned int previousTime = SDL_GetTicks();
        double lag = 0;

        // While application is running
        while (pGameEngine->Running() == true)
        {
            unsigned int currentTime = SDL_GetTicks();
            unsigned int elapsed = currentTime - previousTime;
            previousTime = currentTime;
            lag += elapsed;
            if(pGameEngine->HandleEvents())
            {
                while( lag >= MAX_FRAMESKIP ) 
                {
                    pGameEngine->Update(elapsed / 1000.0);
                    lag -= MAX_FRAMESKIP;
                } 
                lag = 0;
                if(pGameEngine->Running() == true)
                {
                    pGameEngine->Draw();
                }
            }
        }
    }

    return 0;
}
