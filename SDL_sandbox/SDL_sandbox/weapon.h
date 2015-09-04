#ifndef BULLET_H
#define BULLET_H
#include "stdafx.h"
#include "actor.h"
#include <SDL.h>

class tWeapon : public tActor
{
public:
    enum eBulletType
    {
        eBT_Normal,
        eBT_Super,

        eBT_Enemy,
        eBT_End,
    };

    enum eBulletColor
    {
        eBC_Yellow,
        eBC_Green,
        eBC_Blue,
        eBC_Pink,
    };

public:
    tWeapon::tWeapon(int x, int y, tTexture* pTexture, eBulletColor color, eBulletType type = eBT_Normal);

    bool render(SDL_Renderer* pRenderer);

private:
    // The bullet colors
    static std::map<std::pair<tWeapon::eBulletType, tWeapon::eBulletColor>, SDL_Rect> CreateBulletColorMap();
    static std::map<std::pair<tWeapon::eBulletType, tWeapon::eBulletColor>, SDL_Rect> m_BulletColorMap;

    eBulletType m_Type;
    eBulletColor m_Color;

    unsigned int m_Damage;
    int m_Speed;              // pixels per second
    int m_Count;              // bullets count -1 = unlimited
    int m_Spread;             // angle between bullets
    int m_Spacing;            // space between bullets
    int m_Firerate;           // rounds per second
    int m_Cooldown;           // time between series
    int m_Duration;           // series duration
    int m_Aoe;                // area of effect
    bool m_Homing;            // should it follow nearest enemy
    bool m_Tail;              // should it have some tail - example - smoke for missiles
    //mod: some crazy mods for flying paths - for example using sinus function
};

#endif  // BULLET_H