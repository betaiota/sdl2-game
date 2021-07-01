#pragma once

#include "GameObject.h"
#include "TextureLoader.h"


class bulletEntity : public GameObject
{
public:
    bulletEntity(const char* texture, int x, int y);
    ~bulletEntity();
    void Update();
    bool objCollision(GameObject* other);
protected:
    int speed;
};
