#include "playerEntity.h"

playerEntity::playerEntity(const char* texturesheet, int x, int y):GameObject(texturesheet)
{
    xpos = x;
    ypos = y;
    speed = 8;
    srcRect.h = 154;
    srcRect.w = 204;
    srcRect.x = 0;
    srcRect.y = 0;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

playerEntity::~playerEntity()
{
    SDL_DestroyTexture(objTexture);
};

void playerEntity::moveUp()
{
    if(ypos > 10)
    {
        ypos -= speed;
        /*cout << "player x-pos: " << xpos << endl;
        cout << "player y-pos: " << ypos << endl;*/
    }

}

void playerEntity::moveDown()
{
    if(ypos < 610)
    {
        ypos += speed;
        /*cout << "player x-pos: " << xpos << endl;
        cout << "player y-pos: " << ypos << endl;*/

    }

}

