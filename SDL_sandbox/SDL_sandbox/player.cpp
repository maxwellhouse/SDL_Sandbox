#include "player.h"
#include "texture.h"
#include "globals.h"

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

tPlayer::tPlayer(unsigned int hp, int x, int y) :
tActor(x,y)
, m_Hp(hp)
{
    //Load player sprite texture
    if( loadTexture("../../../images/ships/player_ship.png") == false )
    {
        printf( "Failed to load player ship texture!\n");
    }

    m_HalfWidth = m_pTexture->getWidth() / 2;
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

bool tPlayer::render()
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

bool tPlayer::move(const int x, const int y)
{
    bool success = false;
    int newPos_x = m_xPos + x;
    int newPos_y = m_yPos + y;
    if ( (newPos_x + m_pTexture->getWidth() < SCREEN_WIDTH && newPos_x >= 0) /*&& y + m_pTexture->getHeight() != SCREEN_HEIGHT*/)
    {
        m_xPos += x;
        m_yPos += y;
        success = true;
    }

    return success;
}