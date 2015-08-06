#include "actor.h"
#include "texture.h"

tActor::tActor(int x, int y):
m_xPos(x)
, m_yPos(y)
{
    m_pTexture = new tTexture();
}

tActor::~tActor()
{
    delete m_pTexture;
    m_pTexture = 0;
}

void tActor::move(int x, int y)
{
    m_xPos = x;
    m_yPos = y;
}

void tActor::offsetMove(int x, int y)
{
    m_xPos += x;
    m_yPos += y;
}

bool tActor::render()
{
    return m_pTexture->render(m_xPos, m_yPos);
}

bool tActor::loadTexture(const std::string& fileName)
{
    return m_pTexture->loadFromFile(fileName);
}