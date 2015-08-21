#include "bullet.h"
#include "texture.h"
#include "globals.h"

std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect> tBullet::m_BulletColorMap = CreateBulletColorMap();

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
            m_Width = NORMAL_BULLET_WIDTH;
            m_Height = NORMAL_BULLET_HEIGHT;
            m_HalfWidth = NORMAL_BULLET_WIDTH / 2;
        }
        break;
    case eBT_Super:
        {
            m_Width = SUPER_BULLET_WIDTH;
            m_Height = SUPER_BULLET_HEIGHT;
            m_HalfWidth = SUPER_BULLET_WIDTH / 2;
            m_Speed = 10;
        }
        break;
    case eBT_Enemy:
        {
            m_Width = SUPER_BULLET_WIDTH;
            m_Height = SUPER_BULLET_HEIGHT;
            m_HalfWidth = NORMAL_BULLET_WIDTH / 2;
            // negative speed so that the bullets go down
            m_Speed = -5;
        }
        break;
    default:
        {
            printf( "Bullet type not found!\n");
        }
    }
    m_BulletColorMap = CreateBulletColorMap();
}

bool tBullet::render(SDL_Renderer* pRenderer)
{
    bool success = m_pTexture->render(pRenderer, m_xPos - m_HalfWidth , m_yPos, &m_BulletColorMap.find(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(m_Type,m_Color))->second);
    m_yPos -= m_Speed;

    if(m_yPos < 0 || m_yPos > SCREEN_HEIGHT)
    {
        success = false;
    }

   return success;
}

//-----------------------------------------------------------------------------
//!
//-----------------------------------------------------------------------------
std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect> tBullet::CreateBulletColorMap()
{
    std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect> bulletMap;

    SDL_Rect yellow_normal_bullet;
    yellow_normal_bullet.x = 11;
    yellow_normal_bullet.y = 341;
    yellow_normal_bullet.w = NORMAL_BULLET_WIDTH;
    yellow_normal_bullet.h = NORMAL_BULLET_HEIGHT;
    SDL_Rect yellow_super_bullet;
    yellow_super_bullet.x = 145;
    yellow_super_bullet.y = 297;
    yellow_super_bullet.w = SUPER_BULLET_WIDTH;
    yellow_super_bullet.h = SUPER_BULLET_HEIGHT;    

    bulletMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Normal, tBullet::eBC_Yellow), yellow_normal_bullet));
    bulletMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Super, tBullet::eBC_Yellow), yellow_super_bullet));

    SDL_Rect green_normal_bullet;
    green_normal_bullet.x = 29;
    green_normal_bullet.y = 341;
    green_normal_bullet.w = NORMAL_BULLET_WIDTH;
    green_normal_bullet.h = NORMAL_BULLET_HEIGHT;
    SDL_Rect green_super_bullet;
    green_super_bullet.x = 189;
    green_super_bullet.y = 297;
    green_super_bullet.w = SUPER_BULLET_WIDTH;
    green_super_bullet.h = SUPER_BULLET_HEIGHT;    

    bulletMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Normal, tBullet::eBC_Green), green_normal_bullet));
    bulletMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Super, tBullet::eBC_Green), green_super_bullet));

    SDL_Rect blue_normal_bullet;
    blue_normal_bullet.x = 47;
    blue_normal_bullet.y = 341;
    blue_normal_bullet.w = NORMAL_BULLET_WIDTH;
    blue_normal_bullet.h = NORMAL_BULLET_HEIGHT;
    SDL_Rect blue_super_bullet;
    blue_super_bullet.x = 123;
    blue_super_bullet.y = 297;
    blue_super_bullet.w = SUPER_BULLET_WIDTH;
    blue_super_bullet.h = SUPER_BULLET_HEIGHT;

    bulletMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Normal, tBullet::eBC_Blue), blue_normal_bullet));
    bulletMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Super, tBullet::eBC_Blue), blue_super_bullet));

    SDL_Rect pink_normal_bullet;
    pink_normal_bullet.x = 65;
    pink_normal_bullet.y = 341;
    pink_normal_bullet.w = NORMAL_BULLET_WIDTH;
    pink_normal_bullet.h = NORMAL_BULLET_HEIGHT;
    SDL_Rect pink_super_bullet;
    pink_super_bullet.x = 167;
    pink_super_bullet.y = 297;
    pink_super_bullet.w = SUPER_BULLET_WIDTH;
    pink_super_bullet.h = SUPER_BULLET_HEIGHT;    

    bulletMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Normal, tBullet::eBC_Pink), pink_normal_bullet));
    bulletMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Super, tBullet::eBC_Pink), pink_super_bullet));

    SDL_Rect blue_enemy_bullet;
    blue_enemy_bullet.x = 154;
    blue_enemy_bullet.y = 269;
    blue_enemy_bullet.w = 10;
    blue_enemy_bullet.h = 10;    

    bulletMap.insert(std::map<std::pair<tBullet::eBulletType, tBullet::eBulletColor>, SDL_Rect>::value_type(std::pair<tBullet::eBulletType, tBullet::eBulletColor>(tBullet::eBT_Enemy, tBullet::eBC_Blue), blue_enemy_bullet));

    return bulletMap;
}