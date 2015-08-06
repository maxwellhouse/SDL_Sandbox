#ifndef PLAYER_H
#define PLAYER_H

#include "actor.h"
#include "bullet.h"
#include <vector>

// Forward declare
class tBullet;
class tTexture;

class tPlayer : public tActor
{
public:
    tPlayer::tPlayer(unsigned int hp, int x, int y);
    tPlayer::~tPlayer();

    bool AddBullet(tTexture* pTexture, const tBullet::eBulletType type);

    bool render();
    bool move(const int x, const int y);

private:
    unsigned int m_Hp;
    // So we dont have to divide everytime.
    int m_HalfWidth;
    std::vector<tBullet*> m_currentBullets;
};

#endif  // PLAYER_H