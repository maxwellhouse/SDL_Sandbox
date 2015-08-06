#include "bullet.h"
#include "texture.h"
#include "globals.h"

#include <map>

std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect> gBulletColorMap;

#define NORMAL_HEIGHT 8
#define NORMAL_WIDTH 8
#define SUPER_HEIGHT 16
#define SUPER_WIDTH 16

void CreateBulletColorMap()
{
    SDL_Rect yellow_normal_bullet;
    yellow_normal_bullet.x = 11;
    yellow_normal_bullet.y = 341;
    yellow_normal_bullet.w = NORMAL_WIDTH;
    yellow_normal_bullet.h = NORMAL_HEIGHT;
    SDL_Rect yellow_super_bullet;
    yellow_super_bullet.x = 145;
    yellow_super_bullet.y = 297;
    yellow_super_bullet.w = SUPER_WIDTH;
    yellow_super_bullet.h = SUPER_HEIGHT;    

    gBulletColorMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Normal, tBullet::eBC_Yellow), yellow_normal_bullet));
    gBulletColorMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Super, tBullet::eBC_Yellow), yellow_super_bullet));

    SDL_Rect green_normal_bullet;
    green_normal_bullet.x = 29;
    green_normal_bullet.y = 341;
    green_normal_bullet.w = NORMAL_WIDTH;
    green_normal_bullet.h = NORMAL_HEIGHT;
    SDL_Rect green_super_bullet;
    green_super_bullet.x = 189;
    green_super_bullet.y = 297;
    green_super_bullet.w = SUPER_WIDTH;
    green_super_bullet.h = SUPER_HEIGHT;    

    gBulletColorMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Normal, tBullet::eBC_Green), green_normal_bullet));
    gBulletColorMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Super, tBullet::eBC_Green), green_super_bullet));

    SDL_Rect blue_normal_bullet;
    blue_normal_bullet.x = 47;
    blue_normal_bullet.y = 341;
    blue_normal_bullet.w = NORMAL_WIDTH;
    blue_normal_bullet.h = NORMAL_HEIGHT;
    SDL_Rect blue_super_bullet;
    blue_super_bullet.x = 123;
    blue_super_bullet.y = 297;
    blue_super_bullet.w = SUPER_WIDTH;
    blue_super_bullet.h = SUPER_HEIGHT;

    gBulletColorMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Normal, tBullet::eBC_Blue), blue_normal_bullet));
    gBulletColorMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Super, tBullet::eBC_Blue), blue_super_bullet));

    SDL_Rect pink_normal_bullet;
    pink_normal_bullet.x = 65;
    pink_normal_bullet.y = 341;
    pink_normal_bullet.w = NORMAL_WIDTH;
    pink_normal_bullet.h = NORMAL_HEIGHT;
    SDL_Rect pink_super_bullet;
    pink_super_bullet.x = 167;
    pink_super_bullet.y = 297;
    pink_super_bullet.w = SUPER_WIDTH;
    pink_super_bullet.h = SUPER_HEIGHT;    

    gBulletColorMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Normal, tBullet::eBC_Pink), pink_normal_bullet));
    gBulletColorMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Super, tBullet::eBC_Pink), pink_super_bullet));
}



tBullet::tBullet(int x, int y, tTexture* pTexture, eBulletColor color, eBulletType bulletType) :
tActor(x,y),
m_Type(bulletType),
m_Color(color)
{
    // This texture will be kept alive by the main loop.
    m_pTexture = pTexture;

    switch(m_Type)
    {
    case eBT_Normal:
        {
            m_Speed = 5;
            m_HalfWidth = NORMAL_WIDTH / 2;
        }
        break;
    case eBT_Super:
        {
            m_HalfWidth = SUPER_WIDTH / 2;
            m_Speed = 10;
        }
        break;
    default:
        {
            printf( "Bullet type not found!\n");
        }

    }
}

bool tBullet::render()
{
    bool success = m_pTexture->render(m_xPos - m_HalfWidth , m_yPos, &gBulletColorMap.find(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(m_Type,m_Color))->second);
    m_yPos -= m_Speed;

    if(m_yPos < 0)
    {
        success = false;
    }

   return success;
}