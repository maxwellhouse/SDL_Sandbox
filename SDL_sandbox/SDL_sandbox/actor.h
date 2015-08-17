#ifndef ACTOR_H
#define ACTOR_H
#include <string>

class tTexture;

class tActor
{
public:
    tActor(int x, int y, tTexture* pTexture = 0);
    ~tActor();

public:
    bool loadTexture(const std::string& fileName);
    bool render();
    bool move(int x, int y);
    bool offsetMove(int x, int y);
    bool checkCollison(const tActor* pOther) const;

protected:
    tTexture* m_pTexture;
    int m_xPos;
    int m_yPos;

    // So we dont have to divide everytime.
    int m_HalfWidth;
    int m_Height;
    int m_Width;
    int m_Speed;
};

#endif  // GLOBALS_H