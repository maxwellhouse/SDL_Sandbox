#ifndef BULLET_H
#define BULLET_H
#include "stdafx.h"
#include "actor.h"
#include <SDL.h>

class tBullet : public tActor
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
    tBullet::tBullet(int x, int y, tTexture* pTexture, eBulletColor color, eBulletType type = eBT_Normal);

    bool render(SDL_Renderer* pRenderer);

private:
    // The bullet colors
    static std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect> CreateBulletColorMap();
    static std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect> m_BulletColorMap;

    eBulletType m_Type;
    eBulletColor m_Color;
};

#endif  // BULLET_H