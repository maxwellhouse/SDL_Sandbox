#include "enemy.h"
#include "texture.h"

#define MAX_BULLETS 100


tEnemy::tEnemy(unsigned int hp, int x, int y, tTexture* pTexture, tTexture* pExplosionTexture) :
tActor(x,y, pTexture)
, m_Hp(hp)
, m_pExplosionTexture(pExplosionTexture)
{

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

bool tEnemy::render()
{
    // Render player
    bool success = m_pTexture->render(m_xPos, m_yPos);

    // Render bullets fired
    for(std::vector<tBullet*>::iterator it = m_currentBullets.begin(); it != m_currentBullets.end();)
    {
        if((*it)->render() == false)
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
