#ifndef BULLET_H
#define BULLET_H

#include "actor.h"

void CreateBulletColorMap();

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

    bool render();

private:
    eBulletType m_Type;
    eBulletColor m_Color;
    // So we dont have to divide everytime.
    int m_HalfWidth;
    int m_Speed;

};

#endif  // BULLET_H