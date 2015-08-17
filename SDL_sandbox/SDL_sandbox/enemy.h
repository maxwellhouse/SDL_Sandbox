#ifndef ENEMY_H
#define ENEMY_H

#include "actor.h"
#include "bullet.h"
#include <vector>

// Forward declare
class tBullet;
class tTexture;

class tEnemy : public tActor
{
public:
    tEnemy::tEnemy(unsigned int hp, int x, int y, tTexture* pTexture, tTexture* pExplosionTexture);
    tEnemy::~tEnemy();

    bool AddBullet(tTexture* pTexture);

    bool Hit(const tActor* shotTarget);

    bool render();

private:
    unsigned int m_Hp;
    // So we dont have to divide everytime.
    int m_HalfWidth;
    std::vector<tBullet*> m_currentBullets;
    tTexture* m_pExplosionTexture;
};

#endif  // ENEMY_H