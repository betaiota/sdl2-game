#pragma once

#include "Game.h"

class FontHandler
{
public:
    static SDL_Texture* LoadText(TTF_Font* font_p, const char* text, SDL_Color color_p);
};

