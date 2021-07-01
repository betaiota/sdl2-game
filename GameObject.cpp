#include "GameObject.h"
#include "TextureLoader.h"

GameObject::GameObject(const char* texturesheet)
{
    objTexture = TextureLoader::LoadTexture(texturesheet);
}

GameObject::~GameObject(){};

void GameObject::Update()
{
    destRect.x = xpos;
    destRect.y = ypos;
}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

bool GameObject::objCollision(GameObject* other)
{
    if((other->xpos + other->srcRect.w/2 >= this->xpos) && (other->xpos/2 <= this->xpos)  && (this->ypos >= other->ypos - other->srcRect.h/2) && (this->ypos <= (other->ypos + other->srcRect.h/2)))
        return true;
    else
        return false;
}

int GameObject::retXpos()
{
    return xpos;
}

int GameObject::retYpos()
{
    return ypos;
}

int GameObject::retHeight()
{
    return srcRect.h;
}

int GameObject::retWidth()
{
    return srcRect.w;
}
