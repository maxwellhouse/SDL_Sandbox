#ifndef GAMESTATE_H
#define GAMESTATE_H

class tGameEngine;

class tGameState
{
public:
  virtual bool Init(tGameEngine* pGame) = 0;
  virtual void Cleanup() = 0;

  virtual void Pause() = 0;
  virtual void Resume() = 0;

  virtual void HandleEvents(tGameEngine* pGame) = 0;
  virtual void Update(tGameEngine* pGame, const double interpolation) = 0;
  virtual void Draw(tGameEngine* pGame) = 0;

  void ChangeState(tGameEngine* pGame, tGameState* pState);

  protected: 
      tGameState() {}
};

#endif // GAMESTATE_H