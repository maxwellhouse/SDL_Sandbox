#include "player.h"
#include "texture.h"

#define MAX_BULLETS 100

// Get random number between min and max
int roll(int min, int max)
{
    // x is in [0,1[
    double x = rand()/static_cast<double>(RAND_MAX+1); 

    // [0,1[ * (max - min) + min is in [min,max[
    int that = min + static_cast<int>( x * (max - min) );

    return that;
}

tPlayer::tPlayer(unsigned int hp, int x, int y, tTexture* pTexture) :
tActor(x,y, pTexture)
, m_Hp(hp)
{
}

tPlayer::~tPlayer()
{
    for(std::vector<tBullet*>::iterator it = m_currentBullets.begin(); it != m_currentBullets.end(); ++it)
    {
        delete *it;
    }
    m_currentBullets.clear();
}

bool tPlayer::AddBullet(tTexture* pTexture, const tBullet::eBulletType type)
{
    bool success = false;
    if(m_currentBullets.size() < MAX_BULLETS)
    {
        tBullet* bullet = new tBullet(m_xPos + m_HalfWidth, m_yPos, pTexture, static_cast<tBullet::eBulletColor>(roll(0,4)), type);
        m_currentBullets.push_back(bullet);
        success = true;
    }
    return success;
}

bool tPlayer::Hit(const tActor* shotTarget)
{
    for(std::vector<tBullet*>::iterator bullet = m_currentBullets.begin(); bullet != m_currentBullets.end();)
    {
        if(shotTarget->checkCollison(*bullet))
        {
            bullet = m_currentBullets.erase(bullet);
            return true;
        }
        else
        {
            ++bullet;
        }
    }
    return false;
}

bool tPlayer::render(SDL_Renderer* pRenderer)
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
