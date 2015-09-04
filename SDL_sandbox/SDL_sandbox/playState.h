#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "stdafx.h"
#include "gameStateBase.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

// Forward declarations
class tGameEngine;
struct SDL_Renderer;
class tTexture;
class tPlayer;
class tEnemy;
class tGameState;

class tPlayState : public tGameState
{
public:
    // constructor is private - use Instance()
    static void CreateInstance();
	static tPlayState* Instance();

	bool Init(tGameEngine* pGame);
	void Cleanup();

    void Pause() {};
    void Resume() {};

	void HandleEvents(tGameEngine* pGame);
	void Update(tGameEngine* pGame, const double interpolation);
	void Draw(tGameEngine* pGame);

protected:
	tPlayState();

private:
    bool LoadMedia(tGameEngine* pGame);
    bool LoadFont(tGameEngine* pGame);
    void CreateGameObjects();
	
    static tPlayState* m_pInstance;

    // Game objects
    tPlayer* m_pPlayer;
    std::vector<tEnemy*> m_Enemies;
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
    tTexture* m_pSpriteSheetWeapons;
    // Enemy textures
    tTexture* m_pEnemyTexture;
    tTexture* m_pEnemyExplosionTexture;
    // Text texture :)
    tTexture* m_pTextTexture;
    
    // SDL Font
    TTF_Font* m_pFont;
};

#endif // PLAYSTATE_H