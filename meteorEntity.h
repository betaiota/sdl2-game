#pragma once

#include "GameObject.h"
#include "playerEntity.h"

class meteorEntity : public GameObject
{
public:
    meteorEntity(const char* texture, int x, int y);
    ~meteorEntity();
    meteorEntity* spawnMeteor();
    bool Update(playerEntity* ship);
private:
    int speed = rand() % 8 + 6;
};
