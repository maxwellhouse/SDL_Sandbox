#ifndef ENEMY_H
#define ENEMY_H

#include "stdafx.h"
#include "actor.h"
#include <SDL.h>

// Forward declare
class tWeapon;
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
    void move(const double time);

    SDL_Rect GetDeathClip(const unsigned int clip);
private:
    double m_Time;
    int m_Hp;
    int m_CurrentEnemySpeed;
    bool m_IsExploding;
    int m_DeathFrame;
    std::vector<tWeapon*> m_currentWeapons;
    tTexture* m_pExplosionTexture;

    std::vector<SDL_Rect> m_AnimationSpriteClips;

    tCRSpline* m_pSplinePath;
};

#endif  // ENEMY_H