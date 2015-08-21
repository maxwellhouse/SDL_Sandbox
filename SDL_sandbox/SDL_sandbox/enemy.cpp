#include "enemy.h"
#include "texture.h"

#define MAX_BULLETS 100


tEnemy::tEnemy(unsigned int hp, int x, int y, tTexture* pTexture, tTexture* pExplosionTexture) :
tActor(x,y, pTexture)
, m_Hp(hp)
, m_pExplosionTexture(pExplosionTexture)
{
    //Set sprite clips
    m_AnimationSpriteClips.resize(ANIMATION_FRAMES);
    m_AnimationSpriteClips[ 0 ].x =   15;
    m_AnimationSpriteClips[ 0 ].y =   16;
    m_AnimationSpriteClips[ 0 ].w =   34;
    m_AnimationSpriteClips[ 0 ].h =   32;

    m_AnimationSpriteClips[ 1 ].x =   76;
    m_AnimationSpriteClips[ 1 ].y =   13;
    m_AnimationSpriteClips[ 1 ].w =   41;
    m_AnimationSpriteClips[ 1 ].h =   38;

    m_AnimationSpriteClips[ 2 ].x =   137;
    m_AnimationSpriteClips[ 2 ].y =   10;
    m_AnimationSpriteClips[ 2 ].w =   47;
    m_AnimationSpriteClips[ 2 ].h =   44;

    m_AnimationSpriteClips[ 3 ].x =   199;
    m_AnimationSpriteClips[ 3 ].y =   9;
    m_AnimationSpriteClips[ 3 ].w =   51;
    m_AnimationSpriteClips[ 3 ].h =   47;

    m_AnimationSpriteClips[ 4 ].x =   262;
    m_AnimationSpriteClips[ 4 ].y =   7;
    m_AnimationSpriteClips[ 4 ].w =   54;
    m_AnimationSpriteClips[ 4 ].h =   51;

    m_AnimationSpriteClips[ 5 ].x =   4;
    m_AnimationSpriteClips[ 5 ].y =   70;
    m_AnimationSpriteClips[ 5 ].w =   58;
    m_AnimationSpriteClips[ 5 ].h =   53;

    m_AnimationSpriteClips[ 6 ].x =   68;
    m_AnimationSpriteClips[ 6 ].y =   69;
    m_AnimationSpriteClips[ 6 ].w =   59;
    m_AnimationSpriteClips[ 6 ].h =   55;

    m_AnimationSpriteClips[ 7 ].x =   131;
    m_AnimationSpriteClips[ 7 ].y =   69;
    m_AnimationSpriteClips[ 7 ].w =   60;
    m_AnimationSpriteClips[ 7 ].h =   55;

    m_AnimationSpriteClips[ 8 ].x =   194;
    m_AnimationSpriteClips[ 8 ].y =   68;
    m_AnimationSpriteClips[ 8 ].w =   61;
    m_AnimationSpriteClips[ 8 ].h =   57;

    m_AnimationSpriteClips[ 9 ].x =   258;
    m_AnimationSpriteClips[ 9 ].y =   68;
    m_AnimationSpriteClips[ 9 ].w =   61;
    m_AnimationSpriteClips[ 9 ].h =   57;

    m_AnimationSpriteClips[ 10 ].x =  2;
    m_AnimationSpriteClips[ 10 ].y =  133;
    m_AnimationSpriteClips[ 10 ].w =  61;
    m_AnimationSpriteClips[ 10 ].h =  56;

    m_AnimationSpriteClips[ 11 ].x =  66;
    m_AnimationSpriteClips[ 11 ].y =  132;
    m_AnimationSpriteClips[ 11 ].w =  61;
    m_AnimationSpriteClips[ 11 ].h =  57;

    m_AnimationSpriteClips[ 12 ].x =  130;
    m_AnimationSpriteClips[ 12 ].y =  132;
    m_AnimationSpriteClips[ 12 ].w =  61;
    m_AnimationSpriteClips[ 12 ].h =  57;

    m_AnimationSpriteClips[ 13 ].x =  194;
    m_AnimationSpriteClips[ 13 ].y =  132;
    m_AnimationSpriteClips[ 13 ].w =  61;
    m_AnimationSpriteClips[ 13 ].h =  57;

    m_AnimationSpriteClips[ 14 ].x =  258;
    m_AnimationSpriteClips[ 14 ].y =  132;
    m_AnimationSpriteClips[ 14 ].w =  61;
    m_AnimationSpriteClips[ 14 ].h =  57;

    m_AnimationSpriteClips[ 15 ].x =  2;
    m_AnimationSpriteClips[ 15 ].y =  196;
    m_AnimationSpriteClips[ 15 ].w =  61;
    m_AnimationSpriteClips[ 15 ].h =  57;

    m_AnimationSpriteClips[ 16 ].x =  66;
    m_AnimationSpriteClips[ 16 ].y =  196;
    m_AnimationSpriteClips[ 16 ].w =  61;
    m_AnimationSpriteClips[ 16 ].h =  57;

    m_AnimationSpriteClips[ 17 ].x =  132;
    m_AnimationSpriteClips[ 17 ].y =  196;
    m_AnimationSpriteClips[ 17 ].w =  58;
    m_AnimationSpriteClips[ 17 ].h =  57;

    m_AnimationSpriteClips[ 18 ].x =  198;
    m_AnimationSpriteClips[ 18 ].y =  197;
    m_AnimationSpriteClips[ 18 ].w =  56;
    m_AnimationSpriteClips[ 18 ].h =  56;

    m_AnimationSpriteClips[ 19 ].x =  262;
    m_AnimationSpriteClips[ 19 ].y =  197;
    m_AnimationSpriteClips[ 19 ].w =  55;
    m_AnimationSpriteClips[ 19 ].h =  56;

    m_AnimationSpriteClips[ 20 ].x =  9;
    m_AnimationSpriteClips[ 20 ].y =  264;
    m_AnimationSpriteClips[ 20 ].w =  47;
    m_AnimationSpriteClips[ 20 ].h =  52;

    m_AnimationSpriteClips[ 21 ].x =  77;
    m_AnimationSpriteClips[ 21 ].y =  267;
    m_AnimationSpriteClips[ 21 ].w =  39;
    m_AnimationSpriteClips[ 21 ].h =  44;

    m_AnimationSpriteClips[ 22 ].x =  148;
    m_AnimationSpriteClips[ 22 ].y =  275;
    m_AnimationSpriteClips[ 22 ].w =  23;
    m_AnimationSpriteClips[ 22 ].h =  32;
}

tEnemy::~tEnemy()
{
    for(std::vector<tBullet*>::iterator it = m_currentBullets.begin(); it != m_currentBullets.end(); ++it)
    {
        delete *it;
    }
    m_currentBullets.clear();
}

bool tEnemy::AddBullet(tTexture* pTexture)
{
    bool success = false;
    if(m_currentBullets.size() < MAX_BULLETS)
    {
        tBullet* bullet = new tBullet(m_xPos + m_HalfWidth, m_yPos, pTexture, tBullet::eBC_Blue, tBullet::eBT_Enemy);
        m_currentBullets.push_back(bullet);
        success = true;
    }
    return success;
}

bool tEnemy::Hit(const tActor* shotTarget)
{
    for(std::vector<tBullet*>::iterator bullet = m_currentBullets.begin(); bullet != m_currentBullets.end(); bullet++)
    {
        if(shotTarget->checkCollison(*bullet))
        {
            return true;
        }
    }
    return false;
}

bool tEnemy::render(SDL_Renderer* pRenderer)
{
    // Render player
    bool success = m_pTexture->render(pRenderer, m_xPos, m_yPos);

    // Render bullets fired
    for(std::vector<tBullet*>::iterator it = m_currentBullets.begin(); it != m_currentBullets.end();)
    {
        if((*it)->render(pRenderer) == false)
        {
            it = m_currentBullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return success;
}

SDL_Rect tEnemy::GetDeathClip(const unsigned int clip)
{
    if(clip < m_AnimationSpriteClips.size())
    {
        return m_AnimationSpriteClips[clip];
    }
    return SDL_Rect();
}

void tEnemy::wasHit(const unsigned int damage)
{
    m_Hp -= damage;
    if(m_Hp < 0)
    {
        m_Hp = 0;
        m_currentBullets.clear();
    }
}

bool tEnemy::isDead() const
{
    return m_Hp <= 0;
}
