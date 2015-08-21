#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "stdafx.h"

#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>

// Forward declarations
class tTexture;
class tPlayer;
class tEnemy;

class tGameEngine
{
public:
    // constructor is private - use Instance()
    static void CreateInstance();
    static tGameEngine* Instance();

    bool Init(const std::string& title);

    void ChangeState(/*CGameState* state*/);
    void PushState(/*CGameState* state*/);
    void PopState();

    void HandleEvents();
    void Update();
    void Draw(const float interpolation);

    bool Running() { return m_Running; }
    void Quit();

protected:
    tGameEngine(); // constructor is protected - use Instance()
    ~tGameEngine();

private:
    void Cleanup();
    bool LoadFont();
    bool LoadMedia();
    void CreateGameObjects();

    static tGameEngine* m_pInstance;

    // the stack of states
    //vector<CGameState*> states;

    bool m_Running;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    SDL_Event* m_pEvent;
    TTF_Font* m_pFont;

    // Game objects
    tPlayer* m_pPlayer;
    std::vector<tEnemy*> m_Enemies;
    int m_EnemyXPos;
    int m_CurrentEnemySpeed;
    int m_BackgroundXPos;
    int m_BackgroundYPos;
    // Score
    int m_TotalScore;
    std::string m_ScoreString;
    SDL_Color m_ScoreColor;

    // Textures
    tTexture* m_pBackgroundTexture;
    // Player texture
    tTexture* m_pPlayerTexture;
    tTexture* m_pSpriteSheetBullets;
    // Enemy textures
    tTexture* m_pEnemyTexture;
    tTexture* m_pEnemyExplosionTexture;
    // Text texture :)
    tTexture* m_pTextTexture;
};

#endif  // GLOBALS_H