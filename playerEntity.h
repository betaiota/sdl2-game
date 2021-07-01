#pragma once
#include "GameObject.h"

class playerEntity : public GameObject
{
public:
    playerEntity(const char* texture, int x, int y);
    ~playerEntity();
    void moveUp();
    void moveDown();
    int speed;
};

