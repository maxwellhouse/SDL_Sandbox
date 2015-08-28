#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "stdafx.h"
#include <SDL.h>

// Forward declarations
class tGameState;

class tGameEngine
{
public:
    // constructor is private - use Instance()
    static void CreateInstance();
    static tGameEngine* Instance();

    bool Init(const std::string& title);

    void ChangeState(tGameState* state);
    void PushState(tGameState* state);
    void PopState();

    bool HandleEvents();
    void Update(const double interpolation);
    void Draw();

    bool Running() { return m_Running; }
    void Quit();

    SDL_Renderer* Renderer() { return m_pRenderer; }
    SDL_Event* Events() { return m_pEvent; }

protected:
    tGameEngine(); // constructor is protected - use Instance()
    ~tGameEngine();

private:
    void Cleanup();
    void CreateGameObjects();

    static tGameEngine* m_pInstance;

    // the stack of states
    std::vector<tGameState*> m_GameStates;

    bool m_Running;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    SDL_Event* m_pEvent;
};

#endif  // GLOBALS_H