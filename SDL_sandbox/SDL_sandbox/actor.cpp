#include "actor.h"
#include "texture.h"
#include "globals.h"

tActor::tActor(int x, int y, tTexture* pTexture):
m_xPos(x)
, m_yPos(y)
, m_pTexture(pTexture)
{
    if(m_pTexture)
    {
        m_Width = m_pTexture->getWidth();
        m_Height = m_pTexture->getHeight();
        m_HalfWidth = m_Width / 2;
    }
}

tActor::~tActor()
{

}

bool tActor::move(int x, int y)
{
    bool success = false;
    if ( (x + m_pTexture->getWidth() < SCREEN_WIDTH && x >= 0) && (y + m_pTexture->getHeight() < SCREEN_HEIGHT && y >= 0) )
    {
        m_xPos = x;
        m_yPos = y;
        success = true;
    }
    return success;
}

bool tActor::offsetMove(int x, int y)
{
    bool success = false;
    int newPos_x = m_xPos + x;
    int newPos_y = m_yPos + y;
    if ( (newPos_x + m_pTexture->getWidth() < SCREEN_WIDTH && newPos_x >= 0) && (newPos_y + m_pTexture->getHeight() <= SCREEN_HEIGHT && newPos_y >= 0) )
    {
        m_xPos += x;
        m_yPos += y;
        success = true;
    }

    return success;
}

bool tActor::checkCollison(const tActor* pOther) const
{
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    left1 = m_xPos;
    left2 = pOther->m_xPos;

    right1 = left1 + m_Width - 1;
    right2 = left2 + pOther->m_Width - 1;

    top1 = m_yPos;
    top2 = pOther->m_yPos;

    bottom1 = top1 + m_Height - 1;
    bottom2 = top2 + pOther->m_Height - 1;


    if (bottom1 < top2) return false;
    if (top1 > bottom2) return false;

    if (right1 < left2) return false;
    if (left1 > right2) return false;

    return true;
}

bool tActor::render()
{
    return m_pTexture->render(m_xPos, m_yPos);
}

bool tActor::loadTexture(const std::string& fileName)
{
    bool success =  m_pTexture->loadFromFile(fileName);
    m_Width = m_pTexture->getWidth();
    m_Height = m_pTexture->getHeight();
    m_HalfWidth = m_Width / 2;
    return success;
}
