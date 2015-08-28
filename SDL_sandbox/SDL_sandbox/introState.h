#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "stdafx.h"
#include "GameStateBase.h"

class tGameEngine;
class tTexture;
struct SDL_Renderer;

class tIntroState : public tGameState
{
public:
    // constructor is private - use Instance()
    static void CreateInstance();
	static tIntroState* Instance();

	bool Init(tGameEngine* pGame);
	void Cleanup();

    void Pause() {};
    void Resume() {};

    void HandleEvents(tGameEngine* pGame);
	void Update(tGameEngine* pGame, const double interpolation);
	void Draw(tGameEngine* pGame);

protected:
	tIntroState();

private:
	static tIntroState* m_pInstance;

	tTexture* m_pBackground;
	tTexture* m_pFader;
	int m_Alpha;
};

#endif // INTROSTATE_H