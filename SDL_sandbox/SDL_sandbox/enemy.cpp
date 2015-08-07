#include "enemy.h"
#include "texture.h"

#define MAX_BULLETS 100


tEnemy::tEnemy(unsigned int hp, int x, int y) :
tActor(x,y)
, m_Hp(hp)
{
    //Load player sprite texture
    if( loadTexture("../../images/ships/enemy_1.png") == false )
    {
        printf( "Failed to load enemy ship texture!\n");
    }

    m_HalfWidth = m_pTexture->getWidth() / 2;
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
