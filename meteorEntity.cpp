#include "meteorEntity.h"


meteorEntity::meteorEntity(const char* texturesheet, int x, int y):GameObject(texturesheet)
{
    xpos = x;
    ypos = y;
    srcRect.h = 148;
    srcRect.w = 125;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

meteorEntity::~meteorEntity()
{
    SDL_DestroyTexture(objTexture);
};


bool meteorEntity::Update(playerEntity* ship)
{
    destRect.x = xpos;
    destRect.y = ypos;
    xpos -= speed;
    if(objCollision(ship))
    {
        cout << "Ship coords is: xpos - " << ship->retXpos() << "; ypos - " << ship->retYpos() << endl;
        cout << "Meteor coords is: xpos - " << xpos << "; ypos - " << ypos << endl;
        return true;
    }else return false;
}
