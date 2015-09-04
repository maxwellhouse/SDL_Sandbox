#ifndef PLAYER_H
#define PLAYER_H

#include "actor.h"
#include "weapon.h"
#include <vector>

// Forward declare
class tWeapon;
class tTexture;
struct SDL_Renderer;

class tPlayer : public tActor
{
public:
    tPlayer::tPlayer(unsigned int hp, int x, int y, tTexture* pTexture);
    tPlayer::~tPlayer();

    bool AddBullet(tTexture* pTexture, const tWeapon::eBulletType type);

    bool Hit(const tActor* shotTarget);

    bool render(SDL_Renderer* pRenderer);

private:
    unsigned int m_Hp;
    std::vector<tWeapon*> m_currentWeapons;
};

#endif  // PLAYER_H