#pragma once

#include "Game.h"

class TextureLoader
{
public:
    static SDL_Texture* LoadTexture(const char* fileName);
};
