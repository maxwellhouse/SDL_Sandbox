#include "GameStateBase.h"
#include "gameEngine.h"

void ChangeState(tGameEngine* pGame, tGameState* pState) 
{
    pGame->ChangeState(pState);
}