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
    for(std::vector<tWeapon*>::iterator it = m_currentWeapons.begin(); it != m_currentWeapons.end(); ++it)
    {
        delete *it;
    }
    m_currentWeapons.clear();
}

bool tPlayer::AddBullet(tTexture* pTexture, const tWeapon::eBulletType type)
{
    bool success = false;
    if(m_currentWeapons.size() < MAX_BULLETS)
    {
        tWeapon* bullet = new tWeapon(m_xPos + m_HalfWidth, m_yPos, pTexture, static_cast<tWeapon::eBulletColor>(roll(0,4)), type);
        m_currentWeapons.push_back(bullet);
        success = true;
    }
    return success;
}

bool tPlayer::Hit(const tActor* shotTarget)
{
    for(std::vector<tWeapon*>::iterator bullet = m_currentWeapons.begin(); bullet != m_currentWeapons.end();)
    {
        if(shotTarget->checkCollison(*bullet))
        {
            bullet = m_currentWeapons.erase(bullet);
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
    for(std::vector<tWeapon*>::iterator it = m_currentWeapons.begin(); it != m_currentWeapons.end();)
    {
        if((*it)->render(pRenderer) == false)
        {
            it = m_currentWeapons.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return success;
}
