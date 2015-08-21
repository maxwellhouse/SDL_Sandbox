// SDL_sandbox.cpp : Defines the entry point for the console application.
//
#include "gameEngine.h"

#include "stdafx.h"

// windows
#ifdef WIN32
#include<Windows.h>
#endif

unsigned getTickCount()
{
#ifdef WIN32
    return GetTickCount();
#else
    struct timeval tv;
    gettimeofday(&tv, 0);
    return unsigned((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
#endif
}

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
        const int TICKS_PER_SECOND = 50;
        const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
        const int MAX_FRAMESKIP = 10;
        unsigned next_game_tick = GetTickCount();
        int loops;
        float interpolation;

        // While application is running
        while (pGameEngine->Running() == true)
        {
            loops = 0;
            while( GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP) 
            {
                pGameEngine->HandleEvents();
                pGameEngine->Update();
                next_game_tick += SKIP_TICKS;
                loops++;
            }
            interpolation = float( GetTickCount() + SKIP_TICKS - next_game_tick ) / float( SKIP_TICKS );

            pGameEngine->Draw(interpolation);
        }
    }

    return 0;
}
