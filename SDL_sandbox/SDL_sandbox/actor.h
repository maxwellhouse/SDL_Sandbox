#ifndef ACTOR_H
#define ACTOR_H
#include <string>

class tTexture;

class tActor
{
public:
    tActor(int x, int y);
    ~tActor();

public:
    bool loadTexture(const std::string& fileName);
    bool render();
    void move(int x, int y);
    void offsetMove(int x, int y);

protected:
    tTexture* m_pTexture;
    int m_xPos;
    int m_yPos;
};

#endif  // GLOBALS_H