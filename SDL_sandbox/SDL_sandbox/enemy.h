#ifndef ENEMY_H
#define ENEMY_H

#include "stdafx.h"
#include "actor.h"
#include <SDL.h>

// Forward declare
class tBullet;
class tTexture;
class tCRSpline;
// Animation sprite
const int ANIMATION_FRAMES = 23;

class tEnemy : public tActor
{
public:
    tEnemy::tEnemy(unsigned int hp, int x, int y, tTexture* pTexture, tTexture* pExplosionTexture);
    tEnemy::~tEnemy();

    bool AddBullet(tTexture* pTexture);
    bool Hit(const tActor* shotTarget);
    bool isDead() const;
    void wasHit(const unsigned int damage);
    bool render(SDL_Renderer* pRenderer);

    SDL_Rect GetDeathClip(const unsigned int clip);
private:
    int m_Hp;
    std::vector<tBullet*> m_currentBullets;
    tTexture* m_pExplosionTexture;

    std::vector<SDL_Rect> m_AnimationSpriteClips;

    tCRSpline* m_pSplinePath;
};

#endif  // ENEMY_H