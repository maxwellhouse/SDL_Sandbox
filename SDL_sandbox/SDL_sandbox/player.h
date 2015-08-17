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
    tPlayer::tPlayer(unsigned int hp, int x, int y, tTexture* pTexture);
    tPlayer::~tPlayer();

    bool AddBullet(tTexture* pTexture, const tBullet::eBulletType type);

    bool Hit(const tActor* shotTarget);

    bool render();

private:
    unsigned int m_Hp;
    std::vector<tBullet*> m_currentBullets;
};

#endif  // PLAYER_H