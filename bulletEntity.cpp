#include "bulletEntity.h"


bulletEntity::bulletEntity(const char* texturesheet, int x, int y):GameObject(texturesheet)
{
    xpos = x;
    ypos = y;
    speed = 10;
    srcRect.h = 58;
    srcRect.w = 100;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

bulletEntity::~bulletEntity()
{
    SDL_DestroyTexture(objTexture);
}

void bulletEntity::Update()
{
    destRect.x = xpos;
    destRect.y = ypos;
    xpos += speed;
}

bool bulletEntity::objCollision(GameObject* other)
{
if((this->xpos + this->srcRect.w/2 - 35 >= other->retXpos())
   && (this->xpos >= other->retXpos() - other->retWidth()/2)
   && (this->ypos >= other->retYpos() - other->retHeight()/5)
   && (this->ypos <= (other->retYpos() + other->retHeight()/2)))
        return true;
    else return false;
}




