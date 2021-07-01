#pragma once
#include "Game.h"

class GameObject
{
public:
    GameObject(const char* texturesheet);
    virtual ~GameObject();
    virtual void Update();
    void Render();
    virtual bool objCollision(GameObject* other);
    int retXpos();
    int retYpos();
    int retHeight();
    int retWidth();
protected:
    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};
